/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18LF27K40
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

/*
 * Arizona State University
 * Spring 2023
 * EGR 314
 * Professor: Daniel Aukes
 * Team 207
 * Radge Chaira
 * Stefano Greco
 * Hector Peralta
 * Daymon Wilkins
 */

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"


/*
                         Main application
 */
// Definitions 
#define TC74_ADDRESS 0x4c // TC74A4-3.3VCT ADDRESS IS 0b1001100
#define TEMPERATURE_READ 0x00 //RTR Read TEMP Register 
#define AS5600_ADDRESS 0x36 //AS5600 ADDRESS IS 0b0110110
#define AS_ANGLE1 0x0F //AS5600 ANLGE 11:8 Bits Register
#define AS_ANGLE2 0x0E //AS5600 ANGLE 7:0 Bits Register
#define ANGLE_CHECK 0x800
#define BUFFER_SIZE 256 
#define MOTOR_RUN_TIME_MS 5000

//Global Variables
uint8_t bur[2];
uint16_t magnet;
float A = 11.375;
float degree = 0;
uint8_t motorDirection = 0; // 0 - Forward, 1 - Backward
bool timerOverflowFlag = false;
uint32_t motorStartTime = 0;
uint16_t timer_ms = 0;
uint16_t timer_s = 0;
float time = 0.0;
uint8_t ESP32RxBuffer[BUFFER_SIZE];
uint8_t ESP32TxBuffer[BUFFER_SIZE];
uint8_t rxByte;
uint8_t rxIndex = 0;
bool ESPrxComplete = false;
uint8_t endingIndex = 0;
uint8_t startingIndex = 0;
uint8_t lengthMessage = 0;
uint8_t messageTest[4];

//Function Declarations
void motorControl(uint8_t enable);
void timer0InterruptHandler(void);
void UART1ISR(void); // Connected to Debug UART Header RX RC7 and TX RC5
void UART2ISR(void); // Connected to ESP32 Via RX RC0 and TX RC1
void UART2WriteMessage(uint8_t *message, uint8_t startIndex, uint8_t length); // Write multiple bytes of data to form a full message
int8_t readTemperature(void); // Must be run after i2c is initialized


void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    EUSART1_Initialize();
    I2C1_Initialize();
    PIN_MANAGER_Initialize();

    // Custom Interrupt Handler Declarations
    EUSART1_SetRxInterruptHandler(* UART1ISR);
    EUSART2_SetRxInterruptHandler(* UART2ISR);
    TMR0_SetInterruptHandler(* timer0InterruptHandler);
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    SPI2_Open(SPI2_DEFAULT); //SPI activation
    TMR0_StartTimer();
    
    SSP2CON1bits.CKP = 0; // Clock Polarity (CPOL)
    SSP2STATbits.CKE = 0; // Clock Edge (CPHA)
    
    uint8_t temp;
    uint16_t angle;
    bool motorRunning = false;    
    bool thresholdCrossed = false;
    
    while (1)
    {
        if (EUSART1_is_tx_ready()){
            temp = I2C1_Read1ByteRegister(TC74_ADDRESS, TEMPERATURE_READ);
            __delay_ms(200);

            uint8_t data1 = 0x00;
            uint8_t data2 = 0x00;
            uint16_t angle = 0x00;

            // Read the angle from the AS5600 sensor
            data1 = I2C1_Read1ByteRegister(0x36, AS_ANGLE1);
            data2 = I2C1_Read1ByteRegister(0x36, AS_ANGLE2);

            angle = data1 << 8;
            angle += data2;
            
            
            /*if(temp >= 27 || magnet > ANGLE_CHECK){
                DEBUG_LED_SetHigh(); //Turn on Debug LED
                motorControl(1); //Enable Motor
            } else{
                DEBUG_LED_SetLow(); // Turn off Debug LED
                motorControl(0); // Disable motor
            }*/
             if ((temp >= 27 || angle > ANGLE_CHECK) && !motorRunning && !thresholdCrossed) {
                motorControl(1); // Enable motor
                motorRunning = true;
                motorStartTime = TMR0_ReadTimer();
                thresholdCrossed = true;
            } else if (!thresholdCrossed) {
                motorDirection = !motorDirection; // Toggle motor direction
                motorControl(1); // Enable motor
                motorRunning = true;
                motorStartTime = TMR0_ReadTimer();
                thresholdCrossed = true;
                }
             if (motorRunning && (TMR0_ReadTimer() - motorStartTime) >= MOTOR_RUN_TIME_MS) {
                motorControl(0); // Disable motor
                motorRunning = false;
                motorDirection = !motorDirection; // Toggle motor direction
                }
        }
        __delay_ms(50);
        if(ESPrxComplete){
            //UART2WriteMessage(*ESP32RxBuffer, startingIndex, lengthMessage);
            ESPrxComplete = false;
        }
        messageTest[0] = 0;
        messageTest[1] = 1;
        messageTest[2] = 2;
        messageTest[3] = ';';
        
        //UART2WriteMessage(*messageTest, 0, 3);
    }
    SPI2_Close();
}

void motorControl(uint8_t enable) {
    uint8_t command;

    if (enable) {
        command = motorDirection ? 0b11001011 : 0b11001111; // Enable motor with direction control
    } else {
        command = 0b11000000; // Disable motor
    }

    SPI2_SS_SetLow(); // Set SS (RB1) low to start communication
    __delay_us(50);
    SPI2_WriteByte(command); // Send the command 
    __delay_us(50); // Add a small delay between sending commands
    SPI2_SS_SetHigh(); // Set SS (RB1) high to end communication
    __delay_us(50);  // Add a small delay between sending commands
}

void timer0InterruptHandler(void) {
    //motorControl(0); // Disable motor
    //motorDirection = !motorDirection; // Toggle motor direction
    //TMR0_Reload(); // Reset the timer
    //timerOverflowFlag = true;
    timer_ms += 1;
    if(timer_ms >= 1000){
        timer_ms -= 1000;
        timer_s += 1;
    }
}

void UART1ISR(void){
    EUSART1_Receive_ISR();
    
}

void UART2ISR(void){
    EUSART2_Receive_ISR();
    if(EUSART2_is_rx_ready()){
        rxByte = EUSART2_Read();
    }
    ESP32RxBuffer[rxIndex] = rxByte;
    if(rxByte == ';'){
        ESPrxComplete = true;
        endingIndex = rxIndex;
        lengthMessage = endingIndex - startingIndex;
    }
    if(rxByte == '_'){
        startingIndex = rxIndex;
    }
    if(rxIndex >= 255){
        rxIndex = 0;
    }
    else{
        rxIndex++;
    }
    DEBUG_LED_Toggle();
    
}

void UART2WriteMessage(uint8_t *message, uint8_t startIndex, uint8_t length){
    uint8_t i;
    for(i = 0; i < length; i++){
        EUSART2_Write(message[startIndex+i]);
    }
}

int8_t readTemperature(void){
    int8_t temperature = 0;
    temperature = I2C1_Read1ByteRegister(TC74_ADDRESS,TEMPERATURE_READ);
    return temperature;
}
/**
 End of File
*/
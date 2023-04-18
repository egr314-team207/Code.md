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

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"


/*
                         Main application
 */
// Definitions 
#define address 0x4C
#define tempreg 0x00
#define AS_ANGLE1 0x0F
#define AS_ANGLE2 0x0E
#define ANGLE_CHECK 0x800

//Global Variables
uint8_t bur[2];
uint16_t magnet;
float A = 11.375;
float degree = 0;
uint8_t motorDirection = 0; // 0 - Forward, 1 - Backward

//Function Declarations
void motorControl(uint8_t enable);
void timer0InterruptHandler(void);

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    EUSART1_Initialize();
    I2C1_Initialize();
    PIN_MANAGER_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    SPI2_Open(SPI2_DEFAULT); //SPI activation
    TMR0_SetInterruptHandler(timer0InterruptHandler);
    TMR0_StartTimer();
    
    SSP2CON1bits.CKP = 0; // Clock Polarity (CPOL)
    SSP2STATbits.CKE = 0; // Clock Edge (CPHA)
    
    uint8_t temp;
    bool motorRunning = false;
    
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

    while (1)
    {
        if (EUSART1_is_tx_ready()){
            temp = I2C1_Read1ByteRegister(address, tempreg);
            __delay_ms(200);

            uint8_t data1 = 0x00;
            uint8_t data2 = 0x00;
            uint16_t angle = 0x00;

            // Read the angle from the AS5600 sensor
            data1 = I2C1_Read1ByteRegister(0x36, AS_ANGLE1);
            data2 = I2C1_Read1ByteRegister(0x36, AS_ANGLE2);

            angle = data1 << 8;
            angle += data2;

            if(temp >= 27 || magnet > ANGLE_CHECK){
                DEBUG_LED_SetHigh(); //Turn on Debug LED
                motorControl(1); //Enable Motor
            } else{
                DEBUG_LED_SetLow(); // Turn off Debug LED
                motorControl(0); // Disable motor
            }
        }
        __delay_ms(50);
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
    motorControl(0); // Disable motor
    motorDirection = !motorDirection; // Toggle motor direction
   // TMR0_Reload(); // Reset the timer
}

/**
 End of File
*/
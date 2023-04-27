/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18LF27K40
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set DIS aliases
#define DIS_TRIS                 TRISAbits.TRISA1
#define DIS_LAT                  LATAbits.LATA1
#define DIS_PORT                 PORTAbits.RA1
#define DIS_WPU                  WPUAbits.WPUA1
#define DIS_OD                   ODCONAbits.ODCA1
#define DIS_ANS                  ANSELAbits.ANSELA1
#define DIS_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define DIS_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define DIS_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define DIS_GetValue()           PORTAbits.RA1
#define DIS_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define DIS_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define DIS_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define DIS_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define DIS_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define DIS_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define DIS_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define DIS_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set DIR aliases
#define DIR_TRIS                 TRISAbits.TRISA3
#define DIR_LAT                  LATAbits.LATA3
#define DIR_PORT                 PORTAbits.RA3
#define DIR_WPU                  WPUAbits.WPUA3
#define DIR_OD                   ODCONAbits.ODCA3
#define DIR_ANS                  ANSELAbits.ANSELA3
#define DIR_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define DIR_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define DIR_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define DIR_GetValue()           PORTAbits.RA3
#define DIR_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define DIR_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define DIR_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define DIR_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define DIR_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define DIR_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define DIR_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define DIR_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set DEBUG_LED aliases
#define DEBUG_LED_TRIS                 TRISAbits.TRISA6
#define DEBUG_LED_LAT                  LATAbits.LATA6
#define DEBUG_LED_PORT                 PORTAbits.RA6
#define DEBUG_LED_WPU                  WPUAbits.WPUA6
#define DEBUG_LED_OD                   ODCONAbits.ODCA6
#define DEBUG_LED_ANS                  ANSELAbits.ANSELA6
#define DEBUG_LED_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define DEBUG_LED_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define DEBUG_LED_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define DEBUG_LED_GetValue()           PORTAbits.RA6
#define DEBUG_LED_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define DEBUG_LED_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define DEBUG_LED_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define DEBUG_LED_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define DEBUG_LED_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define DEBUG_LED_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define DEBUG_LED_SetAnalogMode()      do { ANSELAbits.ANSELA6 = 1; } while(0)
#define DEBUG_LED_SetDigitalMode()     do { ANSELAbits.ANSELA6 = 0; } while(0)

// get/set TOGGLE_BUTTON aliases
#define TOGGLE_BUTTON_TRIS                 TRISAbits.TRISA7
#define TOGGLE_BUTTON_LAT                  LATAbits.LATA7
#define TOGGLE_BUTTON_PORT                 PORTAbits.RA7
#define TOGGLE_BUTTON_WPU                  WPUAbits.WPUA7
#define TOGGLE_BUTTON_OD                   ODCONAbits.ODCA7
#define TOGGLE_BUTTON_ANS                  ANSELAbits.ANSELA7
#define TOGGLE_BUTTON_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define TOGGLE_BUTTON_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define TOGGLE_BUTTON_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define TOGGLE_BUTTON_GetValue()           PORTAbits.RA7
#define TOGGLE_BUTTON_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define TOGGLE_BUTTON_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define TOGGLE_BUTTON_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define TOGGLE_BUTTON_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define TOGGLE_BUTTON_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define TOGGLE_BUTTON_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define TOGGLE_BUTTON_SetAnalogMode()      do { ANSELAbits.ANSELA7 = 1; } while(0)
#define TOGGLE_BUTTON_SetDigitalMode()     do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set RB1 procedures
#define RB1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define RB1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define RB1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define RB1_GetValue()              PORTBbits.RB1
#define RB1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define RB1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define RB1_SetPullup()             do { WPUBbits.WPUB1 = 1; } while(0)
#define RB1_ResetPullup()           do { WPUBbits.WPUB1 = 0; } while(0)
#define RB1_SetAnalogMode()         do { ANSELBbits.ANSELB1 = 1; } while(0)
#define RB1_SetDigitalMode()        do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set RB2 procedures
#define RB2_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define RB2_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define RB2_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define RB2_GetValue()              PORTBbits.RB2
#define RB2_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define RB2_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define RB2_SetPullup()             do { WPUBbits.WPUB2 = 1; } while(0)
#define RB2_ResetPullup()           do { WPUBbits.WPUB2 = 0; } while(0)
#define RB2_SetAnalogMode()         do { ANSELBbits.ANSELB2 = 1; } while(0)
#define RB2_SetDigitalMode()        do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set RB3 procedures
#define RB3_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define RB3_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define RB3_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define RB3_GetValue()              PORTBbits.RB3
#define RB3_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define RB3_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define RB3_SetPullup()             do { WPUBbits.WPUB3 = 1; } while(0)
#define RB3_ResetPullup()           do { WPUBbits.WPUB3 = 0; } while(0)
#define RB3_SetAnalogMode()         do { ANSELBbits.ANSELB3 = 1; } while(0)
#define RB3_SetDigitalMode()        do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set SPI2_SS aliases
#define SPI2_SS_TRIS                 TRISBbits.TRISB4
#define SPI2_SS_LAT                  LATBbits.LATB4
#define SPI2_SS_PORT                 PORTBbits.RB4
#define SPI2_SS_WPU                  WPUBbits.WPUB4
#define SPI2_SS_OD                   ODCONBbits.ODCB4
#define SPI2_SS_ANS                  ANSELBbits.ANSELB4
#define SPI2_SS_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define SPI2_SS_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define SPI2_SS_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define SPI2_SS_GetValue()           PORTBbits.RB4
#define SPI2_SS_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define SPI2_SS_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define SPI2_SS_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define SPI2_SS_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define SPI2_SS_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define SPI2_SS_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define SPI2_SS_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define SPI2_SS_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set RC0 procedures
#define RC0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define RC0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define RC0_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define RC0_GetValue()              PORTCbits.RC0
#define RC0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define RC0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define RC0_SetPullup()             do { WPUCbits.WPUC0 = 1; } while(0)
#define RC0_ResetPullup()           do { WPUCbits.WPUC0 = 0; } while(0)
#define RC0_SetAnalogMode()         do { ANSELCbits.ANSELC0 = 1; } while(0)
#define RC0_SetDigitalMode()        do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set RC1 procedures
#define RC1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define RC1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define RC1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define RC1_GetValue()              PORTCbits.RC1
#define RC1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define RC1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define RC1_SetPullup()             do { WPUCbits.WPUC1 = 1; } while(0)
#define RC1_ResetPullup()           do { WPUCbits.WPUC1 = 0; } while(0)
#define RC1_SetAnalogMode()         do { ANSELCbits.ANSELC1 = 1; } while(0)
#define RC1_SetDigitalMode()        do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSELC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSELC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSELC4 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCAF7 pin functionality
 * @Example
    IOCAF7_ISR();
 */
void IOCAF7_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCAF7 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCAF7 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF7_SetInterruptHandler(MyInterruptHandler);

*/
void IOCAF7_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCAF7 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCAF7_SetInterruptHandler() method.
    This handler is called every time the IOCAF7 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF7_SetInterruptHandler(IOCAF7_InterruptHandler);

*/
extern void (*IOCAF7_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCAF7 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCAF7_SetInterruptHandler() method.
    This handler is called every time the IOCAF7 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF7_SetInterruptHandler(IOCAF7_DefaultInterruptHandler);

*/
void IOCAF7_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/
/**
 * SPI2 Generated Driver API Header File
 *
 * @file mssp2.h
 *
 * @defgroup spi2 SPI2
 *
 * @brief This header file provides APIs for the SPI2 driver.
 *
 * @version SPI2 Driver Version 2.0.2
*/

/*
© [2023] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef SPI2_H
#define SPI2_H

/**
 * Section: Included Files
 */ 

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "spi_interface.h"

/**
 * @ingroup spi2
 * @struct SPI_INTERFACE SPI2
 * @brief SPI driver interface object.
 */                
extern const struct SPI_INTERFACE SPI2;

/**
 * @ingroup spi2
 * @typedef enum spi2_modes_t
 * @brief Enumeration of the different configurations supported by the driver.A configuration is specified as parameter to SPI2_Open()
 *        and is used by the function to set SPI parameters as specified by the configuration.
 */
typedef enum { 
    MSSP2_DEFAULT
} spi2_modes_t;

/**
 * @ingroup spi2
 * @brief Initialize SPI interface.
 * @param none
 * @return none
 */
void SPI2_Initialize(void);

/**
 * @ingroup spi2
 * @brief Sets the index of Configuration to use in the transfer.
 * @param uint8_t spiConfigIndex - The configuration index
 * @retval true  - SPI status was open.
 * @retval false - SPI status was not open.
 */
bool SPI2_Open(uint8_t spiConfigIndex);

/**
 * @ingroup spi2
 * @brief Close the SPI for communication.
 * @param none
 * @return none
 */
void SPI2_Close(void);

/**
 * @ingroup spi2
 * @brief Exchange one byte over SPI. Blocks until done.
 * @param uint8_t byteData - The byte to transfer
 * @return uint8_t - Received data byte.
 */
uint8_t SPI2_ByteExchange(uint8_t byteData);

/**
 * @ingroup spi2
 * @brief Exchange a buffer over SPI. Blocks if using polled driver.
 * @param[inout] void * bufferData The buffer to transfer. Received data is returned here
 * @param[in] size_t bufferSize The size of buffer to transfer
 * @return none
 */
void SPI2_BufferExchange(void * bufferData, size_t bufferSize);

/**
 * @ingroup spi2
 * @brief Write a buffer over SPI. Blocks if using polled driver.
 * @param[in] void * bufferData The buffer to transfer
 * @param[in] size_t bufferSize The size of buffer to transfer
 * @return none
 */
void SPI2_BufferWrite(void * bufferData, size_t bufferSize);

/**
 * @ingroup spi2
 * @brief Read a buffer over SPI. Blocks if using polled driver.
 * @param[out] void * bufferData Received data is written here.
 * @param[in] size_t bufferSize The size of buffer to transfer
 * @return none
 */
void SPI2_BufferRead(void * bufferData, size_t bufferSize);

/**
 * @ingroup spi2
 * @brief Write data byte to SPI.
 * @param uint8_t byteData The byte to transfer.
 * @return none
 */
void SPI2_ByteWrite(uint8_t byteData);

/**
 * @ingroup spi2
 * @brief Get received data byte from SPI.
 * @param none
 * @return uint8_t - The received data
 */
uint8_t SPI2_ByteRead(void);

uint8_t __attribute__((deprecated)) SPI2_ExchangeByte(uint8_t data);
void __attribute__((deprecated)) SPI2_ExchangeBlock(void *block, size_t blockSize);
void __attribute__((deprecated)) SPI2_WriteBlock(void *block, size_t blockSize);
void __attribute__((deprecated)) SPI2_ReadBlock(void *block, size_t blockSize);
void __attribute__((deprecated)) SPI2_WriteByte(uint8_t byte);
uint8_t __attribute__((deprecated)) SPI2_ReadByte(void);

#endif //SPI2_H
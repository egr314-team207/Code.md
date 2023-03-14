/**
  * SPI2 Generated Driver File
  *
  * @file spi2.c
  *
  * @ingroup spi2
  *
  * @brief This file contains the driver code for SPI2 module.
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

#include <xc.h>
#include "../mssp2.h"

const struct SPI_INTERFACE SPI2 = {
    .Initialize = SPI2_Initialize,
    .Close = SPI2_Close,
    .Open = SPI2_Open,
    .BufferExchange = SPI2_BufferExchange,
    .BufferRead = SPI2_BufferRead,
    .BufferWrite = SPI2_BufferWrite,	
    .ByteExchange = SPI2_ByteExchange,
    .ByteRead = SPI2_ByteRead,	
    .ByteWrite = SPI2_ByteWrite,
};

typedef struct { 
    uint8_t con1; 
    uint8_t stat;
    uint8_t add;
    uint8_t operation;
} spi2_configuration_t;

//con1 == SSPxCON1, stat == SSPxSTAT, add == SSPxADD, operation == Host/Client
static const spi2_configuration_t spi2_configuration[] = {   
    { 0x0, 0x64, 0x1, 0 }
};

void SPI2_Initialize(void)
{
    //SPI setup
    SSP2STAT = 0x64;
    SSP2CON1 = 0x0;
    SSP2ADD = 0x1;
    SSP2CON1bits.SSPEN = 0;
}

bool SPI2_Open(uint8_t spiConfigIndex)
{
    if(!SSP2CON1bits.SSPEN)
    {
        SSP2STAT = spi2_configuration[spiConfigIndex].stat;
        SSP2CON1 = spi2_configuration[spiConfigIndex].con1;
        SSP2CON2 = 0x00;
        SSP2ADD  = spi2_configuration[spiConfigIndex].add;
        SSP2CON1bits.SSPEN = 1;
        return true;
    }
    return false;
}

void SPI2_Close(void)
{
    SSP2CON1bits.SSPEN = 0;
}

uint8_t SPI2_ByteExchange(uint8_t data)
{
    SSP2BUF = data;
    while(!PIR3bits.SSP2IF);
    PIR3bits.SSP2IF = 0;
    return SSP2BUF;
}

void SPI2_BufferExchange(void *block, size_t blockSize)
{
    uint8_t *data = block;
    while(blockSize--)
    {
        SSP2BUF = *data;
        while(!PIR3bits.SSP2IF);
        PIR3bits.SSP2IF = 0;
        *data++ = SSP2BUF;
    }
}

// Half Duplex SPI Functions
void SPI2_BufferWrite(void *block, size_t blockSize)
{
    uint8_t *data = block;
    while(blockSize--)
    {
        SPI2_ByteExchange(*data++);
    }
}

void SPI2_BufferRead(void *block, size_t blockSize)
{
    uint8_t *data = block;
    while(blockSize--)
    {
        *data++ = SPI2_ByteExchange(0);
    }
}

void SPI2_ByteWrite(uint8_t byte)
{
    SSP2BUF = byte;
}

uint8_t SPI2_ByteRead(void)
{
    return SSP2BUF;
}

uint8_t SPI2_ExchangeByte(uint8_t data)
{
    return SPI2_ByteExchange(data);
}

void SPI2_ExchangeBlock(void *block, size_t blockSize)
{
    SPI2_BufferExchange(block, blockSize);
}

void SPI2_WriteBlock(void *block, size_t blockSize)
{
    SPI2_BufferWrite(block, blockSize);
}

void SPI2_ReadBlock(void *block, size_t blockSize)
{
    SPI2_BufferRead(block, blockSize);
}

void SPI2_WriteByte(uint8_t byte)
{
    SPI2_ByteWrite(byte);
}

uint8_t SPI2_ReadByte(void)
{
    return SPI2_ByteRead();
}

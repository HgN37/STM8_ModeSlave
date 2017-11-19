#ifndef __UART_H__
#define __UART_H__

#include "stm8s.h"

void uartInit(uint32_t pBaudRate, uint32_t pBufferSize);
uint32_t uartAvailable(void);
void uartWriteByte(uint8_t pByte);
void uartWrite(uint8_t* pArray, uint32_t pLength);
uint8_t uartRead() ;

#endif
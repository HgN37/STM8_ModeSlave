#include "uart.h"
#include <stdlib.h>
#include <string.h>

struct {
    uint8_t* buffer;
    uint32_t size;
    uint32_t start;
    uint32_t stop;
} _serialBuffer;

void uartInit(uint32_t pBaudRate, uint32_t pBufferSize) {
    _serialBuffer.size = pBufferSize;
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART1, ENABLE);
    UART1_Init(pBaudRate,
               UART1_WORDLENGTH_8D,
               UART1_STOPBITS_1,
               UART1_PARITY_NO,
               UART1_SYNCMODE_CLOCK_DISABLE,
               UART1_MODE_TXRX_ENABLE);
    UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);
    UART1_Cmd(ENABLE);
    _serialBuffer.buffer = (uint8_t*)malloc(_serialBuffer.size);
    memset(_serialBuffer.buffer, 0, _serialBuffer.size);
    _serialBuffer.start = 0;
    _serialBuffer.stop = 0;
}

uint32_t uartAvailable(void) {
    if(_serialBuffer.stop >= _serialBuffer.start) {
        return _serialBuffer.stop - _serialBuffer.start;
    }
    else {
        return _serialBuffer.size - (_serialBuffer.start - _serialBuffer.stop);
    }
}

void uartWriteByte(uint8_t pByte) {
    while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
    UART1_SendData8(pByte);
}

void uartWrite(uint8_t* pArray, uint32_t pLength) {
    uint32_t index = 0;
    while(index < pLength) {
        uartWriteByte(pArray[index]);
        index++;
    }
}

uint8_t uartRead() {
    /* Empty condition */
    if(_serialBuffer.stop == _serialBuffer.start) {
        return 0;
    }
    /* Read from buffer */
    uint8_t byte = _serialBuffer.buffer[_serialBuffer.start];
    /* Update index */
    _serialBuffer.start++;
    if(_serialBuffer.start == _serialBuffer.size) {
        _serialBuffer.start = 0;
    }
    return byte;
}

#pragma vector = 20
__interrupt void uartRxIntHandler(void) {
    UART1_ClearITPendingBit(UART1_IT_RXNE);
    /* Check full condition */
    uint32_t next = _serialBuffer.stop + 1;
    if(next == _serialBuffer.size) {
        next = 0;
    }
    if(next == _serialBuffer.start) {
        return;
    }
    /* Get byte to buffer */
    _serialBuffer.buffer[_serialBuffer.stop] = UART1_ReceiveData8();
    /* Update index */
    _serialBuffer.stop = next;
}

#include "protocol.h"
#include "uart.h"

struct Frame {
    uint16_t id;
    uint16_t func;
    uint16_t reg;
    uint16_t data;
    uint16_t sum;
}_frame;

uint8_t modGetFrame(void) {
    if(!uartAvailable()) {
        return 1;
    }
    uint32_t timeout = 0xFFFF;
    uint32_t count = 0;
    uint8_t buffer[10];
    while((count < 10) & (timeout > 0)) {
        if(uartAvailable()) {
            buffer[count] = uartRead();
            count++;
        }
        timeout--;
    }
    if(timeout == 0) {
        return 1;
    }
    _frame.id = ((uint16_t)buffer[0] << 8)|((uint16_t)buffer[1]);
    _frame.func = ((uint16_t)buffer[2] << 8)|((uint16_t)buffer[3]);
    _frame.reg = ((uint16_t)buffer[4] << 8)|((uint16_t)buffer[5]);
    _frame.data = ((uint16_t)buffer[6] << 8)|((uint16_t)buffer[7]);
    _frame.sum = ((uint16_t)buffer[8] << 8)|((uint16_t)buffer[9]);
    /* Check sum */
    if(_frame.sum != (_frame.id + _frame.func + _frame.reg +  _frame.data)) {
        return 1;
    }
    /* Check function */
    if((_frame.func != 0x0000)&(_frame.func != 0x0001)) {
        return 1;
    }
    return 0;
}
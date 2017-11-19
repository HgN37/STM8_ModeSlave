#include "dev.h"
#include "random.h"

struct Dev {
    uint16_t id;
    uint16_t type;
    uint16_t random;
    uint16_t data1;
    uint16_t data2;
    uint16_t data3;
    uint16_t data4;
    uint16_t data5;
}_device;

void devInit() {
    randomInit();
    _device.id = 0;
    _device.type = DEV_TYPE;
    _device.random = randomGenerate();
    _device.data1 = 0;
    _device.data2 = 0;
    _device.data3 = 0;
    _device.data4 = 0;
    _device.data5 = 0;
    randomDeInit();
}
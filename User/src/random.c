#include "random.h"

void randomInit(void) {
    ADC1_DeInit();
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC, ENABLE);
    ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,
              ADC1_CHANNEL_4,
              ADC1_PRESSEL_FCPU_D2,
              ADC1_EXTTRIG_GPIO,
              DISABLE,
              ADC1_ALIGN_RIGHT,
              ADC1_SCHMITTTRIG_ALL,
              DISABLE);
    ADC1_Cmd(ENABLE);
}

void randomDeInit(void) {
    ADC1_DeInit();
}

uint16_t randomGenerate(void) {
    uint16_t random = 0;
    uint32_t loop = 0;
    while(loop < 8) {
        random = random << 2;
        ADC1_StartConversion();
        random |= ADC1_GetConversionValue()&0x0003;
        loop++;
    }
    return random;
}
#ifndef __COLORS_H__
#define __COLORS_H__

#include "aqi.h"
#include <stdint.h>

class Colors {
    public:
        virtual uint32_t foreground() = 0;
        virtual uint32_t background() = 0;
};

class AirQualityColors : public Colors {
    private:
        const uint16_t *pm2_5;
    
    public:
        AirQualityColors(const uint16_t *pm2_5);

        uint32_t foreground();
        uint32_t background();

        static uint32_t stateColors(QualityStage stage);
};

#endif // __COLORS_H__
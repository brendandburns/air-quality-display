#ifndef __COLORS_H__
#define __COLORS_H__

#include "screens.h"

class AirQualityColors : public Colors {
    private:
        const uint16_t *pm2_5;
    
    public:
        AirQualityColors(const uint16_t *pm2_5);

        uint32_t foreground();
        uint32_t background();
};

#endif // __COLORS_H__
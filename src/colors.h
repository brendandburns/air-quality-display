#ifndef __COLORS_H__
#define __COLORS_H__

#include "screens.h"
#include <PMS.h>

class AirQualityColors : public Colors {
    private:
        PMS::DATA *data;
    
    public:
        AirQualityColors(PMS::DATA* data);

        uint32_t foreground();
        uint32_t background();
};

#endif // __COLORS_H__
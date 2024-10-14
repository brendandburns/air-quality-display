#ifndef __PLOT_H__
#define __PLOT_H__

#include <TFT_eSPI.h>

class Graph {
    public:
        static void boxPlot(TFT_eSPI* tft, const float data[], size_t data_points, int x, int y, float y_max, int width, int height, uint32_t color);
};

#endif // __PLOT_H__
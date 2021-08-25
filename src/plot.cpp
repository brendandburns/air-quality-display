#include "plot.h"


void Graph::boxPlot(TFT_eSPI* tft, const float data[], size_t data_points, int x, int y, float y_max, int width, int height, uint32_t color) {
    for (int i = 0; i < data_points; i++) {
        int y_value = int((data[i] * height) / y_max);
        if (y_value > height) {
            y_value = height;
        }
        tft->fillRect(x * i, y + height - y_value, width, y_value, color);
    }
}
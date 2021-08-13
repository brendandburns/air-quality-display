#include "data.h"

DataSet::DataSet(int count) : values(new float[count]), size(count) {
    for (int i = 0; i < count; i++) {
        this->values[i] = 0.0;
    }
}

DataSet::~DataSet() { delete this->values; }

void DataSet::addDataPoint(float value) {
    for (int i = this->size - 1; i > 0; i--) {
        this->values[i] = this->values[i-1];
    }
    this->values[0] = value;
}

const float* DataSet::data() {
    return this->values;
}

int DataSet::count() {
    return this->size;
}
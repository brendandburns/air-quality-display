#ifndef __DATA_H__
#define __DATA_H__

class DataSet {
    private:
        float *values;
        int size;
    
    public:
        DataSet(int count);
        ~DataSet();
    
        void addDataPoint(float data);
        const float* data();
        int count();
};

#endif // __DATA_H__
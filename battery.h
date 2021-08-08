#ifndef __BATTERY_H__
#define __BATTERY_H__

class Battery {
    public:
        Battery();
    
        void init();
        bool charging();
        float volts();
        int percentage();
};

#endif // __BATTERY_H__
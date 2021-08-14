#ifndef __BATTERY_H__
#define __BATTERY_H__

class Battery {
    private:
        float readings[10];
        int ix;

    public:
        Battery();
    
        void init();
        bool charging();
        float volts();
        int percentage();
        void loop();
};

#endif // __BATTERY_H__
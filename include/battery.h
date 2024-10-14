#ifndef __BATTERY_H__
#define __BATTERY_H__

class Battery {
    private:
        float readings[10];
        int ix;

        Battery();

        static Battery* _instance;

    public:    
        void init();
        bool charging();
        float volts();
        int percentage();
        void loop();

        static Battery* battery();
};

#endif // __BATTERY_H__
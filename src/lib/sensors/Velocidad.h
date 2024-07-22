#ifndef VELOCIDAD_H_
#define VELOCIDAD_H_

#define MAX_HALL_SENSORS 5


class VELOCIDAD{
    public:
        VELOCIDAD();
        void init();
        void loop();
        float getSpeed();
        void addHall(int pin);
    private:
        int _pin[MAX_HALL_SENSORS];
        int _hallSensors;
        float _revs[MAX_HALL_SENSORS] = {0};
        float _times[MAX_HALL_SENSORS][2] = {0}; // fi, ini
        float speed;
        void fromRevsToSpeed(float revs);
};

#endif // VELOCIDAD_H_
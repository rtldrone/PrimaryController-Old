//
// Created by cameronearle on 7/26/2019.
//

#ifndef PRIMARYCONTROLLER_VESCCOMMMANAGER_H
#define PRIMARYCONTROLLER_VESCCOMMMANAGER_H

#include <Arduino.h>
#include <FreeRTOS.h>

extern "C" {
#include <datatypes.h>
}

#define VESC_COMM_MANAGER_RT_STACK_DEPTH 8192
#define VESC_COMM_MANAGER_RT_PRIO 1
#define VESC_COMM_MANAGER_RT_FREQUENCY 1
#define VESC_COMM_MANAGER_MAX_BUFFER_READ_PER_CYCLE 512

class VescCommManager {
public:
    static void stop();
    static void setPercentOut(float percentOut);
    static float getPercentOut();

    static void begin(Stream *_serial);

    struct VESCData {
        float inputVoltage;
        float currentDraw;
        float motorRpm;
    };

    static VESCData getData();
private:
    static Stream *serial;
    static mc_values *values;
    static VESCData currentData;
    static float currentDutyCycle;

    static void sendSerialData(unsigned char *data, unsigned int length);
    static void updateTimer(void *parameter);
    static void read(void *parameter);
    static void write(void *parameter);

    static void onValues(mc_values *newValues);

    static SemaphoreHandle_t commandLock;
    static SemaphoreHandle_t valuesLock;
};

#endif //PRIMARYCONTROLLER_VESCCOMMMANAGER_H

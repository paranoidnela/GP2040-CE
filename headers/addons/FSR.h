#ifndef _FSR_H
#define _FSR_H

#include "gpaddon.h"
#include "GamepadEnums.h"
#include "BoardConfig.h"
#include "enums.pb.h"
#include "types.h"

#ifndef FSR_INPUT_ENABLED
#define FSR_INPUT_ENABLED 0
#endif

#ifndef ANALOG_ADC_PIN_LEFT
#define ANALOG_ADC_PIN_LEFT    -1
#endif

#ifndef ANALOG_ADC_PIN_RIGHT
#define ANALOG_ADC_PIN_RIGHT    -1
#endif

#ifndef ANALOG_ADC_PIN_UP
#define ANALOG_ADC_PIN_UP    -1
#endif

#ifndef ANALOG_ADC_PIN_DOWN
#define ANALOG_ADC_PIN_DOWN    -1
#endif

#ifndef ANALOG_ADC_THRESHOLD_LEFT
#define ANALOG_ADC_THRESHOLD_LEFT    0.2
#endif

#ifndef ANALOG_ADC_THRESHOLD_RIGHT
#define ANALOG_ADC_THRESHOLD_RIGHT    0.2
#endif

#ifndef ANALOG_ADC_THRESHOLD_UP
#define ANALOG_ADC_THRESHOLD_UP    0.2
#endif

#ifndef ANALOG_ADC_THRESHOLD_DOWN
#define ANALOG_ADC_THRESHOLD_DOWN    0.2
#endif


// Analog Module Name
#define AnalogName "FSR"

#define ADC_COUNT 4

typedef struct
{
    Pin_t left_pin;
    Pin_t right_pin;
    Pin_t up_pin;
    Pin_t down_pin;
    float left_value;
    float right_value;
    float up_value;
    float down_value;
    float left_threshold;
    float right_threshold;
    float up_threshold;
    float down_threshold;
    
} adc_instance;

class FSRInput : public GPAddon {
public:
    virtual bool available();
    virtual void setup();       // Analog Setup
    virtual void process();     // Analog Process
    virtual void preprocess() {}
    virtual void postprocess(bool sent) {}
    virtual void reinit() {}
    virtual std::string name() { return AnalogName; }
private:
    float readPin(Pin_t pin);
};

#endif  // _FSR_H_
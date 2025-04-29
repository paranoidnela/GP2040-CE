#include "addons/FSR.h"
#include "config.pb.h"
#include "enums.pb.h"
#include "hardware/adc.h"
#include "helper.h"
#include "storagemanager.h"
#include "drivermanager.h"

#include <math.h>

#define ADC_MAX ((1 << 12) - 1) // 4095
#define ADC_PIN_OFFSET 26

bool FSRInput::available() {
    return Storage::getInstance().getAddonOptions().fsrOptions.enabled;
}

void FSRInput::setup() {
    const FSROptions& FSROptions = Storage::getInstance().getAddonOptions().FSROptions;

    // Setup our 4 arrows
    FSR.left_pin = FSROptions.analogAdcPinLeft;
    FSR.right_pin = FSROptions.analogAdcPinRight;
    FSR.up_pin = FSROptions.analogAdcPinUp;
    FSR.down_pin = FSROptions.analogAdcPinDown;

    FSR.left_threshold = FSROptions.analogAdcThresholdLeft;
    FSR.right_threshold = FSROptions.analogAdcThresholdRight;
    FSR.up_threshold = FSROptions.analogAdcThresholdUp;
    FSR.down_threshold = FSROptions.analogAdcThresholdDown;

    // HW-init
    // TODO: check if valid pin
    adc_gpio_init(FSR.left_pin);
    adc_gpio_init(FSR.right_pin);
    adc_gpio_init(FSR.up_pin);
    adc_gpio_init(FSR.down_pin);
    
}

void FSRInput::process() {
    Gamepad * gamepad = Storage::getInstance().GetGamepad();
    
    uint16_t joystickMid = GAMEPAD_JOYSTICK_MID;
    if ( DriverManager::getInstance().getDriver() != nullptr ) {
        joystickMid = DriverManager::getInstance().getDriver()->GetJoystickMidValue();
    }

    //reading
    // TODO: check if valid pin
    FSR.left_value = readPin(FSR.left_pin);
    FSR.right_value = readPin(FSR.right_pin);
    FSR.up_value = readPin(FSR.up_pin);
    FSR.down_value = readPin(FSR.down_pin);

    if (FSR.left_value > FSR.left_threshold){
        gamepad->state.buttons |= GAMEPAD_MASK_LEFT;
    } 

    if (FSR.right_value > FSR.right_threshold){
        gamepad->state.buttons |= GAMEPAD_MASK_RIGHT;
    } 

    if (FSR.down_value > FSR.down_threshold){
        gamepad->state.buttons |= GAMEPAD_MASK_DOWN;
    } 

    if (FSR.up_value > FSR.up_threshold){
        gamepad->state.buttons |= GAMEPAD_MASK_UP;
    } 

}

float FSRInput::readPin(Pin_t pin_adc) {
    adc_select_input(pin_adc);
    uint16_t adc_value = adc_read();
    return (float)adc_value;
}

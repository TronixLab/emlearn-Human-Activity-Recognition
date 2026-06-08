#pragma once

#include "./constants.h"
#include "./functions/csv.h"
#include "./functions/prompt.h"
#include "./functions/deprecated.h"

#include "./wrappers/Ultrasonic.h"

#if defined(ARDUINO_APDS9960)
#include "./wrappers/APDS9960.h"
#endif

#if defined(__SD_H__)
#include "./wrappers/SDCard.h"
#endif

#if defined(_LSM9DS1_H_)
#include "./wrappers/LSM9DS1.h"
#endif

#if defined(_PDM_H_INCLUDED)
#include "./wrappers/Microphone/PDM.h"
#endif

#if defined(ESP32)
#include "./wrappers/Camera/ESP32CAM.h"
#endif

#if defined(EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE)
#include "./wrappers/Impulse/BaseImpulse.h"

#if EI_CLASSIFIER_SENSOR == EI_CLASSIFIER_SENSOR_FUSION
#include "./wrappers/Impulse/SensorImpulse.h"
#elif EI_CLASSIFIER_SENSOR == EI_CLASSIFIER_SENSOR_MICROPHONE
#include "./wrappers/Impulse/MicrophoneImpulse.h"
#elif EI_CLASSIFIER_OBJECT_DETECTION
#include "./wrappers/Impulse/ObjectDetectionImpulse.h"
#endif

#endif
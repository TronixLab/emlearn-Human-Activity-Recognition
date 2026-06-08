#pragma once

#ifndef FLOAT_DECIMALS
#define FLOAT_DECIMALS 6
#endif

// microphone-related constants
#ifndef PDM_BUFFER_SIZE
#define PDM_BUFFER_SIZE 256
#endif

// Edge Impulse-related constants
#if defined(EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW)
#define PDM_BUFFER_SIZE 1000
#endif

// camera-related constants
/**
 * When Edge Impulse model is in grayscale mode,
 * camera will be set to grayscale mode too to
 * reduce memory consumption.
 * With this option, you can force the camera
 * to take RGB frames (e.g. for further processing)
 */
#ifndef FORCE_RGB_MODE
#define FORCE_RGB_MODE false
#endif

#if EI_CLASSIFIER_OBJECT_DETECTION
    #if EI_CLASSIFIER_INPUT_WIDTH <= 96
        #define FRAMESIZE FRAMESIZE_96X96
    #elif EI_CLASSIFIER_INPUT_WIDTH <= 120
        #define FRAMESIZE FRAMESIZE_QQVGA
    #else
        #error "Edge Impulse frame size not supported: must be less than/equal 120x120"
    #endif

    // detect at compile time if Edge Impulse is in RGB or Grayscale mode
    #define EI_IS_RGB (EI_CLASSIFIER_NN_INPUT_FRAME_SIZE > EI_CLASSIFIER_RAW_SAMPLE_COUNT)

    #if EI_IS_RGB || FORCE_RGB_MODE
        #define PIXFORMAT PIXFORMAT_RGB565
        #define BPP 2
        #define PIXEL_DTYPE uint16_t
    #else
        #define PIXFORMAT PIXFORMAT_GRAYSCALE
        #define BPP 1
        #define PIXEL_DTYPE uint8_t
    #endif
#else
    // if no Edge Impulse model is detected, boot in JPEG mode
    #define PIXFORMAT PIXFORMAT_JPEG
    #define FRAMESIZE FRAMESIZE_QVGA
#endif
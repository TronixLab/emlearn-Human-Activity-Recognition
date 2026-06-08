#if EI_CLASSIFIER_SENSOR == EI_CLASSIFIER_SENSOR_FUSION
#pragma once
#include "./BaseImpulse.h"

namespace tinyml4all {
    /**
     * Impulse for sensor data
     */
    class Impulse : public BaseImpulse {
    public:
        Queue<EI_CLASSIFIER_RAW_SAMPLE_COUNT, EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME> queue;

        /**
         * Constrcutor
         */
        Impulse() : BaseImpulse() {

        }

        /**
         *
         */
        void begin() {
            BaseImpulse::begin();
            queue.shiftInSamples(EI_CLASSIFIER_SLICE_SIZE);
        }

        /**
         * Test if internal queue is full
         */
        inline bool isReady() {
            return queue.isFull();
        }

        /**
         * Run impulse
         */
        bool run() {
            numpy::signal_from_buffer(queue.data, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &sig);

            return failWithCode(
                run_classifier(&sig, &res, config.debug),
                "run_classifier() failed"
            );
        }
    };
}
#endif
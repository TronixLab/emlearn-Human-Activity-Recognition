#if EI_CLASSIFIER_SENSOR == EI_CLASSIFIER_SENSOR_MICROPHONE
#pragma once
#include "./BaseImpulse.h"

namespace tinyml4all {
    /**
     * Impulse for audio data
     */
    class Impulse : public BaseImpulse {
    public:
        int16_t audio[EI_CLASSIFIER_SLICE_SIZE];

        /**
         * Constrcutor
         */
        Impulse() : BaseImpulse(), count(0) {

        }

        /**
         *
         */
        void begin() {
            BaseImpulse::begin();
            sig.total_length = EI_CLASSIFIER_SLICE_SIZE;
        }

        /**
         * Audio classification is always ready
         */
        inline bool isReady() {
            return true;
        }

        /**
         * Run impulse
         */
        template<typename Microphone>
        bool queue(Microphone &microphone) {
            // fill slice data
            if (microphone.length) {
                uint16_t readable = min((uint16_t) microphone.length, (uint16_t)(EI_CLASSIFIER_SLICE_SIZE - count));

                // hopefully memcpy is faster than for loop
                memcpy((uint8_t * )(audio + count), (uint8_t *) microphone.data, readable * 2);
                count = constrain(count + readable, 0, EI_CLASSIFIER_SLICE_SIZE);
                microphone.empty();
            } else {
                return fail("No new data from microphone");
            }

            // slice is full, run prediction
            if (count == EI_CLASSIFIER_SLICE_SIZE) {
                count = 0;
                sig.get_data = [this](size_t offset, size_t length, float *dest) {
                    return numpy::int16_to_float(audio + offset, dest, length);
                };

                return failWithCode(
                    run_classifier_continuous(&sig, &res, config.debug),
                    "run_classifier_continuous() failed"
                );
            }

            return !failed();
        }

    protected:
        uint16_t count;
    };
}
#endif
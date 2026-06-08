#if defined(EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE)
#pragma once

#include "../../traits/CanFail.h"
#include "./Queue.h"

namespace tinyml4all {
    /**
     * Edge Impulse wrapper
     */
    class BaseImpulse : public CanFail {
    public:
        const size_t numInputs = EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE;
        const size_t numOutputs = EI_CLASSIFIER_LABEL_COUNT;
        signal_t sig;
        ei_impulse_result_t res;

        /**
         * Constructor
         */
        BaseImpulse() {
            verbose(false);
            succeed();
            sig.total_length = EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE;
        }

        /**
         * Init EI
         */
        virtual void begin() {
            sig.total_length = EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE;
            run_classifier_init();
        }

        /**
         * Toggle verbose mode
         */
        inline void verbose(bool verbose = true) {
            config.debug = verbose;
        }

        /**
         * Get most probable label
         */
        String label() {
            String label = res.classification[0].label;
            float confidence = res.classification[0].value;

            for (uint8_t i = 1; i < numOutputs && confidence < 0.5; i++) {
                if (res.classification[i].value > confidence) {
                    confidence = res.classification[i].value;
                    label = res.classification[i].label;
                }
            }

            return label;
        }

        /**
         * Get most probable confidence
         */
        float confidence() {
            float confidence = res.classification[0].value;

            for (uint8_t i = 1; i < numOutputs && confidence < 0.5; i++) {
                if (res.classification[i].value > confidence) {
                    confidence = res.classification[i].value;
                }
            }

            return confidence;
        }

    protected:
        struct {
            bool debug;
        } config;
    };
}

#endif // defined(EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE)


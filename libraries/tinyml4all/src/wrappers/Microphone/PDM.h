#if defined(_PDM_H_INCLUDED)
#pragma once
#include "../../traits/CanFail.h"

// utilities to convert the async API into sync
volatile uint16_t __pdmAvailable = 0;
static int16_t __pdmBuffer[PDM_BUFFER_SIZE / 2];

void __onPDMData() {
    __pdmAvailable = PDM.available();
    PDM.read(__pdmBuffer, __pdmAvailable);
}

namespace tinyml4all {
    /**
     * Read data from PDM microphone
     */
    class PDMicrophone : public CanFail {
    public:
        int16_t *data;
        uint16_t length;
        uint16_t consumed;

        /**
         * Constructor
         */
        PDMicrophone() : data(NULL), length(0), consumed(0) {
            frequency("16 khz");
            volume(30);
        }

        /**
         * Set frequency as string
         * (e.g. 16 khz)
         */
        inline void frequency(String freq) {
            config.freq = freq.toInt() * 1000;
        }

        /**
         * Set volume (from 0 to 100)
         *
         * @param volume
         */
        inline void volume(uint8_t volume) {
            config.gain = constrain(volume, 0, 100) * 2.55f;
        }

        /**
         * Get remaining number of samples to consume
         */
        inline uint16_t remaining() {
            return length - consumed;
        }

        /**
         * Init PDM microphone
         * @return
         */
        bool begin(bool endless = true) {
            PDM.setBufferSize(PDM_BUFFER_SIZE);
            PDM.onReceive(__onPDMData);

            if (!PDM.begin(1, config.freq))
                return retry<bool>("Can't begin PDM", [this]() { return begin(true); }, endless);

            PDM.setGain(config.gain);
            return true;
        }

        /**
         * Mark data as consumed
         */
        inline void empty() {
            length = 0;
        }

        /**
         * Busy wait for data
         */
        void await() {
            while (__pdmAvailable < 2) {
                delay(2);
            }

            length = __pdmAvailable / 2;
            data = __pdmBuffer;
            __pdmAvailable = 0;
        }

        /**
         * Write data to Serial
         */
        void print() {
            if (length > 0) {
                Serial.write((uint8_t*) data, length * 2);
                empty();
            }
        }

    protected:
        struct {
            uint16_t freq;
            uint8_t gain;
        } config;
    };
}

#endif
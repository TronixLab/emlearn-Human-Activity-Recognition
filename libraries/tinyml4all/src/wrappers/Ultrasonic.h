#pragma once

namespace tinyml4all {
    /**
     * Ultrasonic distance sensor
     */
    class Ultrasonic {
    public:
        /**
         * Constructor
         * @param echo_
         * @param trig_
         */
        Ultrasonic(uint8_t echo_, uint8_t trig_) : echo(echo_), trig(trig_) {

        }

        /**
         * Init sensor
         */
        void begin() {
            pinMode(trig, OUTPUT);
            pinMode(echo, INPUT);
            digitalWrite(trig, LOW);
        }

        /**
         * Get distance in millimeters
         * @return
         */
        uint16_t millimiters() {
            digitalWrite(trig, LOW);
            delayMicroseconds(2);
            digitalWrite(trig, HIGH);
            delayMicroseconds(10);
            digitalWrite(trig, LOW);

            const uint16_t duration = pulseIn(echo, HIGH);

            return (duration * .343f) / 2;
        }

    protected:
        uint8_t echo;
        uint8_t trig;
    };
}
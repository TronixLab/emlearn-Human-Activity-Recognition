#if defined(ARDUINO_APDS9960)
#ifndef TINYML4ALL_APDS9960_H
#define TINYML4ALL_APDS9960_H

#include "../traits/CanFail.h"

namespace tinyml4all {
    /**
     * Wrap Arduino_APDS9960 library
     *
     */
    class APDS9960 : public CanFail {
    public:
        int r;
        int g;
        int b;
        int proximity;

        /**
         * Constructor
         */
        APDS9960() {
            r = 0;
            g = 0;
            b = 0;
            proximity = 0;
        }

        /**
         * Init sensor
         */
        bool begin(bool endless = true) {
            if (APDS.begin())
                return true;

            return retry<bool>("Can’t init APDS9960 sensor", [this]() { return begin(true); }, endless);
        }

        /**
         * Read R, G, B values
         */
        void readColor() {
            // busy wait for color
            while (!APDS.colorAvailable())
                delay(1);

            APDS.readColor(r, g, b);
        }

        /**
         * Read proximity distance
         */
        void readProximity() {
            // busy wait for proximity
            while (!APDS.proximityAvailable())
                delay(1);

            proximity = APDS.readProximity();

            if (proximity < 0)
                readProximity();
        }
    };
}

#endif //TINYML4ALL_APDS9960_H
#endif // defined(ARDUINO_APDS9960)
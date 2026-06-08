#if defined(__SD_H__)
#pragma once
#include "../functions/csv.h"
#include "../traits/CanFail.h"

namespace tinyml4all {
    /**
     * Write contents to SD card
     */
    class SDCard : public CanFail {
    public:

        /**
         * Init SD card
         */
        bool begin(uint8_t cs, bool endless = true) {
            if (SD.begin(cs))
                return true;

            return retry<bool>("Can't init SD", [this, cs]() { return begin(cs, true); }, endless);
        }

        /**
         * Set output filename
         */
        void writing(String filename) {
            writeTo = filename;
        }

        /**
         * Print multiple values as CSV
         */
        template<typename T, typename... Args>
        void println(T first, Args... args) {
            println(asCSV(first, args...));
        }

        /**
         * Print string
         */
        void println(String data) {
            File file = SD.open(writeTo, O_APPEND);

            file.println(data);
            file.close();
        }

    protected:
        String writeTo;
    };
}

#endif
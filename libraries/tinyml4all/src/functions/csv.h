#pragma once
#include "../constants.h"

namespace tinyml4all {
    namespace csv {
        /**
         * Private function to convert value to string.
         * @tparam T
         * @param arg
         * @return
         */
        template<typename T>
        String toString(T arg) {
            return String(arg);
        }

        /**
         * Private function to convert value to string.
         * Specialized version for floats.
         * @tparam T
         * @param arg
         * @return
         */
        String toString(float arg) {
            return String(arg, FLOAT_DECIMALS);
        }

        /**
         * Stop condition
         * @return
         */
        String append() {
            return "";
        }

        /**
         * Private function to generate a CSV string
         * @tparam T
         * @tparam Args
         * @param stream
         * @param first
         * @param args
         */
        template<typename T, typename... Args>
        String append(T first, Args... args) {
            return "," + tinyml4all::csv::toString(first) + tinyml4all::csv::append(args...);
        }
    }

    /**
     * Convert values to CSV
     * @tparam T
     * @tparam Args
     * @param first
     * @param args
     */
    template<typename T, typename... Args>
    String asCSV(T first, Args... args) {
        return tinyml4all::csv::toString(first) + tinyml4all::csv::append(args...);
    }

    /**
     * Print values as CSV
     * @tparam T
     * @tparam Args
     * @param first
     * @param args
     */
    template<typename T, typename... Args>
    void printCSV(T first, Args... args) {
        Serial.println(asCSV(first, args...));
    }
}
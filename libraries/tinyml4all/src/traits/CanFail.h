#pragma once

namespace tinyml4all {
    /**
     * Trait for classes that can fail doing something
     * (e.g. initialize)
     */
    class CanFail {
    public:

        /**
         * Test if an error occurred
         * @return
         */
        inline bool failed() {
            return errorMessage.length() > 0;
        }

        /**
         * Get error message
         * @return
         */
        inline String error() {
            return errorMessage;
        }

        /**
         * Set error message
         * @param message
         * @return true on success, false on failure
         */
        bool fail(const String& message) {
            errorMessage = message;

            // this may look weird, but it is to allow
            // `return fail()` to evaluate to true on no error
            return !failed();
        }

        /**
         * Set error message + code
         * @param errorCode
         * @param message
         * @return
         */
        bool failWithCode(int errorCode, const String& message) {
            return errorCode != 0 ? fail(message + " with code " + errorCode) : succeed();
        }

        /**
         * Remove error message
         * @return
         */
        bool succeed() {
            return fail("");
        }

        /**
         * Endless print error message
         * @param message
         */
        void abort(const String &message) {
            while (true) {
                Serial.println(message);
                delay(1000);
            }
        }

        /**
         * Retry or abort
         * @tparam ReturnT
         * @tparam Function
         * @param message
         * @param function
         * @param endless
         */
        template<typename ReturnT, typename Function>
        ReturnT retry(const String& message, Function function, bool endless) {
            if (!endless)
                abort(message);

            Serial.println(message);
            return function();
        }

    protected:
        String errorMessage;
    };
}
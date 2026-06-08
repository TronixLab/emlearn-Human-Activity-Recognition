#pragma once

#include <cstdarg>

namespace tinyml4all {
    /**
     * Circular queue
     * @tparam numSamples
     * @tparam numDimensions
     */
    template<size_t numSamples, uint16_t numDimensions>
    class Queue {
    public:
        float data[numSamples * numDimensions];

        /**
         * Constructor
         */
        Queue() :
            _shift(numSamples / 4) {
            clear();
        }

        /**
         * Append data
         * @param first
         * @param ...
         */
        void operator()(float first, ...) {
            static float values[numDimensions] = {first};

            va_list args;
            va_start(args, first);

            for (int i = 1; i < numDimensions; i++)
                values[i] = va_arg(args, double);

            va_end(args);
            append(values);
        }

        /**
         * Get total size of queue
         * @return
         */
        inline size_t size() {
            return numSamples * numDimensions;
        }

        /**
         * Test if queue is full
         * @return
         */
        inline bool isFull() {
            return _isFull;
        }

        /**
         * Clear queue data
         */
        void clear() {
            _head = 0;
            _isFull = false;
            memset(data, 0, size());
        }

        /**
         * Set samples to shift when queue is full
         * @param shift
         */
        inline void shiftInSamples(uint16_t shift) {
            if (shift > numSamples)
                shift = numSamples;

            _shift = shift;
        }

        /**
         * Append row of data
         * @param values
         */
        void append(float *values) {
            if (_isFull) {
                memcpy(data, data + _shift * numDimensions, sizeof(float) * (numSamples - _shift) * numDimensions);
            }

            const size_t offset = _head * numDimensions;

            for (uint16_t i = 0; i < numDimensions; i++)
                data[offset + i] = values[i];

            next();
        }

        /**
         * Print data for debug purposes
         * @tparam Printer
         * @param printer
         * @param separator
         * @param end
         */
        template<typename Printer>
        void printTo(Printer printer, char separator = ',', char end = '\n') {
            printer.print(data[0]);

            for (uint16_t i = 1; i < size(); i++) {
                printer.print(separator);
                printer.print(data[i]);
            }

            printer.print(end);
        }

        /**
         * Print data to Serial
         * @param separator
         * @param end
         */
        void print(char separator = ',', char end = '\n') {
            printTo(Serial);
        }

    protected:
        bool _isFull;
        size_t _head;
        uint16_t _shift;

        /**
         * Move head to next position
         */
        void next() {
            _head += 1;

            if (_head == numSamples) {
                _head -= _shift;
                _isFull = true;
            }
            else {
                _isFull = false;
            }
        }
    };
}
#if defined(_LSM9DS1_H_)
#pragma once

#include "../macros.h"
#include "../traits/CanFail.h"

//#define LSM9DS1_ADDRESS            0x6b
//
//#define LSM9DS1_WHO_AM_I           0x0f
//#define LSM9DS1_CTRL_REG1_G        0x10
//#define LSM9DS1_STATUS_REG         0x17
//#define LSM9DS1_OUT_X_G            0x18
//#define LSM9DS1_CTRL_REG6_XL       0x20
//#define LSM9DS1_CTRL_REG8          0x22
//#define LSM9DS1_OUT_X_XL           0x28

// magnetometer
#define LSM9DS1_ADDRESS_M          0x1e

#define LSM9DS1_CTRL_REG1_M        0x20
//#define LSM9DS1_CTRL_REG2_M        0x21
//#define LSM9DS1_CTRL_REG3_M        0x22
//#define LSM9DS1_STATUS_REG_M       0x27
//#define LSM9DS1_OUT_X_L_M          0x28
//
#ifdef ARDUINO_ARDUINO_NANO33BLE
#define LSM9DS1_WIRE Wire1
#else
#define LSM9DS1_WIRE Wire
#endif

namespace tinyml4all {
    /**
     * LSM9DS1 wrapper
     */
    class LSM9DS1 : public CanFail {
    public:
        float ax, ay, az;
        float gx, gy, gz;
        float mx, my, mz;

        /**
         * Begin sensor
         * @return
         */
        bool begin(bool endless = true) {
            if (!IMU.begin())
                return retry<bool>("Can’t init LSM9DS1 sensor", [this]() { return begin(true); }, endless);

            // set magnetometer to 80 Hz
            const int16_t existing = readRegister(LSM9DS1_ADDRESS_M, LSM9DS1_CTRL_REG1_M);

            if (existing >= 0) {
                const uint8_t setting = 0b11100 | (static_cast<uint8_t>(existing) & 0b11100001);
                writeRegister(LSM9DS1_ADDRESS_M, LSM9DS1_CTRL_REG1_M, setting);
            }

            return true;
        }

        /**
         * Await (and read) acceleration
         */
        void readAcceleration() {
            while (!IMU.accelerationAvailable())
                delay(1);

            IMU.readAcceleration(ax, ay, az);
        }

        /**
         * Await (and read) gyroscope
         */
        void readGyroscope() {
            while (!IMU.gyroscopeAvailable())
                delay(1);

            IMU.readGyroscope(gx, gy, gz);
        }

        /**
         * Await (and read) magnetometer
         */
        void readMagneticField() {
            while (!IMU.magneticFieldAvailable())
                delay(1);

            IMU.readMagneticField(mx, my, mz);
        }

        /**
         * (internal) Write register
         */
        void writeRegister(uint8_t slaveAddress, uint8_t address, uint8_t value) {
            LSM9DS1_WIRE.beginTransmission(slaveAddress);
            LSM9DS1_WIRE.write(address);
            LSM9DS1_WIRE.write(value);
            LSM9DS1_WIRE.endTransmission();
        }

        /**
         * (internal) Read register
         */
        int16_t readRegister(uint8_t slaveAddress, uint8_t address) {
            LSM9DS1_WIRE.beginTransmission(slaveAddress);
            LSM9DS1_WIRE.write(address);

            if (LSM9DS1_WIRE.endTransmission() != 0)
                return -1;

            if (LSM9DS1_WIRE.requestFrom(slaveAddress, 1) != 1)
                return -1;

            return LSM9DS1_WIRE.read();
        }

    protected:
    };
}

#endif // defined(_LSM9DS1_H_)
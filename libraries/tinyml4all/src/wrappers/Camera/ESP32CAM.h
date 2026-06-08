#if defined(ESP32)
#pragma once
#include <esp_camera.h>
#include "../../constants.h"
#include "../../functions/prompt.h"
#include "../../traits/CanFail.h"

namespace tinyml4all {
    // define model with name and pins
    struct esp32_camera_model_t {
        String name;
        int8_t pins[16];
    };

    namespace internal {
        static const uint8_t numCameraModels = 11;
        static const esp32_camera_model_t cameraModels[numCameraModels] = {
                {"AiThinker", {5, 18, 19, 21, 36, 39, 34, 35, 0, 22, 25, 23, 26, 27, 32, -1}},
                {"XIAO", {15, 17, 18, 16, 14, 12, 11, 48, 10, 13, 38, 47, 40, 39, -1, -1}},
                {"M5", {32, 35, 34, 5, 39, 18, 36, 19, 27, 21, 22, 26, 25, 23, -1, 15}},
                {"M5 Fish Eye", {32, 35, 34, 5, 39, 18, 36, 19, 27, 21, 25, 26, 22, 23, -1, 15}},
                {"M5 Timer X", {32, 35, 34, 5, 39, 18, 36, 19, 27, 21, 22, 26, 25, 23, -1, 15}},
                {"ESP-EYE", {34, 13, 14, 35, 39, 38, 37, 36, 4, 25, 5, 27, 18, 23, -1, -1}},
                {"ESP-EYE S3", {11, 9, 8, 10, 12, 18, 17, 16, 15, 13, 6, 7, 4, 5, -1, -1}},
                {"WROVER", {4, 5, 18, 19, 36, 39, 34, 35, 21, 22, 25, 23, 26, 27, -1, -1}},
                {"WROOM S3", {11, 9, 8, 10, 12, 18, 17, 16, 15, 13, 6, 7, 4, 5, -1, -1}},
                {"TTGO PLUS", {34, 13, 26, 35, 39, 38, 37, 36, 4, 25, 5, 27, 18, 23, -1, -1}},
                {"TTGO PIR", {5, 14, 4, 15, 18, 23, 36, 39, 32, 19, 27, 25, 13, 12, 26, -1}},
        };
    }

    using internal::numCameraModels;
    using internal::cameraModels;

    /**
     * Adapter for ESP32
     */
    class Camera : public CanFail {
    public:
        uint8_t *u8;
        uint16_t *u16;
        camera_config_t config;
        sensor_t *sensor;
        camera_fb_t *fb;

        /**
         * Constructor
         */
        Camera() {
            config.pin_d0 = 0;
            config.pin_d1 = 0;
            // default to inference mode
            inferencing();
        }

        /**
         * Configure camera
         * @return
         */
        bool begin(bool endless = true) {
            if (config.pin_d0 == config.pin_d1) {
                promptModel();
            }

            config.ledc_channel = LEDC_CHANNEL_0;
            config.ledc_timer = LEDC_TIMER_0;
            config.fb_count = 1;
            config.pixel_format = conf.pixformat;
            config.frame_size = conf.framesize;
            config.jpeg_quality = 10;
            config.xclk_freq_hz = 2000000;
            config.grab_mode = CAMERA_GRAB_LATEST;

            if (esp_camera_init(&config) != ESP_OK)
                return retry<bool>("esp_camera_init() failed", [this]() { return begin(true); }, endless);

            sensor = esp_camera_sensor_get();
            sensor->set_framesize(sensor, FRAMESIZE);

            return grab();
        }

        /**
         * Capture new frame
         * @return
         */
        bool grab() {
            // free existing frame before capturing
            if (fb != NULL) {
                esp_camera_fb_return(fb);
                fb = NULL;
            }

            fb = esp_camera_fb_get();

            if (fb == NULL || fb->buf == NULL || fb->len == 0)
                return fail("Cannot grab new frame");

            u8 = fb->buf;
            u16 = (uint16_t *) u8;

            return succeed();
        }

        /**
         * Print as binary to Serial
         */
        bool print() {
            if (fb == NULL || fb->len == 0)
                return fail("Can't print empty frame");

            Serial.print("#SOF#");
            Serial.write(fb->buf, fb->len);
            Serial.println("#EOF#");

            return succeed();
        }

        /**
         * Get size of frame
         * @return
         */
        inline size_t size() {
            return fb != NULL ? fb->len : 0;
        }

        /**
         *
         * @return
         */
        String encoding() {
            if (config.pixel_format == PIXFORMAT_JPEG)
                return "jpeg";

            if (config.pixel_format == PIXFORMAT_RGB565)
                return "rgb2";

            if (config.pixel_format == PIXFORMAT_GRAYSCALE)
                return "gray";

            return "Unknown";
        }

        /**
         * Get frame width
         * @return
         */
        inline uint16_t width() {
            return fb == NULL ? 0 : fb->width;
        }

        /**
         * Get frame height
         * @return
         */
        inline uint16_t height() {
            return fb == NULL ? 0 : fb->height;
        }

        /**
         * Set model from string
         */
        void setModel(const String& model) {
            String m(model);

            m.toLowerCase();

            if (m == "aithinker") setPins(&(cameraModels[0]));
            else if (m == "xiao") setPins(&(cameraModels[1]));
            else if (m == "m5") setPins(&(cameraModels[2]));
            else if (m == "m5 fish eye") setPins(&(cameraModels[3]));
            else if (m == "m5 timer x") setPins(&(cameraModels[4]));
            else if (m == "esp-eye") setPins(&(cameraModels[5]));
            else if (m == "esp-eye s3") setPins(&(cameraModels[6]));
            else if (m == "wrover") setPins(&(cameraModels[7]));
            else if (m == "wroom s3") setPins(&(cameraModels[8]));
            else if (m == "ttgo plus") setPins(&(cameraModels[9]));
            else if (m == "ttgo pir") setPins(&(cameraModels[10]));
            else {
                Serial.print("Unknown model: ");
                Serial.println(model);
            }
        }

        /**
         * Ask user to select model from list
         */
        void promptModel() {
            // let user choose model from list
            int choice = 0;
            const String prompt("Select camera model:\n [1] AiThinker\n [2] XIAO\n [3] M5\n [4] M5 Fish Eye\n [5] M5 Timer X\n [6] ESP-EYE\n [7] ESP-EYE S3\n [8] WROVER\n [9] WROOM S3\n [10] TTGO PLUS\n [11] TTGO PIR\nEnter choice number [1-11]: ");

            do {
                choice = promptInt(prompt);
            } while (choice < 1 || choice > numCameraModels);

            const esp32_camera_model_t model = cameraModels[choice - 1];

            Serial.print("Selected ");
            Serial.println(model.name);
            setPins(&model);
        }

        /**
         * Configure for data collection
         */
        void collecting() {
            conf.pixformat = PIXFORMAT_JPEG;
            conf.framesize = FRAMESIZE_240X240;
        }

        /**
         * Configure for inference
         */
        void inferencing() {
            conf.pixformat = PIXFORMAT;
            conf.framesize = FRAMESIZE;
        }

#if EI_CLASSIFIER_OBJECT_DETECTION

        /**
         * Get ready to send data to Edge Impulse
         */
        void prepareData() {
            if (width() == EI_CLASSIFIER_INPUT_WIDTH && height() == EI_CLASSIFIER_INPUT_HEIGHT)
                return;

            // crop image
            const size_t xoff = (width() - EI_CLASSIFIER_INPUT_WIDTH) / 2;
            const size_t yoff = (height() - EI_CLASSIFIER_INPUT_HEIGHT) * width() / 2;
            PIXEL_DTYPE *buf = (PIXEL_DTYPE*) fb->buf;

            for (size_t y = 0; y < EI_CLASSIFIER_INPUT_HEIGHT; y++) {
                const size_t off1 = y * EI_CLASSIFIER_INPUT_WIDTH;
                const size_t off2 = y * width();
                memcpy(buf + off1, buf + off2 + xoff + yoff, EI_CLASSIFIER_INPUT_WIDTH * BPP);
            }
        }

        /**
         * Push data to Edge Impulse buffer
         * @param offset
         * @param length
         * @param out
         */
        int getData(size_t offset, size_t length, float *out) {
            size_t i = 0;
            PIXEL_DTYPE *buf = (PIXEL_DTYPE*) fb->buf;
            const size_t end = min((int) EI_CLASSIFIER_RAW_SAMPLE_COUNT, (int) (offset + length));

            for (size_t y = 0; y < EI_CLASSIFIER_INPUT_HEIGHT; y++) {
                const size_t yoff = y * EI_CLASSIFIER_INPUT_WIDTH;

                for (size_t x = 0; x < EI_CLASSIFIER_INPUT_WIDTH; x++, i++) {
                    if (i < offset) continue;
                    if (i >= end) return 0;

                    const PIXEL_DTYPE pixel = buf[i];

                    #if EI_IS_RGB || FORCE_RGB_MODE
                        // bytes are swapped
                        const uint8_t low = pixel >> 8;
                        const uint16_t high = pixel & 0xFF;
                        const uint16_t pixelSwap = (high << 8) | low;
                        uint32_t r = high & 0b11111000;
                        uint16_t g = (pixelSwap & 0b11111100000) >> 3;
                        uint16_t b = low << 3;

                        #if !EI_IS_RGB
                            // frame is RGB, EI model is grayscale
                            r = g = b = constrain((r * 38 + g * 75 + b * 15) >> 7, 0, 255);
                        #endif
                    #else
                        const uint32_t r = pixel;
                        const uint16_t g = pixel;
                        const uint8_t b = pixel;
                    #endif

                    out[i - offset] = (r << 16) | (g << 8) | b;
                }
            }

            return 0;
        }
#endif

    protected:
        struct {
            pixformat_t pixformat;
            framesize_t framesize;
        } conf;

        /**
         * Set pins
         */
        void setPins(const esp32_camera_model_t *model) {
            config.pin_d0 = model->pins[0];
            config.pin_d1 = model->pins[1];
            config.pin_d2 = model->pins[2];
            config.pin_d3 = model->pins[3];
            config.pin_d4 = model->pins[4];
            config.pin_d5 = model->pins[5];
            config.pin_d6 = model->pins[6];
            config.pin_d7 = model->pins[7];
            config.pin_xclk = model->pins[8];
            config.pin_pclk = model->pins[9];
            config.pin_vsync = model->pins[10];
            config.pin_href = model->pins[11];
            config.pin_sccb_sda = model->pins[12];
            config.pin_sccb_scl = model->pins[13];
            config.pin_pwdn = model->pins[14];
            config.pin_reset = model->pins[15];
        }

    };
}

#endif // if defined(ESP32)
#if EI_CLASSIFIER_OBJECT_DETECTION
#pragma once
#include "./BaseImpulse.h"

/**
 * Bouding box type for object detection results
 */
struct bbox_t {
    String label;
    float confidence;
    uint8_t width;
    uint8_t height;
    uint8_t x;
    uint8_t y;
    uint8_t cx;
    uint8_t cy;
};

namespace tinyml4all {
    /**
     * Impulse for sensor data
     */
    class Impulse : public BaseImpulse {
    public:
        /**
         * Constrcutor
         */
        Impulse() : BaseImpulse() {

        }

        /**
         * Run impulse
         */
        bool run(Camera& camera) {
            if (!camera.size())
                return fail("No frame to detect objects in");

            crop(camera);

            // case 1: camera pixformat is gray, EI expects gray
            if (camera.config.pixel_format == PIXFORMAT_GRAYSCALE && !EI_IS_RGB) {
                sig.get_data = [this, &camera](size_t offset, size_t length, float *out) {
                    return graygray(camera, offset, length, out);
                };
            }
            // case 2: camera pixformat is gray, EI expects rgb
            else if (camera.config.pixel_format == PIXFORMAT_GRAYSCALE && EI_IS_RGB) {
                sig.get_data = [this, &camera](size_t offset, size_t length, float *out) {
                    return grayrgb(camera, offset, length, out);
                };
            }
            // case 3: camera pixformat is rgb, EI expects gray
            else if (camera.config.pixel_format == PIXFORMAT_RGB565 && !EI_IS_RGB) {
                sig.get_data = [this, &camera](size_t offset, size_t length, float *out) {
                    return rgbgray(camera, offset, length, out);
                };
            }
            // case 4: camera pixformat is rgb, EI expects rgb
            else if (camera.config.pixel_format == PIXFORMAT_RGB565 && EI_IS_RGB) {
                sig.get_data = [this, &camera](size_t offset, size_t length, float *out) {
                    return rgbrgb(camera, offset, length, out);
                };
            }

            return failWithCode(
                run_classifier(&sig, &res, config.debug),
                "run_classifier() failed"
            );
        }

        /**
         * Get count of non background bounding boxes
         */
        uint8_t count() {
            uint8_t count = 0;

            for (uint8_t ix = 0; ix < res.bounding_boxes_count; ix++) {
                auto bb = res.bounding_boxes[ix];

                if (bb.value > 0)
                    count++;
            }

            return count;
        }

        /**
         * Get bbox at given index
         * @param index
         * @return
         */
        bbox_t object(uint8_t index) {
            uint8_t count = 0;
            bbox_t result = {
                    .label = "Not found",
                    .confidence = 0,
                    .width = 0,
                    .height = 0,
                    .x = 0,
                    .y = 0,
                    .cx = 0,
                    .cy = 0
            };

            for (uint8_t ix = 0; ix < res.bounding_boxes_count; ix++) {
                auto bb = res.bounding_boxes[ix];

                if (bb.value > 0 && index == count) {
                    result.label = bb.label;
                    result.confidence = bb.value;
                    result.width = bb.width;
                    result.height = bb.height;
                    result.x = bb.x;
                    result.y = bb.y;
                    result.cx = bb.x + bb.width / 2;
                    result.cy = bb.y + bb.height / 2;

                    break;
                }

                if (bb.value > 0)
                    count++;
            }

            return result;
        }

    protected:

        /**
         * Resize data to Edge Impulse dimensions
         */
        void crop(Camera& camera) {
            // easy case: frame size matches Edge Impulse size (a.k.a. 96x96)
            if (camera.width() == EI_CLASSIFIER_INPUT_WIDTH && camera.height() == EI_CLASSIFIER_INPUT_HEIGHT)
                return;

            // hard case: crop image (in-place)
            const size_t offX = (camera.width() - EI_CLASSIFIER_INPUT_WIDTH) / 2;
            const size_t offY = (camera.height() - EI_CLASSIFIER_INPUT_HEIGHT) * camera.width() / 2;
            const size_t offCrop = offX + offY;
            PIXEL_DTYPE *buf = (PIXEL_DTYPE*) (camera.fb->buf);

            for (size_t y = 0; y < EI_CLASSIFIER_INPUT_HEIGHT; y++) {
                const size_t offDest = y * EI_CLASSIFIER_INPUT_WIDTH;
                const size_t offSource = y * camera.width();

                memcpy((uint8_t*) (buf + offDest), (uint8_t*) (buf + offSource + offCrop), EI_CLASSIFIER_INPUT_WIDTH * BPP);
            }
        }

        /**
         * Copy data (gray camera, gray EI)
         * @param camera
         * @param offset
         * @param length
         * @param out
         * @return
         */
        size_t graygray(Camera& camera, size_t offset, size_t length, float *out) {
            for (size_t i = offset; i < offset + length; i++)
                *(out++) = camera.fb->buf[i];

            return EIDSP_OK;
        }

        /**
         * Copy data (gray camera, rgb EI)
         * @param camera
         * @param offset
         * @param length
         * @param out
         * @return
         */
        size_t grayrgb(Camera& camera, size_t offset, size_t length, float *out) {
            for (size_t i = offset; i < offset + length; i++) {
                const uint32_t pixel = camera.fb->buf[i];

                *(out++) = (pixel << 16) | (pixel << 8) | pixel;
            }

            return EIDSP_OK;
        }

        /**
         * Copy data (rgb camera, gray EI)
         * @param camera
         * @param offset
         * @param length
         * @param out
         * @return
         */
        size_t rgbgray(Camera& camera, size_t offset, size_t length, float *out) {
            uint16_t *buf = (uint16_t*) (camera.fb->buf);

            for (size_t i = offset; i < offset + length; i++) {
                const uint16_t pixelSwapped = buf[i];
                // bytes are swapped when coming out of the camera
                const uint16_t pixel = __builtin_bswap16(pixelSwapped);
                const uint8_t r5 = (pixel >> 11) & 0x1F;
                const uint8_t g6 = (pixel >> 5) & 0x3F;
                const uint8_t b5 = pixel & 0x1F;
                const uint16_t r = (r5 << 3) | (r5 >> 2);
                const uint16_t g = (g6 << 2) | (g6 >> 4);
                const uint16_t b = (b5 << 3) | (b5 >> 2);
                const uint32_t gray = (r * 77 + g * 150 + b * 29) >> 8;

                *(out++) = (gray << 16) | (gray << 8) | gray;
            }

            return EIDSP_OK;
        }

        /**
         * Copy data (rgb camera, rgb EI)
         * @param camera
         * @param offset
         * @param length
         * @param out
         * @return
         */
        size_t rgbrgb(Camera& camera, size_t offset, size_t length, float *out) {
            uint16_t *buf = (uint16_t*) (camera.fb->buf);

            for (size_t i = offset; i < offset + length; i++) {
                const uint16_t pixelSwapped = buf[i];
                // bytes are swapped when coming out of the camera
                const uint16_t pixel = __builtin_bswap16(pixelSwapped);
                const uint8_t r5 = (pixel >> 11) & 0x1F;
                const uint8_t g6 = (pixel >> 5) & 0x3F;
                const uint8_t b5 = pixel & 0x1F;
                const uint32_t r = (r5 << 3) | (r5 >> 2);
                const uint16_t g = (g6 << 2) | (g6 >> 4);
                const uint8_t b = (b5 << 3) | (b5 >> 2);

                *(out++) = (r << 16) | (g << 8) | b;
            }

            return EIDSP_OK;
        }
    };
}
#endif
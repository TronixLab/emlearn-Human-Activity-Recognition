#ifndef SLIDING_WINDOW_H
#define SLIDING_WINDOW_H

#include <stddef.h>
#include <stdint.h>

// Reusable fixed-size sliding window for embedded targets.
// - Channels: number of signal axes (for IMU: 3)
// - MaxWindowSamples: compile-time memory limit for one frame
template<size_t Channels, size_t MaxWindowSamples>
class SlidingWindow {
public:
  SlidingWindow()
    : sample_rate_hz_(0),
      window_size_samples_(0),
      stride_samples_(0),
      head_(0),
      count_(0),
      samples_since_emit_(0),
      emitted_once_(false),
      configured_(false) {
    clear();
  }

  // Configure sliding window using time-domain parameters (milliseconds).
  // Returns false if parameters are invalid or exceed MaxWindowSamples.
  bool begin(int sample_rate_hz, uint16_t window_frame_size_ms, uint16_t window_stride_ms) {
    if (sample_rate_hz <= 0 || window_frame_size_ms == 0 || window_stride_ms == 0) {
      configured_ = false;
      return false;
    }

    const size_t window_samples = msToSamples(window_frame_size_ms, sample_rate_hz);
    const size_t stride_samples = msToSamples(window_stride_ms, sample_rate_hz);

    if (window_samples == 0 || stride_samples == 0 || window_samples > MaxWindowSamples) {
      configured_ = false;
      return false;
    }

    sample_rate_hz_ = sample_rate_hz;
    window_size_samples_ = window_samples;
    stride_samples_ = stride_samples;
    clear();
    configured_ = true;
    return true;
  }

  // Push one sample vector (length = Channels).
  // Returns true when a full frame is ready.
  bool pushSample(const float *sample) {
    if (!configured_ || sample == NULL) {
      return false;
    }

    for (size_t c = 0; c < Channels; c++) {
      buffer_[head_][c] = sample[c];
    }

    head_ = (head_ + 1) % window_size_samples_;
    if (count_ < window_size_samples_) {
      count_++;
    }

    if (count_ < window_size_samples_) {
      return false;
    }

    if (!emitted_once_) {
      emitted_once_ = true;
      samples_since_emit_ = 0;
      return true;
    }

    samples_since_emit_++;
    if (samples_since_emit_ >= stride_samples_) {
      samples_since_emit_ = 0;
      return true;
    }

    return false;
  }

  // Convenience wrapper when parameters are passed at runtime alongside each sample.
  bool processSample(const float *sample,
                     uint16_t window_frame_size_ms,
                     uint16_t window_stride_ms,
                     int sample_rate_hz) {
    if (!configured_ || sample_rate_hz != sample_rate_hz_ || window_size_samples_ != msToSamples(window_frame_size_ms, sample_rate_hz) || stride_samples_ != msToSamples(window_stride_ms, sample_rate_hz)) {
      if (!begin(sample_rate_hz, window_frame_size_ms, window_stride_ms)) {
        return false;
      }
    }
    return pushSample(sample);
  }

  // Convenience overload for 3-axis signals.
  bool pushSample(float x, float y, float z) {
    static_assert(Channels == 3, "pushSample(x,y,z) requires Channels == 3");
    const float v[3] = { x, y, z };
    return pushSample(v);
  }

  // Copy the latest full frame into out[window_size_samples * Channels], oldest to newest.
  // Returns false if frame is not yet available.
  bool windowFrame(float *out) const {
    if (!configured_ || out == NULL || count_ < window_size_samples_) {
      return false;
    }

    for (size_t i = 0; i < window_size_samples_; i++) {
      const size_t src_idx = (head_ + i) % window_size_samples_;
      for (size_t c = 0; c < Channels; c++) {
        out[(i * Channels) + c] = buffer_[src_idx][c];
      }
    }
    return true;
  }

  // Copy frame into per-axis arrays (each length = window_size_samples).
  // Useful when subsequent processing expects separate axis buffers.
  bool windowFrame(float *acc_x, float *acc_y, float *acc_z) const {
    static_assert(Channels == 3, "windowFrame(acc_x,acc_y,acc_z) requires Channels == 3");
    if (!configured_ || acc_x == NULL || acc_y == NULL || acc_z == NULL || count_ < window_size_samples_) {
      return false;
    }

    for (size_t i = 0; i < window_size_samples_; i++) {
      const size_t src_idx = (head_ + i) % window_size_samples_;
      acc_x[i] = buffer_[src_idx][0];
      acc_y[i] = buffer_[src_idx][1];
      acc_z[i] = buffer_[src_idx][2];
    }
    return true;
  }

  size_t windowSamples() const {
    return window_size_samples_;
  }
  size_t strideSamples() const {
    return stride_samples_;
  }
  int sampleRateHz() const {
    return sample_rate_hz_;
  }
  bool isConfigured() const {
    return configured_;
  }

private:
  static size_t msToSamples(uint16_t ms, int sample_rate_hz) {
    const size_t numerator = ((size_t)ms * (size_t)sample_rate_hz) + 500U;
    const size_t rounded = numerator / 1000U;
    return (rounded > 0U) ? rounded : 1U;
  }

  void clear() {
    head_ = 0;
    count_ = 0;
    samples_since_emit_ = 0;
    emitted_once_ = false;
    for (size_t i = 0; i < MaxWindowSamples; i++) {
      for (size_t c = 0; c < Channels; c++) {
        buffer_[i][c] = 0.0f;
      }
    }
  }

  float buffer_[MaxWindowSamples][Channels];
  int sample_rate_hz_;
  size_t window_size_samples_;
  size_t stride_samples_;
  size_t head_;
  size_t count_;
  size_t samples_since_emit_;
  bool emitted_once_;
  bool configured_;
};

#endif
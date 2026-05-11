#ifndef EML_FFT_WRAPPER_H
#define EML_FFT_WRAPPER_H

#include <math.h>
#include <stddef.h>

#include <eml_fft.h>

// Reusable FFT wrapper for fixed-size real-valued windows.
// - N must be a power of 2.
// - window_lut can be a Hann, boxcar, or any other precomputed window of size N.
template <size_t N>
class SingleSidedFFT
{
public:
  static constexpr size_t kBins = (N / 2) + 1;

  SingleSidedFFT(const float (&window_lut)[N], int sample_rate_hz)
      : window_lut_(window_lut), sample_rate_hz_(sample_rate_hz), window_sum_(0.0f), initialized_(false)
  {
    static_assert((N & (N - 1)) == 0, "FFT length N must be a power of 2");

    fft_.length = (int)(N / 2);
    fft_.cos = cos_table_;
    fft_.sin = sin_table_;

    for (size_t i = 0; i < N; i++)
    {
      window_sum_ += window_lut_[i];
      real_buf_[i] = 0.0f;
      imag_buf_[i] = 0.0f;
    }
    if (window_sum_ <= 0.0f)
    {
      window_sum_ = (float)N;
    }
  }

  EmlError begin()
  {
    const EmlError err = eml_fft_fill(fft_, N);
    initialized_ = (err == EmlOk);
    return err;
  }

  // One-line API: init-if-needed + run FFT + return single-sided magnitude.
  // input must point to at least N samples.
  EmlError single_sided_FFT(const float *input, float *magnitude_out)
  {
    if (input == NULL || magnitude_out == NULL)
    {
      return EmlUninitialized;
    }

    if (!initialized_)
    {
      const EmlError init_err = begin();
      if (init_err != EmlOk)
      {
        return init_err;
      }
    }

    float mean = 0.0f;
    for (size_t i = 0; i < N; i++)
    {
      mean += input[i];
    }
    mean /= (float)N;

    for (size_t i = 0; i < N; i++)
    {
      real_buf_[i] = (input[i] - mean) * window_lut_[i];
      imag_buf_[i] = 0.0f;
    }

    const EmlError fft_err = eml_fft_forward(fft_, real_buf_, imag_buf_, N);
    if (fft_err != EmlOk)
    {
      return fft_err;
    }

    for (size_t k = 0; k < kBins; k++)
    {
      const float re = real_buf_[k];
      const float im = imag_buf_[k];
      float mag = sqrtf((re * re) + (im * im));

      // Match notebook/scipy scaling: 2 * abs(X) / sum(window) for all bins.
      mag *= (2.0f / window_sum_);
      magnitude_out[k] = mag;
    }

    return EmlOk;
  }

  float frequencyForBin(size_t bin) const
  {
    return ((float)bin * (float)sample_rate_hz_) / (float)N;
  }

  int sampleRateHz() const
  {
    return sample_rate_hz_;
  }

  static const char *errorName(EmlError err)
  {
    switch (err)
    {
    case EmlOk:
      return "EmlOk";
    case EmlSizeMismatch:
      return "EmlSizeMismatch";
    case EmlUnsupported:
      return "EmlUnsupported";
    case EmlUninitialized:
      return "EmlUninitialized";
    case EmlPostconditionFailed:
      return "EmlPostconditionFailed";
    case EmlUnknownError:
      return "EmlUnknownError";
    default:
      return "InvalidEmlError";
    }
  }

private:
  const float *window_lut_;
  int sample_rate_hz_;
  float window_sum_;
  bool initialized_;

  EmlFFT fft_;
  float sin_table_[N / 2];
  float cos_table_[N / 2];
  float real_buf_[N];
  float imag_buf_[N];
};

#endif
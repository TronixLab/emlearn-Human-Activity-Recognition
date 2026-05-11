#ifndef EML_IIR_FILTER_H
#define EML_IIR_FILTER_H

#include <eml_iir.h>

template<size_t Order, size_t Stages>
class EmlIIRFilter {
public:
  explicit EmlIIRFilter(const float (&coefficients)[Stages * 6])
    : coefficients_(coefficients), initialized_(false), last_error_(EmlUninitialized) {
    static_assert(Order == (Stages * 2), "IIR order must be 2 * number of SOS stages");
    for (size_t i = 0; i < (Stages * 4); i++) {
      states_[i] = 0.0f;
    }
    configure();
  }

  EmlError init() {
    configure();
    initialized_ = true;
    last_error_ = eml_iir_check(filter_);
    return last_error_;
  }

  EmlError check() {
    last_error_ = eml_iir_check(filter_);
    return last_error_;
  }

  float run(float input) {
    if (!initialized_ || last_error_ != EmlOk) {
      const EmlError err = init();
      if (err != EmlOk) {
        return input;
      }
    }
    return eml_iir_filter(filter_, input);
  }

  EmlError lastError() const {
    return last_error_;
  }

  static const char *errorName(EmlError err) {
    switch (err) {
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
  void configure() {
    filter_.n_stages = (int)Stages;
    filter_.states = states_;
    filter_.states_length = (int)(Stages * 4);
    filter_.coefficients = coefficients_;
    filter_.coefficients_length = (int)(Stages * 6);
  }

  float states_[Stages * 4];
  const float *coefficients_;
  EmlIIR filter_;
  bool initialized_;
  EmlError last_error_;
};

#endif
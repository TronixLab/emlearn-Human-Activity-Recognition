// StandardScaler for Arduino - matches scikit-learn StandardScaler transform
#ifndef STANDARD_SCALER_H
#define STANDARD_SCALER_H

class StandardScaler {
public:
  static constexpr int n_features = 18;

  const float scaler_means[18] = { 1.106705f, 0.062631f, 0.181076f, 0.047950f, 3.116750f, 0.169195f,
                                   2.405398f, 0.138468f, 0.393426f, 0.269937f, 17.545903f, 0.366945f, 2.596526f, 0.148013f, 0.423397f,
                                   0.281909f, 18.324102f, 0.395334f };

  const float scaler_stds[18] = { 0.782459f, 0.045361f, 0.123132f, 0.044991f, 2.924384f, 0.115511f,
                                  2.124605f, 0.125016f, 0.339342f, 0.287740f, 18.703131f, 0.316995f, 2.022821f, 0.118400f, 0.320382f,
                                  0.274019f, 17.811253f, 0.299490f };

  // Scale input array in-place
  void transform(float* X, float* X_scaled) const {
    for (int i = 0; i < n_features; i++) {
      X_scaled[i] = (X[i] - scaler_means[i]) / scaler_stds[i];
    }
  }

  // Inverse scale input array in-place
  void inverse_transform(float* X_scaled, float* X) const {
    for (int i = 0; i < n_features; i++) {
      X[i] = X_scaled[i] * scaler_stds[i] + scaler_means[i];
    }
  }
};

#endif  // STANDARD_SCALER_H
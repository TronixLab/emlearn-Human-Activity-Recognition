# emlearn Human Activity Recognition

An end-to-end TinyML project that trains a neural network classifier in Python and deploys it on an **Arduino Nano 33 BLE Sense** (BMI270 IMU) using the [emlearn](https://emlearn.org) library. The board classifies four real-time wrist/hand motions: **Clockwise**, **Horizontal**, **Idle**, and **Vertical**.

---

## Table of Contents

- [Overview](#overview)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Repository Structure](#repository-structure)
- [Workflow](#workflow)
  - [1. Data Collection](#1-data-collection)
  - [2. Model Training](#2-model-training)
  - [3. Deployment](#3-deployment)
- [Signal Processing Pipeline](#signal-processing-pipeline)
- [Neural Network Architecture](#neural-network-architecture)
- [Motion Classes](#motion-classes)
- [Getting Started](#getting-started)
- [License](#license)

---

## Overview

This project demonstrates a complete TinyML pipeline:

1. **Collect** raw 3-axis accelerometer data from the Arduino at 100 Hz and save it as CSV files.
2. **Train** a lightweight neural network in a Jupyter Notebook (Keras + scikit-learn) using frequency-domain (spectral) features extracted via FFT.
3. **Export** the trained model and StandardScaler parameters to C++ header files using `emlearn`.
4. **Deploy** the classifier back to the Arduino, where it performs real-time inference with no cloud dependency.

---

## Hardware Requirements

| Component | Details |
|-----------|---------|
| Arduino Nano 33 BLE Sense | BMI270 + BMM150 IMU |
| USB cable | For programming and serial output |

---

## Software Requirements

### Arduino (Embedded)
- [Arduino IDE](https://www.arduino.cc/en/software) ≥ 2.x
- `Arduino_BMI270_BMM150` library
- `emlearn` Arduino library (provides `eml_net.h`, `eml_fft.h`, `eml_iir.h`)
- `tinyml4all` library (used by the data-capture sketch)

### Python (Training)
- Python 3.x
- TensorFlow / Keras
- scikit-learn
- NumPy, pandas, matplotlib
- emlearn Python package (`pip install emlearn`)

---

## Repository Structure

```
emlearn-Human-Activity-Recognition/
├── CaptureMotionCSV/
│   └── CaptureMotionCSV.ino      # Arduino sketch: records IMU data to CSV via Serial
│
├── data/
│   ├── clockwise.csv / .txt      # Collected accelerometer data — clockwise motion
│   ├── horizontal.csv / .txt     # Collected accelerometer data — horizontal motion
│   ├── idle.csv / .txt           # Collected accelerometer data — idle (no motion)
│   └── vertical.csv / .txt       # Collected accelerometer data — vertical motion
│
├── HAR_model_training.html       # Rendered Jupyter Notebook (training pipeline)
├── HAR_model_training.pdf        # PDF version of the training notebook
│
└── Arduino_HAR/
    ├── Arduino_HAR.ino           # Main inference sketch (real-time HAR)
    ├── NeuralNetworkClassifier.h # Trained NN weights/biases exported by emlearn
    ├── StandardScaler.h          # Scaler means & stds exported from scikit-learn
    ├── SlidingWindow.h           # Reusable fixed-size sliding window (C++ template)
    ├── SpectralFeatures.h        # Spectral feature extraction from FFT magnitudes
    ├── eml_FFT.h                 # C++ wrapper around emlearn's FFT
    ├── eml_iir_filter.h          # C++ wrapper around emlearn's IIR filter
    └── boxcar_128_lut.h          # Precomputed 128-point boxcar window LUT
```

---

## Workflow

### 1. Data Collection

Upload `CaptureMotionCSV/CaptureMotionCSV.ino` to the board. Open the Serial Monitor (115200 baud). The sketch prompts you for:

- **Motion label** – e.g., `clockwise`, `horizontal`, `idle`, `vertical`
- **Duration in minutes** – number of minutes to record

It then streams data at **100 Hz** in CSV format:

```
timestamp,accX,accY,accZ,motion
0,0.645237,-2.387019,5.018247,clockwise
10,0.905008,-2.613271,4.495114,clockwise
...
```

Acceleration values are in m/s². Copy the Serial output into a `.csv` file under the `data/` directory.

### 2. Model Training

Open `HAR_model_training.html` (or the source `.ipynb`) to follow the full training pipeline:

1. **Load & merge** the four CSV files.
2. **Preprocess** – apply a 4th-order Butterworth low-pass filter (cutoff 5 Hz) to each axis.
3. **Segment** – slice the time-series into overlapping windows (2000 ms window, 500 ms stride).
4. **Feature extraction** – compute a 128-point FFT on each window per axis, then extract 6 spectral features per axis → **18 features** total.
5. **Normalise** – fit a `StandardScaler` (zero mean, unit variance).
6. **Train** – a Keras Sequential neural network (see architecture below).
7. **Export** – use `emlearn` to generate `NeuralNetworkClassifier.h` and export scaler parameters to `StandardScaler.h`.

### 3. Deployment

Copy the generated header files into `Arduino_HAR/` and upload the sketch. The board will:

- Sample the IMU at 100 Hz.
- Filter each axis with the IIR low-pass filter.
- Fill the sliding window; emit a frame every 500 ms.
- Run the 128-point FFT → extract 18 spectral features → scale → classify.
- Print the predicted label and confidence over Serial.

Example Serial output:
```
Predicted Label: clockwise    Probability: 94.32%
Predicted Label: idle         Probability: 98.71%
```

---

## Signal Processing Pipeline

```
IMU (100 Hz)
    │
    ▼
4th-order Butterworth IIR LPF (cutoff 5 Hz)
    │  SOS biquad implementation via emlearn
    │
    ▼
Sliding Window  (2000 ms frame, 500 ms stride → 200 samples)
    │
    ▼
128-point Single-Sided FFT  (boxcar window)  × 3 axes
    │
    ▼
Spectral Feature Extraction  (6 features × 3 axes = 18 features)
  peak | mean | RMS | PSD | energy | std_dev
    │
    ▼
StandardScaler  (subtract mean, divide by std)
    │
    ▼
Neural Network Classifier  →  { clockwise | horizontal | idle | vertical }
```

---

## Neural Network Architecture

| Layer | Units | Activation |
|-------|-------|-----------|
| Input | 18 | — |
| Dense | 16 | ReLU |
| Dense | 12 | ReLU |
| Dropout | — | 0.05 rate |
| Dense | 8 | ReLU |
| Dense (output) | 4 | Softmax |

- **Optimizer:** Adam
- **Loss:** Categorical cross-entropy
- **Epochs:** 30 | **Batch size:** 32
- **Export format:** C header (`eml_net.h` compatible) via emlearn

---

## Motion Classes

| Label | Description |
|-------|------------|
| `clockwise` | Wrist/hand rotating in a clockwise circular motion |
| `horizontal` | Lateral side-to-side motion |
| `idle` | No deliberate motion (resting) |
| `vertical` | Up-and-down motion |

---

## Getting Started

1. **Clone the repository**
   ```bash
   git clone https://github.com/TronixLab/emlearn-Human-Activity-Recognition.git
   ```

2. **Collect data** – upload `CaptureMotionCSV.ino`, capture ~1 minute per class.

3. **Train the model** – open the Jupyter Notebook, run all cells, and copy the generated header files to `Arduino_HAR/`.

4. **Deploy** – open `Arduino_HAR.ino` in the Arduino IDE, compile, and upload.

5. **Observe results** – open the Serial Monitor at **115200 baud** to see live predictions.

---

## License

See [LICENSE](LICENSE) for details.

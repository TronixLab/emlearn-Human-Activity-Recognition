# emlearn Human Activity Recognition

An end-to-end TinyML project for classifying wrist and hand motions on an **Arduino Nano 33 BLE Sense Rev2**. The repository still includes the data-collection sketch and model-training notebook, but the Arduino inference source has been replaced with a **precompiled firmware binary** that is flashed with **Arduino CLI**.

---

## Table of Contents

- [Overview](#overview)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Repository Structure](#repository-structure)
- [Workflow](#workflow)
  - [1. Data Collection](#1-data-collection)
  - [2. Model Training](#2-model-training)
  - [3. Flash Prebuilt Firmware](#3-flash-prebuilt-firmware)
- [Signal Processing Pipeline](#signal-processing-pipeline)
- [Neural Network Architecture](#neural-network-architecture)
- [Motion Classes](#motion-classes)
- [Getting Started](#getting-started)
- [Notes](#notes)
- [Licenses](#licenses)

---

## Overview

This project demonstrates a TinyML human-activity-recognition workflow:

1. **Collect** raw 3-axis accelerometer data from the Arduino at 100 Hz and save it as CSV files.
2. **Train** a lightweight neural network in Python using FFT-based spectral features.
3. **Use the bundled firmware binary** to run real-time inference on the Arduino Nano 33 BLE Sense Rev2.

The trained firmware recognises four motion classes in real time:
**Clockwise**, **Horizontal**, **Idle**, and **Vertical**.

---

## Hardware Requirements

| Component | Details |
|-----------|---------|
| Arduino Nano 33 BLE Sense Rev2 | BMI270 + BMM150 IMU |
| USB cable | For programming and serial output |

---

## Software Requirements

### Bundled in this repository
- `arduino-cli_1.5.1_Windows_64bit.zip` — Windows Arduino CLI executable archive
- `arduino.mbed_nano.nano33ble/Arduino_HAR.ino.bin` — precompiled firmware image
- `libraries/Arduino_BMI270_BMM150/` — IMU library bundle
- `libraries/emlearn/` — emlearn Arduino headers
- `libraries/tinyml4all/` — helper library used by the data-capture sketch

### Python (training/reference)
- Python 3.x
- TensorFlow / Keras
- scikit-learn
- NumPy, pandas, matplotlib
- emlearn Python package

---

## Repository Structure

```text
emlearn-Human-Activity-Recognition/
├── CaptureMotionCSV/
│   └── CaptureMotionCSV.ino              # Arduino sketch for recording IMU data over Serial
├── data/
│   ├── clockwise.csv / .txt              # Clockwise motion samples
│   ├── horizontal.csv / .txt             # Horizontal motion samples
│   ├── idle.csv / .txt                   # Idle motion samples
│   └── vertical.csv / .txt               # Vertical motion samples
├── HAR_model_training.ipynb              # Source notebook for the training pipeline
├── HAR_model_training.html               # Rendered training notebook
├── HAR_model_training.pdf                # PDF export of the notebook
├── arduino-cli_1.5.1_Windows_64bit.zip   # Bundled Arduino CLI for Windows
├── arduino.mbed_nano.nano33ble/
│   ├── Arduino_HAR.ino.bin               # Prebuilt firmware flashed to the board
│   └── README.txt                        # Example `arduino-cli` upload commands
└── libraries/
    ├── Arduino_BMI270_BMM150/            # Bundled sensor library
    ├── emlearn/                          # Bundled emlearn headers
    └── tinyml4all/                       # Bundled helper library
```

---

## Workflow

### 1. Data Collection

Upload `CaptureMotionCSV/CaptureMotionCSV.ino` to the board, then open the Serial Monitor at **115200 baud**.

The sketch asks for:
- **Motion label** — `clockwise`, `horizontal`, `idle`, or `vertical`
- **Duration in minutes** — recording length

It then streams CSV rows such as:

```text
timestamp,accX,accY,accZ,motion
0,0.645237,-2.387019,5.018247,clockwise
10,0.905008,-2.613271,4.495114,clockwise
```

Save the captured output into the matching files under `/data`.

### 2. Model Training

`HAR_model_training.ipynb` documents the end-to-end training pipeline:

1. Load and merge the four motion datasets.
2. Apply a 4th-order Butterworth low-pass filter.
3. Segment the signal into overlapping windows.
4. Extract FFT-based spectral features from each axis.
5. Normalise features with `StandardScaler`.
6. Train a Keras neural network classifier.

The notebook is retained as training/reference material. The repository currently distributes the **compiled Arduino firmware** instead of the original Arduino inference source files.

### 3. Flash Prebuilt Firmware

The repository now ships the compiled firmware as `arduino.mbed_nano.nano33ble/Arduino_HAR.ino.bin`.

On Windows:

1. Extract `arduino-cli_1.5.1_Windows_64bit.zip`.
   To add the Arduino CLI to your system's environment variables, you must add the folder containing your arduino-cli executable to your system's PATH variable.
   This allows you to run arduino-cli from any terminal or command prompt window without typing its full directory path.
   - i. **Copy the path**: Locate the folder where you extracted arduino-cli.exe (e.g., C:\ArduinoCLI) and copy the full path from the File Explorer address bar.
   - ii. **Open System Properties**: Press the Windows Key, type Environment Variables, and select Edit the system environment variables.
   - iii. **Open Environment Variables**: Click the Environment Variables... button at the bottom right of the window.
   - iv. **Edit the Path variable**:
       - Under System variables (or User variables), scroll down and select Path.
       - Click Edit...
   - v. **Add your folder**: Click New, paste the folder path you copied in step 1, and click OK to close all windows.
   
  To verify that the operating system recognizes the tool globally, open a brand new terminal or command prompt window and run:
  ```bash
  arduino-cli version
  ```
2. Connect the Arduino Nano 33 BLE Sense Rev2.
3. Use Arduino CLI to detect the port:

   ```bash
   arduino-cli board list
   ```

4. Upload the bundled binary with the Nano 33 BLE FQBN:

   ```bash
   arduino-cli upload -p COM6 --fqbn arduino:mbed_nano:nano33ble -i .\arduino.mbed_nano.nano33ble\Arduino_HAR.ino.bin
   ```

Replace `COM6` with the port reported on your machine. A sample upload session is included in `arduino.mbed_nano.nano33ble/README.txt`.

After flashing, open the serial monitor to observe live motion predictions from the prebuilt model.

---

## Signal Processing Pipeline

```text
IMU (100 Hz)
    │
    ▼
4th-order Butterworth IIR low-pass filter
    │
    ▼
Sliding window segmentation
    │
    ▼
128-point FFT on 3 axes
    │
    ▼
Spectral feature extraction
    │
    ▼
StandardScaler normalisation
    │
    ▼
Neural network classifier
    │
    └──> { clockwise | horizontal | idle | vertical }
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
- **Epochs:** 30
- **Batch size:** 32

---

## Motion Classes

| Label | Description |
|-------|------------|
| `clockwise` | Wrist/hand rotating in a clockwise circular motion |
| `horizontal` | Lateral side-to-side motion |
| `idle` | No deliberate motion |
| `vertical` | Up-and-down motion |

---

## Getting Started

1. Clone the repository.
2. If needed, collect or review motion data using `CaptureMotionCSV/CaptureMotionCSV.ino` and the files in `data/`.
3. Review the training workflow in `HAR_model_training.ipynb`, `HAR_model_training.html`, or `HAR_model_training.pdf`.
4. Extract the bundled Arduino CLI archive.
5. Flash `arduino.mbed_nano.nano33ble/Arduino_HAR.ino.bin` with `arduino-cli upload`.
6. Open the serial monitor and verify the board prints live predicted labels.

---

## Notes

- The repository no longer includes the Arduino inference source sketch.
- The `libraries/` directory is bundled so the data-capture workflow and related Arduino dependencies are available locally.
- The upload command uses the board FQBN `arduino:mbed_nano:nano33ble`.

---

## Licenses

This repository includes third-party components with their own license files, including:
- `libraries/Arduino_BMI270_BMM150/LICENSE`
- `libraries/tinyml4all/LICENSE`
- `arduino-cli_1.5.1_Windows_64bit.zip` (`LICENSE.txt` inside the archive)

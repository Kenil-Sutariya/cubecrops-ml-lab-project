# CubeCrops ML Lab Project ☘️

## Overview
CubeCrops is an AI-driven system designed to analyze the health of radish microgreens using various sensor data and image processing techniques. The project integrates IoT devices, machine learning models, and a Flask-based API to collect, process, and visualize plant health metrics.

## Project Components
### 1. Data Collection
- Uses ESP32-CAM for capturing images.
- Arduino sensors for collecting biomass and environmental data.
- Data is transmitted via a Flask API to a cloud or local server for further processing.

### 2. Machine Learning Models
- **LeafBoxBounding.pt** - Detects leaf bounding boxes for plant health assessment.
- **PigmentAnalysis.keras** (Keras) - Analyzes plant pigment levels to determine chlorophyll content.

### 3. Data Processing & Analysis
- **Colab Notebooks** for running the health scoring system and full pipeline analysis.
- **Flask API** processes and transmits data to the dashboard.

## Setup & Installation
### Prerequisites
- Python 3.x
- Arduino IDE for microcontroller programming (Version: 
- Flask for API development
- Keras for running ML models
- OpenCV for image processing

### Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/Kenil-Sutariya/cubecrops-ml-lab-project.git
   cd cubecrops-ml-lab-project
   ```
2. Install dependencies:
   ```bash
   pip install -r requirements.txt
   ```
3. Deploy the Flask API:
   ```bash
   python Flask_code_VM.py
   ```
4. Upload Arduino scripts to ESP32 and sensors.
5. Run Colab notebooks for data analysis.

## Usage
1. Deploy the camera and sensors in the target environment.
2. Collect and transmit data to the Flask API.
3. Process the collected data using machine learning models.
4. Visualize results in Google Colab or a dashboard.

## File Descriptions
camera.ino – The main Arduino sketch that initializes and controls the camera module.
app_httpd.cpp – Handles HTTP server functions, allowing the camera to stream video over a web interface.
camera_index.h – Contains HTML and JavaScript code for the web interface that displays the camera feed.
camera_pins.h – Defines the GPIO pin configuration for the camera module.

### Required libraries for Arduino IDE

1. SP32-Specific Libraries:
esp_camera.h
esp_http_server.h 
esp_timer.h 
sdkconfig.h
esp32-hal-ledc.h

2. Common Sensor Libraries:
DHT.h 
Wire.h 
Adafruit_Sensor.h 
Adafruit_BMP280.h 
Adafruit_SHT31.h 
HX711.h
esp_http_server.h
esp_camera.h

### Method to install required libraries in Arduino IDE:
1. Open Arduino IDE.
2. Go to Sketch → Include Library → Manage Libraries.
3. Search for each of the following libraries and click Install

### How to Use Arduino IDE

1. Open camera.ino in the Arduino IDE.
2. Ensure all required libraries (like esp_camera.h for ESP32-CAM) are installed.
3. Connect your camera module to the microcontroller.
4. Upload the sketch to your board.
5. If using a web stream, find the IP address printed in the Serial Monitor.

### Reference links:
1. How to make use load Cell sensor with Arduino : https://www.youtube.com/watch?v=pWiS-oW3Snc&t=262s
2. How to make use height Cell sensor with Arduino : https://www.youtube.com/watch?v=n-gJ00GTsNg&t=60s
3. How to make use temperature and humidity sensor with Arduino : https://www.youtube.com/watch?v=1AgcNQ-J0Y8
4. How to make use camera with FDTI sensor with Arduino : https://www.youtube.com/watch?v=JYchUapoqzc

## Sensors & Connections

| Sensor         | Pin  | Connection       |
|--------------|------|-----------------|
| **DHT22**     | VCC  | 5V             |
|              | Data  | D2             |
|              | GND   | GND            |
| **HX711**    | VCC  | 5V             |
|              | GND   | GND            |
|              | DT    | D4             |
|              | SCK   | D5             |
| **HC-SR04 1** | VCC  | 5V             |
|              | Trig  | D7             |
|              | Echo  | D6             |
|              | GND   | GND            |
| **HC-SR04 2** | VCC  | 5V             |
|              | Trig  | D8             |
|              | Echo  | D9             |
|              | GND   | GND            |
| **ESP32 Camera** | VCC  | 5V (FTDI VCC) |
|                  | GND  | GND (FTDI GND) |
|                  | TX   | RX (FTDI Module) |
|                  | RX   | TX (FTDI Module) |


## Repository Structure
```
cubecrops-ml-lab-project/
│
├── colab_notebooks/            # Contains Google Colab notebooks for running the CubeCrops pipeline
│   ├── health_scoring_system.ipynb  # Notebook for calculating the health scoring system
│   └── full_pipeline.ipynb         # Notebook for running the complete CubeCrops pipeline
│
├── models/                    # Pre-trained AI models
│   ├── LeafBoxBounding.pt      # PyTorch model for leaf bounding box detection
│   └── PigmentAnalysis.keras   # Keras model for pigment analysis
│
├── camera_files/               # ESP32-CAM firmware and configurations
│   ├── app_httpd.cpp           # HTTP server for camera streaming
│   ├── camera.ino              # Arduino script for camera module
│   ├── camera_index.h          # Web interface for the camera
│   ├── camera_pins.h           # Camera pin definitions
│
├── sensors_files/              # Sensor data processing scripts
│   ├── biomass.ino             # Arduino script for biomass sensor
│   ├── camera_stream.py        # Python script for handling camera stream
│   ├── sketch_jan29b.ino       # Additional Arduino sketch for sensor handling
│
├── Flask_code_VM.py            # Flask server script for data transmission and processing
├── readme.md                   # Project documentation (this file)
```

## Project Contributors

1. **Kenil Sutariya** 
2. **Niket Kapoor** 
3. **Shree Shangaavi Nagaraj**
4. **Faezeh Moradi**
5. **Hannah Heyne** 

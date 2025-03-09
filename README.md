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
- Arduino IDE for microcontroller programming
- Flask for API development
- Keras for running ML models
- OpenCV for image processing

### Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/cubecrops-ml-lab-project.git
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

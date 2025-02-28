# Cubecrops-ml-lab-project


CubeCrops is a smart agricultural system that utilizes AI models to analyze microgreen crops and provide health scoring based on various parameters such as pigment analysis, height, and biomass. This repository contains the core components of the CubeCrops project, including Colab notebooks and pre-trained models.


# Project Overview

The CubeCrops system is designed to:

Detect leaves and their boundaries using a bounding box model.

Analyze the pigment composition of microgreens to estimate chlorophyll content.

Measure crop height and calculate biomass through image-based techniques.

Generate an overall health score based on the combined analysis.

# Prerequisites

The following dependencies are required to run the project:

Python 3.x

Google Colab (for notebooks)

PyTorch

TensorFlow

NumPy

Pandas

OpenCV

Scikit-learn

Matplotlib


# Installation

```
Clone the repository:
git clone https://github.com/Kenil-Sutariya/cubecrops-ml-lab-project.git
cd cubecrops-ml-lab-project
```

Install dependencies
```
pip install -r requirements.txt
```
# How to Run

Upload the models from the models folder to your Google Colab session.

Open the respective notebook from the colab_notebooks folder.

Follow the instructions provided in the notebook to run either the health scoring system or the full pipeline.

```
cubecrops-ml-lab-project/
│
├── colab_notebooks/            # Contains Google Colab notebooks for running the CubeCrops pipeline
│   ├── health_scoring_system.ipynb  # Notebook for calculating the health scoring system
│   └── full_pipeline.ipynb         # Notebook for running the complete CubeCrops pipeline
│
└── models/                    # Pre-trained AI models
    ├── LeafBoxBounding.pt      # PyTorch model for leaf bounding box detection
    └── PigmentAnalysis.keras   # Keras model for pigment analysis
```

#include <HX711_ADC.h>
#include <EEPROM.h>

// Pins for HX711
const int HX711_dout = 4; // HX711 data pin
const int HX711_sck = 5;  // HX711 clock pin

// HX711 constructor
HX711_ADC LoadCell(HX711_dout, HX711_sck);

const int calVal_eepromAdress = 0; // EEPROM address for storing calibration value
unsigned long t = 0;

void setup() {
  Serial.begin(57600);
  delay(10);
  Serial.println("Starting...");

  // Initialize the load cell
  LoadCell.begin();
  unsigned long stabilizingtime = 2000; // Stabilizing time in ms
  bool _tare = true;                   // Perform tare on startup
  LoadCell.start(stabilizingtime, _tare);

  if (LoadCell.getTareTimeoutFlag() || LoadCell.getSignalTimeoutFlag()) {
    Serial.println("Timeout, check wiring and pin configurations.");
    while (1);
  } else {
    Serial.println("Load Cell Startup Complete.");
    LoadCell.setCalFactor(1.0); // Default calibration factor
  }

  while (!LoadCell.update());
  calibrate(); // Start the calibration process
}

void loop() {
  static bool newDataReady = false;
  const int serialPrintInterval = 1000; // Print every 1 second

  // Check for new data
  if (LoadCell.update()) newDataReady = true;

  // Get smoothed value from the load cell
  if (newDataReady) {
    if (millis() > t + serialPrintInterval) {
      float value = LoadCell.getData();
      Serial.print("Load Cell Output Value: ");
      Serial.println(value);
      newDataReady = false;
      t = millis();
    }
  }

  // Receive commands from the Serial Monitor
  if (Serial.available() > 0) {
    char inByte = Serial.read();
    if (inByte == 't') {
      LoadCell.tareNoDelay(); // Perform tare
    } else if (inByte == 'r') {
      calibrate(); // Start calibration
    } else if (inByte == 'c') {
      changeSavedCalFactor(); // Change calibration factor manually
    }
  }

  // Check if tare operation is complete
  if (LoadCell.getTareStatus()) {
    Serial.println("Tare complete.");
  }
}

void calibrate() {
  Serial.println("***");
  Serial.println("Start Calibration");
  Serial.println("Place the load cell on a stable, level surface and remove all weights.");
  Serial.println("Send 't' from Serial Monitor to tare the load cell.");

  bool _resume = false;
  while (!_resume) {
    LoadCell.update();
    if (Serial.available() > 0) {
      char inByte = Serial.read();
      if (inByte == 't') {
        LoadCell.tareNoDelay();
      }
    }
    if (LoadCell.getTareStatus()) {
      Serial.println("Tare complete.");
      _resume = true;
    }
  }

  Serial.println("Place a known weight on the load cell.");
  Serial.println("Send the weight value (e.g., 100.0) from Serial Monitor.");

  float known_mass = 0;
  _resume = false;
  while (!_resume) {
    LoadCell.update();
    if (Serial.available() > 0) {
      known_mass = Serial.parseFloat();
      if (known_mass != 0) {
        Serial.print("Known mass is: ");
        Serial.println(known_mass);
        _resume = true;
      }
    }
  }

  // Calculate and store calibration value
  LoadCell.refreshDataSet();
  float newCalibrationValue = LoadCell.getNewCalibration(known_mass);
  Serial.print("New calibration value: ");
  Serial.println(newCalibrationValue);

  // Save calibration value to EEPROM
  EEPROM.put(calVal_eepromAdress, newCalibrationValue);
  float readValue;
  EEPROM.get(calVal_eepromAdress, readValue);
  Serial.print("Calibration value saved to EEPROM: ");
  Serial.println(readValue);

  Serial.println("Calibration complete.");
}

void changeSavedCalFactor() {
  float oldCalibrationValue = LoadCell.getCalFactor();
  Serial.println("***");
  Serial.print("Current calibration value: ");
  Serial.println(oldCalibrationValue);
  Serial.println("Enter a new calibration value (e.g., 123.45):");

  float newCalibrationValue = 0;
  bool _resume = false;
  while (!_resume) {
    if (Serial.available() > 0) {
      newCalibrationValue = Serial.parseFloat();
      if (newCalibrationValue != 0) {
        Serial.print("New calibration value: ");
        Serial.println(newCalibrationValue);
        LoadCell.setCalFactor(newCalibrationValue);
        _resume = true;
      }
    }
  }

  // Save new calibration value to EEPROM
  EEPROM.put(calVal_eepromAdress, newCalibrationValue);
  float readValue;
  EEPROM.get(calVal_eepromAdress, readValue);
  Serial.print("New calibration value saved to EEPROM: ");
  Serial.println(readValue);

  Serial.println("Calibration factor updated.");
}

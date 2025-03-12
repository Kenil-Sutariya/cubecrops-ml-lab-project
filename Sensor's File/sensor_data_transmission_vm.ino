#include <WiFiS3.h>
#include <ArduinoHttpClient.h>
#include "DHT.h"

// WiFi Credentials
const char* ssid = "************";         // Your WiFi network name
const char* password = "***********"; // Your WiFi password

// Flask API Details
const char* serverAddress = "*********";  // Your server domain
const int serverPort = ***;  // HTTPS Port

WiFiSSLClient wifi;           
HttpClient client(wifi, serverAddress, serverPort);  

const char* authToken = "*********";  // Authorization token

// **Ultrasonic Sensor Pins**
const int trig1 = 7, echo1 = 6;  // Height Sensor 1
const int trig2 = 8, echo2 = 9;  // Height Sensor 2

// **DHT Sensor Configuration**
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    Serial.println(F("Initializing Sensors..."));

    // **Connect to WiFi**
    Serial.print("Connecting to WiFi...");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("\n✅ Connected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // **Initialize Sensors**
    pinMode(trig1, OUTPUT);
    pinMode(echo1, INPUT);
    pinMode(trig2, OUTPUT);
    pinMode(echo2, INPUT);
    dht.begin();

    Serial.println(F("✅ Sensors Initialized!"));

    // **Test sending data**
    sendData();
}

void loop() {
    // **Send sensor data every 30 minutes**
    sendData();
    delay(600000);  // 30 minutes (1,800,000 ms)
}

// **Function to send sensor data to the Flask API**
void sendData() {
    Serial.println(F("📡 Collecting Sensor Data..."));

    // **Measure Height Sensors**
    int height1 = getDistance(trig1, echo1);
    int height2 = getDistance(trig2, echo2);

    // **Measure Temperature & Humidity**
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    // **Check for sensor errors**
    if (isnan(humidity) || isnan(temperature)) {
        Serial.println(F("❌ Error: Failed to read from DHT sensor!"));
        return;
    }

    // **Create API Request URL**
    String url = "/shree/api/ping?height_1=" + String(height1) +
                 "&height_2=" + String(height2) +
                 "&temperature=" + String(temperature) +
                 "&humidity=" + String(humidity);

    Serial.println("🌍 Sending data to API: " + url);

    // **Send GET request**
    client.beginRequest();
    client.get(url);
    client.sendHeader("Authorization", authToken);  
    client.sendHeader("Connection", "close");       
    client.endRequest();

    // **Check API Response**
    int statusCode = client.responseStatusCode();
    String response = client.responseBody();

    Serial.print("📡 API Response Code: ");
    Serial.println(statusCode);
    Serial.println("📩 Response:");
    Serial.println(response);

    if (statusCode == 200) {
        Serial.println(F("✅ Data sent successfully!"));
    } else {
        Serial.println(F("❌ Failed to send data. Check your server."));
    }
}

// **Function to get distance from Ultrasonic Sensors**
int getDistance(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    int distance = duration * 0.034 / 2;  // Convert to cm
    return distance;
}

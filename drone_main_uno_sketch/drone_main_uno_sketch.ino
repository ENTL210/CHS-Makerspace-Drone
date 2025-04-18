#include <SoftwareSerial.h>

// Define the RX and TX pins you'll use for communication with the ESP32
const int rxPin = 11; // Example: Arduino RX pin connected to ESP32 TX pin
const int txPin = 12; // Example: Arduino TX pin connected to ESP32 RX pin

SoftwareSerial espSerial(rxPin, txPin);

// Make sure to define your UART port (Serial1)
void setup() {
  Serial.begin(115200); // For debug output via USB
  espSerial.begin(115200); // For receiving data from ESP32

  Serial.println("Arduino ready to receive gyro data...");
}

void loop() {
  // Check if there are enough bytes to read
  if (espSerial.available() >= sizeof(float) * 3) {
    float gyroData[3]; // Array to store incoming gyro data

    // Read the 3 floats (12 bytes total)
    for (int i = 0; i < 3; i++) {
      byte data[4];
      espSerial.readBytes(data, 4);  // Read 4 bytes for one float
      gyroData[i] = *(float*)data; // Cast bytes into float and store
    }

    // Print the gyro values received from ESP32
    Serial.print("Gyro X: "); Serial.print(gyroData[0]);
    Serial.print(" | Gyro Y: "); Serial.print(gyroData[1]);
    Serial.print(" | Gyro Z: "); Serial.println(gyroData[2]);

    // Here, you could implement further logic like sending data to motors or other control actions

  }
  else {
    Serial.println("No Data");
  }
  delay(10);  // Optional delay to limit the read rate
}

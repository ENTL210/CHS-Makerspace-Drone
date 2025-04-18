#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);
  Serial1.begin(115200);
  Wire.begin(21,22);

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("MPU6050 ready!");
}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float gyroData[3] = {
    g.gyro.x,
    g.gyro.y,
    g.gyro.z
  };

  Serial1.write((uint8_t*)gyroData, sizeof(gyroData));

  Serial.print("Gyro X: "); Serial.print(gyroData[0]);
  Serial.print(" | Y: "); Serial.print(gyroData[1]);
  Serial.print(" | Z: "); Serial.println(gyroData[2]);
  
  delay(10);

}


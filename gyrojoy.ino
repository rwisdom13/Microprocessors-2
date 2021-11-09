#include<Wire.h>

int JoyX;
int JoyY;
int setting = 1;
int apple_buzzer = 0;

const int axisX = A0;
const int axisY = A1;
const int buzzer = 2;
const int MPU_addr = 0x68;
int16_t AccelX;
int16_t AccelY;
int16_t AccelZ;
int16_t Tmp;
int16_t GyroX;
int16_t GyroY;
int16_t GyroZ;

void setup(){
  Serial.begin(9600);
  
  Wire.begin();
  Wire.beginTransmission(MPU_addr);

  Wire.write(0x68);
  Wire.write(0);
  
  Wire.endTransmission(true);
  
  pinMode(axisX, INPUT);
  pinMode(axisY, INPUT);
}

void loop() {
  noTone(buzzer);
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x38);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  
  AccelX = Wire.read() << 8 | Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AccelY = Wire.read() << 8 | Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AccelZ = Wire.read() << 8 | Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyroX = Wire.read() << 8 | Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyroY = Wire.read() << 8 | Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyroZ = Wire.read() << 8 | Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
  JoyX = analogRead(axisX);
  JoyY = analogRead(axisY);

  if (setting == 0) {
    Serial.print(JoyX);
    Serial.print(',');
    Serial.println(JoyY);
  }

  if (setting == 1) {
    Serial.print(AccelX);
    Serial.print(',');
    Serial.println(AccelY);
  }

  if (Serial.available() > 0){
    apple_buzzer = Serial.read();
  }

  if (apple_buzzer = 'E'){
    tone(buzzer, 1000); // Send 1KHz sound signal...
    apple_buzzer = 0;
  }




  delay(300);
}

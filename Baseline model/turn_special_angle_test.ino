#include <AFMotor.h>
#include <NewPing.h>
#include <Wire.h>
#include <LIS3MDL.h>
#include <LSM6.h>

LIS3MDL mag;
LSM6 imu;

#define TRIGGER_PIN  25  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     23  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
AF_DCMotor motor1(1);  // 左前轮
AF_DCMotor motor2(2);  // 左后轮
AF_DCMotor motor3(3);  // 右后轮
AF_DCMotor motor4(4);  // 右前轮

LIS3MDL::vector<int16_t> m_min = {-32767, -32767, -32767};
LIS3MDL::vector<int16_t> m_max = {+32767, +32767, +32767};

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  if (!mag.init())
  {
    Serial.println("Failed to detect and initialize LIS3MDL magnetometer!");
    while (1);
  }
  mag.enableDefault();

  if (!imu.init())
  {
    Serial.println("Failed to detect and initialize LSM6 IMU!");
    while (1);
  }
  imu.enableDefault();
}

void loop() {
  mag.read();
  imu.read();
  float heading = computeHeading();
  Serial.println(heading);
  delay(100);
}

void leftTurn() {
  motor1.setSpeed(150);   // 设置电机1的速度为150
  motor2.setSpeed(150);   // 设置电机2的速度为150
  motor3.setSpeed(255);   // 设置电机3的速度为255
  motor4.setSpeed(255);   // 设置电机4的速度为255

  motor1.run(BACKWARD);   // 电机1反转
  motor2.run(BACKWARD);   // 电机2反转
  motor3.run(FORWARD);    // 电机3正转
  motor4.run(FORWARD);    // 电机4正转
}

template <typename T> float computeHeading(LIS3MDL::vector<T> from)
{
  LIS3MDL::vector<int32_t> temp_m = {mag.m.x, mag.m.y, mag.m.z};

  // copy acceleration readings from LSM6::vector into an LIS3MDL::vector
  LIS3MDL::vector<int16_t> a = {imu.a.x, imu.a.y, imu.a.z};

  // subtract offset (average of min and max) from magnetometer readings
  temp_m.x -= ((int32_t)m_min.x + m_max.x) / 2;
  temp_m.y -= ((int32_t)m_min.y + m_max.y) / 2;
  temp_m.z -= ((int32_t)m_min.z + m_max.z) / 2;

  // compute E and N
  LIS3MDL::vector<float> E;
  LIS3MDL::vector<float> N;
  LIS3MDL::vector_cross(&temp_m, &a, &E);
  LIS3MDL::vector_normalize(&E);
  LIS3MDL::vector_cross(&a, &E, &N);
  LIS3MDL::vector_normalize(&N);

  // compute heading
  float heading = atan2(LIS3MDL::vector_dot(&E, &from), LIS3MDL::vector_dot(&N, &from)) * 180 / PI;
  if (heading < 0) heading += 360;
  return heading;
}

float computeHeading()
{
  return computeHeading((LIS3MDL::vector<int>){1, 0, 0});
}
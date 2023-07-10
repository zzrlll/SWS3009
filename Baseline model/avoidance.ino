#include <AFMotor.h>
#include <NewPing.h>

#define TRIGGER_PIN  25  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     23  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
AF_DCMotor motor1(1);  // 左前轮
AF_DCMotor motor2(2);  // 左后轮
AF_DCMotor motor3(3);  // 右后轮
AF_DCMotor motor4(4);  // 右前轮

void setup() {
  Serial.begin(115200);
  Serial3.begin(9600);
}

void loop() {
  if (Serial3.available() > 0) {
    // Read a byte from the serial port
    int receivedByte = Serial3.read();
    // Perform the handshake
    if (receivedByte == 'w') {
      forward();
    }
    if (receivedByte == 'a') {
      leftTurn();
    }
    if (receivedByte == 's') {
      backward();
    }
    if (receivedByte == 'd') {
      rightTurn();
    }
    if (receivedByte == 'v') {
      avoidance();
    }
    if (receivedByte == 'q') {
      stop();
    }
  }
}

// 向前行驶
void forward() {
  motor1.setSpeed(200);  // 设置电机1的速度
  motor2.setSpeed(200);  // 设置电机2的速度
  motor3.setSpeed(200);  // 设置电机3的速度
  motor4.setSpeed(200);  // 设置电机4的速度
  motor1.run(FORWARD);  // 电机1正转
  motor2.run(FORWARD);  // 电机2正转
  motor3.run(FORWARD);  // 电机3正转
  motor4.run(FORWARD);  // 电机4正转
}

// 向后行驶
void backward() {
  motor1.setSpeed(200);  // 设置电机1的速度
  motor2.setSpeed(200);  // 设置电机2的速度
  motor3.setSpeed(200);  // 设置电机3的速度
  motor4.setSpeed(200);  // 设置电机4的速度
  motor1.run(BACKWARD);  // 电机1反转
  motor2.run(BACKWARD);  // 电机2反转
  motor3.run(BACKWARD);  // 电机3反转
  motor4.run(BACKWARD);  // 电机4反转
}

// 左转弯
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

// 右转弯
void rightTurn() {
  motor1.setSpeed(255);   // 设置电机1的速度为255
  motor2.setSpeed(255);   // 设置电机2的速度为255
  motor3.setSpeed(150);   // 设置电机3的速度为150
  motor4.setSpeed(150);   // 设置电机4的速度为150

  motor1.run(FORWARD);    // 电机1正转
  motor2.run(FORWARD);    // 电机2正转
  motor3.run(BACKWARD);   // 电机3反转
  motor4.run(BACKWARD);   // 电机4反转
}

//避障
void avoidance() {
  int leftcount=0;
  int receivedByte=0;
  bool flg=0;
  unsigned long elapsed=millis(),cur=millis();
  while(leftcount<5) {
    motor1.setSpeed(150);  // 设置电机1的速度
    motor2.setSpeed(150);  // 设置电机2的速度
    motor3.setSpeed(150);  // 设置电机3的速度
    motor4.setSpeed(150);  // 设置电机4的速度
    motor1.run(FORWARD);  // 电机1正转
    motor2.run(FORWARD);  // 电机2正转
    motor3.run(FORWARD);  // 电机3正转
    motor4.run(FORWARD);  // 电机4正转
    while(1)
    {
      delay(50);
      if (Serial3.available() > 0) {
        // Read a byte from the serial port
        receivedByte = Serial3.read();
        // Perform the handshake
        if (receivedByte == 'q') {
          stop();
          flg=1;
          break;
        }
      }
      if(sonar.ping_cm()<=20 && sonar.ping_cm()>0) {
        leftcount++;
        avoidleft(leftcount);
        break;
      }
    }
    if(flg)
      break;
  }
}

// 左转弯
void avoidleft(int leftcount) {
  motor1.run(RELEASE);  // 释放电机1，停止转动
  motor2.run(RELEASE);  // 释放电机2，停止转动
  motor3.run(RELEASE);  // 释放电机3，停止转动
  motor4.run(RELEASE);  // 释放电机4，停止转动
  Serial3.print("Distance:");
  Serial3.println(sonar.ping_cm());
  delay(2000);
  motor1.setSpeed(150);   // 设置电机1的速度为150
  motor2.setSpeed(150);   // 设置电机2的速度为150
  motor3.setSpeed(255);   // 设置电机3的速度为255
  motor4.setSpeed(255);   // 设置电机4的速度为255
  motor1.run(BACKWARD);   // 电机1反转
  motor2.run(BACKWARD);   // 电机2反转
  motor3.run(FORWARD);    // 电机3正转
  motor4.run(FORWARD);    // 电机4正转
  delay(1000);
  motor1.run(RELEASE);  // 释放电机1，停止转动
  motor2.run(RELEASE);  // 释放电机2，停止转动
  motor3.run(RELEASE);  // 释放电机3，停止转动
  motor4.run(RELEASE);  // 释放电机4，停止转动
  delay(2000);
}

// 停止
void stop() {
  motor1.run(RELEASE);  // 释放电机1，停止转动
  motor2.run(RELEASE);  // 释放电机2，停止转动
  motor3.run(RELEASE);  // 释放电机3，停止转动
  motor4.run(RELEASE);  // 释放电机4，停止转动
}
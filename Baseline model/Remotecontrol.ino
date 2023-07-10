#include <AFMotor.h>

AF_DCMotor motor1(1);  // 左前轮
AF_DCMotor motor2(2);  // 左后轮
AF_DCMotor motor3(3);  // 右后轮
AF_DCMotor motor4(4);  // 右前轮

void setup() {
  Serial3.begin(9600);
  motor1.setSpeed(200);  // 设置电机1的速度
  motor2.setSpeed(200);  // 设置电机2的速度
  motor3.setSpeed(200);  // 设置电机3的速度
  motor4.setSpeed(200);  // 设置电机4的速度
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
void rightTurn() {
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
void leftTurn() {
  motor1.setSpeed(255);   // 设置电机1的速度为255
  motor2.setSpeed(255);   // 设置电机2的速度为255
  motor3.setSpeed(150);   // 设置电机3的速度为150
  motor4.setSpeed(150);   // 设置电机4的速度为150

  motor1.run(FORWARD);    // 电机1正转
  motor2.run(FORWARD);    // 电机2正转
  motor3.run(BACKWARD);   // 电机3反转
  motor4.run(BACKWARD);   // 电机4反转
}

// 停止
void stop() {
  motor1.run(RELEASE);  // 释放电机1，停止转动
  motor2.run(RELEASE);  // 释放电机2，停止转动
  motor3.run(RELEASE);  // 释放电机3，停止转动
  motor4.run(RELEASE);  // 释放电机4，停止转动
}

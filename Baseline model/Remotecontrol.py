import cv2
import serial
import time

# 打开摄像头
cap = cv2.VideoCapture(0)

# 设置视频流的分辨率
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

# 打开串口
ser = serial.Serial('/dev/ttyS0', 9600)  # 根据需要修改串口路径和波特率

def send_command(command):
    # 发送指令给Arduino
    ser.write(command)

# 创建一个窗口来显示摄像头图像
cv2.namedWindow('Camera', cv2.WINDOW_NORMAL)

print("use keyboard to control:")
print("w: forward")
print("s: backward")
print("a: left")
print("d: right")
print("q: quit")
print("C: photo")
print("E: exit")

photo_counter = 0  # 照片计数器

while True:
    # 读取摄像头图像帧
    ret, frame = cap.read()

    # 检查是否成功读取帧
    if not ret:
        break

    # 在窗口中显示摄像头图像
    cv2.imshow('Camera', frame)

    # 检查键盘输入
    key = cv2.waitKey(1) & 0xFF

    # 发送指令给Arduino
    if key == ord('w'):
        send_command(b'w')
        print("forward")
    elif key == ord('s'):
        send_command(b's')
        print("backward")
    elif key == ord('a'):
        send_command(b'a')
        print("left")
    elif key == ord('d'):
        send_command(b'd')
        print("right")
    elif key == ord('q'):
        send_command(b'q')
        print("stop")
    elif key == ord('C'):
        photo_name = f"photo_{photo_counter}.jpg"  # 图片文件名
        cv2.imwrite(photo_name, frame)
        print(f"拍照并保存为 {photo_name}")
        photo_counter += 1
    elif key == ord('e') or key == ord('E'):
        break

# 释放摄像头资源
cap.release()

# 关闭串口
ser.close()

# 关闭窗口
cv2.destroyAllWindows()


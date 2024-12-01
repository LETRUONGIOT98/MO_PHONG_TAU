
#include <Servo.h>

Servo myServo;
int banDau = 120; // Vị trí ban đầu của servo 
int toiThieu = 120; // Giới hạn tối thiểu của servo
int toiDa = 180; // Giới hạn tối đa của servo
bool stopButtonPressed = true, tt = true; // Biến để kiểm tra nút dừng đã được nhấn hay chưa
bool tien = false; // Biến để kiểm tra nút tiến đã được nhấn hay chưa
int i =0;
void setup() {
  Serial.begin(9600); // Khởi tạo giao tiếp Serial
  myServo.attach(10); // Kết nối servo vào chân số 9
  pinMode(2, INPUT_PULLUP); // Nút tiến
  pinMode(3, INPUT_PULLUP); // Nút dừng
  pinMode(4, INPUT_PULLUP); // Nút lùi
  pinMode(5, INPUT_PULLUP); // Nút tăng ga
  pinMode(6, INPUT_PULLUP); // Nút giảm ga chậm
  pinMode(7, INPUT_PULLUP); // Nút giảm ga nhanh
  pinMode(8, INPUT_PULLUP); // Nút giảm đột ngột
  pinMode(9, INPUT_PULLUP); // Nút đề
  myServo.write(banDau);
  Serial.println("OK");
}
void loop() {
  // Đọc trạng thái của các nút và xử lý
  if (digitalRead(9) == LOW) { // Nút đề
    if (tt == true) {
      tt = false;
      stopButtonPressed = true;
      tien = true;
     /* banDau = banDau + 30;
      myServo.write(banDau);*/
      Serial.println("DE");
      banDau = 120;
      myServo.write(banDau);
      delay(100);
    }
  }
  while (digitalRead(9) == HIGH) { // Nút đề
    tt = true;
    myServo.write(0);
  }
  if (digitalRead(2) == LOW) { // Nút tiến
    if (stopButtonPressed) {
      
      stopButtonPressed = false;
      tien = true;
      banDau = banDau - 30;
      myServo.write(banDau);
      Serial.println("TIEN");
      delay(500);
      
      banDau = 120;
      myServo.write(banDau);
    }
  }
  else if (digitalRead(3) == LOW && stopButtonPressed == false && banDau <= 120) { // Nút dừng
    stopButtonPressed = true;
    tien = false;
    banDau = banDau + 25;
    myServo.write(banDau);
    Serial.println("DUNG");
    delay(500);
    banDau = 120;
    myServo.write(banDau);
  }
  else if (digitalRead(4) == LOW && stopButtonPressed == true) { // Nút lùi
    banDau = banDau - 30;
    
    stopButtonPressed = false;
    myServo.write(banDau);
    tien = false;
    Serial.println("LUI.");
    delay(500);
    
    banDau = 120;
    myServo.write(banDau);
  }
  
   if (digitalRead(5) == LOW && tien == true) { // Nút tăng ga
    bool c = true;
    while(digitalRead(5)== 0 && i <= 3){
      delay(50);
    if(c == true){
    c = false;
    i +=1 ;
    Serial.println(i);
    }
  }

  if(i >= 4){
    while (digitalRead(5) == LOW && banDau < toiDa) {
      Serial.println("TANG");
      banDau += 1;
      myServo.write(banDau);
      delay(40);
    }
    Serial.println("Nút tăng ga đã được nhấn.");
  }
  }

  
  if (digitalRead(6) == LOW && tien == true) { // Nút giảm ga chậm
    while (digitalRead(6) == LOW && banDau > toiThieu) {
      banDau -= 1;
      myServo.write(banDau);
      if(banDau <= toiThieu){
    i=0;
  }
      delay(40);
    }
    Serial.println("Nút giảm ga chậm đã được nhấn.");
  }
  else if (digitalRead(7) == LOW && tien == true) { // Nút giảm ga nhanh
    while (digitalRead(7) == LOW && banDau > toiThieu) {
      Serial.println("GIAM GA");
      banDau -= 2;
      myServo.write(banDau);
      if(banDau <= toiThieu){
    i=0;
  }
  
      delay(40);
    }
    Serial.println("Nút giảm ga nhanh đã được nhấn.");
  }
  else if (digitalRead(8) == LOW && tien) { // Nút giảm đột ngột
    banDau = 120;
    myServo.write(banDau);
    if(banDau <= toiThieu){
    i=0;
  }
  
    Serial.println("GIAM DOT NGOT.");
  }

  // Đặt vị trí servo
  
}

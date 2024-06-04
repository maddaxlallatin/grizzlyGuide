#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <ezButton.h>

char x;
String room = "";
const int StepX = 2;
const int DirX = 5;
const int StepY = 3;
const int DirY = 6;
const int rotations = 15;
const double constant = 3.56;




ezButton limitSwitch1(9);
ezButton limitSwitch2(10);


void setup() {

  pinMode(StepX, OUTPUT);
  pinMode(DirX, OUTPUT);
  pinMode(StepY, OUTPUT);
  pinMode(DirY, OUTPUT);

  pinMode(8, OUTPUT);

  digitalWrite(8, LOW);
  // Define the LED pin as Output
  pinMode(LED_BUILTIN, OUTPUT);
  // Start the I2C Bus as Slave on address 9
  Wire.begin(9);
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  digitalWrite(LED_BUILTIN, LOW);
}

void receiveEvent(int bytes) {

  x = Wire.read();
  if (x == 'R') {
    resetRoom();
  } else {
    room += x;

  }
}

void loop() {
  Serial.println(room);


if(room[0] == 'A'){
if(room == "A0"){
    home();
    delay(3000);
    moveLeft(6);
    moveUp(9);
    moveLeft(13.5);
    moveUp(20.5);
    moveLeft(18);
    moveUp(8);
    resetRoom();
    return;
    }
    room.remove(0, 1);

  int temp = (room.toInt()/10);

    if(temp>= 116 && temp<= 124){
      home();
      delay(3000);
    moveLeft(6);
    moveUp(9);
    moveLeft(13.5);
    moveUp(20.5);
    moveLeft(10);
    
    resetRoom();
    return;
    }

    if(temp>=101 && temp<=110){
       home();
      delay(3000);
    moveLeft(6);
    moveUp(9);
    moveLeft(13.5);
    moveUp(34);
    moveLeft(10);
    
    resetRoom();
    return;
    }
    
if(temp>= 111 && temp<= 115){
    home();
    delay(3000);
    moveLeft(6);
    moveUp(9);
    moveLeft(13.5);
    moveUp(20.5);
    moveLeft(18);
    moveUp(8);
    resetRoom();
    return;
    }
    
    

}

else if(room[0] == 'B'){
  if(room == "B0"){
     home();
    delay(3000);
    moveLeft(6);
    moveUp(9);
    moveLeft(5.5);
    moveUp(20.5);
    moveRight(17);
    moveUp(8);
    resetRoom();
    return;
  }
  room.remove(0, 1);

  int temp = (room.toInt()/10);

    if(temp>= 116 && temp<= 124){
    home();
    delay(3000);
    moveLeft(6);
    moveUp(9);
    moveLeft(5.5);
    moveUp(20.5);
    moveRight(9);
    resetRoom();
    return;
    
    }

    if(temp>=101 && temp<=110){
     home();
    delay(3000);
    moveLeft(6);
    moveUp(9);
    moveLeft(5.5);
    moveUp(35);
    moveRight(14);
    resetRoom();
    return;
     
    }
    
if(temp>= 111 && temp<= 115){
    home();
    delay(3000);
    moveLeft(6);
    moveUp(9);
    moveLeft(5.5);
    moveUp(20.5);
    moveRight(17);
    moveUp(8);
    resetRoom();
    return;
    
    }
    
}

else if(room[0] == 'C'){
  if(room == "C0"){
    home();
    delay(3000);
    moveLeft(6);
    moveUp(9);
    moveLeft(5.5);
    moveUp(33);
    moveLeft(5);
    moveUp(5);
    delay(3000);
    moveUp(39);
    delay(3000);
    moveDown(5);
    moveLeft(20);
    moveDown(9);
    resetRoom();
    return;
  }

  room.remove(0, 1);

  int temp = (room.toInt()/10);

    if(temp>= 116 && temp<= 124){
    
    home();
    delay(3000);
    moveLeft(6);
    moveUp(9);
    moveLeft(5.5);
    moveUp(33);
    moveLeft(5);
    moveUp(5);
    delay(3000);
    moveUp(39);
    delay(3000);
    moveDown(5);
    moveLeft(5);
    moveDown(14);
    moveLeft(15);
    resetRoom();
    return;
    }

    if(temp>=101 && temp<=110){
     home();
    delay(3000);
    moveLeft(6);
    moveUp(9);
    moveLeft(5.5);
    moveUp(33);
    moveLeft(5);
    moveUp(5);
    delay(3000);
    moveUp(39);
    delay(3000);
    moveDown(5);
    moveLeft(10);
    resetRoom();
    return;
     
    }
    
if(temp>= 111 && temp<= 115){
    home();
    delay(3000);
    moveLeft(6);
    moveUp(9);
    moveLeft(5.5);
    moveUp(33);
    moveLeft(5);
    moveUp(5);
    delay(3000);
    moveUp(39);
    delay(3000);
    moveDown(5);
    moveLeft(20);
    moveDown(9);
    resetRoom();
    return;
    
    }
}

else if(room[0] == 'D'){
  if(room == "D0"){
    home();
    delay(3000);
    moveLeft(6);
    moveUp(9);
    moveLeft(5.5);
    moveUp(33);
    moveLeft(5);
    moveUp(5);
    delay(3000);
    moveUp(40);
    delay(3000);
    moveDown(5);
    moveRight(20);
    moveDown(9);
    resetRoom();
  }

  room.remove(0, 1);

  int temp = (room.toInt()/10);

    if(temp>= 116 && temp<= 124){
     home();
    delay(3000);
    moveLeft(6);
    moveUp(9);
    moveLeft(5.5);
    moveUp(33);
    moveLeft(5);
    moveUp(5);
    delay(3000);
    moveUp(40);
    delay(3000);
    moveDown(5);
    moveRight(5);
    moveDown(15);
    moveRight(10);
    resetRoom();
    
    }

    if(temp>=101 && temp<=110){
     
      home();
    delay(3000);
    moveLeft(6);
    moveUp(9);
    moveLeft(5.5);
    moveUp(33);
    moveLeft(5);
    moveUp(5);
    delay(3000);
    moveUp(40);
    delay(3000);
    moveDown(5);
    moveRight(15);
    resetRoom();
    }
    
if(temp>= 111 && temp<= 115){
     home();
    delay(3000);
    moveLeft(6);
    moveUp(9);
    moveLeft(5.5);
    moveUp(33);
    moveLeft(5);
    moveUp(5);
    delay(3000);
    moveUp(40);
    delay(3000);
    moveDown(5);
    moveRight(20);
    moveDown(9);
    resetRoom();

    }
}

else if (room == "9" || room == "90") {
    home();
    resetRoom();
    return;
  } 
   else if (room == "1"|| room == "10"){
    home();
    delay(3000);
    moveLeft(5);
    moveDown(9);
    moveLeft(19);
    resetRoom();
    return;
  } 
   else if (room == "2"|| room == "20"){
    home();
    delay(3000);
    moveLeft(5);
    moveDown(9);
    moveLeft(8);
    resetRoom();
    return;

  
  } 
   else if (room == "3"|| room == "30"){
    home();
    delay(3000);
    moveLeft(5);
    moveDown(9);
    moveLeft(19);
    moveUp(10);
    resetRoom();
    return;
  } 
   else if (room == "4" || room == "40"){
    home();
    delay(3000);
    moveLeft(6);
    moveUp(10);
    moveLeft(10);
       resetRoom();
    return;
  }
}

void moveStepper(double distance) {
  double turns = ((distance / rotations) * 1600 * constant); // Specify the amount of time the steppers will move
  for (double x = 0; x < turns; x++) { 
    digitalWrite(StepX, HIGH); // Turns on X Stepper Motor
    digitalWrite(StepY, HIGH); // Turns on Y Stepper Motor
    delayMicroseconds(250); // Delay 250 microseconds
    digitalWrite(StepX, LOW); // Turns off X Stepper Motor
    digitalWrite(StepY, LOW);// Turns off Y Stepper Motor
    delayMicroseconds(250); // Delay 250 ms
  }
}

void moveRight(double distance) {
  digitalWrite(DirX, HIGH); //Sets the steppers to turn in the correct direction for the movment
  digitalWrite(DirY, HIGH); //Sets the steppers to turn in the correct direction for the movment
  moveStepper(distance); // calls the moveStepper function for the distance specified
}


void moveLeft(double distance) {
  digitalWrite(DirX, LOW);
  digitalWrite(DirY, LOW);
  moveStepper(distance);
}

void moveDown(double distance) {
  digitalWrite(DirX, HIGH);  // Enables the motor to move right
  digitalWrite(DirY, LOW);   // Enables the motor to move right
  moveStepper(distance);
}

void moveUp(double distance) {
  digitalWrite(DirX, LOW);   // Enables the motor to move right
  digitalWrite(DirY, HIGH);  // Enables the motor to move right
  moveStepper(distance);
}
void home() {

  digitalWrite(DirY, HIGH);
  digitalWrite(DirX, HIGH);

  bool state = true;
  digitalWrite(DirX, HIGH);  // Enables the motor to move right
  digitalWrite(DirY, LOW);

  while (state == true) {
    limitSwitch1.loop();  // MUST call the loop() function first

    digitalWrite(StepX, HIGH);
    digitalWrite(StepY, HIGH);
    delayMicroseconds(250);
    digitalWrite(StepX, LOW);
    digitalWrite(StepY, LOW);
    delayMicroseconds(250);

    if (limitSwitch1.isPressed())
      break;
  }

  digitalWrite(DirX, HIGH);
  digitalWrite(DirY, HIGH);
  while (state == true) {
    limitSwitch2.loop();  // MUST call the loop() function first

    digitalWrite(StepX, HIGH);
    digitalWrite(StepY, HIGH);
    delayMicroseconds(250);
    digitalWrite(StepX, LOW);
    digitalWrite(StepY, LOW);
    delayMicroseconds(250);

    if (limitSwitch2.isPressed()) {

      break;
    }
  }
  moveUp(38);
  moveLeft(6);
}


void resetRoom() {
  room = "";
}
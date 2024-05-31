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


String aLeft[] = { "A123", "A122", "A121", "A120", "A119", "A118", "A117", "A116" };
String aBack[] = {};
String aRight[] = {};



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
    Serial.println("Recieved");
    room += x;
    Serial.println(room);
  }
}

void loop() {


  if (room == "A123") {
    moveRight(50);
    moveLeft(50);
    moveUp(50);
    moveDown(50);


    resetRoom();
  } else if (room == "A321") {

    moveStepper(40);

    resetRoom();

  } else if (room == "A000") {
    home();
    resetRoom();
    return;
  } else if (room == "B1") {
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
  } else if (room == "A1") {
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
  } else if (room == "C1") {
    home();
    delay(3000);
    moveLeft(6);
    moveUp(9);
    moveLeft(5.5);
    moveUp(35);
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
  } else if (room == "D1") {
    home();
    delay(3000);
    moveLeft(6);
    moveUp(9);
    moveLeft(5.5);
    moveUp(35);
    moveLeft(5);
    moveUp(5);
    delay(3000);
    moveUp(40);
    delay(3000);
    moveDown(5);
    moveRight(20);
    moveDown(9);
    resetRoom();
    return;
  }
}

void moveStepper(double distance) {


  double turns = ((distance / rotations) * 1600 * constant);
  for (double x = 0; x < turns; x++) {

    digitalWrite(StepX, HIGH);
    digitalWrite(StepY, HIGH);
    delayMicroseconds(250);
    digitalWrite(StepX, LOW);
    digitalWrite(StepY, LOW);
    delayMicroseconds(250);
  }
}

void moveRight(double distance) {
  digitalWrite(DirX, HIGH);
  digitalWrite(DirY, HIGH);
  moveStepper(distance);
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
  moveUp(36.5);
  moveLeft(6);
}

void resetRoom() {
  room = "";
}
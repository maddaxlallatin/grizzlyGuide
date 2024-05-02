#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

char x;
String room = "";
const int StepX = 2;
const int DirX = 5;
const int StepY = 3;
const int DirY = 6;
const int rotations = 15;

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
    if(x =='R'){
      resetRoom();
   } else{
  Serial.println("Recieved");
  room += x;
  Serial.println(room);
  }
}

void loop() {


  if (room == "A123") {
    moveStepper(2, StepY, DirY, 30);
    moveStepper(2, StepX, DirX, 30);
  
    resetRoom();
  }
  else if (room == "A321") {

    moveStepper(2, StepY, DirY, 40);
    
    resetRoom();

   } 
}

void moveStepper(int seconds, int stepperVal, int stepperDir, int distance){

digitalWrite(stepperDir, HIGH);

int turns = ((distance/rotations) * 1600);
for (int x = 0; x < turns; x++) { 
      digitalWrite(stepperVal, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepperVal, LOW);
      delayMicroseconds(500);
    }
}

void resetRoom() {
  room = "";
}
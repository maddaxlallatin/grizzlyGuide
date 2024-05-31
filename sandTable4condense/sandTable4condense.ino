/*   
 *  Arduino GRBL by Benjamin Newson
    Newson's Electronics
 *  newsonselectronics.ca
 */

//#include <IRremote.hpp>

//#include <math.h>
int num = 1;
int colour = 0;  //leds
int button = 0;
int delayMin = 1;
bool homing = false;
int change = 0;
int power = 1;
int pause = 0;
//int right=0;

#define IR_Input 12
#define Sync_Time 3000
#define One_Time 1000
#define Zero_Time 400
volatile byte Bit_Count = 0;
volatile byte Byte_Count = 0;
volatile byte Byte_Ready = false;
volatile byte IR_Bytes[4];
unsigned long Start_Time = 0;
unsigned long Pulse_Width;




//int arrayLength = 0;
//float slope = 0;
float m = 0;
float distance = 1;

int dx = 10; // for bounce
int dy = 5;

int width = 165;
int height = 190;
int buttonState = 1;
int buttonState2 = 1;
//x , y

//math diameter 15mm
// ONe rotation = 1600 pulses
//int incomingByte = 0;
// defines pins
#define stepPin 2  //x
#define dirPin 5   //x
#define enPin 8    //
#define stepPin2 3  //y
#define dirPin2 6   //y
#define green A0  
#define blue A1   
#define red A2
#define ySwitch 10
#define xSwitch 9
int speed = 800;
float rotations = 15;  //15mm per rotations = 1600 pulses
float x = 0;
float y = 0;
//int x1, y1, x2, y2 = 0;
int ranNum = 0;
//in mm
double turns = (distance / rotations) * 1600;

int hex[] = {
  128,35,
142,90,
102,130,
48,115,
33,61,
73,21,
128,35,
158,105,
118,145,
63,131,
49,76,
89,36,
143,51,
158,105,
112,167,
58,152,
43,97,
83,57,
138,72,
152,127,
112,167,
36,158,
22,103,
62,63,
116,78,
131,132,
91,172,
36,158,
6,88,
46,48,
101,62,
115,117,
75,157,
21,142,
6,88,
52,26,
106,41,
121,96,
81,136,
26,121,
12,66,
52,26,
};

int polygons[] = {
  128,
  35,
  142,
  90,
  102,
  130,
  48,
  115,
  33,
  61,
  73,
  21,
  128,
  35,
  158,
  105,
  118,
  145,
  63,
  131,
  49,
  76,
  89,
  36,
  143,
  51,
  158,
  105,
  112,
  167,
  58,
  152,
  43,
  97,
  83,
  57,
  138,
  72,
  152,
  127,
  112,
  167,
  36,
  158,
  22,
  103,
  62,
  63,
  116,
  78,
  131,
  132,
  91,
  172,
  36,
  158,
  6,
  88,
  46,
  48,
  101,
  62,
  115,
  117,
  75,
  157,
  21,
  142,
  6,
  88,
  52,
  26,
  106,
  41,
  121,
  96,
  81,
  136,
  26,
  121,
  12,
  66,
  52,
  26,

};






void plotShape(int shape[], int size) {
 
 for (int t = 0; t < (size / 2) - 1; t++)  // size of array div 2.
  {
    if (button > 0) { return; }
    int x2 = shape[t * 2];
    int y2 = shape[t * 2 + 1];
    plot(x, y, x2, y2);
  
  }
 
}



int sun[] = {
  75,
  21,
  127,
  35,
  113,
  87,
  61,
  73,
  75,
  21,
  39,
  35,
  91,
  21,
  105,
  73,
  53,
  87,
  39,
  35,
  14,
  65,
  53,
  27,
  91,
  65,
  53,
  103,
  14,
  65,
  8,
  103,
  22,
  51,
  75,
  65,
  61,
  117,
  8,
  103,
  22,
  140,
  8,
  88,
  61,
  74,
  75,
  126,
  22,
  140,
  53,
  164,
  14,
  126,
  53,
  88,
  91,
  126,
  53,
  164,
  91,
  170,
  39,
  156,
  53,
  104,
  105,
  118,
  91,
  170,
  127,
  156,
  75,
  170,
  61,
  118,
  113,
  104,
  127,
  156,
  152,
  126,
  113,
  164,
  75,
  126,
  113,
  88,
  152,
  126,
  158,
  88,
  144,
  140,
  91,
  126,
  105,
  74,
  158,
  88,
  144,
  51,
  158,
  103,
  105,
  117,
  91,
  65,
  144,
  51,
  113,
  27,
  152,
  65,
  113,
  103,
  75,
  65,
  113,
  27,
  75,
  21,
  127,
  35,
  113,
  87,
  61,
  73,
  75,
  21,
  39,
  35,
  91,
  21,
  //105,
  //73,
  //53,
  //87,
  //39,
  //35,
  //14,
  //65,
  //53,
  //27,
  //91,
  //65,
  //53,
  //103,
  //14,
  //65,
  //8,
  //103,
  //22,
  //51,
  // 75,
  //65,
  //61,
  //117,
  //8,
  //103,
  //22,
  //140,
  //8,
  //88,
  //61,
  //74,
  //75,
  //126,
  //22,
  //140,


};


int triangleSpiral[] = {
  26,
  16,
  77,
  159,
  160,
  38,
  14,
  38,
  92,
  154,
  139,
  27,
  8,
  61,
  105,
  146,
  117,
  22,
  9,
  82,
  114,
  136,
  97,
  24,
  15,
  101,
  119,
  125,
  79,
  31,
  26,
  116,
  121,
  113,
  66,
  41,
  39,
  126,
  120,
  103,
  57,
  54,
  52,
  131,
  116,
  95,
  53,
  67,
  66,
  132,
  110,
  89,
  53,
  79,
  77,
  129,
  103,
  85,
  57,
  89,


};


int stars[] = {

  85,
  52,
  131,
  29,
  122,
  78,
  160,
  113,
  108,
  120,
  85,
  165,
  61,
  120,
  9,
  113,
  47,
  78,
  38,
  29,
  85,
  52,
  85,
  52,
  94,
  60,
  94,
  60,
  137,
  52,
  119,
  90,
  142,
  127,
  98,
  121,
  70,
  153,
  60,
  111,
  20,
  94,
  58,
  73,
  61,
  31,
  94,
  60,
  94,
  60,
  100,
  70,
  100,
  70,
  136,
  72,
  114,
  99,
  124,
  133,
  90,
  119,
  61,
  138,
  62,
  103,
  34,
  81,
  69,
  73,
  80,
  40,
  100,
  70,
  100,
  70,
  102,
  84,
  102,
  84,
  125,
  96,
  103,
  106,
  100,
  131,
  82,
  113,
  58,
  117,
  69,
  95,
  57,
  72,
  81,
  77,
  98,
  59,
  102,
  84,
  102,
  84,
  100,
  92,
  100,
  92,
  113,
  107,
  95,
  109,
  86,
  126,
  79,
  108,
  60,
  104,
  74,
  91,
  71,
  72,
  87,
  82,
  104,
  73,
  100,
  92,
  100,
  92,
  95,
  102,
  95,
  102,
  95,
  116,
  84,
  108,
  72,
  113,
  76,
  100,
  68,
  89,
  82,
  89,
  90,
  77,
  93,
  90,
  106,
  94,
  95,
  102,
  95,
  102,
  88,
  103,
  88,
  103,



};

int squares[]{
  10,
  23,
  159,
  23,
  159,
  172,
  10,
  172,
  10,
  23,
  10,
  23,
  83,
  23,
  83,
  23,
  159,
  96,
  86,
  171,
  10,
  98,
  83,
  23,
  83,
  23,
  117,
  56,
  117,
  56,
  126,
  129,
  52,
  138,
  43,
  65,
  117,
  56,
  117,
  56,
  121,
  93,
  121,
  93,
  88,
  134,
  48,
  101,
  81,
  60,
  121,
  93,
  121,
  93,
  103,
  115,
  103,
  115,
  67,
  115,
  67,
  79,
  103,
  79,
  103,
  115,
  103,
  115,
  85,
  115,
  85,
  115,
  67,
  97,
  85,
  79,
  102,
  97,
  85,
  115,
};

void RGB(int colour) {
  digitalWrite(green, !bitRead(colour, 1));
  digitalWrite(red, !bitRead(colour, 2));
  digitalWrite(blue, !bitRead(colour, 0));
}


/// Basic Functions
void stepperMotor(float distance) {
  turns = (distance / rotations) * 1600;
  for (int i = 0; i < turns; i++) {

    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(speed);
    digitalWrite(stepPin, LOW);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(speed);
    while (pause == 1) {
      Serial.println("pause");
    };


    //if (power==1){return;}
  }
}

void right(float distance) {

  if (button > 0) { return; }
  digitalWrite(dirPin, HIGH);   // Enables the motor to move right
  digitalWrite(dirPin2, HIGH);  // Enables the motor to move right
  stepperMotor(distance);
  x = x + distance;
}

void up(float distance) {

  if (button > 0) { return; }
  digitalWrite(dirPin, HIGH);  // Enables the motor to move right
  digitalWrite(dirPin2, LOW);  // Enables the motor to move right/HIGH left/LOW
  stepperMotor(distance);
  y = y + distance;
}

void down(float distance) {

  if (button > 0) { return; }
  digitalWrite(dirPin, LOW);    // Enables the motor to move right
  digitalWrite(dirPin2, HIGH);  // Enables the motor to move right/HIGH left/LOW
  stepperMotor(distance);
  y = y - distance;
}

void left(float distance) {

  if (button > 0) { return; }
  digitalWrite(dirPin, LOW);   //Changes the rotations direction left
  digitalWrite(dirPin2, LOW);  //Changes the rotations direction left
  stepperMotor(distance);
  x = x - distance;
}



/////// Clear Functions
//0
void leftRight()  //clear
{
  plot(x, y, width, height);
  while (y > 10) {
    //if (power==1){break;}
    if (button > 0) { return; }
    plot(x, y, 0, y);
    plot(x, y, 0, y - 5);
    plot(x, y, width, y);
    plot(x, y, width, y - 5);
  }
}
//1
void zigZag()  //clear zag
{

  int l = 0;
  //for (int i = 16; i <= 160-16; i+=16) {
  while (l < 160) {
    if (button > 0) { return; }
    l = l + 8;
    plot(x, y, 0, l);
    plot(x, y, l, 0);
    l = l + 8;
    plot(x, y, l, 0);
    plot(x, y, 0, l);
  }

  //delay(2000);
  int h = -8;
  while (l < 190) {
    if (button > 0) { return; }
    l = l + 8;
    h = h + 8;
    plot(x, y, 0, l);
    plot(x, y, width, h);
    l = l + 8;
    h = h + 8;
    plot(x, y, width, h);
    plot(x, y, 0, l);
  }

  l = 0;
  while (l < 160) {
    if (button > 0) { return; }
    l = l + 8;
    h = h + 8;
    plot(x, y, l, height);
    plot(x, y, width, h);
    l = l + 8;
    h = h + 8;
    plot(x, y, width, h);
    plot(x, y, l, height);
  }
}
//2
void upDown() {
  plot(x, y, width, 0);
  while (x > 10) {
    if (button > 0) { return; }
    plot(x, y, x, height);
    plot(x, y, x - 5, y);
    plot(x, y, x, 0);
    plot(x, y, x - 5, y);
    // if (button == 69) { break; }
  }
  plot(x, y, x, height);
  plot(x, y, x - 5, y);
  plot(x, y, x, 0);
}




/// Other patturns
void bounce()  // bounces off walls
{
  Serial.println("bounce");
  int i = 0;
  plot(x, y, width/2, height/2);
  while (i < 20) {
    if (x < 40) {
      dx = 1;
      i = i + 1;
    }
    if (x > width - 40) { dx = -dx; }
    if (y > height - 40) { dy = -dy; }
    if (y < 40) { dy = 1; }
    plot(x, y, x + dx, y + dy);
    // Serial.println("bounce");
    if (button > 0) {
      button = 0;
      return;
    }
  }
}

void randomLine() {
  //for (int i = 0; i <= (height / 5) ; i++) {
  plot(x, y, random(0, width), random(0, height));
  plot(x, y, width / 2, height / 2);
  if (button > 0) { return; }
  //}
}

void dimonds() {  // large

  plot(x, y, 0, 0);
  while (x < width - 40) {
    // if (button == 69) { break; }
    plot(x, y, x + 80, y);
    if (button > 0) { return; }
    for (int i = 0; i < 2; i++) {
      plot(x, y, x - 80, y + height / 5);
      plot(x, y, x + 80, y + height / 5);
    }
    plot(x, y, x - 80, y + height / 5);
    plot(x, y, x + 80, y);
    while (y > 40) {
      if (button > 0) { return; }
      plot(x, y, x - 80, y - height / 5);
      plot(x, y, x + 80, y - height / 5);
    }
    plot(x, y, x - 80, y - height / 5);
    plot(x, y, x + 80, y);
  }
}







void square() {  // mids
  for (int i = 0; i < 40; i = i + 10) {
    // if (button == 69) { break; }
    plot(x, y, 0, (height / 2) + i);
    plot(x, y, (width / 2) + i, 5);
    plot(x, y, width, (height / 2) - i);
    plot(x, y, (width / 2) - i, height);
    if (button > 0) {
      button = 0;
      return;
    }
  }
}



///////////Main plot function between two points
void plot(int x1, int y1, int x2, int y2) {

  if (button > 0) { return; }
  m = float(y2 - y1) / float(x2 - x1);  // y/x  slope

  Serial.print("dy=");
  Serial.print((y2 - y1));
  Serial.print(" dx=");
  Serial.print((x2 - x1));

  Serial.print(" slope=");
  Serial.print(m);
  Serial.print(" loc=");

  Serial.print(x);
  Serial.print(",");
  Serial.print(y);

  Serial.print(" num=");
  Serial.print(num);
  Serial.print(" pow=");
  Serial.print(power);
  Serial.print(" button=");
  Serial.print(button);
  Serial.print(" ranNum=");
  Serial.println(ranNum);
  //Serial.println(button);

  //Serial.print("slope=");


  while (y + (y2 - y1) > height + 3 || x + (x2 - x1) > width + 2 || x + (x2 - x1) < -2 || y + (y2 - y1) < -2) {
    Serial.print("outsideRange");
  }
  if ((x2 - x1 == 0))  // dx=0 up or down.
  {
    for (int i = 0; i < abs(y2 - y1); i++)  //x  one// unit in x dir.
    {
      //    if (power==1){break;}
      distance = 1;  //in mm
      //turns = (distance / rotations) * 1600;

      if ((y2 - y1) > 0) {
        up(distance);
      }

      if (y2 - y1 < 0) {
        down(distance);
      }
    }
  }
  // go on angles
  else {
    if (x2 - x1 > 0)  // going right
    {
      for (int i = 0; i < abs(x2 - x1); i++)  //x  one unit in x dir.
      {
        distance = 1;  //in mm
                       // turns = (distance / rotations) * 1600;
        right(distance);
        distance = abs(m);  //in mm in y dir.
                            // turns = (distance / rotations) * 1600;
        if (m > 0) {
          up(distance);
        }

        if (m < 0) {
          down(distance);
        }
      }
    }

    if (x2 - x1 < 0)  // going left
    {
      for (int i = 0; i < abs(x2 - x1); i++)  //x  one unit in x dir.
      {
        distance = 1;  //in mm
                       //   turns = (distance / rotations) * 1600;
        left(distance);
        distance = abs(m);  //in mm in y dir.
                            //   turns = (distance / rotations) * 1600;
        if (m > 0) {
          down(distance);
        }

        if (m < 0) {
          up(distance);
        }
      }
    }
  }
}

void squareSpiral()  //centre out
{
  plot(x, y, (width / 2) + 5, (height / 2) + 5);
  for (int i = 0; i < 160; i = i + 10) {
    plot(x, y, x - 5, y - 5);
    plot(x, y, x, y + i);
    plot(x, y, x + i, y);
    plot(x, y, x, y - i);
    plot(x, y, x - i, y);
    if (button > 0) { return; }
  }
}


void checkIR() {

  if (button == 67) {  // reset
    num = 0;


    Serial.println("main loop");
  }



  if (button == 22) {  /// button 0
    button = 0;


    plotShape(polygons, sizeof(polygons) / sizeof(polygons[0]));
  //  plotShape(triangle, sizeof(triangle) / sizeof(triangle[0]), 50, 50);
  }





  //}

  if (button == 12) {  /// button 1
                       //Serial.println("Stars");
                       //drawStars();
                       //clear();
    button = 0;
    
     plotShape(polygons, sizeof(polygons) / sizeof(polygons[0]));
    //drawHex();
    //drawTriangles();
    //upDown();
  }
  if (button == 24) {  // 2
                       //          Serial.println("up");
    //   up(10);

    //clear();
    button = 0;
    square();
  }

  if (button == 94) {

    button = 0;
    //drawStars();
     plotShape(stars, sizeof(stars) / sizeof(stars[0]));
  }

  if (button == 8) {  //4
                      //clear();
    button = 0;
   // drawSquares();
     plotShape(squares, sizeof(squares) / sizeof(squares[0]));

    //Serial.println("left");
    //left(10);
  }


  if (button == 28)  /// button 5
  {

    for (int i = 0; i < 20; i = i + 10) {

      plot(x, y, 0, (height / 2) + i);
      plot(x, y, (width / 2) + i, 5);
      plot(x, y, width, (height / 2) - i);
      plot(x, y, (width / 2) - i, height);
    }
  }


  if (button == 90) {  //6
                       //Serial.println("right");
                       //right(10);
                       // upDown();
                       //clear();
    button = 0;
    dimonds();
  }

  if (button == 66)  // button 7
  {
    Serial.println("case 7");
    //down(10);
    //clear();
    button = 0;
    //randomLine();
   // drawSun();
     plotShape(sun, sizeof(sun) / sizeof(sun[0]));
  }


  if (button == 82) {  //8
    Serial.println("down");
    //down(10);
    //clear();
    button = 0;
    square();
  }

  /////////////////////////////////////////////////
  if (button == 74)  /// 9
  {

    button = 0;
    bounce();
  }



  if (button == 13)  /// clear screen
  {
    Serial.println("C");
    //down(10);
    button = 0;
    clear();
    // leftRight();
  }

  if (button == 68)  // test= home
  {
    //Serial.println("main loop");
    button = 0;
  }
}







void setup() {

  Serial.begin(9600);


  bitSet(PCMSK0, IR_Input - 8);
  PCICR = B00000001;  // enable PCIE0 group


  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  // Sets the two pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);

  digitalWrite(green, HIGH);
  digitalWrite(red, HIGH);
  digitalWrite(blue, HIGH);

  randomSeed(analogRead(0));
  Serial.print("Sand Plotter Starting");
  // upDown();
}





void clear() {
  ranNum = random(3);
  Serial.print("Clear#:");
  Serial.println(ranNum);

  //clean outsides
  //plot(x, y, 0, 0);
  //plot(x, y, 0, height);
  //plot(x, y, width, height);
  //plot(x, y, width, 0);
  //plot(x, y, 0, 0);
  if (ranNum == 0) { leftRight(); }
  if (ranNum == 1) { upDown(); }
  //if (ranNum == 2) { upDown(); }
  if (ranNum == 2) { zigZag(); }
  if (button > 0) {
    button = 0;
    return;
  }
}

//dx=10;
//dy=5;
void wait() {

  Serial.println("Wait");
  // Serial.println(num);
  for (int i = 0; i < 10 * 60 * delayMin; i++) {
    delay(100);


    if (button > 0) {

      return;
    }
  }
  num = num + 1;
  if (num > 10) { num = 1; }
}


void loop() {


  Serial.println("main");

  while (power == 0) {
    button = 0;
    digitalWrite(enPin, HIGH);
    RGB(0);
  }
  //RGB(ranNum = random(3));
  //Serial.println(ranNum);
  //delay(300);

  if (num == 0) { checkIR(); }


  RGB(num);
  //Serial.println("clear");

  // button=0;
  //clear();


  // Serial.println("num");
  //Serial.println(num);
  while (num > 0) {

    button = 0;
    clear();  //clear screen
    if (num == 1 && change == 0) { bounce(); }
    if (num == 2 && change == 0) { squareSpiral(); }
    if (num == 3 && change == 0) {  plotShape(polygons, sizeof(polygons) / sizeof(polygons[0])); }
    if (num == 4 && change == 0) {  plotShape(hex, sizeof(hex) / sizeof(hex[0])); }
    if (num == 5 && change == 0) {  plotShape(sun, sizeof(sun) / sizeof(sun[0])); }
    if (num == 6 && change == 0) { dimonds(); }
    if (num == 7 && change == 0) {  plotShape(triangleSpiral, sizeof(triangleSpiral) / sizeof(triangleSpiral[0])); }
    if (num == 8 && change == 0) { plotShape(squares, sizeof(squares) / sizeof(squares[0])); }
    if (num == 9 && change == 0) { plotShape(stars, sizeof(stars) / sizeof(stars[0])); }
    if (num == 10 && change == 0) { plotShape(sun, sizeof(sun) / sizeof(sun[0]));}



    if (change == 0) { wait(); }
    change = 0;
    // num=1;
  }

  //change=0;
  //button = 0;
}





// Interrupt-on-change handler
ISR(PCINT0_vect) {
  //when the pin goes HIGH record the pulse start time


  if (digitalRead(IR_Input) == HIGH) {
    Start_Time = micros();
  } else  // pin went low
    if (Start_Time != 0) {
      //calculate the pulse width
      Pulse_Width = micros() - Start_Time;
      //clear the timer
      Start_Time = 0;

      if (Pulse_Width > Sync_Time) {
        // sync bit
        Byte_Ready = false;
        Bit_Count = 0;
        Byte_Count = 0;
      } else if (Pulse_Width > One_Time) {
        // data bit = 1
        bitSet(IR_Bytes[Byte_Count], Bit_Count);
        Bit_Count++;
      } else if (Pulse_Width > Zero_Time) {
        // data bit = 0
        bitClear(IR_Bytes[Byte_Count], Bit_Count);
        Bit_Count++;
      } else
        Bit_Count = 0;  // error

      if (Bit_Count == 8) {  //8bits to a byte
        Byte_Ready = true;
        Bit_Count = 0;
        //        Serial.println("ready");
      }
    }


  if (Byte_Ready == true) {
    Byte_Ready = false;
    Byte_Count++;

    if (Byte_Count == 4) {


      // got all four data bytes
      Byte_Count = 0;

      // Check for valid header
      if ((IR_Bytes[0] == 0x00) && (IR_Bytes[1] == 0xFF)) {
        // Decode command byte
        button = IR_Bytes[2];
        Serial.print("button=");
        Serial.println(button);

        if (button == 71 || button == 70)  /// Menu // colour
        {
          colour = colour + 1;
          if (colour == 7) {
            colour = 0;
            // IR_Bytes[2] = 0;
          }
          RGB(colour);
          button = 0;
          // return;
          //dela//y(200);
        }
        if (button == 64) {  //speed
          if (speed > 250) {

            if (speed < 1000) { speed = speed - 100; }
            if (speed >= 1000) { speed = speed - 500; }
            Serial.print("speed=");
            Serial.println(speed);
          }
          button = 0;
          //delay(100);
        }

        if (button == 25) {  //speed
          if (speed < 10000) {

            if (speed < 1000) { speed = speed + 100; }
            if (speed >= 1000) { speed = speed + 1000; }

            speed = speed + 100;

            Serial.print("speed=");
            Serial.println(speed);
          }
          button = 0;
          //delay(100);
        }


        if (homing == true) { button = 0; }
        if (homing == false) {
          if (button == 21) {
            pause = !pause;
            //colour = !colour;
            RGB(colour);
            if (pause == 1) {
              RGB(4);
            }

            //else
            // RGB(0);

            button = 0;
            //Serial.println(pause);
          }






          if (button == 9 || button == 8) {  /// >> right

            change = 1;
            num = num + 1;

            if (num > 10) {
              num = 1;
            }
            RGB(colour = random(1, 7));
          }

          if (button == 6 || button == 7) {  /// <<< left

            //button=0;
            change = 1;
            num = num - 1;
            if (num == 0) {
              num = 10;
            }

            RGB(colour = random(1, 7));
          }


          if (button == 69) {  /// power button


            power = !power;
            change = 1;
            num = 0;



            if (power == 1) {
              digitalWrite(enPin, LOW);
              button = 0;
              change = 0;
              RGB(colour);

              num = 1;
            }
            //button=0;
          }
        }
      }
    }
  }
}

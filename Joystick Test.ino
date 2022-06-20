#include "Mouse.h"

//sets pinout
const int VRx = A0;
const int VRy = A1;
#define joystickVCC 21
#define SW 7
#define LED 4
#define redButton 
#define delayResponse 2

//sets some initial global variables
int analogVRx;              //a constantly updating analog reading from the joysticks horizontal axis
int analogVRy;              //a constantly updating analog reading from the joysticks vertical axis

bool cursorRight;
bool cursorLeft;
bool cursorUp;
bool cursorDown;


//------------------------------setup and initialize----------------------
void setup(){
  Serial.begin(9600);
  
  pinMode(SW, INPUT_PULLUP);
  pinMode(joystickVCC, OUTPUT);
  pinMode(LED, OUTPUT);
  initialize();
  }
void initialize(){                            //maybe this can be used as an interrupt later to "recalibrate"
  digitalWrite(joystickVCC, HIGH);
    int i = 0;
  while(i<5){                                //flashes a light 5 times
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);
    delay(100);
    i++;
  }
  int analogVRy = analogRead(VRx);          //initializes a reading from the joystick's vertical movement;
  int analogVRx = analogRead(VRy);          //initializes a reading from the joystick's horizontal movement;
   cursorUp = 0;
   cursorDown = 0;
   cursorLeft = 0;
   cursorRight = 0;
  
  digitalWrite(LED, HIGH);                  //a single long flash to OK operation
  delay(1000);
  digitalWrite(LED, LOW);
}

void loop(){
  //digitalFeedback();        //debug reads and prints digitalPin status
  //analogFeedback();         //debug reads and prints digitalPin status
  //booleanFeedback();        //debug displays, LEFT, RIGHT, UP, DOWN as TRUE/FALSE
  inputRecord();              //sets the status variables
  mouseCommands();            //checks variables and commands the mouse
  delay(delayResponse);
}
void digitalFeedback(){
  Serial.println("dVRx");
  Serial.println(digitalRead(VRx));
  Serial.println("dVRy");
  Serial.println(digitalRead(VRy));
  Serial.println("dSW");
  Serial.println(digitalRead(SW));
  }
void analogFeedback(){
  Serial.println("aVRx");
  Serial.println(analogRead(VRx));
  Serial.println("aVRy");
  Serial.println(analogRead(VRy));
  Serial.println("aSW");
  Serial.println(analogRead(SW));
  }
void inputRecord(){
  int thresholdHigh = 540;   //sets a threshold hold to convert the analog reading into binary
  int thresholdLow = 500;    //sets a threshold hold to convert the analog reading into binary
  int analogVRx = analogRead(VRx);
  int analogVRy = analogRead(VRy);
  
  //the following decides horizontal movement
  if (analogVRx > thresholdHigh){       //allows right command
    cursorRight = 0;
    cursorLeft = 1;
  } 
  else if(analogVRx < thresholdLow){
    cursorRight = 1;
    cursorLeft = 0;
  }
  else {
    cursorRight = 0;
    cursorLeft = 0;
  }

  //the following decides vertical movement
  if (analogVRy > thresholdHigh){       //allows right command
    cursorDown = 1;
    cursorUp = 0;
  } 
  else if(analogVRy < thresholdLow){    //allows left command
    cursorDown = 0;
    cursorUp = 1;
  }
  else {
    cursorDown = 0;
    cursorUp = 0;
  }
  //Serial.print(cursorLeft);
  //Serial.print(cursorRight);
  //Serial.print(cursorDown);
  //Serial.println(cursorUp);
  }

void booleanFeedback(){
  Serial.print(cursorLeft);
  Serial.print(cursorRight);
  Serial.print(cursorDown);
  Serial.print(cursorUp);
  }
void mouseCommands(){

  if (cursorRight == 1){
    Mouse.move(1,0,0);
    Serial.println("Moving Right");
  }

  if (cursorLeft == 1){
    Mouse.move(-1,0,0);
    Serial.println("Moving Left");
  }

  if (cursorDown == 1){
    Mouse.move(0,-1,0);
    Serial.println("Moving Up");
  }

  if (cursorUp == 1){
    Mouse.move(0,1,0);
    Serial.println("Moving Down");
  }
  }  
    


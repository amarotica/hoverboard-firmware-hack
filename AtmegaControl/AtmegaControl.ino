// ROV MCU 2/05/2019

#include <SoftwareSerial.h>

#define DEBUG //If uncommented, all transmissions go through hardware serial port

SoftwareSerial pie(2,3);

int timeDelay = 20;

void setup() {

Serial.begin(19200);
pie.begin(9600);
pie.println("This program expects a message (Control mode) and three integers: Left Velocity, Right Velocity, Left time, Right time.");
  pie.println("Enter data in this style <Hello, 27, 12, 24, 30>  ");
  pie.println();
  
  #ifdef DEBUG
  Serial.println("Debug is enabled");
  #endif
  }
  
void loop() {
    recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);

    parseData();
    #ifdef DEBUG
    showParsedData();
    #endif
    newData = false;
#ifdef DEBUG
Serial.println("New Data");
#endif
  }
  
  VelocityRamp();
  
  }
  
void VelocityRamp() {
  int LoopsL = LeftTimeInput/timeDelay;
  int LoopsR = RightTimeInput/timeDelay;
  int vcL = LeftVelocityInput/LoopsL;
  int vcR = RightVelocityInput/LoopsR;
  
  int countL = 0;
  int countR = 0;
  int velocityL = 0;
  int velocityR = 0;
  Max = max(LoopsL,LoopsR);
  
for   (int i=0; i<=Max; i++){
  if (velocityL < LeftVelocityInput) {// && (LeftVelocityInput >= 0)) {
    velocityL = velocityL + 10;
  }
  if (velocityL > LeftVelocityInput) {// && (LeftVelocityInput <= 0)) {
    velocityL = velocityL - 10;
  }

  if (velocityR < RightVelocityInput) {// && (RightVelocityInput >= 0)){
    velocityR = velocityR + 10;
  } 
  if (velocityR > RightVelocityInput) {// && (RightVelocityInput <= 0)){
    velocityR = velocityR - 10;
  } 
    Serial.write((uint8_t *) &velocityL, sizeof(velocityL));
    Serial.write((uint8_t *) &velocityR, sizeof(velocityR));
    delay(timeDelay);
}
  }
  
  void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = pie.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

//============

void parseData() {      // split the data into its parts

  char * strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(tempChars, ",");     // get the first part - the string
  strcpy(pieMessage, strtokIndx); // copy it to pieMessage

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  LeftVelocityInput = atoi(strtokIndx);     // convert this part to an integer

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  LeftTimeInput = atoi(strtokIndx);     // convert this part to an integer

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  RightVelocityInput = atoi(strtokIndx);     // convert this part to an integer

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  RightTimeInput = atoi(strtokIndx);     // convert this part to an integer
}

//============

void showParsedData() {
  pie.print("Message ");
  pie.println(messageFromPC);
  pie.print("RightDistanceInput: ");
  pie.println(RightDistanceInput);
  pie.print("LeftDistanceInput: ");
  pie.println(LeftDistanceInput);
  pie.print("AccelerationInput: ");
  pie.println(AccelerationInput);
}

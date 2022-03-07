#include "Servo.h"
#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"


const int chipSelect = 10;
const int microphonePin1 = A0;
const int microphonePin2 = A1;
int delayVal = 100; 
int Level0 = 325;
int Level1 = 350;
int Level2 = 400;
int Level3 = 500;

TMRpcm tmrpcm;
Servo myservo;

void setup() {
  // put your setup code here, to run once:
  tmrpcm.speakerPin = 3; 
  myservo.attach (6); 
  pinMode (A0, INPUT); 
  pinMode (A1, INPUT);
  pinMode (6, OUTPUT); 
  pinMode (9, OUTPUT); 
  
  Serial.begin (9600); 
  if (!SD.begin(chipSelect)) {
    Serial.println("SD Fail");
    return; 
  } 
  Serial.println ("OK"); 
  tmrpcm.setVolume(6);
  Serial.println ("Volume");
}

void loop() {
  // put your main code here, to run repeatedly:
  int mn1 = 1024;
  int mx1 = 0;
  
  int mn2 = 1024;
  int mx2 = 0;

  for (int i = 0; i < 10000; ++i) {

    int val1 = analogRead(microphonePin1);
    
    mn1 = min(mn1, val1);
    mx1 = max(mx1, val1);

    int val2 = analogRead(microphonePin2);
    
    mn2 = min(mn2, val2);
    mx2 = max(mx2, val2); 
    
  }
  
  int delta1 = mx1 - mn1; // delta gives an idea of the volume of sound detected
  int delta2 = mx2 - mn2;
  int Volume = (delta1 + delta2)/2;
  
//  if (Volume < Level0) {
//    Serial.print(" QUIET Volume = ");
//    Serial.println(Volume);
//    
//  }
  
  if (Volume >= Level0 && Volume < Level1) {
    Serial.print(" LOW Volume = ");
    Serial.println(Volume);
    
    myservo.write (0); 
    delay (delayVal);
    myservo.write (90); 
  
    tmrpcm.play("1.wav");
    delay (1000);
    
    
  }
  
  else if (Volume >= Level1 && Volume < Level2) {
    Serial.print(" MEDIUM Volume = ");
    Serial.println(Volume);
    
    myservo.write (0);  
    delay (delayVal);
    myservo.write (90); 
  
    tmrpcm.play("2.wav");
    delay (750);
  }
  
  else if (Volume >= Level2 && Volume < Level3) {
    Serial.print(" HIGH Volume = ");
    Serial.println(Volume); 
    
    myservo.write (0);  
    delay (delayVal);
    myservo.write (90); 
 
    tmrpcm.play("3.wav");
    delay (500);
  }
  
  else if (Volume >= Level3 ) {
    Serial.print(" UNACCEPTABLE!! Volume = ");
    Serial.println(Volume);
    myservo.write (0);  
    delay (delayVal-=5);
    myservo.write (90); 
 
    tmrpcm.play("4.wav");
    delay (250);
  }
  else {
    Serial.print(" QUIET Volume = ");
    Serial.println(Volume);
  }
 
}

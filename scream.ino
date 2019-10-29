#include <SD.h>                      // need to include the SD library
//#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SD_ChipSelectPin 4  //using digital pin 4 on arduino nano 328, can use other pins
#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>
//#include <Servo.h>

int ledPin = 3;
int lastButtonState = HIGH;
const int trigPin = 7;
const int echoPin = 6;
//const int servoPin = 6;

//Servo servo;
int angle = 0;  

long duration;
int distance;

TMRpcm tmrpcm;   // create an object for use in this sketch

void setup(){

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
//  servo.attach(8);

  tmrpcm.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc

  Serial.begin(9600);
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initializzd:
    Serial.println("SD fail");  
    return;   // don't do anything more if not
  }

//  playMusic();
  pinMode(ledPin, OUTPUT);
}


void scream() {
  tmrpcm.setVolume(6);
  digitalWrite(ledPin, HIGH);
// servo.write(90);
tmrpcm.play("scream.wav");  
  delay(2000); 
  digitalWrite(ledPin, LOW);
//  servo.write(0);
  delay(3000);
}


void loop(){  
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration /29 /2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  if (distance<40) {
    scream();
  }
  
}

#include <Arduino.h>
#include <Servo.h>
Servo s1;
Servo s2;
int trigPin1 = 2; 
int echoPin1 = 4; 
int servopin2= 10;
int trigPin2 = 5; 
int echoPin2 = 7; 
int servopin1= 9;
long duration1; 
int distance1; 
long duration2; 
int distance2; 
bool entryGateOpen = false;
bool exitGateOpen = false;

void openGate(Servo& gateServo, bool& gateStatus) {
  gateServo.write(90);
  gateStatus = true;
  delay(1000);
}

bool carPassed(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long dur = pulseIn(echoPin, HIGH);
  int dist = dur * 0.034 / 2;
  Serial.println(dist);
  return dist > 50;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  Serial.begin(9600);
  s1.attach(servopin1);
  s2.attach(servopin2);
  s1.write(90);
  s2.write(90);
  delay(2000);
  s1.write(0);
  s2.write(0);

}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'E') {
      // openGate(s2, entryGateOpen);
      // entryGateOpen = true;
      s2.write(90);
      delay(6000);
      s2.write(0);
    } else if (command == 'X') {
      // openGate(s1, exitGateOpen);
      // exitGateOpen = true;
      s1.write(90);
      delay(6000);
      s1.write(0);
    }
  }

  // Handle gate closing
  if (entryGateOpen && carPassed(trigPin1, echoPin1)) {
    delay(2000); // allow full car pass
    s2.write(0);
    entryGateOpen = false;
  }

  if (exitGateOpen && carPassed(trigPin2, echoPin2)) {
    delay(2000);
    s1.write(0);
    exitGateOpen = false;
  }
}
  // delay(1000);
  // if (Serial.available() > 0) {
  //   char command = Serial.read();
  //   if (command == 'O') {
  //   x.write(0);
  //   delay(2000);
  //   x.write(90);
  //   delay(2000);
  //   // y.write(0);
  //   // delay(2000);
  //   // y.write(90);
  //   // delay(2000);
      
  //   }
  // }



#define trigA 8
#define echoA 9
#define trigB 10
#define echoB 11

#define ledA1 3
#define ledA2 5
#define ledA3 6
#define ledB1 2
#define ledB2 4
#define ledB3 7

const int thresholdA = 17; // distance in cm for sensor A
const int thresholdB = 12; // distance in cm for sensor B
const unsigned long neutralDelay = 5000; // 30 seconds in milliseconds

char activeState = 'N'; // A, B, or N (none)
unsigned long lastDetectionTime = 0; // tracks last time an object was detected

long getDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH, 25000);
  return duration * 0.034 / 2;
}

void setup() {
  pinMode(trigA, OUTPUT);
  pinMode(echoA, INPUT);
  pinMode(trigB, OUTPUT);
  pinMode(echoB, INPUT);

  pinMode(ledA1, OUTPUT);
  pinMode(ledA2, OUTPUT);
  pinMode(ledA3, OUTPUT);
  pinMode(ledB1, OUTPUT);
  pinMode(ledB2, OUTPUT);
  pinMode(ledB3, OUTPUT);
}

void loop() {
  long distA = getDistance(trigA, echoA);
  long distB = getDistance(trigB, echoB);

  // Check for object detection with individual thresholds
  if (distA > 0 && distA < thresholdA) {
    activeState = 'A';
    lastDetectionTime = millis(); // reset timer
  }
  else if (distB > 0 && distB < thresholdB) {
    activeState = 'B';
    lastDetectionTime = millis(); // reset timer
  }
  else {
    // No objects detected - check if 30 seconds have passed
    if (activeState != 'N' && (millis() - lastDetectionTime >= neutralDelay)) {
      activeState = 'N';
    }
  }

  // LED control
  if (activeState == 'A') {
    digitalWrite(ledA1, HIGH);
    digitalWrite(ledA2, HIGH);
    digitalWrite(ledA3, HIGH);
    digitalWrite(ledB1, LOW);
    digitalWrite(ledB2, LOW);
    digitalWrite(ledB3, LOW);
  }
  else if (activeState == 'B') {
    digitalWrite(ledA1, LOW);
    digitalWrite(ledA2, LOW);
    digitalWrite(ledA3, LOW);
    digitalWrite(ledB1, HIGH);
    digitalWrite(ledB2, HIGH);
    digitalWrite(ledB3, HIGH);
  }
  else { // activeState == 'N'
    digitalWrite(ledA1, LOW);
    digitalWrite(ledA2, LOW);
    digitalWrite(ledA3, LOW);
    digitalWrite(ledB1, LOW);
    digitalWrite(ledB2, LOW);
    digitalWrite(ledB3, LOW);
  }
}
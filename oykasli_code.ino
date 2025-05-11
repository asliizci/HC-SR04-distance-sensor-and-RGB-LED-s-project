const int trigPin = 5;
const int echoPin = 18;

int redPin = 4;
int greenPin = 2;
int bluePin = 15;

float distanceCm;
float distanceInch;
const float CM_TO_INCH = 0.3937;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  distanceCm = getAverageDistance(5);
  distanceInch = distanceCm * CM_TO_INCH;

  if (distanceCm == 0) {
    Serial.println("Measurement failed!Signal could not be reflected.");
    setColor(false, false, false); 
  } else if (distanceCm < 5 ) {
    Serial.println("Measurement failed! The object is too close.");
    setColor(false, false, false); 
  }else if (distanceCm > 40) {
    Serial.println("Measurement failed! The object is too far.");
    setColor(false, false, false); 
  }else {
    Serial.print("Distance (cm): ");
    Serial.println(distanceCm);
    Serial.print("Distance (inch): ");
    Serial.println(distanceInch);

    if (distanceCm < 5) {
      setColor(false, true, true);  
    } else if (distanceCm < 8) {
      setColor(true, false, false); 
    } else if (distanceCm < 20) {
      setColor(false, true, false);
    } else if (distanceCm < 40) {
      setColor(false, false, true);
    } else {
      setColor(true, true, true); 
    }
  }

  delay(1000);
}

float getAverageDistance(int numMeasurements) {
  float total = 0;
  int validReadings = 0;

  for (int i = 0; i < numMeasurements; i++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 30000); 

    if (duration > 100 && duration < 30000) {  
      float distance = duration * 0.03432 / 2.0;  
      total += distance;
      validReadings++;
    }

    delay(50);  
  }

  if (validReadings == 0) return 0;
  return total / validReadings;
}

void setColor(bool redOn, bool greenOn, bool blueOn) {
  digitalWrite(redPin, redOn ? HIGH : LOW);
  digitalWrite(greenPin, greenOn ? HIGH : LOW);
  digitalWrite(bluePin, blueOn ? HIGH : LOW);
}
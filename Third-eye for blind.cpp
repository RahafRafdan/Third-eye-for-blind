#define echoPin 5 // Echo Pin
#define trigPin 4 // Trigger Pin
#define LED 10 // LED Pin
#define buzzer 3 // Buzzer Pin
#define SAMPLE_SIZE 5 // Sample size for moving average filter

long distanceSamples[SAMPLE_SIZE];
int sampleIndex = 0;
long duration, distance;
int distanceThreshold = 70; // Default distance threshold

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(LED, LOW);
  digitalWrite(buzzer, LOW);
  Serial.println("Setup complete. Adjust threshold with 'T<number>'.");
}

void loop() {
  readSerialCommands();
  distance = measureDistance();
  distance = getFilteredDistance();
  controlFeedbackDevices(distance);

  delay(10); // Short delay to prevent measurement interference
}

void readSerialCommands() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    if (command.startsWith("T")) {
      distanceThreshold = command.substring(1).toInt();
      Serial.print("Threshold set to: ");
      Serial.println(distanceThreshold);
    }
  }
}

long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2; // Convert time to distance
}

long getFilteredDistance() {
  updateDistanceSamples(distance);
  long sum = 0;
  for (int i = 0; i < SAMPLE_SIZE; i++) {
    sum += distanceSamples[i];
  }
  return sum / SAMPLE_SIZE;
}

void updateDistanceSamples(long newDistance) {
  distanceSamples[sampleIndex % SAMPLE_SIZE] = newDistance;
  sampleIndex++;
}

void controlFeedbackDevices(long distance) {
  if (distance < distanceThreshold) {
    digitalWrite(LED, HIGH);
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(LED, LOW);
    digitalWrite(buzzer, LOW);
  }
}

#define echoPin 5 // Echo Pin
#define trigPin 4 // Trigger Pin
#define LED 10 // Motor Pin
#define buzzer 3

long duration, distance;

void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(LED , LOW);
  digitalWrite(buzzer, LOW);
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  //Serial.println(distance);
  delay(10);

  if (distance < 70) {

    digitalWrite(LED, 1);
    //stop buzzer
    digitalWrite(buzzer, 1);
  }
  else {
    digitalWrite(LED, 0  );
    digitalWrite(buzzer, 0);
  }
}
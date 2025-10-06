// C++ code
//
int redPin = 8;
int bluePin = 9;
int yellowPin = 10;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
}

void loop() {
  digitalWrite(yellowPin, HIGH); // turn on Yellow
  delay(100);
  digitalWrite(yellowPin, LOW);  // turn off Yellow
  delay(100);

  digitalWrite(yellowPin, HIGH); // turn on Yellow
  delay(100);
  digitalWrite(yellowPin, LOW);  // turn off Yellow
  delay(300);

  digitalWrite(redPin, HIGH);   // turn on Red
  delay(100);
  digitalWrite(redPin, LOW);    // turn off Red
  delay(100);

  digitalWrite(redPin, HIGH);   // turn on Red
  delay(100);
  digitalWrite(redPin, LOW);    // turn off Red
  delay(300);

  digitalWrite(bluePin, HIGH);  // turn on Blue
  delay(100);
  digitalWrite(bluePin, LOW);   // turn off Blue
  delay(100);

  digitalWrite(bluePin, HIGH);  // turn on Blue
  delay(100);
  digitalWrite(bluePin, LOW);   // turn off Blue
  delay(300);

}
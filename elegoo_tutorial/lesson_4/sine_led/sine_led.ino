// Define Pins
#define BLUE 3
#define GREEN 5
#define RED 6

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

// define variables
const int delayTime = 10;
const float pi = 3.14159265;

// main loop
void loop() {
  for (int i = 0; i < 360; i++) {
    float angle = i * pi / 180.0;

    int redValue = (sin(angle) * 127.5) + 127.5;
    int greenValue = (sin(angle + (2 * pi / 3)) * 127.5) + 127.5;
    int blueValue = (sin(angle + (4 * pi / 3)) * 127.5) + 127.5;

    analogWrite(RED, redValue);
    analogWrite(GREEN, greenValue);
    analogWrite(BLUE, blueValue);

    delay(delayTime);
  }
}


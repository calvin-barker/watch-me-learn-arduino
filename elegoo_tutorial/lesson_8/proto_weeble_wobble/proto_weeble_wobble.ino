#define BALL_SWITCH 13

void setup() {
  pinMode(BALL_SWITCH, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  if (digitalRead(BALL_SWITCH) == HIGH) {
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    digitalWrite(BALL_SWITCH, HIGH);
  }
}

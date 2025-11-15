// ----------------------------
// Pin configuration (PWM-capable)
// ----------------------------
#define RED 5
#define BUTTON_A_PIN 9
#define BUTTON_B_PIN 8

// Constants
const int DELAY_TIME = 10;

// State
int redValue = 128;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(BUTTON_A_PIN, INPUT_PULLUP);
  pinMode(BUTTON_B_PIN, INPUT_PULLUP);

  analogWrite(RED, HIGH);
}

void loop() {

  if (digitalRead(BUTTON_A_PIN) == LOW && redValue < 255) {
    redValue += 1;
  }

  if (digitalRead(BUTTON_B_PIN) == LOW && redValue > 0 ) {
    redValue -= 1;
  }

  redValue = min(redValue, 255); // Can be at most 255
  redValue = max(redValue, 0); // Must be at least 0

  analogWrite(RED, redValue);

  delay(DELAY_TIME);
}

const int UNIT = 150;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

static inline void on(int ms) {digitalWrite(LED_BUILTIN, HIGH); delay(ms);}
static inline void off(int ms) {digitalWrite(LED_BUILTIN, LOW); delay(ms);}

// S = . . .
void morseS() {
  for (int i = 0; i < 3; i += 1) {
    on(UNIT);
    if (i < 2) off(UNIT);
  }
}

// O = - - -
void morseO() {
  for (int i = 0; i < 3; i += 1) {
    on(3 * UNIT);
    if (i < 2) off(3 * UNIT);
  }
}

// the loop function runs over and over again forever
void loop() {
  // ...
  morseS();
  off(3 * UNIT); // letter gap
  
  // ---
  morseO();
  off(3 * UNIT); // letter gap

  // ...
  morseS();
  off(7 * UNIT); // word gap
}


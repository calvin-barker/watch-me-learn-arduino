// Pin configuration
#define SPEAKER 5
#define BUTTON_A_PIN 8 
#define BUTTON_B_PIN 9
#define BUTTON_C_PIN 10
#define BUTTON_D_PIN 11 

// Define pitches
// Two octaves: C3 to C5
#define NOTE_C4   262
#define NOTE_C5   523

// Metronome configuration
int bpm = 0;
int sigNumerator = 4;
int sigDenominator = 4;
int beat = 0;

// Constants
const int SOUND_DURATION = 50;
const long MINUTE_MS = 60000l;
int beatDelay = 0;

// State
int prevAState = HIGH;
int prevBState = HIGH;
int prevCState = HIGH;
int prevDState = HIGH;

// Helper function to set the beat delay.
void setNewBPM(int b) {
  bpm = b;
  beatDelay = MINUTE_MS / b;
  beat = 0;
}

void setup() {
  setNewBPM(120);

  pinMode(SPEAKER, OUTPUT);
  pinMode(BUTTON_A_PIN, INPUT_PULLUP);
  pinMode(BUTTON_B_PIN, INPUT_PULLUP);
  pinMode(BUTTON_C_PIN, INPUT_PULLUP);
  pinMode(BUTTON_D_PIN, INPUT_PULLUP);
}

void loop() {
  
  int currentAState = digitalRead(BUTTON_A_PIN);
  int currentBState = digitalRead(BUTTON_B_PIN);
  int currentCState = digitalRead(BUTTON_C_PIN);
  int currentDState = digitalRead(BUTTON_D_PIN);
  
  // Makes the tempo slower.
  if (currentAState == LOW && bpm > 30) {
    setNewBPM(bpm - 1);
    delay(5);
  }

  // Makes the tempo faster.
  if (currentBState == LOW && bpm < 300) {
    setNewBPM(bpm + 1);
    delay(5);
  }

  // Reduces the time signature numerator. Example: 4/4 -> 3/4
  if (prevCState == HIGH && currentCState == LOW && sigNumerator > 1) {
    sigNumerator -= 1;
    beat = 0;
    delay(10);
  }

  // Increases the time signature numerator. Example: 3/4 -> 4/4
  if (prevDState == HIGH && currentDState == LOW && sigNumerator < 10) {
    sigNumerator += 1;
    beat = 0;
    delay(10);
  }
  
  // Update previous states.
  prevAState = currentAState;
  prevBState = currentBState;
  prevCState = currentCState;
  prevDState = currentDState;

  if (beat % sigNumerator == 0) {
    tone(SPEAKER, NOTE_C5, SOUND_DURATION);
  } else {
    tone(SPEAKER, NOTE_C4, SOUND_DURATION);
  }
  beat += 1;
  delay(beatDelay - SOUND_DURATION);
}

// Pin configuration
#define SPEAKER 5
#define BUTTON_A_PIN 8 
#define BUTTON_B_PIN 9
#define BUTTON_C_PIN 10
#define BUTTON_D_PIN 11 

// Define pitches
// Two octaves: C3 to C5
#define NOTE_C3   131
#define NOTE_CS3  139
#define NOTE_D3   147
#define NOTE_DS3  156
#define NOTE_E3   165
#define NOTE_F3   175
#define NOTE_FS3  185
#define NOTE_G3   196
#define NOTE_GS3  208
#define NOTE_A3   220
#define NOTE_AS3  233
#define NOTE_B3   247
#define NOTE_C4   262
#define NOTE_CS4  277
#define NOTE_D4   294
#define NOTE_DS4  311
#define NOTE_E4   330
#define NOTE_F4   349
#define NOTE_FS4  370
#define NOTE_G4   392
#define NOTE_GS4  415
#define NOTE_A4   440
#define NOTE_AS4  466
#define NOTE_B4   494
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

// Pin configuration
#define SPEAKER       5
#define BUTTON_A_PIN  8 
#define BUTTON_B_PIN  9
#define BUTTON_C_PIN  10
#define BUTTON_D_PIN  11 

// Define pitches (C4 to C5)
#define NOTE_C4   262
#define NOTE_C5   523

// Metronome configuration
int bpm          = 0;
int sigNumerator = 4;
int beat         = 0;

// Constants
const int           SOUND_DURATION          = 50;          // ms
const unsigned long MINUTE_MS               = 60000UL;
const int           MIN_BPM                 = 30;
const int           MAX_BPM                 = 300;
const unsigned long TEMPO_STEP_INTERVAL_MS  = 60;          // ms between tempo steps when holding A/B
const unsigned long SIG_CHANGE_DEBOUNCE_MS  = 150;         // ms debounce for C/D

// Derived timing
unsigned long beatDelay = 0;   // ms between beats

// Button state (for C/D edge detection)
int prevCState = HIGH;
int prevDState = HIGH;

// Timing state
unsigned long lastTickMs       = 0;
unsigned long lastTempoStepMs  = 0;
unsigned long lastSigChangeMs  = 0;

// Helper function to set the beat delay.
void setNewBPM(int b) {
  if (b < MIN_BPM) b = MIN_BPM;
  if (b > MAX_BPM) b = MAX_BPM;

  bpm       = b;
  beatDelay = MINUTE_MS / (unsigned long)b;
}

void blink() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(SOUND_DURATION);
  digitalWrite(LED_BUILTIN, LOW);
}

void setup() {
  setNewBPM(120);

  pinMode(SPEAKER,       OUTPUT);
  pinMode(LED_BUILTIN,   OUTPUT);
  pinMode(BUTTON_A_PIN,  INPUT_PULLUP);
  pinMode(BUTTON_B_PIN,  INPUT_PULLUP);
  pinMode(BUTTON_C_PIN,  INPUT_PULLUP);
  pinMode(BUTTON_D_PIN,  INPUT_PULLUP);
  
  unsigned long now = millis();
  lastTickMs       = now;
  lastTempoStepMs  = now;
  lastSigChangeMs  = now;
}

void loop() {
  unsigned long now = millis();
  
  int currentAState = digitalRead(BUTTON_A_PIN);
  int currentBState = digitalRead(BUTTON_B_PIN);
  int currentCState = digitalRead(BUTTON_C_PIN);
  int currentDState = digitalRead(BUTTON_D_PIN);
  
  // TEMPO CONTROL (HOLD A = slower, HOLD B = faster)
  if (now - lastTempoStepMs >= TEMPO_STEP_INTERVAL_MS) {
    bool tempoChanged = false;

    if (currentAState == LOW && bpm > MIN_BPM) {
      setNewBPM(bpm - 1);
      tempoChanged = true;
    }

    if (currentBState == LOW && bpm < MAX_BPM) {
      setNewBPM(bpm + 1);
      tempoChanged = true;
    }

    if (tempoChanged) {
      lastTempoStepMs = now;
    }
  }
 
  // TIME SIGNATURE CONTROL (C/D one step per click, debounced)
  if (now - lastSigChangeMs >= SIG_CHANGE_DEBOUNCE_MS) {
    if (prevCState == HIGH && currentCState == LOW && sigNumerator > 1) {
      sigNumerator -= 1;
      beat          = 0;
      lastSigChangeMs = now;
    }

    if (prevDState == HIGH && currentDState == LOW && sigNumerator < 10) {
      sigNumerator += 1;
      beat          = 0;
      lastSigChangeMs = now;
    }
  }

  // Update previous states for edge detection
  prevCState = currentCState;
  prevDState = currentDState;

  // METRONOME TICK SCHEDULER
  if (now - lastTickMs >= beatDelay) {
    lastTickMs += beatDelay;
    
    if (beat == 0) {
      tone(SPEAKER, NOTE_C5, SOUND_DURATION);   // accented beat
    } else {
      tone(SPEAKER, NOTE_C4, SOUND_DURATION);
    }
    blink();

    // Advance beat within bar
    beat += 1;
    if (beat >= sigNumerator) {
      beat = 0;
    }
  }
}
// ============================
// RGB Pendulum: jittered sines
// ============================

// ----------------------------
// Pin configuration (PWM-capable)
// ----------------------------
#define BLUE 3
#define GREEN 5
#define RED 6

// ----------------------------
// Tunable configuration
// ----------------------------
const unsigned int UPDATE_INTERVAL_MS = 10;     // pacing per frame

// Base oscillator frequencies (Hz). Slightly different per channel.
const float BASE_HZ_R = 0.13f;
const float BASE_HZ_G = 0.15f;
const float BASE_HZ_B = 0.17f;

// Slow LFOs that bend phase (pendulum-like imperfection)
const float LFO_HZ_R = 0.010f;                  // ~100 s period
const float LFO_HZ_G = 0.012f;                  // ~83 s
const float LFO_HZ_B = 0.014f;                  // ~71 s
const float LFO_AMP  = 0.25f;                   // radians of phase bend (±)

// Small random-walk drift (keeps paths from repeating)
const float DRIFT_STEP_PER_UPDATE = 0.0000020f; // radians/ms per update step
const float DRIFT_CLAMP           = 0.00050f;   // max |drift| (radians/ms)

// Brightness scaling [0..1]
const float BRIGHTNESS = 1.0f;

// Initial phase offsets to spread channels evenly
const float PHASE_OFFSET = TWO_PI / 3.0f;       // 120 degrees

// ----------------------------
// Derived constants
// ----------------------------
const float OMEGA_R = TWO_PI * BASE_HZ_R / 1000.0f; // rad per ms
const float OMEGA_G = TWO_PI * BASE_HZ_G / 1000.0f;
const float OMEGA_B = TWO_PI * BASE_HZ_B / 1000.0f;

// ----------------------------
// State
// ----------------------------
unsigned long lastMs = 0;
float phaseR = 0.0f;
float phaseG = PHASE_OFFSET;           // +120°
float phaseB = 2.0f * PHASE_OFFSET;    // +240°

float driftR = 0.0f, driftG = 0.0f, driftB = 0.0f;

// ----------------------------
// Helpers
// ----------------------------
static inline float clampf(float v, float lo, float hi) {
  return v < lo ? lo : (v > hi ? hi : v);
}

static inline int toPWM(float x /* [-1,1] */) {
  float v = (x * 0.5f + 0.5f) * 255.0f * BRIGHTNESS;
  if (v < 0) v = 0; if (v > 255) v = 255;
  return (int)(v + 0.5f);
}

static inline float lfoPhaseBend(float lfoHz, float t_ms, float phaseBias) {
  return LFO_AMP * sinf(TWO_PI * lfoHz * (t_ms / 1000.0f) + phaseBias);
}

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  // Seed RNG without relying on A0
  randomSeed(millis());

  lastMs = millis();
}

void loop() {
  const unsigned long now = millis();
  const unsigned long dtMs = now - lastMs;
  lastMs = now;

  // Tiny random walk on frequency drift per channel
  // random(-1, 2) returns -1, 0, or 1
  driftR = clampf(driftR + (float)random(-1, 2) * DRIFT_STEP_PER_UPDATE, -DRIFT_CLAMP, DRIFT_CLAMP);
  driftG = clampf(driftG + (float)random(-1, 2) * DRIFT_STEP_PER_UPDATE, -DRIFT_CLAMP, DRIFT_CLAMP);
  driftB = clampf(driftB + (float)random(-1, 2) * DRIFT_STEP_PER_UPDATE, -DRIFT_CLAMP, DRIFT_CLAMP);

  // Advance base phases with small per-channel drifts
  phaseR += (OMEGA_R + driftR) * (float)dtMs;
  phaseG += (OMEGA_G + driftG) * (float)dtMs;
  phaseB += (OMEGA_B + driftB) * (float)dtMs;

  // Slow phase bends (different biases to avoid symmetry)
  const float t_ms = (float)now;
  const float bendR = lfoPhaseBend(LFO_HZ_R, t_ms, 0.31f);
  const float bendG = lfoPhaseBend(LFO_HZ_G, t_ms, 2.17f);
  const float bendB = lfoPhaseBend(LFO_HZ_B, t_ms, 4.02f);

  // Compute channel values
  const int redValue   = toPWM(sinf(phaseR + bendR));
  const int greenValue = toPWM(sinf(phaseG + bendG));
  const int blueValue  = toPWM(sinf(phaseB + bendB));

  // Output
  analogWrite(RED, redValue);
  analogWrite(GREEN, greenValue);
  analogWrite(BLUE, blueValue);

  // Soft pacing
  delay(UPDATE_INTERVAL_MS);
}


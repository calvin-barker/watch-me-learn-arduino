# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Repository Overview

This is a personal Arduino learning repository containing experimental sketches from the Elegoo tutorial kit. Projects focus on LED control, timing, and animation effects.

## Development Workflow

### Arduino IDE Commands
- **Open sketch**: Open any `.ino` file in the Arduino IDE
- **Upload to board**: Select board/port in Tools menu, then click Upload (or Ctrl+U / Cmd+U)
- **Verify/Compile**: Click Verify button (or Ctrl+R / Cmd+R) to check for compilation errors

### Testing Hardware
This repository uses physical Arduino hardware with LEDs. To test changes:
1. Connect Arduino board via USB
2. Ensure correct board type is selected in Arduino IDE (Tools > Board)
3. Select the correct port (Tools > Port)
4. Upload the sketch and observe LED behavior

There are no automated tests - verification is done by observing LED output.

## Code Architecture

### Project Organization
Sketches are organized by Elegoo tutorial lesson number:
- `elegoo_tutorial/lesson_X/project_name/` - Each project has its own directory
- Main sketch file is always `project_name.ino`

### Common Patterns

**Pin Definitions**: Hardware pins are defined at the top using `#define`:
```cpp
#define RED 6
#define GREEN 5
#define BLUE 3
```

**Timing Control**: Projects use either:
- Simple `delay()` for blocking timing (blink_sos, dimmer)
- Delta-time tracking with `millis()` for non-blocking animations (pendulum_led)

**LED Control**:
- Digital on/off: `digitalWrite(pin, HIGH/LOW)`
- Analog brightness (PWM): `analogWrite(pin, 0-255)`

**Animation Techniques**:
- Sine waves for smooth color transitions (sine_led)
- Phase offsets for multi-channel effects (pendulum_led uses 120° spacing)
- LFO (Low Frequency Oscillator) phase bending for organic movement (pendulum_led)
- Small random drift to prevent repetitive patterns (pendulum_led)

### Project Complexity Levels
1. **Basic**: blink_sos - Simple timing and digital output
2. **Intermediate**: sine_led, dimmer - PWM control and math functions
3. **Advanced**: pendulum_led - Complex phase math, drift, and non-blocking timing

## Hardware Context

Projects assume Elegoo tutorial kit components:
- Arduino board (Uno or compatible)
- RGB LEDs on PWM-capable pins (typically 3, 5, 6)
- Buttons with INPUT_PULLUP configuration (dimmer)
- Built-in LED (LED_BUILTIN) for basic projects

Pin numbers in sketches correspond to physical Arduino pin headers.

# watch-me-learn-arduino

A collection of Arduino experiments and projects as I learn/play with
the fundamentals of electronics and microcontrollers.

## About

This repository documents my learnings with Arduino through hands-on
experimentation. It contains various sketches and projects, primarily
working through tutorials and creating remixes of example code.

## Hardware

- Arduino board (based on project files)
- Various LEDs and components from the Elegoo tutorial kit

## Project Structure

```plaintext
elegoo_tutorial/
├── lesson_2/
│   └── blink_sos/          # SOS signal using LED blinks
├── lesson_4/
│   ├── sine_led/           # LED brightness control using sine wave
│   └── pendulum_led/       # Pendulum-inspired LED animation
└── lesson_5/
    └── dimmer/             # LED dimmer circuit
```

## Getting Started

### Using Arduino CLI (Recommended)

1. **Install Arduino CLI** (macOS with Homebrew):
   ```bash
   brew install arduino-cli
   ```

2. **Initialize configuration**:
   ```bash
   # Create default configuration file
   arduino-cli config init
   ```

3. **Update package index**:
   ```bash
   # Download latest package index for boards
   arduino-cli core update-index
   ```

4. **Install Arduino AVR core**:
   ```bash
   # Install support for Arduino Uno and similar boards
   arduino-cli core install arduino:avr
   ```

5. **Verify installation**:
   ```bash
   # List installed cores
   arduino-cli core list

   # Detect connected boards
   arduino-cli board list
   ```

6. **Compile a sketch**:
   ```bash
   # Compile for Arduino Uno
   arduino-cli compile --fqbn arduino:avr:uno elegoo_tutorial/lesson_2/blink_sos
   ```

7. **Upload to board**:
   ```bash
   # Replace /dev/cu.usbmodem2101 with your board's port from step 5
   arduino-cli upload -p /dev/cu.usbmodem2101 --fqbn arduino:avr:uno elegoo_tutorial/lesson_2/blink_sos
   ```

8. **Monitor serial output** (optional):
   ```bash
   # View serial output at 9600 baud
   arduino-cli monitor -p /dev/cu.usbmodem2101 -c baudrate=9600
   ```

### Using Justfile shortcuts

This repository includes a `justfile` for common commands. Install [just](https://github.com/casey/just) and run from any sketch directory:

```bash
# Compile current directory sketch
just compile

# Upload to board (edit PORT in justfile first)
just upload

# Monitor serial output
just monitor
```

## Projects

### Lesson 2: Blink SOS

A remix of the basic blink sketch that outputs an SOS signal in Morse code.

### Lesson 4: LED Animations

- **Sine LED**: Uses sine wave calculations to create smooth RGB LED brightness transitions
- **Pendulum LED**: Creates a pendulum-like swinging effect with an RGB LED

### Lesson 5: Dimmer

A basic LED dimmer implementation exploring PWM control.

## Learning Resources

Following along with the Elegoo tutorial kit and experimenting with variations
of the provided examples.

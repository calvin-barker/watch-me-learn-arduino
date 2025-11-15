# Justfile for Arduino CLI shortcuts
# Usage: run these commands from within a sketch directory (e.g., elegoo_tutorial/lesson_2/blink_sos/)
# Note: Set --working-directory to override the sketch location

# Configuration - edit these to match your setup
BOARD := "arduino:avr:uno"
PORT := "/dev/cu.usbmodem2101"
BAUDRATE := "9600"

# Compile the sketch in the current directory
compile:
    arduino-cli compile --fqbn {{BOARD}} {{invocation_directory()}}

# Upload the compiled sketch to the board
upload:
    arduino-cli upload -p {{PORT}} --fqbn {{BOARD}} {{invocation_directory()}}

# Monitor serial output from the board
monitor:
    arduino-cli monitor -p {{PORT}} -c baudrate={{BAUDRATE}}

# Compile and upload in one command
flash: compile upload

# Full workflow: compile, upload, and start monitoring
run: compile upload monitor

# List all connected boards (useful for finding PORT)
boards:
    arduino-cli board list

# Clean build artifacts
clean:
    rm -rf {{invocation_directory()}}/build/

# Show this help message
help:
    @just --list

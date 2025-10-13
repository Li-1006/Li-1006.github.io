// ===== Configuration =====
int Red = 9;   // Red LED
int Yellow = 10;   // Yellow LED
int Blue = 6;   // Blue LED
int BTN   = 2;   // Button D2

int STEP = 5;          // fade step size
int STEP_DELAY = 20;  // delay per step in ms

volatile bool running = true;        // true=start, false=stop

// Debounce variables
unsigned long lastChange = 0;
const unsigned long debounceMs = 25;
int stableBtn = HIGH;                // INPUT_PULLUP: HIGH=Not pressed, LOW=Pressed

// Turn off lights at once
void allOff() {
  analogWrite(Red, 0);
  analogWrite(Yellow, 0);
  analogWrite(Blue, 0);
}

// Read button and debounce, detect "press" to switch play/pause
void pollButtonToggle() {
  int readNow = digitalRead(BTN);
  if (readNow != stableBtn) {
    lastChange = millis();           // Record change time
  }
  if (millis() - lastChange > debounceMs) {
    // Confirm after stabilization
    if (stableBtn == HIGH && readNow == LOW) {
      // Detect a press -> switch play/pause
      running = !running;
    }
    stableBtn = readNow;
  }
}

// Stay at the current brightness when paused and continue polling the button until playback resumes
void waitWhilePaused(uint8_t pin, int value) {
  while (!running) {
    pollButtonToggle();              // Wait until you press Resume again
    analogWrite(pin, value);
    delay(5);
  }
}

// Perform a fade-in->fade-out on a certain LED, and pause/resume it at any time
void fadeOne(uint8_t pin) {
  allOff();

  // Fadein 0->255
  for (int v = 0; v <= 255; v += STEP) {
    pollButtonToggle();
    if (!running) waitWhilePaused(pin, v);
    analogWrite(pin, v);
    delay(STEP_DELAY);
  }
  // Fadeout 255->0
  for (int v = 255; v >= 0; v -= STEP) {
    pollButtonToggle();
    if (!running) waitWhilePaused(pin, v);
    analogWrite(pin, v);
    delay(STEP_DELAY);
  }
  // Guaranteed to be destroyed at the end
  digitalWrite(pin, LOW);
}

void setup() {
  pinMode(Red, OUTPUT);
  pinMode(Yellow, OUTPUT);
  pinMode(Blue, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);        // Internal pull-up, pressed = LOW
  allOff();
}

void loop() {
  fadeOne(Red);
  fadeOne(Yellow);
  fadeOne(Blue);
  // Repeated cycle
}
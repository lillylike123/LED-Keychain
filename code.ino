// ---- PINS ----
const int motionPin = 2;   // PIR sensor OUT
const int ledPin = 9;      // LED or MOSFET gate (for strip)

// ---- STATE ----
int mode = 0;
bool lastMotionState = false;

unsigned long lastTriggerTime = 0;
const unsigned long debounceTime = 2000; // prevents spam switching

void setup() {
  pinMode(motionPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  bool motion = digitalRead(motionPin);

  // detect rising edge (no motion → motion)
  if (motion && !lastMotionState && millis() - lastTriggerTime > debounceTime) {
    mode = (mode + 1) % 4;  // cycle designs
    lastTriggerTime = millis();
    Serial.println(mode);
  }

  lastMotionState = motion;

  // run current mode
  switch (mode) {
    case 0:
      breathe();
      break;
    case 1:
      strobe();
      break;
    case 2:
      fadeSimple();
      break;
    case 3:
      sparkle();
      break;
  }
}

// ---- MODES ----

void breathe() {
  for (int i = 0; i < 255; i++) {
    analogWrite(ledPin, i);
    delay(5);
  }
  for (int i = 255; i > 0; i--) {
    analogWrite(ledPin, i);
    delay(5);
  }
}

void strobe() {
  digitalWrite(ledPin, HIGH);
  delay(80);
  digitalWrite(ledPin, LOW);
  delay(80);
}

void fadeSimple() {
  analogWrite(ledPin, 120);
  delay(50);
  analogWrite(ledPin, 30);
  delay(50);
}

void sparkle() {
  int val = random(50, 255);
  analogWrite(ledPin, val);
  delay(60);
}

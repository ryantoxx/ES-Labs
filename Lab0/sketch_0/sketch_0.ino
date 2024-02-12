const int BUTTON_PIN = 2; // Pinul la care este conectat butonul
const int LED_PIN = 13;   // Pinul la care este conectat LED-ul

int buttonState = 0;     // Variabilă pentru starea butonului

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN); // Citeste starea butonului

  if (buttonState == HIGH) { // Daca butonul este apasat
    digitalWrite(LED_PIN, HIGH); // Aprinde LED-ul
  } else {
    digitalWrite(LED_PIN, LOW); // Stinge LED-ul
  }
}

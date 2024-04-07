#include "relay.h"
#include <Arduino.h>

void relay_init(void) {
  pinMode(RELAY_PIN, OUTPUT);
}

void relay_on(void) {
  digitalWrite(RELAY_PIN, HIGH);
}

void relay_off(void) {
  digitalWrite(RELAY_PIN, LOW);
}
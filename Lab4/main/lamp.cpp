#include "lamp.h"
#include "relay.h"

void lamp_init(void) {
  relay_init();
}

void lamp_on(void) {
  relay_on(); 
}

void lamp_off(void) {
  relay_off();
}
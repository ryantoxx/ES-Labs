#include <Arduino.h>
#include <stdio.h>

#define LED_PIN 12
#define BAUD_RATE 9600
#define TEXT_ON  "LED_ON"
#define TEXT_OFF  "LED_OFF"

int my_putChar(char ch, FILE * f) {
  return Serial.write(ch);
}
char my_getChar(FILE * f) {
  while(!Serial.available()) {
  }
  return Serial.read();
}

void setup() {
  Serial.begin(BAUD_RATE);
  FILE *my_stream = fdevopen(my_putChar, my_getChar);
  stdin = stdout = my_stream;
  pinMode(LED_PIN, OUTPUT);
  printf("Select 'LED_ON' OR 'LED_OFF' to change the state of the led: ");
}
void loop() {
    char command[64] = "";
    scanf("%s", command);
    if (strcmp(command, TEXT_ON) == 0) {
      digitalWrite(LED_PIN, HIGH);
      printf("The led has turned on. => ");
    }
    else if (strcmp(command, TEXT_OFF) == 0) {
      digitalWrite(LED_PIN, LOW);
      printf("The led has turned off. => ");
    }
    else {
      printf("No such command available. ");
    }
  }

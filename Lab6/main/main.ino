// ---------------- BUTTONS
#define BUTTON_NORTH_PIN 11
#define BUTTON_EAST_PIN 2

#define NONE_REQ 0b00
#define NORTH_REQ 0b01
#define EAST_REQ 0b10
#define BOTH_REQ 0b11

// ---------------- TRAFIC LIGHT
#define NORTH_RED_PIN 10
#define NORTH_YELLOW_PIN 9
#define NORTH_GREEN_PIN 8

#define EAST_RED_PIN 5
#define EAST_YELLOW_PIN 4
#define EAST_GREEN_PIN 3

// ---------------- STATES
#define NORTH_ACTIVE 0    // 0b00
#define NORTH_PASSIVE 1   // 0b01

#define EAST_ACTIVE 2     // 0b10
#define EAST_PASSIVE 3    // 0b11

// ---------------- OUTPUT
#define GO_NORTH_OUT 0b100001
#define WAIT_NORTH_OUT 0b110010
#define GO_EAST_OUT 0b001100
#define WAIT_EAST_OUT 0b010110

// ---------------- WAIT TIME
#define GO_NORTH_TIME 1500
#define WAIT_NORTH_TIME 1000
#define GO_EAST_TIME 1500
#define WAIT_EAST_TIME 1000

#define BAUD_RATE 9600

struct State {
  unsigned long out;
  unsigned long time;
  unsigned long next[4];
};

typedef const struct State STyp;

STyp FSM[4] = {
    {GO_NORTH_OUT, GO_NORTH_TIME, {NORTH_ACTIVE, NORTH_PASSIVE, NORTH_ACTIVE, NORTH_PASSIVE}},
    {WAIT_NORTH_OUT, WAIT_NORTH_TIME, {EAST_ACTIVE, EAST_ACTIVE, EAST_ACTIVE, EAST_ACTIVE}},
    {GO_EAST_OUT, GO_EAST_TIME, {EAST_ACTIVE, EAST_ACTIVE, EAST_PASSIVE, EAST_PASSIVE}},
    {WAIT_EAST_OUT, WAIT_EAST_TIME, {NORTH_ACTIVE, NORTH_ACTIVE, NORTH_ACTIVE, NORTH_ACTIVE}}
};

// STyp FSM[4] = {
//                   // 00  01 10  11
//     {0b100001, 1500, {0, 1, 0, 1}},
//     {0b110010, 1000, {2, 2, 2, 2}},
//     {0b001100, 1500, {2, 2, 3, 3}},
//     {0b010110, 1000, {0, 0, 0, 0}}
// };

int FSM_State = NORTH_ACTIVE;

int GetInput(void) {
  int northButton = digitalRead(BUTTON_NORTH_PIN);
  int eastButton = digitalRead(BUTTON_EAST_PIN);
  if (northButton && eastButton)
    return BOTH_REQ;
  else if (eastButton)
    return EAST_REQ;
  else if (northButton)
    return NORTH_REQ;
  else
    return NONE_REQ; 
}

void SetOutput(int out) {
  int ledState;
  ledState = (out & (1 << 5)) ? HIGH : LOW;
  digitalWrite(EAST_RED_PIN, ledState);
  ledState = (out & (1 << 4)) ? HIGH : LOW;
  digitalWrite(EAST_YELLOW_PIN, ledState);
  ledState = (out & (1 << 3)) ? HIGH : LOW;
  digitalWrite(EAST_GREEN_PIN, ledState);
  ledState = (out & (1 << 2)) ? HIGH : LOW;
  digitalWrite(NORTH_RED_PIN, ledState);
  ledState = (out & (1 << 1)) ? HIGH : LOW;
  digitalWrite(NORTH_YELLOW_PIN, ledState);
  ledState = (out & (1 << 0)) ? HIGH : LOW;
  digitalWrite(NORTH_GREEN_PIN, ledState);
}

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(BUTTON_NORTH_PIN, INPUT_PULLUP);
  pinMode(BUTTON_EAST_PIN, INPUT_PULLUP);

  pinMode(NORTH_RED_PIN, OUTPUT);
  pinMode(NORTH_YELLOW_PIN, OUTPUT);
  pinMode(NORTH_GREEN_PIN, OUTPUT);

  pinMode(EAST_RED_PIN, OUTPUT);
  pinMode(EAST_YELLOW_PIN, OUTPUT);
  pinMode(EAST_GREEN_PIN, OUTPUT);

  FSM_State = NORTH_ACTIVE;
}

void loop() {
  int FSM_Output = FSM[FSM_State].out;
  SetOutput(FSM_Output);
  delay(FSM[FSM_State].time);

  int FSM_Inputs = GetInput();
  FSM_State = FSM[FSM_State].next[FSM_Inputs];
}

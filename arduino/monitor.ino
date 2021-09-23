#define ADDR_SIZE 16
#define DATA_SIZE 8
#define CLOCK 2
#define READ_WRITE  3

const byte addr_pins[] = { 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52 };
const byte data_pins[] = { 39, 41, 43, 45, 47, 49, 51, 53 };

void setupInput(const byte* pins, int count) {
  for (int i = 0; i < count; i++) {
    pinMode(pins[i], INPUT);
  }  
}

void setup() {
  setupInput(addr_pins, ADDR_SIZE);
  setupInput(data_pins, DATA_SIZE);
 
  pinMode(CLOCK, INPUT);
  pinMode(READ_WRITE, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(CLOCK), onClock, RISING);

  Serial.begin(57600);
}

unsigned int readInput(const byte* pins, int count) {
  unsigned int value = 0;

  for (int i = 0; i < count; i++) {
    int bit = digitalRead(pins[i]);
    Serial.print(bit);
    value = (value << 1) + bit;
  }

  return value;
}

void onClock() {
  digitalWrite(LED_BUILTIN, HIGH);
  unsigned int addr = readInput(addr_pins, ADDR_SIZE); 
  Serial.print("  ");
  byte data = readInput(data_pins, DATA_SIZE);
  bool reading = digitalRead(READ_WRITE);
  char output[15];
  sprintf(output, "  %04X  %c %02X", addr, reading ? 'r' : 'w', data);
  Serial.println(output);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
}

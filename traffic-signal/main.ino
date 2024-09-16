const int GREEN_LED = 12;
const int YELLOW_LED = 14;
const int RED_LED = 26;

// GREEN: 20 s = 20.000 ms
// YELLOW: 3 s = 3.000 ms
// RED: 40 s = 40.000 ms

void setup() {
  Serial.begin(115200);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
}

void loop() {
  awaitAndProgress(GREEN_LED, 20000);
  awaitAndProgress(YELLOW_LED, 3000);
  awaitAndProgress(RED_LED, 40000);
}

void awaitAndProgress(int sign, int time){
  digitalWrite(sign, HIGH);
  delay(time);
  digitalWrite(sign, LOW);
}
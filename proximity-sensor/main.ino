const int trigPin01 = 14;
const int echoPin01 = 27;

const int trigPin02 = 17;
const int echoPin02 = 16;

#define SOUND_SPEED 0.034
#define MIN_DISTANCE_IN_CM 60.0
#define MAX_DISTANCE_IN_CM 120.0

int peopleInRoom = 0;

void ensureInitalized(int trig, int echo) {
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

void setup() {
    Serial.begin(115200);
    ensureInitalized(trigPin01, echoPin01);
    ensureInitalized(trigPin02, echoPin02);
}

void loop() {
    clearAll();

    float distanceTrig01 = getDistance(trigPin01, echoPin01); // cm
    Serial.println("Distancia Sensor 01: " + String(distanceTrig01) + " cm");
    if (distanceTrig01 > 0 && distanceTrig01 <= MIN_DISTANCE_IN_CM) {
        Serial.println("Uma pessoa entrou na sala");
        peopleInRoom++;
    }

    delayMicroseconds(2);

    float distanceTrig02 = getDistance(trigPin02, echoPin02); // cm
    Serial.println("Distancia Sensor 02: " + String(distanceTrig02) + " cm");
    if (distanceTrig02 >= MIN_DISTANCE_IN_CM && distanceTrig02 <= MAX_DISTANCE_IN_CM) {
        Serial.println("Uma pessoa saiu da sala");
        peopleInRoom--;
    }

    delay(1000);

    if (peopleInRoom < 0) peopleInRoom = 0;
    
    Serial.println();
    Serial.println("Pessoas na sala: " + String(peopleInRoom));
}


int getDistance(int trigTarget, int echoTarget) {
    emitPulse(trigTarget);
    long duration = pulseIn(echoTarget, HIGH);
    return (duration * SOUND_SPEED) / 2;
}

void emitPulse(int trigPin) {
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
}

void clearAll() {
    digitalWrite(trigPin01, LOW);
    digitalWrite(trigPin02, LOW);
    delayMicroseconds(2);
}

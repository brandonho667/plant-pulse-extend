#define IN_PIN A0
#define OUT_PIN 4
unsigned long lastPulse = 0;
int outPinStatus = 0;

void setup() {
  pinMode(IN_PIN, INPUT);
  pinMode(OUT_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  float in_val = analogRead(IN_PIN)* (5.0 / 1023.0);

  Serial.print("Timestamp:");
  Serial.print(millis());
  Serial.print(",");

  Serial.print("Input:");
  Serial.print(in_val);
  Serial.print(",");
  

  if (in_val > 2 && !outPinStatus) {
    outPinStatus = 1;
    digitalWrite(OUT_PIN, HIGH);
    lastPulse = millis();
    // Serial.write("Got high, setting output");
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(250);
    // Serial.write("Pulse extended");
    // analogWrite(OUT_PIN, 0);
    // digitalWrite(LED_BUILTIN, LOW);
  } 
  
  if (millis() - lastPulse > 250 && outPinStatus) {
    outPinStatus = 0;
    digitalWrite(OUT_PIN, LOW);
    // digitalWrite(LED_BUILTIN, LOW);
  }
  Serial.print("Output:");
  Serial.println(outPinStatus*3);

}

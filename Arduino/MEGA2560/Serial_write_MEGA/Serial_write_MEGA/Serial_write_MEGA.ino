#define BAUDRATE 115200
#define MAX_FPS 30 // Max Frames Per Second

int red = 0;
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(BAUDRATE);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= (unsigned long)(((float)1/MAX_FPS)*1000)) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    
    Serial.print("[");
    Serial.print(millis());
    Serial.print(" ms] ");
    Serial.print("red value: ");
    Serial.println(red);
    
    analogWrite(LED_BUILTIN, red);
  }
}

void serialEvent() {
  while (Serial.available()) {
    red = Serial.parseInt(); 
  }
}

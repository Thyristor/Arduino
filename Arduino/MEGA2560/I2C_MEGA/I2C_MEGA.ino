#include <Wire.h>

#define BAUDRATE 115200

#define BLACK   "\033[1;30m"    // ^[1;30m   Bg Black on white
#define RED     "\033[1;31m"    // ^[1;31m   Bg Red foreground
#define GREEN   "\033[1;32m"    // ^[1;32m   Bg Green foreground
#define YELLOW  "\033[1;33m"    // ^[1;33m   Bg Yellow foreground
#define BLUE    "\033[1;34m"    // ^[1;34m   Bg Blue foreground
#define MAGENTA "\033[1;35m"    // ^[1;35m   Bg Magenta foreground
#define CYAN    "\033[1;36m"    // ^[1;36m   Bg Cyan foreground
#define WHITE   "\033[1;37m"    // ^[1;37m   Bg White foreground
#define RESET   "\033[1;39m"    // ^[1;39m   RESET color

#define MAX_STRING  100
#define MAX_FPS     2 // Max Frames Per Second

String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
unsigned int i = 0;

int brightness = 0;  // how bright the LED is
int fadeAmount = 5;  // how many points to fade the LED by
int sensorValue;     // read the input on analog pin 0
  
unsigned long previousMillis = 0;  // will store last time LED was updated

byte x = 0;

void setup() {
  // put your setup code here, to run once:
  // initialize serial:
  Serial.begin(BAUDRATE);
  Serial.setTimeout(5000); // 5 s
  while(!Serial); // Loop until UART is ready
  Serial.println("");
  Serial.print("[");
  Serial.print(millis());
  Serial.print(" ms]\t");
  Serial.println("UART is ready");
  
  // reserve MAX_STRING bytes for the inputString:
  inputString.reserve(MAX_STRING);
  Serial.print("[");
  Serial.print(millis());
  Serial.print(" ms]\t");
  Serial.println("Reserve space for inputString");
  
  // declare pin 9 to be an output:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.print("[");
  Serial.print(millis());
  Serial.print(" ms]\t");
  Serial.println("Set pin mode LED_BUILTIN as OUTPUT");
  
  // Setup I2C
  pinMode(SCL, INPUT_PULLUP);
  pinMode(SDA, INPUT_PULLUP);
  Wire.begin(8);                // join i2c bus with address #8 slave
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event
  Serial.print("[");
  Serial.print(millis());
  Serial.print(" ms]\t");
  Serial.println("Set pin mode SCL and SDA as INPUT_PULLUP");
  
  Serial.print("\033[1;32m");
  Serial.print("[");
  Serial.print(millis());
  Serial.print(" ms]\t");
  Serial.print("MEGA2560 setup is ready");
  Serial.println("\033[1;39m");
}

void loop() {  
  // wait for 16 milliseconds to see the dimming effect
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= (unsigned long)(((float)1/MAX_FPS)*1000)) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    
    sensorValue = analogRead(A0);
    // print out the value you read:
    Serial.print("[");
    Serial.print(millis());
    Serial.print(" ms]\t");
    Serial.print("ADC value: ");
    Serial.println(sensorValue);
    
    // put your main code here, to run repeatedly:
    // print the string when a newline arrives:
    // set the brightness of pin 9:
    analogWrite(LED_BUILTIN, brightness);
    Serial.print("[");
    Serial.print(millis());
    Serial.print(" ms]\t");
    Serial.print("Set LED_BUILTIN brightness to: ");
    Serial.println(brightness);
    
    // change the brightness for next time through the loop:
    brightness += fadeAmount;
  
    // reverse the direction of the fading at the ends of the fade:
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
      Serial.print("[");
      Serial.print(millis());
      Serial.print(" ms]\t");
      Serial.print("Set fadeAmount to: ");
      Serial.println(fadeAmount);
    } // end of if
    
//    Wire.beginTransmission(4); // transmit to device #4
//    Wire.write("x is ");       // sends five bytes
//    Wire.write(x);             // sends one byte  
//    Wire.endTransmission();    // stop transmitting
//
//    x++;
  } // end of if currentMillis - previousMillis >= MAX_DELAY
  
  if (stringComplete) {
    Serial.print("[");
    Serial.print(millis());
    Serial.print(" ms]\t");
    Serial.println(inputString);
    
    Serial.print("Amount of characters: ");
    Serial.println(i);
    // clear the string:
    inputString = "";
    stringComplete = false;
    i = 0;
  } // end of if 
} // end of loop

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
//    Serial.readBytesUntil('\n', inputString, MAX_STRING);

    // add it to the inputString:
    inputString += inChar;
    i++;
    
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } // end if
  } // end while
} // end serialEvent

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) { // slave receiver
  Serial.print("\033[1;36m");
  Serial.print("[");
  Serial.print(millis());
  Serial.print(" ms]\t");
  while(1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);      // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.print(x);        // print the integer
  Serial.println("\033[1;39m");
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write("hello "); // respond with message of 6 bytes
  // as expected by master
}

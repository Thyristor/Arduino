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
#define MAX_FPS     30 // Max Frames Per Second

String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
unsigned int i = 0;

int brightness = 0;  // how bright the LED is
int fadeAmount = 5;  // how many points to fade the LED by

unsigned long previousMillis = 0;  // will store last time LED was updated

void setup() {
  // put your setup code here, to run once:
  // initialize serial:
  Serial.begin(BAUDRATE);
  Serial.setTimeout(5000); // 5 s
  while(!Serial); // Loop until UART is ready
  Serial.println("UART is ready");
  Serial.print(millis());
  Serial.println(" ms");
  
  // reserve MAX_STRING bytes for the inputString:
  inputString.reserve(MAX_STRING);
  Serial.println("Reserve space for inputString");
  Serial.print(millis());
  Serial.println(" ms");
  
  // declare pin 9 to be an output:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Set pin mode LED_BUILTIN as OUTPUT");
  Serial.print(millis());
  Serial.println(" ms");
}

void loop() {
  // wait for 16 milliseconds to see the dimming effect
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= (unsigned long)(((float)1/MAX_FPS)*1000)) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // put your main code here, to run repeatedly:
    // print the string when a newline arrives:
    // set the brightness of pin 9:
    analogWrite(LED_BUILTIN, brightness);
    Serial.print("Set LED_BUILTIN brightness to: ");
    Serial.print(brightness);
    Serial.println();
    Serial.print(millis());
    Serial.println(" ms");
  
    // change the brightness for next time through the loop:
    brightness += fadeAmount;
  
    // reverse the direction of the fading at the ends of the fade:
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
      Serial.print("Set fadeAmount to: ");
      Serial.print(fadeAmount);
      Serial.println();
      Serial.print(millis());
      Serial.println(" ms");
    } // end of if    
  } // end of if currentMillis - previousMillis >= MAX_DELAY
  
  if (stringComplete) {
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

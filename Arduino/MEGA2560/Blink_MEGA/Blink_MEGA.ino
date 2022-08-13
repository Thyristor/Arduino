/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

#define GPIO0 0
#define FLASH_PIN GPIO0
#define BLACK   "\033[1;30m"    // ^[1;30m   Bg Black on white
#define RED     "\033[1;31m"    // ^[1;31m   Bg Red foreground
#define GREEN   "\033[1;32m"    // ^[1;32m   Bg Green foreground
#define YELLOW  "\033[1;33m"    // ^[1;33m   Bg Yellow foreground
#define BLUE    "\033[1;34m"    // ^[1;34m   Bg Blue foreground
#define MAGENTA "\033[1;35m"    // ^[1;35m   Bg Magenta foreground
#define CYAN    "\033[1;36m"    // ^[1;36m   Bg Cyan foreground
#define WHITE   "\033[1;37m"    // ^[1;37m   Bg White foreground
#define RESET   "\033[1;39m"    // ^[1;39m   RESET color

bool toggle = false;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200); // Initialize UART
  Serial.setTimeout(5000); // 5 s
  while(!Serial); // Loop until UART is ready
  Serial.println("UART is ready");
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Set pin mode LED_BUILTIN as OUTPUT");
  Serial.println(millis());
}

// the loop function runs over and over again forever
void loop() {
  if(toggle) {
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
    Serial.println(GREEN "LED_BUILTIN ON" RESET);
    Serial.println(millis());
    //toggle = !toggle;
    //delay(500);                      // Wait for a second
  }
  else {
    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
    Serial.println(RED "LED_BUILTIN OFF" RESET);
    Serial.println(millis());
    //toggle = !toggle;
    //delay(500);                      // Wait 
  }
  toggle = !toggle;
  delay(500); // Wait 0,5 s
}

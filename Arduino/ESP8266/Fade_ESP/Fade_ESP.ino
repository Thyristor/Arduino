/*
  Fade

  This example shows how to fade an LED on pin 9 using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
  are identified with a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Fade
*/

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

int brightness = 0;   // how bright the LED is
int fadeAmount = 5;   // how many points to fade the LED by
int my_delay = 10;    // Set delay to 10 ms

// Called at the end of loop() when data is available. Use Serial.read() to capture this data.
void serialEvent() {
  Serial.println("Write delay in ms");
  //Serial.println(millis());
  my_delay = Serial.read(); // Statements
}

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(BAUDRATE); // Initialize UART
  Serial.setTimeout(5000); // 5 s
  while(!Serial); // Loop until UART is ready
  Serial.println("UART is ready");
  Serial.println(millis());
  
  // declare pin 9 to be an output:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Set pin mode LED_BUILTIN as OUTPUT");
  Serial.println(millis());
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 9:
  analogWrite(LED_BUILTIN, brightness);
  Serial.print("Set LED_BUILTIN brightness to: ");
  Serial.print(brightness);
  Serial.println();
  Serial.println(millis());

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
    Serial.print("Set fadeAmount to: ");
    Serial.print(fadeAmount);
    Serial.println();
    Serial.println(millis());
  }
  
  // wait for 10 milliseconds to see the dimming effect
  delay(my_delay);
}

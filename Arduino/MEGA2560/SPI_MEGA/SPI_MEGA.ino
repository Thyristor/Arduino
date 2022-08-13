// SPI ARDUINO SLAVE

#include <SPI.h>

#define BAUDRATE 115200
#define MAX_FPS   30 // Max Frames Per Second

#define BLACK   "\033[1;30m"    // ^[1;30m   Bg Black on white
#define RED     "\033[1;31m"    // ^[1;31m   Bg Red foreground
#define GREEN   "\033[1;32m"    // ^[1;32m   Bg Green foreground
#define YELLOW  "\033[1;33m"    // ^[1;33m   Bg Yellow foreground
#define BLUE    "\033[1;34m"    // ^[1;34m   Bg Blue foreground
#define MAGENTA "\033[1;35m"    // ^[1;35m   Bg Magenta foreground
#define CYAN    "\033[1;36m"    // ^[1;36m   Bg Cyan foreground
#define WHITE   "\033[1;37m"    // ^[1;37m   Bg White foreground
#define RESET   "\033[1;39m"    // ^[1;39m   RESET color

char buff[100];
volatile byte index;
volatile bool receivedone; /* use reception complete flag */

unsigned long previousMillis = 0;  // will store last time was updated

void setup() {
  // put your setup code here, to run once:
  // Set SPI Mega as slave
  Serial.begin(BAUDRATE);
  while(!Serial);

  Serial.println("\033[1;33m");
  Serial.print("[");
  Serial.print(millis());
  Serial.print(" ms]\t");
  Serial.print("MEGA2560 Slave!");
  Serial.println("\033[1;39m");
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.print("[");
  Serial.print(millis());
  Serial.print(" ms]\t");
  Serial.print("LED_BUILTIN pin: ");
  Serial.println(LED_BUILTIN); 

  SPCR |= bit(SPE); //_BV(SPE); //bit(SPE); /* Enable SPI */
  pinMode(MISO, OUTPUT); /* Make MISO pin as OUTPUT */
  index = 0;
  receivedone = false;
  SPI.attachInterrupt(); /* Attach SPI interrupt */
}

void loop() {
  if(receivedone) { /* Check and print received buffer if any */
    Serial.print("\033[1;33m"); // yellow
    Serial.print("[");
    Serial.print(millis());
    Serial.print(" ms]\t");
    Serial.print("buff: ");
    Serial.print(buff);
    Serial.println("\033[1;39m");
  
    Serial.print("[");
    Serial.print(millis());
    Serial.print(" ms]\t");
    if(!strcmp(buff, "LED OFF")) {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.print("\033[1;31m");
      Serial.print("LED is OFF");
    }
    else if(!strcmp(buff, "LED ON")) {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.print("\033[1;32m");
      Serial.print("LED is ON");
    }
    else {
      Serial.print("Default statement");
    }
    Serial.println("\033[1;39m");
    
    buff[index] = 0;
    index = 0;
    receivedone = false;
  }
} // end loop

// SPI interrupt routine
ISR (SPI_STC_vect) {
  uint8_t oldsrg = SREG;
  cli();
  byte c = SPDR;
  if(index < sizeof(buff)) {
    buff[index++] = c;
    if((c == '\r') || 
       (c == '\n') || 
       (c == '\0')) { /* Check for newline character as end of msg */
      receivedone = true;
    }
  }
  SREG = oldsrg;
}

// SPI ARDUINO MASTER
// SPI pins are:
// GPIO14 SCLK
// GPIO12 MISO
// GPIO13 MOSI
// GPIO15 CS

#include <SPI.h>

#define BAUDRATE 115200
#define MAX_FPS 2 // Max Frames Per Second
#define FLASHBTN 0

#define BLACK   "\033[1;30m"    // ^[1;30m   Bg Black on white
#define RED     "\033[1;31m"    // ^[1;31m   Bg Red foreground
#define GREEN   "\033[1;32m"    // ^[1;32m   Bg Green foreground
#define YELLOW  "\033[1;33m"    // ^[1;33m   Bg Yellow foreground
#define BLUE    "\033[1;34m"    // ^[1;34m   Bg Blue foreground
#define MAGENTA "\033[1;35m"    // ^[1;35m   Bg Magenta foreground
#define CYAN    "\033[1;36m"    // ^[1;36m   Bg Cyan foreground
#define WHITE   "\033[1;37m"    // ^[1;37m   Bg White foreground
#define RESET   "\033[1;39m"    // ^[1;39m   RESET color

unsigned long previousMillis = 0;  // will store last time LED was updated
uint8_t received_byte;
unsigned char btnstatus = 0;
unsigned char buff[] = {"Hello World!"};
unsigned char ledoff[] = {"LED OFF"};
unsigned char ledon[] = {"LED ON"};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUDRATE);
  while(!Serial);

  Serial.println("\033[1;35m");
  Serial.print("[");
  Serial.print(millis());
  Serial.print(" ms]\t");
  Serial.print("ESP8266 Master!");
  Serial.println("\033[1;39m");
  
  // declare pin 2 to be an output:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.print("[");
  Serial.print(millis());
  Serial.print(" ms]\t");
  Serial.print("LED_BUILTIN pin: ");
  Serial.println(LED_BUILTIN); 

  // declare pin 0 to be an input:
  pinMode(FLASHBTN, INPUT);
  Serial.print("[");
  Serial.print(millis());
  Serial.print(" ms]\t");
  Serial.print("FLASHBTN pin: ");
  Serial.println(FLASHBTN); 

  // SPI begin
  SPI.begin();                          // Begins the SPI communication
  //SPI.setClockDivider(SPI_CLOCK_DIV16); // Sets clock for SPI communication 80MHz/16 = 5MHz
  //SPI.setBitOrder(LSBFIRST);            // Sets Less Significant Byte First 
  //rcaSPI.setDataMode(SPI_MODE0);           // Sets Data Mode to SPI_MODE0
  pinMode(SS, OUTPUT);                  // Sets the Chip Select pin as output
  digitalWrite(SS, HIGH);               // Sets de CS pin HIGH to stop any communication    
}

void loop() {
  btnstatus = digitalRead(FLASHBTN);
  
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= (unsigned long)(((float)1/MAX_FPS)*1000)) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    digitalWrite(LED_BUILTIN, btnstatus);
    Serial.print("[");
    Serial.print(millis());
    Serial.print(" ms]\t");
    Serial.print("btnstatus: ");
    Serial.println(btnstatus);

    // read three bytes from master device
    SPI.beginTransaction(SPISettings(625000, MSBFIRST, SPI_MODE0));
    digitalWrite(SS, LOW);
    //SPI.transfer(0);
    if(btnstatus) {
      for(int i = 0; i < sizeof(ledoff); i++) {
        received_byte = SPI.transfer(ledoff[i]);
        Serial.print("\033[1;31m");
        Serial.print("[");
        Serial.print(millis());
        Serial.print(" ms]\t");
        Serial.print("ledoff[");
        Serial.print(i);
        Serial.print("]: ");
        Serial.print(ledoff[i]);
        Serial.print("\t");
        Serial.print("received_byte: ");
        Serial.print(received_byte);
        Serial.println("\033[1;39m");
      }  
    }
    else {
      for(int i = 0; i < sizeof(ledon); i++) {
        received_byte = SPI.transfer(ledon[i]);
        Serial.print("\033[1;32m");
        Serial.print("[");
        Serial.print(millis());
        Serial.print(" ms]\t");
        Serial.print("ledon[");
        Serial.print(i);
        Serial.print("]: ");
        Serial.print(ledon[i]);
        Serial.print("\t");
        Serial.print("received_byte: ");
        Serial.print(received_byte);
        Serial.println("\033[1;39m");
      }
    }
      
    for(int i = 0; i < sizeof(buff); i++) {
      received_byte = SPI.transfer(buff[i]);
      Serial.print("\033[1;33m");
      Serial.print("[");
      Serial.print(millis());
      Serial.print(" ms]\t");
      Serial.print("buff[");
      Serial.print(i);
      Serial.print("]: ");
      Serial.print(buff[i]);
      Serial.print("\t");
      Serial.print("received_byte: ");
      Serial.print(received_byte);
      Serial.println("\033[1;39m");
    }
    digitalWrite(SS, HIGH);
    SPI.endTransaction();  
  } // currentmillis
}

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

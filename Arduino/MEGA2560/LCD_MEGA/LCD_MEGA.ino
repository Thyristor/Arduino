// Program an LCD 16x2 
#include <LiquidCrystal.h>

#define BAUDRATE 115200
#define MAX_FPS 2 // Max Frames Per Second

#define RS  49    // pin 4 yellow
#define RW  48    // pin 5 green
#define E   47    // pin 6 blue
#define DB4 46    // pin 11 purple
#define DB5 45    // pin 12 grey
#define DB6 44    // pin 13 white
#define DB7 43    // pin 14 brown

#define BLACK   "\033[1;30m"    // ^[1;30m   Bg Black on white
#define RED     "\033[1;31m"    // ^[1;31m   Bg Red foreground
#define GREEN   "\033[1;32m"    // ^[1;32m   Bg Green foreground
#define YELLOW  "\033[1;33m"    // ^[1;33m   Bg Yellow foreground
#define BLUE    "\033[1;34m"    // ^[1;34m   Bg Blue foreground
#define MAGENTA "\033[1;35m"    // ^[1;35m   Bg Magenta foreground
#define CYAN    "\033[1;36m"    // ^[1;36m   Bg Cyan foreground
#define WHITE   "\033[1;37m"    // ^[1;37m   Bg White foreground
#define RESET   "\033[1;39m"    // ^[1;39m   RESET color

unsigned long previousMillis = 0; // will store last time LED was updated
int incomingByte[16];
int pos = 0;
byte firstTime = true;

LiquidCrystal lcd(RS, RW, E, DB4, DB5, DB6, DB7);
// make some custom characters:

byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};


byte smiley[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};


byte frownie[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b10001
};


byte armsDown[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b01010
};


byte armsUp[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00100,
  0b01010
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUDRATE);
  while(!Serial);

  Serial.println("\033[1;35m");
  Serial.print("[");
  Serial.print(millis());
  Serial.print(" ms]\t");
  Serial.print("Arduino MEGA 2560 with LCD 16x2!");
  Serial.println("\033[1;39m");

  // declare pin 2 to be an output:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.print("[");
  Serial.print(millis());
  Serial.print(" ms]\t");
  Serial.print("LED_BUILTIN pin: ");
  Serial.println(LED_BUILTIN);

  lcd.begin(16, 2);
  lcd.createChar(0, heart); // create a new character
  lcd.createChar(1, smiley); // create a new character
  lcd.createChar(2, frownie); // create a new character
  lcd.createChar(3, armsDown); // create a new character
  lcd.createChar(4, armsUp); // create a new character
  lcd.clear();
  //lcd.setCursor(0, 0);
  for(int i=0; i<5; i++) {
    lcd.home();
    lcd.print("Hello ");
    lcd.write(byte(i));
    lcd.print(" World!");
    delay(1000); // 1 second delay 
  }
  //lcd.cursor();
  //lcd.blink();
  //lcd.display();
}

void loop() {
  
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= (unsigned long)(((float)1/MAX_FPS)*1000)) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    digitalWrite(LED_BUILTIN, !(digitalRead(LED_BUILTIN)));
    Serial.print("[");
    Serial.print(millis());
    Serial.print(" ms]\t");
    Serial.print("LED_BUILTIN is: ");
    Serial.println(digitalRead(LED_BUILTIN));

    lcd.clear(); // Clear screen
    
    while(Serial.available() > 0) {
      if(firstTime) {
        pos = 0;
        firstTime = false;
      }
      incomingByte[pos] = Serial.read();
      pos++;
    }
    firstTime = true;

    lcd.home();
    for(int i=0; i<pos; i++){
      lcd.write(incomingByte[i]);
    }
    
    lcd.setCursor(0, 1);
    lcd.print("seconds: ");
    lcd.print(millis() / 1000); // print the number of seconds since reset:
    //lcd.scrollDisplayLeft();    
  } // end if millis
}

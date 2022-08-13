/*
  ESP8266 Blink by Simon Peter
  Blink the blue LED on the ESP-01 module
  This example code is in the public domain

  The blue LED on the ESP-01 module is connected to GPIO1
  (which is also the TXD pin; so we cannot use Serial.print() at the same time)

  Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/

// Load Wi-Fi library
//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
//#include <WiFiClient.h>

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

// Replace with your network credentials
const char* ssid     = "MiFibra-F6CB";
const char* password = "bz5Pkign";

bool toggle = false;

void blink() {  
  Serial.println(MAGENTA "Interrupt calling to blink" RESET);
}

void setup() {
  Serial.begin(115200); // Initialize UART
  Serial.setTimeout(5000); // 5 s
  while(!Serial); // Loop until UART is ready
  Serial.println("UART is ready");
  Serial.println(millis());
  
  pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED_BUILTIN pin as an output
  Serial.println("Set pin mode LED_BUILTIN as OUTPUT");
  Serial.println(millis());
  
  pinMode(FLASH_PIN, INPUT); // Initialize the FLASH_PIN pin as an input
  Serial.println("Set pin mode FLASH_PIN as INPUT");
  Serial.println(millis());
  
//  attachInterrupt(digitalPinToInterrupt(FLASH_PIN), blink, FALLING); // Define interrupt pin
//  Serial.println("Set interrupt pin to GPIO0");
//  Serial.println(millis());

//  // Establecer modo estación
//  WiFi.mode(WIFI_STA);
//
//  // Conexión con red WiFi
//  WiFi.begin(ssid, password);
//  Serial.println("INICIO WIFI");
//  Serial.println(millis());
//
//  // Ahora esperamos hasta que la conexión se ha establecido
//  while (WiFi.status() != WL_CONNECTED);
//  Serial.println(millis());
//  Serial.print("CONECTADO A WIFI ");
//  Serial.println(ssid);
  
//  Serial.println("INICIO WIFICLIENT");
//  Serial.println(millis());
//  // Petición HTTP
//  WiFiClient client;
//  HTTPClient http;
//  if (http.begin(client, "http://jigsaw.w3.org/HTTP/connection.html")) {
//    int httpCode = http.GET();
//    if (httpCode > 0) {
//      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
//        String payload = http.getString();
//      }
//    }
//    http.end();
//  } else {
//    Serial.println(RED "ERROR WIFICLIENT" RESET);
//  }
//  Serial.println(millis());
//  Serial.println("FIN WIFICLIENT");
//  delay(1000);
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
  
//  Serial.println(MAGENTA "INICIO ESP8266 DEEP SLEEP" RESET);
//  delay(1000);
//  Serial.end();
//  Serial.println(millis());
//  Serial.println("Modo ESP8266 deep sleep durante 10 segundos");
//  ESP.deepSleep(10e6); // 10e6 es 10.000.000 microsegundos
}

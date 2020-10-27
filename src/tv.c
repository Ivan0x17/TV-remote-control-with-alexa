 /*
GNU GENERAL PUBLIC LICENSE
Version 3, 29 June 2007

Obiettivo:
Questo sketch a l'obbiettivo di realizzare un telecomando smart per comandare il TV con Alexa

Dipendenze:
Software:
    - IRremoteESP8266 -->  https://github.com/crankyoldgit/IRremoteESP8266.git   (versione testata: 2.7.6)
    - Espalexa -->         https://github.com/Aircoookie/Espalexa                (versione testata: 2.4.7)
    - esp8266 Community --> https://arduino.esp8266.com/stable/package_esp8266com_index.json (versione testata: 2.7.1)
Hardware:
    - esp8266 d1 mini
    - ir led (trasmiter)
Debug IR code:
    - arduino uno
    - ir led (receiver)
    - IRremote --> https://github.com/z3t0/Arduino-IRremote.git (versione testata: 2.3.3)
*/
#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>


#define POWER 3772793023
#define VOLUMEP 3772833823
#define VOLUMEM 3772829743
#define AVANTI 3772795063
#define INDIETRO 3772778743
#define EXIT 3772822603
#define NETFLIX 3772829488
#define OK 3772782313
// CANALI
#define ZERO 3772811383
#define UNO 3772784863
#define DUE 3772817503
#define TRE 3772801183
#define QUATTRO 3772780783
#define CINQUE 3772813423
#define SEI 3772797103
#define SETTE 3772788943
#define OTTO 3772821583
#define NOVE 3772805263

IRsend irsend(4); // d2

boolean connectWifi();

//Wifi Credenziali
const char* ssid = ""; // nome rete
const char* password = ""; // password rete
boolean wifiConnected = false;



Espalexa espalexa;

void setup()
{
  irsend.begin();
  Serial.begin(115200);
  wifiConnected = connectWifi();
  
  if(wifiConnected){
    
    // Alexa Device 
    espalexa.addDevice("TV", power); // alexa accendi TV
    espalexa.addDevice("alza", alza); // alexa imposta alza a (numero)
    espalexa.addDevice("abbassa", abbassa); // alexa imposta abbassa a (numero)
    espalexa.addDevice("avanti", avanti); // alexa imposta avanti a (numero)
    espalexa.addDevice("indietro", indietro); // alexa imposta indietro a (numero)
    espalexa.addDevice("esci", esci); // alexa accendi esci
    espalexa.addDevice("netflix",netflix); // apri netflix
    espalexa.addDevice("prime", primevideo); // apri prime video
    espalexa.addDevice("canale", canali); // apri un canale da 1..9
    espalexa.begin();
    
  } else
  {
    while (1) {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}
 
void loop()
{
   espalexa.loop();
   delay(1);
}

// Tv command functions

// POWER
void power(uint8_t brightness) {
    irsend.sendSAMSUNG(POWER,32,0);
}
// ALZA
void alza(uint8_t brightness) {
    if (brightness) {
      uint16_t perc = brightness*100/255;
    if(perc != 100){
      for (int i=0;i<perc;i++){
            irsend.sendSAMSUNG(VOLUMEP,32,0);
            delay(100);
            Serial.print(i);
        }}}}

// ABBASSA
void abbassa(uint8_t brightness){
     if (brightness){
      uint16_t perc = brightness*100/255;
if(perc != 100){
      for (int i=0;i<perc;i++){
            irsend.sendSAMSUNG(VOLUMEM,32,0);
            delay(100);
            Serial.print(i);
        }}}}

// AVANTI
void avanti(uint8_t brightness){
  if (brightness){
      uint16_t perc = brightness*100/255;
      if(perc != 100){
      for (int i=0;i<perc;i++){
            irsend.sendSAMSUNG(AVANTI,32,0);
            delay(100);
            Serial.print(i);
        }}}}
        
// INDIETRO
void indietro(uint8_t brightness){
  if (brightness) {
      uint16_t perc = brightness*100/255;
if(perc != 100){
      for (int i=0;i<perc;i++){
            irsend.sendSAMSUNG(INDIETRO,32,0);
            delay(100);
            Serial.print(i);
        }}}}
// EXIT
void esci(uint8_t brightness){
    irsend.sendSAMSUNG(EXIT,32,0);
}
// APRI NETFLIX 
void netflix(uint8_t brightness){
  irsend.sendSAMSUNG(NETFLIX,32,0);
  delay(1000);
  irsend.sendSAMSUNG(OK,32,0); // ok button
  delay(100);
  }

// APRI PRIME VIDEO
void primevideo(uint8_t brightness){
//irsend.sendSAMSUNG(primevideo_code,32,0); 
  }

// APRI I CANALI DA 1 A 100

void canali(uint8_t brightness){
  uint16_t perc = brightness*100/255;
  switch(perc){
    case 1:
    irsend.sendSAMSUNG(UNO,32,0);
    break;
    case 2:
    irsend.sendSAMSUNG(DUE,32,0);
    break;
    case 3:
    irsend.sendSAMSUNG(TRE,32,0);
    break;
    case 4:
    irsend.sendSAMSUNG(QUATTRO,32,0);
    break;
    case 5:
    irsend.sendSAMSUNG(CINQUE,32,0);
    break;
    case 6:
    irsend.sendSAMSUNG(SEI,32,0);
    break;
    case 7:
    irsend.sendSAMSUNG(SETTE,32,0);
    break;
    case 8:
    irsend.sendSAMSUNG(OTTO,32,0);
    break;
    case 9:
    irsend.sendSAMSUNG(NOVE,32,0);
    break;
    case 20:
    irsend.sendSAMSUNG(DUE,32,0);
    delay(100);
    irsend.sendSAMSUNG(ZERO,32,0);
    delay(100);
    break;
    case 22:
    irsend.sendSAMSUNG(DUE,32,0);
    delay(100);
    irsend.sendSAMSUNG(DUE,32,0);
    delay(100);
    break;
    case 24:
    irsend.sendSAMSUNG(DUE,32,0);
    delay(100);
    irsend.sendSAMSUNG(QUATTRO,32,0);
    delay(100);
    break;
    case 25:
    irsend.sendSAMSUNG(DUE,32,0);
    delay(100);
    irsend.sendSAMSUNG(CINQUE,32,0);
    delay(100);
    break;
    case 26:
    irsend.sendSAMSUNG(DUE,32,0);
    delay(100);
    irsend.sendSAMSUNG(SEI,32,0);
    delay(100);
    break;
    case 27:
    irsend.sendSAMSUNG(DUE,32,0);
    delay(100);
    irsend.sendSAMSUNG(SETTE,32,0);
    delay(100);
    break;
    case 35:
    irsend.sendSAMSUNG(TRE,32,0);
    delay(100);
    irsend.sendSAMSUNG(CINQUE,32,0);
    delay(100);
    break;
    case 49:
    irsend.sendSAMSUNG(QUATTRO,32,0);
    delay(100);
    irsend.sendSAMSUNG(NOVE,32,0);
    delay(100);
    break;
    case 52:
    irsend.sendSAMSUNG(CINQUE,32,0);
    delay(100);
    irsend.sendSAMSUNG(DUE,32,0);
    delay(100);
    break;
    }
  }

// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;
  
  WiFi.mode(WIFI_STA);
  WiFi.hostname("TV");
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20){
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state){
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}

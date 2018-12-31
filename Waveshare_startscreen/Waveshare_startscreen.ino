// include library, include base class, make path known
#include <GxEPD.h>

//#include <GxGDEW027C44/GxGDEW027C44.cpp>    // 2.7" b/w/r
#include <GxGDEW027W3/GxGDEW027W3.cpp>      // 2.7" b/w
// BUSY -> 16, RST -> 5, DC -> 4, CS -> D8, CLK -> D5, DIN -> D7, GND -> GND, 3.3V -> 3.3V

#include <GxIO/GxIO_SPI/GxIO_SPI.cpp>
#include <GxIO/GxIO.cpp>

// FreeFonts from Adafruit_GFX
#include <Fonts/FreeSansBold24pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>

//#include <YoutubeApi.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
//#include "youtubelogo.h"
//#include <ArduinoJson.h> // This Sketch doesn't technically need this, but the library does so it must be installed.



#if defined(ESP8266)

// for SPI pin definitions see e.g.:
// C:\Users\xxx\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.4.2\variants\generic\common.h

GxIO_Class io(SPI, /*CS=D8*/ SS, /*DC=D3*/ 4, /*RST=D4*/ 5); // arbitrary selection of D3(=0), D4(=2), selected for default of GxEPD_Class
GxEPD_Class display(io, /*RST=D4*/ 5, /*BUSY=D2*/ 16); // default selection of D4(=2), D2(=4)
// Heltec E-Paper 1.54" b/w without RST, BUSY
//GxEPD_Class display(io, /*RST=D4*/ -1, /*BUSY=D2*/ -1); // no RST, no BUSY

#endif

#define DEMO_DELAY 10

//------- Replace the following! ------
char ssid[] = "sadf";       // your network SSID (name)
char password[] = "sdf";  // your network key
#define API_KEY "sd"  // your google apps API Token
#define CHANNEL_ID "UCqur3wdt2I-pVhckJb8n0bg" // makes up the url of channel


WiFiClientSecure client;
//YoutubeApi api(API_KEY, client);

unsigned long api_mtbs = 60000; //mean time between api requests
unsigned long api_lasttime;   //last time api request has been done

long subs = 0;
String subscribers, viewCount, videoCount;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  display.init();
  display.setRotation(3);
  Serial.println("setup done");

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.print("ESP8266: ");
  Serial.println(ESP8266);
  Serial.print("SS: ");
  Serial.println(SS);



  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);


  // setup the display
  display.init();

  // colours are good.
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);

  // load a font - in the library
  display.setFont(&FreeMonoBold9pt7b);

  // let the strings begin
  display.setCursor(0, 0);
  display.println();
  display.println("Hello. My name is Inigo Montoya. You killed my father. Prepare to die." );


  display.println();
  display.println("This is another line!" );
  display.update();


}

void loop() {
  // put your main code here, to run repeatedly:
  //if (millis() - api_lasttime > api_mtbs)  {
  Serial.println("Looping...");
  subscribers = 35;
  viewCount = 12;
  videoCount = 7;
  Serial.print("Subscriber Count: ");
  Serial.println(subscribers);
  Serial.print("View Count: ");
  Serial.println(viewCount);
  Serial.print("Video Count: ");
  Serial.println(videoCount);
  delay(6000);
  display.drawPaged(showFontCallback);
  // api_lasttime = millis();
  //}
  delay(api_mtbs);


}

void showFontCallback()
{
  const char* name = "FreeSansBold24pt7b";
  const GFXfont* f = &FreeSansBold24pt7b;

  const char* name18 = "FreeSansBold18pt7b";
  const GFXfont* f18pt = &FreeSansBold18pt7b;

  const char* name9 = "FreeSans9pt7b";
  const GFXfont* f9pt = &FreeSans9pt7b;


  Serial.println("showFontCallback");
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setCursor(0, 130);
  display.println();
  display.drawLine(0, 60, 264, 60, GxEPD_BLACK);
  //display.drawLine(0, 60, 264, 60, GxEPD_RED);
  display.setFont(f);
  int x = (subscribers.length() * 30) / 2; // make the text in the center of the display
  //display.setTextWrap(true);
  display.setCursor(132 - x, 100);
  display.println(subscribers);
  display.setFont(f9pt);
  display.setCursor(80, 120);
  display.setTextColor(GxEPD_BLACK);
  display.println("Subscribers");

  //display.drawBitmap(60, 10, gImage_ytlogo1, 46, 32, GxEPD_RED);
  //display.drawBitmap(60, 10, gImage_ytlogo1, 46, 32, GxEPD_BLACK);
  //display.drawBitmap(110, 10, gImage_ytlogo2, 94, 29, GxEPD_BLACK);

  display.drawLine(0, 140, 264, 140, GxEPD_BLACK);
  display.setTextColor(GxEPD_BLACK);
  display.setCursor(0, 165);
  display.println("Views:" + viewCount);
  display.setCursor(142, 165);
  display.println("Videos:" + videoCount);


}

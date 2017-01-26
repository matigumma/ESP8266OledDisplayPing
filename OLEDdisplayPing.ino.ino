#include <Wire.h>
#include <SSD1306.h>
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>

SSD1306  display(0x3c, D4, D5);
const char* ssid     = "COPETELWIFIFCEB";
const char* password = "4A05FCEB";

const char* remote_host = "www.google.com";
typedef void (*Demo)(void);
int avgp;

void setup() {
  Serial.begin(115200);
  delay(10);
  // Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println("Connecting to WiFi");
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("WiFi connected with ip ");  
  Serial.println(WiFi.localIP());

  Serial.print("Pinging host ");
  Serial.println(remote_host);
}

void drawText() {
  // Text alignment demo
  display.setFont(ArialMT_Plain_10);
  // The coordinates define the left starting point of the text
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 0, "Pingueando: ");
  display.setFont(ArialMT_Plain_24);
  String st = String("Ping: ");
  st += Ping.averageTime();
  st += "ms";
  display.drawString(0, 35, st );     
}

Demo demos[] = {drawText};

void loop() { 
  // clear the display
  display.clear();
  if(Ping.ping(remote_host)) {
    demos[0]();
    display.display();
    Serial.println("Success!!");
    Serial.println(Ping.averageTime());
  } else {
    Serial.println("Error :(");
  }  
  delay(5);
}

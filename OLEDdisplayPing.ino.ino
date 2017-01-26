#include <Wire.h>
#include <SSD1306.h>
#include <OLEDDisplayFonts.h>
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>
//set pinout 
SSD1306  display(0x3c, D4, D5); //replace d4 in case it needed
const char* ssid     = "xxxxxxxxx"; //replace with your ssid wifi
const char* password = "xxx"; //replace with your wifi pass

const char* remote_host = "www.google.com";
typedef void (*Demo)(void);

void setup() {
  Serial.begin(115200);
  delay(10);
  // Initialising the UI will init the display too.
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  //Serial.println();
  //Serial.println("Connecting to WiFi");
  display.drawString(0, 28, "Conectando ...");
  WiFi.begin(ssid, password);
  display.display();
  int count = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
    if (count >= 100){
     display.drawProgressBar(0, 40, 120, 10, 100);
     display.display();
    }else{
     display.drawProgressBar(0, 40, 120, 10, count);
     display.display();
    }
    count ++;
  }
  //Serial.print(".");
  // clear the display
  display.clear();
  //Serial.println();
  //Serial.print("WiFi connected with ip ");
  display.drawString(0, 16, "Wifi conectado");
  display.display();
  delay(500);
  //Serial.println(WiFi.localIP());
  //Serial.print("Pinging host ");
  //Serial.println(remote_host);
}

void draw() {
  int progress;
  // Text alignment demo
  display.setFont(ArialMT_Plain_10);
  // The coordinates define the left starting point of the text
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 0, "Pingueando: ");
  display.drawString(0, 13, remote_host);
  // draw the progress bar if ping > 100 draw full line
  if(Ping.averageTime() >= 100){
     progress = 100;
  }else{
     progress = (Ping.averageTime()) % 100;
  }
  display.drawProgressBar(0, 28, 120, 10, progress);  
  display.setFont(ArialMT_Plain_16);
  // draw the Ping: XXms  
  String st = String("Ping: ");
  st += Ping.averageTime();
  st += "ms";  
  display.drawString(0, 40, st );  
}

Demo demos[] = {draw};

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

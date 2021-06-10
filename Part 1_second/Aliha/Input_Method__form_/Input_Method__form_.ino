#include "M5Atom.h"

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>


#include "index.h"

const char* ssid = "princeAP1";
const char* password = "superlab";

WebServer server(80);


void handleRoot() {
  server.send(200, "text/html", html);
}

bool RelayFlag = false;

String DataCreate() {
  String RelayState = (RelayFlag) ? "on" : "off";
  String Data =  "W#state:" + RelayState;
  return Data;
}

void setup() {
  M5.begin(true, false, true);
  M5.dis.drawpix(0, 0xe0ffff);

  WiFi.softAP(ssid, password);
  Serial.print("AP SSID: ");
  Serial.println(ssid);
  Serial.print("AP PASSWORD: ");
  Serial.println(password);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());  //IP address assigned to your ESP

  server.on("/", handleRoot);

  server.on("/review1", []() {
    String params_1 = server.arg(0);
    

    Serial.print("Value 1: ");
    Serial.println(params_1);
    
    RelayFlag = false;
    server.send(200, "text/plain", DataCreate());
  });

 server.on("/review2", []() {
    
    String params_2 = server.arg(1);
    Serial.print("Value 2: ");
    Serial.println(params_2);
    RelayFlag = false;
    server.send(200, "text/plain", DataCreate());
  });
  
  server.on("/data", []() {
    server.send(200, "text/plain", DataCreate());
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {

  if (M5.Btn.wasPressed()) {
    RelayFlag = !RelayFlag;
    
  }
  if (RelayFlag) {
    M5.dis.drawpix(0, 0xff0000);
  } else {
    M5.dis.drawpix(0, 0xe0ffff);
  }
  M5.update();
  server.handleClient();
}

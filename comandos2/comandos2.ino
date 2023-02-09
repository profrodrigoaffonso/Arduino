#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "rodrigo02"
#define STAPSK  "rodrigo2369"
#endif
int tempo = 1000;
const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

const int led = 13;

void handleRoot() {
  //digitalWrite(led, 1);
  if(server.arg("comando")=="on"){
    digitalWrite(server.arg("l").toInt(), LOW);
    Serial.println("ligou");
  }
  if(server.arg("comando")=="off"){
    digitalWrite(server.arg("l").toInt(), HIGH);
    Serial.println("desligou");
  }
  
  server.send(200, "text/plain", server.arg("comando"));
 // digitalWrite(led, 0);
  
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(4, OUTPUT); 
  pinMode(5, OUTPUT); 
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  //pinMode(led, OUTPUT);
  //digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  
  server.handleClient();
  MDNS.update();
}

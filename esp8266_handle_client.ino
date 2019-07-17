#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "esp8266iscool";
const char *password = "pingu4prez";

ESP8266WebServer server(80);

void handleSentVar() {
Serial.println("handleSentVar function called...");
if (server.hasArg("sensor_reading")) { // this is the variable sent from the client
Serial.println("Sensor reading received...");

int readingInt = server.arg("sensor_reading").toInt();
char readingToPrint[5];
itoa(readingInt, readingToPrint, 10); //integer to string conversion for OLED library

Serial.print("Reading: ");
Serial.println(readingToPrint);
Serial.println();
int pwmValLin = map(readingInt, 999, 8, 0, 1023);
int pwmValSqrt = sqrt(pwmValLin)*32;

analogWrite(LED_BUILTIN, pwmValSqrt);
server.send(200, "text/html", "Data received");
}
}

void setup() {
delay(1000);
Serial.begin(115200);
Serial.println();
Serial.print("Configuring access point...");

WiFi.softAP(ssid, password, 11, true);

IPAddress myIP = WiFi.softAPIP();
Serial.print("AP IP address: ");
Serial.println(myIP);
server.on("/data/", HTTP_GET, handleSentVar); // when the server receives a request with /data/ in the string then run the handleSentVar function
server.begin();
Serial.println("HTTP server started");

}


void loop() {
server.handleClient();
}

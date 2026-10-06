#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

const char *ssid = "Narat";
const char *password = "Likliklik9";

ESP8266WebServer server(80);

#define RELAY_PIN 0 // Relay control (active LOW)

volatile bool relayState = false;

void handle_on() {
    relayState = true;
    digitalWrite(RELAY_PIN, LOW); // active LOW
    server.send(200, "text/plain", "Relay ON");
    Serial.println("Relay ON");
}

void handle_off() {
    relayState = false;
    digitalWrite(RELAY_PIN, HIGH);
    server.send(200, "text/plain", "Relay OFF");
    Serial.println("Relay OFF");
}

void handle_status() {
    server.send(200, "text/plain", relayState ? "ON" : "OFF");
}

void connect_wifi() {
    WiFi.mode(WIFI_STA);
    WiFi.persistent(false);
    WiFi.begin(ssid, password);

    const unsigned long timeoutMs = 20000;
    unsigned long start = millis();

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");

        if (millis() - start > timeoutMs) {
            Serial.println("\nWiFi connect timed out, restarting...");
            ESP.restart();
        }
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void setup() {
    Serial.begin(9600);

    // Ensure relay stays OFF before WiFi setup
    digitalWrite(RELAY_PIN, HIGH);
    pinMode(RELAY_PIN, OUTPUT);

    connect_wifi();

    // mDNS must be started after WiFi is connected
    if (MDNS.begin("wifi-relay")) {
        Serial.println("mDNS responder started: http://wifi-relay.local");
        MDNS.addService("http", "tcp", 80);
    } else {
        Serial.println("Error starting mDNS");
    }

    // HTTP endpoints
    server.on("/on", handle_on);
    server.on("/off", handle_off);
    server.on("/status", handle_status);

    server.begin();
}

void loop() {
    server.handleClient();
    MDNS.update();
}

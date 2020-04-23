#include <WiFi.h>
#include <PubSubClient.h>

//Fill out the following configuration for your setup
const char* ssid     = "ssid";
const char* password = "password";
const char* mqtt_broker = "broker.hivemq.com";
const int mqtt_port = 1883;

//Depending on your board selection you might need to uncomment the following line, and select the correct pin. 
//#define BUILTIN_LED 2

WiFiClient espClient;
PubSubClient client(espClient);
long lastHBSent = 0; //time since last MQTT message sent.
char payload[50]; //buffer for incomming payloads
int value = 0;

void setup_wifi() {

}

void callback(char* topic, byte* _payload, unsigned int length) { 

}

void reconnect() {

}

void setup() {

}

void loop() {
}

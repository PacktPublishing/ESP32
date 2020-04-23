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

void setup_wifi() {  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* _payload, unsigned int length) { 
  printf("Message arrived: %s\n", topic);
  strncpy(payload,(char*) _payload, length);
  payload[length] = 0; //null terminate the string.
  Serial.println(payload);
  // Switch on the LED if we received “on” as the payload
  if (strncmp("on", payload, length) == 0 && length > 0) {
    digitalWrite(BUILTIN_LED, HIGH);   
      } else {
    digitalWrite(BUILTIN_LED, LOW);  
  }
}

void reconnect() {  while (!client.connected()) {
   Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(WiFi.macAddress());
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe("IOTwESP32/in");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT); 
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
}

void loop() {  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastHBSent > 2000) {
    lastHBSent = now;
    ++value;
    snprintf (payload, 50, "hello world %ld", value);
    Serial.print("Publish message: ");
    Serial.println(payload);
    client.publish("IOTwESP32", payload);
  }
}

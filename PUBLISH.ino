
/********************************LIBRARY******************************************/
#include <WiFi.h>
#include <PubSubClient.h>
/********************************variable******************************************/
const char* ssid = "Juel";
const char* password =  "60388612";
const char* mqttServer = "m16.cloudmqtt.com";
const int mqttPort = 16320;
const char* mqttUser = "voquwcpl";
const char* mqttPassword = "TuLVCf6ow6tr";
/********************************OBJECT******************************************/
WiFiClient espClient;
PubSubClient client(espClient);
//--------------------------------------------------------------------------------


/********************************SETUP START******************************************/
void setup() {
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
}
/********************************SETUP END******************************************/



/********************************LOOP start*****************************************/
void loop() {
  client.loop();
  client.publish("esp/test", "Hello");
  delay(1000);
}
/********************************LOOP END******************************************/

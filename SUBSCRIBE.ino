/********************************LIBRARY******************************************/
#include <WiFi.h>
#include <PubSubClient.h>
/********************************server variable******************************************/
const char* ssid = "Juel";
const char* password =  "60388612";
const char* mqttServer = "m16.cloudmqtt.com";
const int mqttPort = 16320;
const char* mqttUser = "voquwcpl";
const char* mqttPassword = "TuLVCf6ow6tr";
/********************************OBJECT******************************************/
WiFiClient espClient;
PubSubClient client(espClient);

int Kitchen_led=2;// ESP32 D2 pin
//--------------------------------------------------------------------------------


/********************************SETUP START******************************************/
void setup() {
 
  Serial.begin(115200);
  pinMode(Kitchen_led,OUTPUT);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
  client.subscribe("kitchen/light");
}
/********************************SETUP END******************************************/
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  String msg="";

  for (int i = 0; i < length; i++) {
    msg=msg+(char)payload[i];
  }
  
  Serial.print("Topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  Serial.println(msg);
 
  Serial.println("-----------------------");
  if((String)topic=="kitchen/light" & msg=="on")
  {
    digitalWrite(Kitchen_led,HIGH);
    Serial.println("ON done");
    }
  else if((String)topic=="kitchen/light" & msg=="off")
  {
    digitalWrite(Kitchen_led,LOW);
    Serial.println("OFF done");
    }
}


/********************************LOOP start*****************************************/
void loop() {
  client.loop();
}
/********************************LOOP END******************************************/

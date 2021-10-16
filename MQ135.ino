#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <PubSubClientTools.h>
#include "MQ135.h"              // https://github.com/GeorgK/MQ135

#include <Thread.h>             // https://github.com/ivanseidel/ArduinoThread
#include <ThreadController.h>

#define WIFI_SSID "Flybox"        //add your SSID
#define WIFI_PASS "72229480"        //add your Password

#define MQTT_SERVER "broker.hivemq.com"
#define MQTT_PORT 1883    //add port of your MQTT brocker. Usualy 1833. If not put yours
//#define MQTT_SERVER " 141.94.175.18" //add the IP of your MQTT brocker
//#define mqtt_user "robotika"             //add username of your MQTT Brocker
//#define mqtt_password "robotika"         //add password of your MQTT Brocker

// topic definitions
#define RZero_topic "sensor/RZero"
#define PPM_topic "sensor/PPM"
#define Voltage_topic "sensor/Voltage"


// MQ135 sensor
#define PIN_MQ135 A0
MQ135 mq135_sensor = MQ135(PIN_MQ135);

WiFiClient espClient;
PubSubClient client(MQTT_SERVER, MQTT_PORT, espClient);
PubSubClientTools mqtt(client);
ThreadController threadControl = ThreadController();
Thread thread = Thread();

int value = 0;
const String s = "";
const int gasSensor =0;

void setup() {
  Serial.begin(115200);
  Serial.println();
  // Connect to WiFi
  Serial.print(s+"Connecting to WiFi: "+WIFI_SSID+" ");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
      reconnect();
    delay(500);
    Serial.print(".");
  }
  Serial.println("connected");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to MQTT
  Serial.print(s+"Connecting to MQTT: "+MQTT_SERVER+" ... ");
  if (client.connect("GasSensor")) {
    Serial.println("connected");

   
    /*      //Another available topic for future use
    //mqtt.subscribe("test_in/#",        topic3_subscriber);
    */
  } else {
    Serial.println(s+"failed, rc="+client.state());
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("GasSensor")) {
  //  if (client.connect("GasSensor", mqtt_user, mqtt_password)) {

      Serial.println("connected");
    } else  {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
bool checkBound(float newValue, float prevValue, float maxDiff) {
  return !isnan(newValue) &&
         (newValue < prevValue - maxDiff || newValue > prevValue + maxDiff);
         client.subscribe("Temp_Ext_topic");
         client.subscribe("Humi_Ext_topic");
}

long lastMsg = 0;
float RZero = 0.0;
float PPM = 0.0;
float Voltage = 0.0;
float diff = 1.0;

void loop() {
    if (!client.connected() && WiFi.status() == 3) {reconnect();}
    client.loop();
    threadControl.run();
    long now = millis();
    if (now - lastMsg > 5000) {
    lastMsg = now;
// let's take the maximum info provided by MQ135 sensor
    float newRZero = mq135_sensor.getRZero();
    double newPPM = mq135_sensor.getPPM();
    if (checkBound(newRZero, RZero, diff)) {
      RZero = newRZero;
      client.publish(RZero_topic, String(RZero).c_str(), true);
    }
      Serial.print(newPPM);
      PPM=((newPPM/10000)*100);      
      Serial.print("New PPM :");
      Serial.println(String(PPM).c_str());      
      client.publish(PPM_topic, String(PPM).c_str(), true); 
  }
}

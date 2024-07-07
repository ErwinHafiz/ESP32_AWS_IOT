#include "Secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"

#define LDR_PIN 33    
#define LED_PIN 13

#define AWS_IOT_PUBLISH_TOPIC   "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"

int ldr ;

WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".wifigakkonek.");
  }

  // AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT
  client.setServer(AWS_IOT_ENDPOINT, 8883);

  // Create a message handler
  client.setCallback(messageHandler);

  Serial.println("Connecting to AWS IOT");

  while (!client.connect(THINGNAME))
  {
    Serial.print(".awsgakkonek.");
    delay(100);
  }

  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }

  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
}

void publishMessage()
{
  StaticJsonDocument<200> doc;
  doc["ldr"] = ldr;

  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); 
 
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.print("incoming: ");
  Serial.println(topic);

  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["message"];
  Serial.println(message);

  // If message received is "ON", turn on the LED
  if (strcmp(message, "ON") == 0) {
    digitalWrite(LED_PIN, HIGH);
  }
  // If message received is "OFF", turn off the LED
  else if (strcmp(message, "OFF") == 0) {
    digitalWrite(LED_PIN, LOW);
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT); 
  connectAWS();
}

void loop()
{
  ldr = analogRead(LDR_PIN); 

  if (isnan(ldr))  // Check if any reads failed
  {
    Serial.println(F("Failed to read from LDR sensor!"));
    return;
  }

  Serial.print(F("Intensitas Cahaya: "));
  Serial.print(ldr);
  
  publishMessage();
  client.loop();
  delay(1000);
}

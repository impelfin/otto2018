/* 
 * Make by 2018.08.17 
 * Main 김진우 Support 김석휘
 */
 
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
int gas = A0;
int led = 0;
const char* ssid = "iptime";
const char* password = "";
const char* mqtt_server = "223.194.27.67";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int val = 0;

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(gas, INPUT);
  pinMode(led, OUTPUT);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
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

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266gas")) {
      Serial.println("connected");
      client.publish("sensor", "sender");
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  val = analogRead(A0);
  if (val > 600) {
    digitalWrite(led,HIGH);
  } else {
    digitalWrite(led,LOW);
  }
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
    lastMsg = now;
    snprintf (msg, 75,"%ld", val);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("sensor", msg);
    delay(5000);
}

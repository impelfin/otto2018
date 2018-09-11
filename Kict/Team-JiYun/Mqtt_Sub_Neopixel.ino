/* 
 * Make by 2018.08.17 
 * Main 김진우 Support 김석휘
 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
// Update these with values suitable for your network.
int led = 2;
const char* ssid = "iptime";
const char* password = "";
const char* mqtt_server = "223.194.27.67";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(0,OUTPUT);
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
  char temp2[100];
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    temp2[i] = payload[i];
  }
  Serial.println();
  int buf = atoi(temp2);
  String temp = topic;
  if (temp == "A") {
    if (0<=buf && buf <= 100) {
      digitalWrite(0,LOW);
      Serial.println("aa");
    }else if(100<=buf && buf < 200){
      analogWrite(0, 85);
      Serial.println("bb");
    }else if(200<=buf && buf < 300){
      analogWrite(0, 170);
      Serial.println("cc");
    }else if(300<=buf && buf < 400){
      analogWrite(0, 255);
      Serial.println("dd");
    }else
    analogWrite(0, 0);
  }else if (temp == "B") {
    if (0<=buf && buf <= 100) {
      analogWrite(0, 0);
      Serial.println("aa");
    }else if(100<=buf && buf < 200){
      analogWrite(0, 85);
      Serial.println("bb");
    }else if(200<=buf && buf < 300){
      analogWrite(0, 170);
      Serial.println("cc");
    }else if(300<=buf && buf < 400){
      analogWrite(0, 255);
      Serial.println("dd");
    }else
      analogWrite(0, 0);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266b")) {
      Serial.println("connected");
      
      client.subscribe("A");
      client.subscribe("B");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
}

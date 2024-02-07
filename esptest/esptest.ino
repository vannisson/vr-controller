#include <WiFi.h>
#include <PubSubClient.h>

// WiFi
const char* ssid = "brisa-2856088";  // Enter your WiFi name
const char* password = "ryjcnt0o";   // Enter WiFi password

// const char* ssid = "dijkstra";  // Enter your WiFi name
// const char* password = "taescritonovr";   // Enter WiFi password

// MQTT Broker
// const char* broker_url = "192.168.0.7";
const char* broker_url = "192.168.0.133";
const int broker_port = 1883;

// Topic
const char* topic = "mqtt/esp32";

// const char *mqtt_username = "emqx";
// const char *mqtt_password = "public";

// Leds
const byte led_red = 18;
const byte led_green = 21;

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
bool flag = 0;
void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  char tmp_msg[length + 1];  // +1 for the null terminator
  for (int i = 0; i < length; i++) {
    tmp_msg[i] = (char)payload[i];
  }
  tmp_msg[length] = '\0';  // Null-terminate the string
  if (strcmp(tmp_msg, "Red") == 0) {
    client.publish("mqtt/esp32", "Received Red");
    digitalWrite(led_red, HIGH);
    digitalWrite(led_green, LOW);
  } else if (strcmp(tmp_msg, "Green") == 0) {
    client.publish("mqtt/esp32", "Received Green");
    digitalWrite(led_red, LOW);   
    digitalWrite(led_green, HIGH);  
  }
  Serial.print(tmp_msg);
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe(topic);

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  Serial.begin(9600);
  setup_wifi();
  client.setServer(broker_url, broker_port);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // unsigned long now = millis();
  // if (now - lastMsg > 2000) {
  //   lastMsg = now;
  //   if (flag == 0) {
  //     client.publish("mqtt/esp32", "Red");
  //     digitalWrite(led_red, HIGH);
  //     digitalWrite(led_green, LOW);
  //   } else {
  //     client.publish("mqtt/esp32", "Green");
  //     digitalWrite(led_red, LOW);   
  //     digitalWrite(led_green, HIGH);  
  //   }
  //   flag = !flag;
  // }
}
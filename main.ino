// RED 5V
// ORANGE 13
// BROWN GND
#include <WiFi.h> //WIFI shield
#include <PubSubClient.h>
#include <ESP32Servo.h>

Servo myservo;
int pos = 0;
int servoPin = 13;

char ssid[] = "";
char password[] = "";
const char *mqtt_server = "";

char topic[] = "";
char nickname[] = "";
char mqtt_id[] = "";
char mqtt_pw[] = "";

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    String msg = "";
    for (int i = 0; i < length; i++)
    {
        msg += (char)payload[i];
    }
    if (msg.equals("ON"))
    {
        myservo.attach(servoPin);
        myservo.write(140);
        delay(3000);
        myservo.detach();
    }
    else if (msg.equals("OFF"))
    {
        myservo.attach(servoPin);
        myservo.write(100);
        delay(3000);
        myservo.detach();
    }
    Serial.print(msg);
    Serial.println();
}

void setup()
{
    Serial.begin(115200); //ESP8266
    setup_wifi();         // Connect to wifi
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}
void setup_wifi()
{
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        for (int i = 0; i < 500; i++)
        {
            delay(1);
        }
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
void reconnect()
{
    // Loop until we're reconnected
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect(nickname, mqtt_id, mqtt_pw))
        {
            Serial.println("connected");

            // ... and resubscribe
            client.subscribe(topic);

            // Once connected, publish an announcement...
            //client.publish("IOT", "test msg");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
            // Wait 5 seconds before retrying
        }
    }
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
}

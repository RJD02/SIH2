#include <DHT.h>
#include <Arduino_JSON.h>
#include <WiFiClientSecure.h>
//#include <Vector.h>
WiFiClient wifiClient;
const char *ssid = "Tab 8";
const char *password = "KSRJDulange13";
const char* host = "young-dawn-87102.herokuapp.com";
const char fingerPrint[] = "34 6A 4F 35 49 D7 8B C1 EA 74 B9 9E C9 A8 C9 1F 5E 6C 27 61";

#define MQ2PIN  36
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
#define DHTPIN 23
#define DHTTYPE DHT11
#define token "pk.0937384ebc66656e7cec5a0384f0f3b7"

DHT dht(DHTPIN, DHTTYPE);

const int trigPin = 12;
const int echoPin = 13;
// 
long unsigned duration = 0;
double distanceCm;
double distanceInch;

// Location api variables
String jsonString = "{\n";
double latitude = 0.0;
double longitude = 0.0;
double accuracy = 0.0;

// unwiredlabs Hostname & Geolocation Endpoint url
const char* Host = "www.unwiredlabs.com";
String endpoint = "/v2/process.php";

const char* test_root_ca = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n"\
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n"\
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n"\
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n"\
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n"\
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n"\
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n"\
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n"\
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n"\
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n"\
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n"\
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n"\
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n"\
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n"\
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n"\
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n"\
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n"\
"rqXRfboQnoZsG4q5WTP468SQvvG5\n"\
"-----END CERTIFICATE-----\n";

void setup() {
  
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  connectToWifi();

  dht.begin();
  delay(2000);
}

void loop() {
  delay(2000);
  digitalWrite(trigPin, OUTPUT);
  delayMicroseconds(20);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED/2;
  distanceInch = distanceCm * CM_TO_INCH;
  Serial.print("Duration: ");
  Serial.println(duration);
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);
  float val = analogRead(MQ2PIN);
  Serial.println(val);
  sendRequest(distanceInch, val);
//  auto details = getLocation();
  delay(5000);
}

String getResponse(String path, String body, String methodData, String headersData)
{
  WiFiClientSecure httpsClient;
  httpsClient.setCACert(test_root_ca);
  httpsClient.setTimeout(10000);
  delay(1000);

  Serial.println("HTTPS Connecting");

  httpsClient.connect(host, 443);

 while(httpsClient.connected())
  {
    Serial.println("Verified " + path);
    if (body != "" and headersData != "") {
      String sending = methodData + " " + path + " " + String("HTTP/1.1\r\n") +
                        String("Host: ") + host + String("\r\n") +
                        headersData + String("\r\n\r\n") +
                        body + String("\r\n") +
                        String("Connection: close\r\n\r\n");
      Serial.println(sending);
      httpsClient.print(sending);
    } else {
      String sending = methodData + " " + path + " " + String("HTTP/1.1\r\n") +
                        String("HOST: ") + host + String("\r\n") +
                        String("Connection: close\r\n\r\n");
      Serial.println(sending);
      httpsClient.print(sending);
    }
    String response = "";
    while (httpsClient.connected())
    {
      String line = httpsClient.readStringUntil('\n');
      if (line == "\r")
      {
        Serial.println("Headers received");
        break;
      }
    }
    while (httpsClient.available())
    {
      String line = httpsClient.readStringUntil('\n');
      response += line;
    }
    return response;
  }
  Serial.println("Certificates don't match");
  return "";
}

void connectToWifi()
{
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Waiting for connection");
  }

  Serial.println("Connected...");
  delay(1000);
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("Wi-Fi connected!");
  }
  delay(2000);
}

void getLocation() {
    char bssid[6];
    JSONVar jsonBuffer;

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");

    if (n == 0 ) {
        Serial.println("No networks available");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
    }
      // now build the jsonString...
      jsonString = "{\n";
      jsonString += "\"token\" : \"";
      jsonString += token;
      jsonString += "\",\n";
      jsonString += "\"id\" : \"saikirandevice01\",\n";
      jsonString += "\"wifi\": [\n";
      for (int j = 0; j < n; ++j) {
          jsonString += "{\n";
          jsonString += "\"bssid\" : \"";
          jsonString += (WiFi.BSSIDstr(j));
          jsonString += "\",\n";
          jsonString += "\"signal\": ";
          jsonString += WiFi.RSSI(j);
          jsonString += "\n";
          if (j < n - 1) {
              jsonString += "},\n";
          } else {
              jsonString += "}\n";
          }
      }
      jsonString += ("]\n");
      jsonString += ("}\n");
      Serial.println(jsonString);

      WiFiClientSecure client;

      //Connect to the client and make the api call
      Serial.println("Requesting URL: https://" + (String)Host + endpoint);
      if (client.connect(Host, 443)) {
          Serial.println("Connected");
          client.println("POST " + endpoint + " HTTP/1.1");
          client.println("Host: " + (String)Host);
          client.println("Connection: close");
          client.println("Content-Type: application/json");
          client.println("User-Agent: Arduino/1.0");
          client.print("Content-Length: ");
          client.println(jsonString.length());
          client.println();
          client.print(jsonString);
          delay(500);
      }

      //Read and parse all the lines of the reply from server
      while (client.available()) {
          String line = client.readStringUntil('\r');
          JSONVar root = jsonBuffer.parse(line);
          if (1) {
              latitude    = root["lat"];
              longitude   = root["lon"];
              accuracy    = root["accuracy"];

              Serial.println();
              Serial.print("Latitude = ");
              Serial.println(latitude, 6);
              Serial.print("Longitude = ");
              Serial.println(longitude, 6);
              Serial.print("Accuracy = ");
              Serial.println(accuracy);
          }
      }

      Serial.println("closing connection");
      Serial.println();
      client.stop();

      delay(5000);
//      return {latitude, longitude, accuracy};
}

void sendRequest(float level, float MQ2) {
  JSONVar body;
  body["MQ2"] = MQ2;
  body["level"] = level;
//  body["humidity"] = humidity;
//  body["temperature"] = temperature;
   String jsonBody = JSON.stringify(body);
  String headersData = "Content-Type: application/json\r\nContent-Length: " + String(jsonBody.length());
  String response = getResponse("/record/", jsonBody, "POST", headersData);
  Serial.println(response);
}

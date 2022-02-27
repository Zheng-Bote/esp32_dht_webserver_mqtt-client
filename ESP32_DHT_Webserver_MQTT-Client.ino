/*
PROG:
  ESP32 temperature/humidity Wifi Webserver & MQTT client
DESC: 
  Arduino prog for DHT11, DHT22 (AM2302), DHT21 (AM2301) sensor with WiFi, dis-/enabled Webserver and dis-/enabled MQTT client
      - optional: show Temperature and Humidity on Website (refresh every 15 seconds)
      - optional: MQTT client intervall publishing (customizable)
      - optional: MQTT publish data and do ESP32 deep sleep intervall (customizable) 

SOURCE:
  https://github.com/Zheng-Bote/esp32_dht_webserver_mqtt-client

DEPENDENCIES:
  - Adafruit DHT Library
  - MQTT PubSubClient

Version | Date       | Developer                         | Comments
------- | ---------- | --------------------------------- | ---------------------------------------------------------------
0.1.0   | 2022-02-20 | https://github.com/Zheng-Bote     | created; WiFi, Webserver and MQTT client
1.0.0   | 2022-02-23 | https://github.com/Zheng-Bote     | clean-up, separating into libs
        |            |                                   | to dos: - automatic firmware update and reboot, if enabled
                                                                   - enable MQTT subscribing
                                                                   - code / libraries clean up

*/

// ##### 
const char* appTitle = "ESP32 Temp/Hum Wifi Webserver & MQTT client";
const char *appVersion = "1.0.0";

bool firmwareUpdateAvailable = false;
const int led = 13;
// ##### Timer
unsigned long previousMillis = 0;
// #####

#include "credentials.h"
#include "rz_wifi.h"
#include "rz_version.h"
#include "rz_system.h"
#include "rz_http.h"
#include "rz_dht.h"
#include "rz_mqtt.h"
#include "rz_webserver.h"

// create instances
RZ_System *esp32System = new RZ_System(); 
RZ_WiFi *mywifi = new RZ_WiFi(wifiSsid, wifiPassword);
RZ_Version *versions = new RZ_Version();
RZ_HTTP *httpclient = new RZ_HTTP();
RZ_DHT *dhtsensor = new RZ_DHT();

// # destroy instance, freeing mem
// delete versions;
// versions = NULL;


// ##### Setup
void setup() {
  std::string bufferStr;
  
  Serial.begin(SERIAL_SPEED); 
  
  Serial.print("\nStarting\n- "); 
  digitalWrite(led, 1);
  Serial.print(appTitle); Serial.print(" v"); Serial.println(appVersion);
  Serial.print("-- on "); Serial.println(esp32System->getHostId().c_str());
  
  Serial.print(F("- Initializing WiFi\n"));
  if(mywifi->startWiFi()) {
    Serial.print("\n-- Connected to ");
    Serial.println(wifiSsid);
    Serial.print("-- IP-Address "); Serial.println(mywifi->getIpAddr());

    Serial.print(F("- Initializing MDNS responder\n"));
    if(mywifi->startMDNS(esp32System->getHostId())) {
      bufferStr = esp32System->getHostId() + ".local";
      Serial.print("-- MDNS started: "); Serial.println(bufferStr.c_str());
    }
    else {
      Serial.println("-- MDNS failed");
    }
  }
  else {
    Serial.println("\n-- WiFi connect failed. => restart in 10 seconds\n");
    delay(10000);
    esp32System->doRestart();
  }

  if(CHECK_FIRMWARE) {
    checkVersion(versions->checkVersions(appVersion, httpclient->checkFirmware()));  
  }

  Serial.print(F("- Initializing DHT sensor\n"));
  dhtsensor->readData();
  Serial.print("-- Temperature: "); Serial.println(dhtsensor->getTemperature());
  Serial.print("-- Humidity: "); Serial.println(dhtsensor->getHumidity());

  if(enableMQTT) {
    char buffer[20];
    Serial.print(F("- Initializing MQTT client\n"));
    Serial.print("-- MQTT publish interval in seconds: ");
    Serial.println(mqttInterval / 1000);
    rz_mqttclient_start(esp32System->getHostId());
    bufferStr = esp32System->getHostId() + "/status";
    esp32System->ntpLocalTime(ntpServer, gmtOffset_sec, daylightOffset_sec);
    strcpy(buffer, esp32System->getDateTimeString().c_str()); 
    rz_mqtt_sendMsg(bufferStr, buffer); 
    sendMqttData();
  }

  if(enableWebserver) {
    Serial.print(F("- Initializing Webserver\n"));
    webServer.on("/", handleRoot);
    webServer.on("/getjsonvals", getDataJson);
    webServer.on("/checkversion", getVersion);
    webServer.begin();
    Serial.println("-- HTTP server started");
    bufferStr = "-- http://" + esp32System->getHostId() + ".local:";
    Serial.print(bufferStr.c_str()); Serial.println( + webserverPort);
  }
  
  digitalWrite(led, 0);
}
// ##### Setup

// checkVersion(versions->checkVersions(v1, v2));
// esp32System->getHostId();
void checkVersion(int ret) {
  switch (ret) {
    case 0: {Serial.println("-- current version is up to date"); break;}
    case 1: {Serial.println("-- current version is greater than Github version. Pls check"); break;}
    case 2: {
      Serial.println("-- a new Firmware is available on Github"); 
      firmwareUpdateAvailable = true;
      if(DO_FIRMWARE_UPDATE) {  }
      break;
    }
    default:
      {Serial.println("case default"); break;}
  }
}

void getDataJson() {
  std::string bufferStr;
  std::string buffer;

  bufferStr = "{\"temperature\": \"";
  buffer = dhtsensor->getTemperature().c_str();
  bufferStr += buffer;
  
  bufferStr += "\",\"humidity\": \"";
  buffer = dhtsensor->getHumidity().c_str();
  bufferStr += buffer + "\"}";
  
  // Serial.println(bufferStr.c_str());

  webServer.send(200, "application/json", bufferStr.c_str());
}

void getVersion() {
  char json[100];
  char buf[100];
  char version[10];
  char isUpdate[] = "false";

  if(firmwareUpdateAvailable) {
    strcpy(version, httpclient->getUpdVersion().c_str()); 
    strcpy(isUpdate, "true");
  }
  else {
    strcpy(version, appVersion);
    strcpy(isUpdate, "false");
  }

  strcpy(json, "{\"version\": \"");
  sprintf(buf, "%s", version);
  strcat(json, buf);
  strcat(json, "\",\"isupdate\": \"");
  sprintf(buf, "%s", isUpdate);
  strcat(json, buf);
  strcat(json, "\"}");
  
  // Serial.println(json);

  webServer.send(200, "application/json", json);
}

void sendMqttData() {
  std::string bufferStr;
  char buffer[10];
    
  bufferStr = esp32System->getHostId() + "/temperature";
  strcpy(buffer, dhtsensor->getTemperature().c_str()); 

  /*Serial.println("sendMqttData");
  Serial.println(buffer);
  Serial.println(bufferStr.c_str());*/
  
  rz_mqtt_sendMsg(bufferStr, buffer); 
  
  bufferStr = esp32System->getHostId() + "/humidity";
  strcpy(buffer, dhtsensor->getHumidity().c_str()); 

  /*Serial.println("sendMqttData");
  Serial.println(buffer);
  Serial.println(bufferStr.c_str());*/
  
  rz_mqtt_sendMsg(bufferStr, buffer);   
}

// ##### LOOP
void loop()
{
  if(enableMQTT) {
    // Serial.println("MQTT Timer Loop");
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= mqttInterval) {
      previousMillis = currentMillis;
      sendMqttData();
    }
  }

  if(enableWebserver) {
    webServer.handleClient();
  }
  delay(2);
  
  if(deepSleep) {
    Serial.print("- Initializing ESP32 Deep Sleep\n-- duration: "); Serial.print(TIME_TO_SLEEP); Serial.println(" seconds");
    esp32System->doStartDeepSleep(TIME_TO_SLEEP);
  }
}

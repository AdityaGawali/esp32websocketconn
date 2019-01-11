///Working code
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "ESPmDNS.h"



const char* ssid = "Ajinkya";
const char* password = "ajinkya21";

AsyncWebServer server(80);
AsyncWebSocketClient * globalClient = NULL;
AsyncWebSocket websocket("/socket");

String input_data;
int event_flag = 0;

int count = 0 ;
void setup()
{
  Serial.begin(115200);
  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  Serial.println("~~SPIFFS Mounting sucessfull~~");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.print("Connected with IP : ");
  Serial.println(WiFi.localIP());

    //mDNS server
  if (MDNS.begin("esp32"))
  {
    Serial.println("~~MDNS responder sucessfull!!~~");
    
  }
  
  websocket.onEvent(onWsEvent);
  server.addHandler(&websocket);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send(SPIFFS, "/webpage.html" , "text/html");
  });
  server.begin();
  //MDNS.addService("http", "tcp", 80);
}
void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len)
{

  if (type == WS_EVT_CONNECT)
  {
    Serial.println("Websocket client connection received");
    globalClient = client;
  }
  else if (type == WS_EVT_DISCONNECT)
  {
    Serial.println("Client disconnected");
    Serial.println("-----------------------");
    globalClient = NULL;
  }
  else if (type == WS_EVT_DATA)
  {
    event_flag = 1;

    char input_buffer[len + 1] = {};
    Serial.print("Data received: ");

    for (int i = 0; i < len; i++)
    {
      input_buffer[i] = (char)data[i];
    }

    input_data = String(input_buffer);
    input_data.toLowerCase();
    Serial.print(input_data);
    Serial.println();
  }
}

void loop()
{
  if ((input_data == "slow") && (event_flag == 1))
  {
    Serial.println("10A code here");
    event_flag = 0;
    dacWrite(25, 0);
    if (globalClient != NULL && globalClient->status() == WS_CONNECTED)
    {
      String ack = "slow";
      globalClient->text(ack);
    }
  }
    else if ((input_data == "medium") && (event_flag == 1))
    {
      Serial.println("22A code here");
      event_flag = 0;
      dacWrite(25, 128);
      if (globalClient != NULL && globalClient->status() == WS_CONNECTED)
      {
        String ack = "medium";
        globalClient->text(ack);
      }
    }

    else if ((input_data == "fast") && (event_flag == 1))
    {
      Serial.println("45A code here");
      event_flag = 0;
      dacWrite(25, 255);
      if (globalClient != NULL && globalClient->status() == WS_CONNECTED)
      {
        String ack = "fast";
        globalClient->text(ack);
      }
    }

  }

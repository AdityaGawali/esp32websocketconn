#include "WiFi.h"
#include "ESPAsyncWebServer.h"
// "socket(\"ws://192.168.1.78/test\"); ws.onopen=function(){document.getElementById(\"inputText\").disabled=false; document.getElementById(\"sendButton\").disabled=false; document.getElementById(\"connectButton\").disabled=true; document.getElementById(\"disconnectButton\").disabled=false;}; ws.onclose=function(){document.getElementById(\"inputText\").disabled=true; document.getElementById(\"sendButton\").disabled=true; document.getElementById(\"connectButton\").disabled=false; document.getElementById(\"disconnectButton\").disabled=true; alert(\"Connection closed\");};}function CloseWebsocket(){ws.close();}function SendData(){var textToSend=document.getElementById(\"inputText\").value; ws.send(textToSend);}</script> </head> <body> <div> <button onclick=\"OpenWebsocket()\" id=\"connectButton\">CONNECT</button> <button onclick=\"CloseWebsocket()\" disabled=\"true\" id=\"disconnectButton\">DISCONNECT</button> </div><div> <input type=\"text\" disabled=\"true\" id=\"inputText\"></input> <button onclick=\"SendData()\" disabled=\"true\" id=\"sendButton\">SEND</button> </div></body></html>";
const char HTML[] PROGMEM = "<!DOCTYPE html><html> <head> <script type=\"text/javascript\">var ws=null; function OpenWebsocket(){ws=new WebSocket(\"ws://192.168.0.103/test\"); ws.onopen=function(){document.getElementById(\"inputText\").disabled=false; document.getElementById(\"sendButton\").disabled=false; document.getElementById(\"connectButton\").disabled=true; document.getElementById(\"disconnectButton\").disabled=false;}; ws.onclose=function(){document.getElementById(\"inputText\").disabled=true; document.getElementById(\"sendButton\").disabled=true; document.getElementById(\"connectButton\").disabled=false; document.getElementById(\"disconnectButton\").disabled=true; alert(\"Connection closed\");};}function CloseWebsocket(){ws.close();}function SendData(){var textToSend=document.getElementById(\"inputText\").value; ws.send(textToSend);}</script> </head> <body> <div> <button onclick=\"OpenWebsocket()\" id=\"connectButton\">CONNECT</button> <button onclick=\"CloseWebsocket()\" disabled=\"true\" id=\"disconnectButton\">DISCONNECT</button> </div><div> <input type=\"text\" disabled=\"true\" id=\"inputText\"></input> <button onclick=\"SendData()\" disabled=\"true\" id=\"sendButton\">SEND</button> </div></body></html>";
const char* ssid = "Ajinkya";
const char* password = "ajinkya21";
AsyncWebServer server(80);
AsyncWebSocket ws("/test");

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());

  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send(200, "text/html", HTML); // Lambda body implementation
  });
  server.begin();
}
void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len)
{

  if (type == WS_EVT_CONNECT)
  {
   Serial.println("Websocket client connection received");
  }
  else if (type == WS_EVT_DISCONNECT) 
  {
    Serial.println("Client disconnected");
    Serial.println("-----------------------");
  } 
  else if (type == WS_EVT_DATA) 
  {
    Serial.print("Data received: ");
    for (int i = 0; i < len; i++) 
    {
    Serial.print((char) data[i]);
    }
  Serial.println();
  }
}

    void loop()
    {


    }

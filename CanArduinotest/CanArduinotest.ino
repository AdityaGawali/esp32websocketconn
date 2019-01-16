// demo: CAN-BUS Shield, receive data
#include <mcp_can.h>
#include <SPI.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

MCP_CAN CAN0(10);                               // Set CS to pin 10


void setup()
{
  Serial.begin(115200);
  CAN0.begin(CAN_250KBPS,MCP_8MHz );                       // init can bus : baudrate = 500k 
  Serial.println("MCP2515 Library Receive Example...");
}

void loop()
{
    if(CAN0.checkReceive() == CAN_MSGAVAIL)
    {
      CAN0.readMsgBuf(&len, rxBuf);              // Read data: len = data length, buf = data byte(s)
      rxId = CAN0.getCanId();                    // Get message ID
      Serial.print("ID: ");
      Serial.print(rxId, HEX);
      Serial.print("  Data: ");
      for(int i = 0; i<len; i++)                // Print each byte of the data
      {
        if(rxBuf[i] < 0x10)                     // If data byte is less than 0x10, add a leading zero
        {
          Serial.print("0");
        }
        Serial.print(rxBuf[i], DEC);
        Serial.print(" ");
      }
      Serial.println();
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

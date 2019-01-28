/*  ESP TX -> module_TX(UART)   ~~~~  TX32  ->  RX32  ~~~~ ICTX -> RX 
 *  ESP RX -> module RX(UART)   ~~~~  RX32  ->  TX32  ~~~~ ICRX -> TX   
 *  3v3 -> VCC              
 *  GND -> GND                  ~~~~  GND   ->  GND   ~~~~
 *  
 *  rs232.begin(baud-rate, protocol, RX pin, TX pin);
 */


HardwareSerial rs232(2);
#define RXD2 16
#define TXD2 17

String input_data;
void setup() 
{
  Serial.begin(9600);
  rs232.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

void loop() 
{ 
  while (rs232.available()) 
  { 
    input_data = rs232.readString();
    Serial.println(input_data);
  }
}

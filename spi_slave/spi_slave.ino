#include<avr/io.h>
#include<stdlib.h>
#include<compat/deprecated.h>
#include<util/delay.h>
#include<avr/eeprom.h>
#include <inttypes.h>

  void setup()
  {
    SPISlaveInit();               
    //SPIMasterInit();
    Serial.begin(115200);

  }

void loop()
{
 //transmit(1);
  
  receiveData();
}

void SPISlaveInit(void)
{
  DDRB=(1<<4);         //MISO as OUTPUT
  PORTB=(1<<PB2);      //pull up ss
  SPCR=(1<<SPE);                                
 
}

void receiveData()
{
  while(!(SPSR & (1<<SPIF)));
  Serial.println(SPDR);
 }

 void SPIMasterInit(void)
{
  DDRB|=(1<<PB3)|(1<<PB2)|(1<<PB5);         //MOSI,SCK,SS as OUTPUT
  PORTB=(1<<PB2);     
  SPCR |= (1<<SPE)|(1<<MSTR);
 
}
void transmit(unsigned char data)
{
  SPDR = data;
  while(!(SPSR & (1<<SPIF)));

}


//PB5 SCK 13 
//PB4 MISO 12
//PB3 MOSI 11
//PB2 SS 10

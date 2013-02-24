#include <JeeLib.h>
#include <OneWire.h>
#include <DallasTemperature.h>

long counter;


//#define ONE_WIRE_BUS 7
#define ONE_WIRE_BUS 6

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

ISR(WDT_vect) { Sleepy::watchdogEvent(); }

#define LDR 0 // the LDR will be connected to AIO1, i.e. analog 0

void setup () {
  Serial.begin(9600);
  pinMode(14+LDR, INPUT_PULLUP);
  // node 1, group 212, 915 MHz
  Sleepy::loseSomeTime(32);
  rf12_initialize(1, RF12_915MHZ, 212);
  rf12_control(0xC68F);
  sensors.begin(); // default 9 bit measurement
}

void loop () {
  struct  {
    int c,t,b,l;
  } mess;
  int batt;
  int ldr;
  float t;
  
  Serial.begin(9600);
  pinMode(14+LDR, INPUT_PULLUP);
  
  ++counter;
  sensors.requestTemperatures(); // Send the command to get temperatures
  t = sensors.getTempCByIndex(0);
  batt = map(analogRead(1), 0, 1023, 0,6600) ;
  ldr =  1024-analogRead(LDR);
  mess.c=counter;
  mess.t=int(t*10);
  mess.b=batt;
  mess.l=ldr;
  
  while (!rf12_canSend())
    rf12_recvDone();
  rf12_sendStart(0, &mess, sizeof mess);
  
 Serial.print(counter);
 Serial.print(" ");
 Serial.print(t*1.8+32.0);
 Serial.print(" ");
 Serial.print(ldr);
 Serial.print(" ");
 Serial.println(batt);
 // wait for transmit buffer to empty
 delay(1000);
 
 rf12_sleep(RF12_SLEEP);
 Sleepy::loseSomeTime(60000);
 rf12_sleep(RF12_WAKEUP);
}




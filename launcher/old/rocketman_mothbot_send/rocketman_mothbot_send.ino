// Feather9x_TX
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messaging client (transmitter)
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example Feather9x_RX
//#include <OneWire.h> //https://github.com/PaulStoffregen/OneWire
#include <SPI.h>
#include <RH_RF95.h> //https://cdn-learn.adafruit.com/assets/assets/000/035/106/original/RadioHead-1.62.zip?1472068723
#include <Bounce2.h> // https://github.com/thomasfredericks/Bounce2

#define BUTTON_A_PIN A4


typedef struct {
  float         press; //pressure
  float         temp;   //temperature maybe?
  //float         temp2;
} Payload;
Payload theData;


// Radio pins for mothbot
#define RFM95_CS 8
#define RFM95_RST 7
#define RFM95_INT 2


#define VBATPIN D4
   
// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 905.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

//OneWire  ds(12);  // on pin 10 (a 4.7K resistor is necessary)

#define LED 13

Bounce2::Button button_A= Bounce2::Button();

//Button button_A = Button();

void setup() 
{

 pinMode(BUTTON_A_PIN, INPUT_PULLUP);
  
button_A.attach( BUTTON_A_PIN, INPUT_PULLUP ); // USE EXTERNAL PULL-UP
  button_A.interval(5); 
  button_A.setPressedState(LOW);

  pinMode(LED, OUTPUT);
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  Serial.begin(115200);

  delay(100);

  Serial.println("Feather LoRa TX Test!");

  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    Serial.println("Uncomment '#define SERIAL_DEBUG' in RH_RF95.cpp for detailed debug info");
    while (1);
  }
  Serial.println("LoRa radio init OK!");

  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
  
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);
    rf95.sleep();
  digitalWrite(LED, LOW);
}

int16_t packetnum = 0;  // packet counter, we increment per xmission

const int num_sensors = 2; // number of temp sensors
float temps[num_sensors];


void loop()
{

  button_A.update();

  if ( button_A.pressed() ) {
    Serial.println("pressed!");
    delay(100);
  }

float t = 10.0;
float p = 20.0;
theData.temp = 10.;
theData.press = 10.;
  //rf95.send((uint8_t *)radiopacket, 20);
  //rf95.send((const void*)(&theData), sizeof(theData))
  rf95.send((uint8_t *)&theData, sizeof(theData));
  Serial.println("sending!");
  rf95.waitPacketSent();
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(100);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(100); 
  
  delay(1000);      
}
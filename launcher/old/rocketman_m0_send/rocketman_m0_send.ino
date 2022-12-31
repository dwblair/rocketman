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

#define BUTTON_PIN A5
#define LED_PIN 13
#include <Bounce2.h> // https://github.com/thomasfredericks/Bounce2

Bounce2::Button button = Bounce2::Button();

// SET A VARIABLE TO STORE THE LED STATE
int ledState = LOW;

typedef struct {
  float         press; //pressure
  float         temp;   //temperature maybe?
  //float         temp2;
} Payload;
Payload theData;


// for feather m0  
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3



#define VBATPIN A7
   
// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 905.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

//OneWire  ds(12);  // on pin 10 (a 4.7K resistor is necessary)


//Button button_A = Button();

void setup() 
{
button.attach( BUTTON_PIN, INPUT ); // USE EXTERNAL PULL-UP

  // DEBOUNCE INTERVAL IN MILLISECONDS
  button.interval(5); 

  // INDICATE THAT THE LOW STATE CORRESPONDS TO PHYSICALLY PRESSING THE BUTTON
  button.setPressedState(LOW); 
  
  // LED SETUP
  pinMode(LED_PIN,OUTPUT);
  digitalWrite(LED_PIN,ledState);
  //pinMode(LED, OUTPUT);
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
  //digitalWrite(LED, LOW);
}

int16_t packetnum = 0;  // packet counter, we increment per xmission

const int num_sensors = 2; // number of temp sensors
float temps[num_sensors];


void loop()
{


  button.update();


if ( button.pressed() ) {
    
    // TOGGLE THE LED STATE : 
    ledState = !ledState; // SET ledState TO THE OPPOSITE OF ledState
    digitalWrite(LED_PIN,ledState); // WRITE THE NEW ledState

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
  //digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  //delay(100);                      // wait for a second
  //digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  //delay(100); 
  
  delay(1000);      
}
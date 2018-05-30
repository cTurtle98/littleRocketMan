/*  
 *  Ciaran Farley
 *  Rocket Data Logger
 */

/*
 * Time is in standard "hour:minute:second.milisecond"
 */

#include <Wire.h>
#include <Adafruit_MPL3115A2.h>
#include <SPI.h>
#include <SD.h>

Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

const int SDCARDPIN = 4;

String dataLabel = "Time Sinse Boot,Pressure(Pascals),Altitude(Meters),Temp(C)";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  Serial.begin(9600);

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(SDCARDPIN)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  
  Serial.println("card initialized.");

  //add headers to top of csv
  File dataFile = SD.open("data.csv", FILE_WRITE);
  
  if (dataFile) {
    dataFile.println(dataLabel);
    dataFile.close();
    Serial.println(dataLabel);
  }
}

void loop() {

  digitalWrite(LED_BUILTIN, HIGH);
  
  if (! baro.begin()) {
    Serial.println("Couldnt find sensor");
    return;
  }

  File dataFile = SD.open("data.csv", FILE_WRITE);

  if (dataFile) {

    Serial.println("");
    dataFile.println("");
    Serial.print(millis());
    dataFile.print(millis());
    Serial.print(",");
    dataFile.print(",");
    Serial.print("");
    dataFile.print("");
    Serial.print(",");
    dataFile.print(",");
    Serial.print(baro.getPressure());
    dataFile.print(baro.getPressure());
    Serial.print(",");
    dataFile.print(",");
    Serial.print(baro.getAltitude());
    dataFile.print(baro.getAltitude());
    Serial.print(",");
    dataFile.print(",");
    Serial.print(baro.getTemperature());
    dataFile.print(baro.getTemperature());
    
    //add labels to the serial console every 10 seconds
    if(millis() % 10000 == 0){
      Serial.println(dataLabel);
    }
    dataFile.close();
  } else {
    Serial.println("error opening data.csv");
  }

  digitalWrite(LED_BUILTIN, LOW);
  delay(50);
}

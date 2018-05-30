/*  
 *  Ciaran Farley
 *  Rocket Data Logger
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

  while (!Serial) {
    ;
  }
  
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
    Serial.println("DATA LABEL IN FILE");
  }
}

void loop() {

  digitalWrite(LED_BUILTIN, HIGH);

Serial.println("LOOP STARTED");
  
  if (! baro.begin()) {
    Serial.println("Couldnt find sensor");
    return;
  }

Serial.println("BARO BEGIN FINISHED");

  File dataFile = SD.open("data.csv", FILE_WRITE);
  Serial.println("FILE OPENED");

  if (dataFile) {

    Serial.print(millis());
    dataFile.print(millis());
    Serial.print(",");
    dataFile.print(",");
    dataFile.flush();
    
    Serial.print("");
    dataFile.print("");
    Serial.print(",");
    dataFile.print(",");
    dataFile.flush();
    
    Serial.print(baro.getPressure());
    dataFile.print(baro.getPressure());
    Serial.print(",");
    dataFile.print(",");
    dataFile.flush();
    
    Serial.print(baro.getAltitude());
    dataFile.print(baro.getAltitude());
    Serial.print(",");
    dataFile.print(",");
    dataFile.flush();
    
    Serial.print(baro.getTemperature());
    dataFile.print(baro.getTemperature());
    Serial.print(",");
    dataFile.print(",");
    dataFile.flush();
    
    Serial.println("");
    dataFile.println("");
    Serial.println("DATA PRINT COMPLETE");
    dataFile.close();
    Serial.println("DATA FILE CLOSED");
  } else {
    Serial.println("error opening data.csv");
  }
Serial.println("DATA LOOP COMPLETE");
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}

/*  
 *  Ciaran Farley
 *  Rocket Data Logger
 */

#include <Wire.h>
#include <Adafruit_MPL3115A2.h>
#include <SPI.h>
#include <SD.h>

Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

const int SDCARDPIN = 4;//pin for sd card
String dataLabel = "Time Since Boot,Pressure(Pascals),Altitude(Meters),Temp(C)"; //label for top of csv
File dataFile = SD.open("data.csv", FILE_WRITE); //name of file on sd card  
long time = 0;
long lastTime = 0;
long timeDelta = 0;
float pascals = 0;
float altm = 0;
float tempc = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  Serial.begin(9600);
  
  // see if the card is present and can be initialized:
  Serial.print("Initializing SD card...");
  if (!SD.begin(SDCARDPIN)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

  //check if mpl3115a2 sensor exists
  if (! baro.begin()) {
    Serial.println("Couldnt find sensor");
    return;
  }

  //add headers to top of csv
  if (dataFile) {
    dataFile.println("");
    dataFile.println(dataLabel);
    Serial.println(dataLabel);
    dataFile.flush();
  }
}

void loop() {

  digitalWrite(LED_BUILTIN, HIGH);

  //sensor values
  pascals = baro.getPressure();
  altm = baro.getAltitude();
  tempc = baro.getTemperature();
  time = millis();
  timeDelta = time - lastTime;

//  Serial.print(time);
//  dataFile.print(time);
//  Serial.print(",");
//  dataFile.print(",");
  
  Serial.print(timeDelta);
//  dataFile.print(timeDelta);
//  Serial.print(",");
//  dataFile.print(",");
  
//  Serial.print(pascals);
//  dataFile.print(pascals);
//  Serial.print(",");
//  dataFile.print(",");
  
//  Serial.print(altm);
//  dataFile.print(altm);
//  Serial.print(",");
//  dataFile.print(",");
  
//  Serial.print(tempc);
//  dataFile.print(tempc);
//  Serial.print(",");
//  dataFile.print(",");
  
  Serial.println("");
//  dataFile.println("");
  
  dataFile.flush();

  lastTime = time;
  digitalWrite(LED_BUILTIN, LOW);
}

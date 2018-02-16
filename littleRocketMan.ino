/* CIARAN FARLEY
 *  Rocket Data Logger
 *  v 0.1
 */
#include <Wire.h>
#include <Adafruit_MPL3115A2.h>
#include <SPI.h>
#include <SD.h>

Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

const int cardSelect = 4;

unsigned long time;

void setup() {
pinMode(LED_BUILTIN, OUTPUT);
digitalWrite(LED_BUILTIN, LOW);
  
  Serial.begin(9600);

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(cardSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

//add headers to top of csv
 String dataLabel = "Time Sinse Boot,Pressure(Pascals),Altitude(Meters),Temp(C)";
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

  //sensor strings
  float pascals = baro.getPressure();
  float altm = baro.getAltitude();
  float tempc = baro.getTemperature();
  long time = millis();

  //log data string
  String dataString = String(time) + "," + String(pascals) + "," + String(altm) + "," + String(tempc);

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("data.csv", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening data.csv");
  }
digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}

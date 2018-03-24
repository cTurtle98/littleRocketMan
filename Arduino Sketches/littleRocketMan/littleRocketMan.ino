/*  CIARAN FARLEY
    Rocket Data Logger
    v 0.1

    HH = Hour in 2 digit format
    MM = minute in 2 digit format
    SS = second in 2 digit format
    MsMs = miliseconds in 3 digit format
*/

#include <Wire.h>
#include <Adafruit_MPL3115A2.h>
#include <SPI.h>
#include <SD.h>

Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

const int SDCARDPIN = 4;
const int MILISECONDSPERSECOND = 1000;
const int SECONDSPERMINUTE = 60;
const int MINUTESPERHOUR = 60;


unsigned long totalMillis;
unsigned int currentMilliSeconds;
unsigned long totalSeconds;
unsigned int currentSeconds;
unsigned long totalMinutes;
unsigned int currentMinutes;
unsigned long totalHours;
unsigned long currentHours;

String formattedMilliSeconds;
String formattedSeconds;
String formattedMinutes;
String formattedHours;
String time;

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
  long totalMillis = millis();
  
  //format time to look pretty with HH:MM:SS:MsMs
  currentMilliSeconds = totalMillis % MILISECONDSPERSECOND;
  totalSeconds = totalMillis / MILISECONDSPERSECOND;
  currentSeconds = totalSeconds % SECONDSPERMINUTE;
  totalMinutes = totalSeconds / SECONDSPERMINUTE;
  currentMinutes = totalMinutes % MINUTESPERHOUR;
  totalHours = totalMinutes / MINUTESPERHOUR;
  currentHours = totalHours;

  //add zero padding to milliseconds
  if(currentMilliSeconds == 0){
    formattedMilliSeconds = "000";
  }
  else if(currentMilliSeconds < 10){
    formattedMilliSeconds = "00" + String(currentMilliSeconds);
  }
  else if(currentMilliSeconds < 100){
    formattedMilliSeconds = "0" + String(currentMilliSeconds);
  }
  else{
    formattedMilliSeconds = String(currentMilliSeconds);
  }
  
  //add zero padding to seconds
  if(currentSeconds == 0){
    formattedSeconds = "00";
  }
  else if(currentSeconds < 10){
    formattedSeconds = "0" + String(currentSeconds);
  }
  else{
    formattedSeconds = String(currentSeconds);
  }
  
  //add zero padding to minutes
  if(currentMinutes == 0){
    formattedMinutes = "00";
  }
  else if(currentMinutes < 10){
    formattedMinutes = "0" + String(currentMinutes);
  }
  else{
    formattedMinutes = String(currentMinutes);
  }
  
  //add zero padding to hours
  if(currentHours == 0){
    formattedHours = "00";
  }
  if(currentHours < 10){
    formattedHours = "0" + String(currentHours);
  }
  else{
    formattedHours = String(currentHours);
  }

  time = (String(formattedHours) + ":" + String(formattedMinutes) + ":" + String(formattedSeconds) + ":" + String(formattedMilliSeconds));

  //log data string
  String dataString = String(time) + "," + String(pascals) + "," + String(altm) + "," + String(tempc);

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  
  File dataFile = SD.open("data.csv", FILE_WRITE);

  // if the file is available, write to it:

  // print to the serial port:
  Serial.println(dataString);
  
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  } else {
    Serial.println("error opening data.csv");
  }

  digitalWrite(LED_BUILTIN, LOW);
  delay(50);
}

# littleRocketMan

Arduino based "flight recorder" initially designed to be used for estes rockets but expanded for use in other aerospace projects

I currently use an Adafruit Feather M0 adalogger as the arduino because it has an built in sd card slot and is not too expensive. the adalogger uses the standard pin4 for the sd card so you can repolace it with any arduino and sd card combination without needing to change the code as long as the card is on pin 4

The code currently only logs from an MPL3115A2(https://www.adafruit.com/product/1893)

In the future I plan to expand it to record from an BNO055(https://www.adafruit.com/product/2472) as well

I also want to add gps support but I am already at 795ms time delta between readings and I would like to keep it under a second

## Hardware
you can find a list of the hardware im using in the wiki here: [Wiki Parts List](https://github.com/cTurtle98/littleRocketMan/wiki/Parts-List)

## Arduino IDE Setup
[setup guide in wiki](https://github.com/cTurtle98/littleRocketMan/wiki/Arduino-IDE-Setup-Guide)

## Cabrillo Aerospace Club
this project is/was used for data collection within Cabrillo Aerospace Club projects

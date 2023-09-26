#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW
#define MAX_DEVICES 4
#define CS_PIN 10
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
const float BETA = 3950; // should match the Beta Coefficient of the thermistor

void setup() {
  myDisplay.begin();
  // Set the intensity (brightness) of the display (0-15):
  myDisplay.setIntensity(0);
  // Clear the display:
  myDisplay.displayClear();
}

void loop() {
  int analogValue = analogRead(A0);
  float celsius = 1 / (log(1 / (1023. / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15;
  String temp;
  char emoji;
  if (celsius < 8) {
    temp = "frio: ";
    emoji = ':c';
  } else if (celsius > 25) {
    temp = "caliente: ";
    emoji = ':o';
  } else {
    temp = "normal:";
    emoji = 'c:';
  }
  temp + " C " + emoji;
  myDisplay.print(temp);
  delay(1000);
}
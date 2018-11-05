#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//temperature sensor
const int temperaturePin = 3;
int temperatureInput;
float temperature;
float resistance;

//light sensor
const int lightPin = 2;
float light;

//motion sensor
const int motionPin = 6;

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 1);
}

void loop() {
  //delay(500);
  
  lcd.setCursor(0, 0);
  //lcd.print("Temperatur ");
  //lcd.print(getTemperature());

  //lcd.print("Licht: ");
  //lcd.print(getLight());

  //lcd.print("Bewegung: ");
  //lcd.print(getMotion());
}

//temperature in celcius
float getTemperature() {
  temperatureInput = analogRead(temperaturePin);
  resistance = (float) (1023 - temperatureInput) * 10000 / temperatureInput;
  return 1/(log(resistance/10000)/3975 + 1/298.15) - 273.15;
}

//light value between 0 (dark) and 1023 (bright)
float getLight() {
    return 1023 - analogRead(lightPin);
}

int getMotion() {
  return digitalRead(motionPin);
}

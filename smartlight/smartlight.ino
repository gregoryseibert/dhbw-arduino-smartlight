#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Adafruit_NeoPixel neo;

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

//neopixel
const int neoPin = 8;

//rotary switches
const int switchPin1 = 0;
const int switchPin2 = 1;

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);

  neo = Adafruit_NeoPixel(12, neoPin, NEO_GRB + NEO_KHZ800);
  neo.begin();
  neo.setBrightness(75);
  neo.show();
}

void loop() {
  delay(500);
}

void temperatureMode() {
  if(getTemperature() > 20) {
    setPixelColor(255, 150, 40);
  } else {
    setPixelColor(255, 255, 250);
  }
}

//temperature in celcius
float getTemperature() {
  temperatureInput = analogRead(temperaturePin);
  resistance = (float) (1023 - temperatureInput) * 10000 / temperatureInput;
  return 1 / (log(resistance / 10000) / 3975 + (1 / 298.15)) - 273.15;
}

//light value between 0 (dark) and 1023 (bright)
float getLight() {
    return 1023 - analogRead(lightPin);
}

//motion value 0 or 1
int getMotion() {
  return digitalRead(motionPin);
}

//set the color of all pixels at once
void setPixelColor(int green, int red, int blue) {
  for(int i = 0; i < neo.numPixels(); i++) {
    neo.setPixelColor(i, green, red, blue);
  }

  neo.show();
}

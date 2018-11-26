#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>

//lcd
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//neopixel
Adafruit_NeoPixel neo;

//delay of the looping method in milliseconds
const int loopDelay = 250;

//push button
const int buttonPin = 7;
int buttonState = 0;
const int numberOfModes = 4;
int currentMode = 1;

//poti
const int potiPin = 0;
float potiState = 0;

//temperature sensor
const int temperaturePin = 3;
const int temperatureTreshold = 20; //20 Celcius
int temperatureInput;
float temperature;
float resistance;

//light sensor
const int lightPin = 2;
const int lightTreshold = 700;
float light;

//motion sensor
const int motionPin = 6;
const int motionDelayDuration = 1000 * 10; //10s
int motionDelayCounter = motionDelayDuration / loopDelay;

//neopixel
const int neoPin = 8;

//rotary switches
const int switchPin1 = 0;
const int switchPin2 = 1;

//colors
uint32_t white = neo.Color(255, 255, 255);
uint32_t warmWhite = neo.Color(255, 150, 40);
const uint32_t black = neo.Color(0, 0, 0);

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);

  neo = Adafruit_NeoPixel(12, neoPin, NEO_GRB + NEO_KHZ800);
  neo.begin();
  neo.setBrightness(75);
  neo.show();

  pinMode(buttonPin, INPUT);
}

void loop() { 
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    currentMode = currentMode + 1;

    if(currentMode > numberOfModes) {
      currentMode = 1;
    }
  }
  
  delay(loopDelay);
  
  if(currentMode == 1) {
    manualMode();
  } else if(currentMode == 2) {
    motionMode();
  } else if (currentMode == 3) {
    lightMode();
  } else {
    temperatureMode();    
  }
}

void manualMode() {
  potiState = analogRead(potiPin); //0-1023
  setPixelColor(mapToColor(potiState, 0, 1023);
}

void motionMode() {
  lcd.clear();
  lcd.setCursor(0, 0);
    
  if(getMotion()) {
    lcd.print("Motion active");
    
    setPixelColor(white);
    motionDelayCounter = motionDelayDuration / loopDelay;
  } else {
    lcd.print("Motion inactive");
    lcd.setCursor(0, 1);
    lcd.print("-> Sleep in ");
    lcd.print(motionDelayCounter * loopDelay / 1000);
    lcd.print("s");
    
    if(motionDelayCounter <= 0) {
      setPixelColor(black);
    } else {
      motionDelayCounter = motionDelayCounter - 1;
    }
  }
}

void lightMode() {
  float light = getLight();
    
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Brightness ");
  lcd.print(light/lightTreshold);
  
  if(light > lightTreshold) {
    lcd.setCursor(0, 1);
    lcd.print("-> Light off");
    
    setPixelColor(black);
  } else {
    lcd.setCursor(0, 1);
    lcd.print("-> Light on");
    
    setPixelColor(white);
  }
}

void temperatureMode() {
  float temperature = getTemperature();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature ");
  lcd.print(temperature);
    
  if(temperature > temperatureTreshold) {
    lcd.setCursor(0, 1);
    lcd.print("-> Warm light");
    
    setPixelColor(warmWhite);
  } else {
    lcd.setCursor(0, 1);
    lcd.print("-> Cool light");
    
    setPixelColor(white);
  }
}

//map a value which is between minimum and maximum to a neopixel color
uint32_t mapToColor(int value, int minimum, int maximum) {
  float ratio = 2 * (value - minimum) / (maximum - minimum);
  
  int blue = max(0, 255 * (1 - ratio));
  int red = max(0, 255 * (ratio - 1));
  int green = 255 - blue - red;

  return neo.Color(green, red, blue);
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

//set the color of all pixels at once
void setPixelColor(uint32_t color) {
  for(int i = 0; i < neo.numPixels(); i++) {
    neo.setPixelColor(i, color);
  }

  neo.show();
}

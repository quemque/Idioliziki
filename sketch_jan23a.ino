#include "HX711.h"//библиотека для преобразователя
#include <LiquidCrystal.h>//библиотека для дисплея

HX711 scale(A1, A0);   // DT, CLK

float calibration_factor = -7.1; // коофицент калибровки
float units;
float ounces;
int buttonPin = 2;
constexpr uint8_t PIN_RS = 6;
constexpr uint8_t PIN_EN = 7;
constexpr uint8_t PIN_DB4 = 8;
constexpr uint8_t PIN_DB5 = 9;
constexpr uint8_t PIN_DB6 = 10;
constexpr uint8_t PIN_DB7 = 11;

LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_DB4, PIN_DB5, PIN_DB6, PIN_DB7);

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  scale.set_scale();
  long zero_factor = scale.read_average();
}

void loop() {
  bool but = digitalRead(buttonPin);
  scale.set_scale(calibration_factor); 
  if(but==1)
      scale.tare();
  units = scale.get_units(), 10;
  if (units < 0)
  {
    units = 0.00;
  }
  ounces = units * 0.035274;
  lcd.setCursor(0, 0);
  lcd.print("weight(g):");
  lcd.setCursor(0, 1);
  lcd.print(ounces);
}

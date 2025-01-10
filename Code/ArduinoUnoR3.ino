#include <Adafruit_LiquidCrystal.h> // Библиотека за работа с I2C LCD дисплеи
#include <Wire.h> // Библиотека за I2C комуникация

// Създаване на обект за I2C LCD дисплей с адрес 0x20
Adafruit_LiquidCrystal lcd_1(0x20);

// Определяне на пин 2 за свързване на бутона
const int buttonPin = 2;

// Променливи за управление на времето
long startTime = 0; // Начално време
long curTime = 0;   // Текущо време
long elapsedTime = 0; // Изминало време в секунди

void setup()
{
  Serial.begin(4800); // Инициализация на сериен порт с скорост 4800 bps (за дебъг)
  
  lcd_1.begin(16, 2); // Инициализация на I2C LCD дисплея с 16 колони и 2 реда
  
  pinMode(buttonPin, INPUT_PULLUP); // Настройка на пин 2 като вход с вътрешен pull-up резистор
  
  startTime = millis(); // Запазване на началното време в милисекунди
}

void loop()
{
  curTime = millis(); // Четене на текущото време в милисекунди от началото на изпълнение на програмата
  
  // Проверка дали бутонът е натиснат (когато е свързан към GND)
  if (digitalRead(buttonPin) == LOW) { 
    startTime = millis(); // Рестартиране на началното време (зануляване на броенето)
  }

  // Изчисляване на изминалото време в секунди
  elapsedTime = curTime / 1000; 

  // Обновяване на I2C LCD дисплея
  lcd_1.setCursor(0, 0); // Позициониране на курсора на първи ред и първа колона
  lcd_1.print("Time: "); // Изписване на текста "Time: "
  lcd_1.setCursor(0, 1); // Позициониране на курсора на втори ред и първа колона
  lcd_1.print(elapsedTime); // Изписване на изминалото време
  lcd_1.print(" s"); // Добавяне на " s" за секунди

  delay(100); // Малко забавяне (100 милисекунди), за да се избегне трептене на дисплея
}

#include <SoftwareSerial.h> // Библиотека за създаване на софтуерен сериен порт

const uint8_t APIN2 = 0; // Определяне на пин 0 за TX на софтуерния сериен порт
const uint8_t APIN3 = 1; // Определяне на пин 1 за RX на софтуерния сериен порт
const uint8_t led = 3;   // Пин 3 се използва за управление на светодиода
const uint8_t TPB = 2;   // Пин 2 се използва за свързване на бутона

bool click = false; // Флаг, който следи състоянието на бутона (натиснат/ненатиснат)

SoftwareSerial UARTOut(APIN2, APIN3); // Инициализация на софтуерен сериен порт

unsigned long startTime = 0;   // Начално време
unsigned long curTime = 0;     // Текущо време
unsigned long elapsedTime = 0; // Изминало време в секунди

void setup()
{
  pinMode(TPB, INPUT_PULLUP); // Настройка на бутона като вход с вътрешен pull-up резистор
  pinMode(led, OUTPUT);       // Настройка на светодиода като изход

  UARTOut.begin(4800); // Инициализация на софтуерния сериен порт с 4800 bps
  delay(100);          // Кратко забавяне за стабилизиране на комуникацията

  UARTOut.print("Initiated "); // Изпращане на съобщение за успешно стартиране на серийния порт
  startTime = millis();        // Запазване на началното време
}

void loop()
{
  curTime = millis(); // Четене на текущото време в милисекунди

  // Проверка дали бутонът е натиснат и състоянието му не е обработено
  if (digitalRead(TPB) == LOW && !click) {
    UARTOut.print("Timer Reset: "); // Съобщение за зануляване на таймера
    UARTOut.print(millis());        // Показване на текущото време в милисекунди
    UARTOut.println(" ms");         // Допълнение към съобщението

    startTime = millis(); // Зануляване на началното време
    digitalWrite(led, HIGH); // Включване на светодиода
    click = true; // Промяна на състоянието на флага (бутонът е обработен)
  }

  // Проверка дали бутонът е отпуснат
  if(digitalRead(TPB)&& !click) {
    UARTOut.print(millis()); 
    digitalWrite(led, HIGH);
    click = true;
  }
  if(!digitalRead(TPB)){
    digitalWrite(led, LOW);
    click = false;
    elapsedTime = 0;
  }

  // Изчисляване на изминалото време в секунди
  elapsedTime = (curTime - startTime) / 1000;
  UARTOut.print("Elapsed Time: "); // Съобщение за изминалото време
  UARTOut.print(elapsedTime);      // Показване на изминалото време
  UARTOut.println(" s");           // Допълнение към съобщението

  delay(100); // Кратко забавяне за стабилизиране на серийните съобщения
}

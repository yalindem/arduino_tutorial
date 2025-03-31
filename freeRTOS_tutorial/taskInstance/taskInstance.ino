#include <Arduino.h>
#include <Arduino_FreeRTOS.h>


#define YELLOW 6
#define GREEN  7
#define RED    8

typedef int TaskProfiler;

TaskProfiler RedLEDProfiler;
TaskProfiler YellowLEDProfiler;
TaskProfiler GreenLEDProfiler;

const uint16_t *greenLED = (uint16_t*) GREEN;
const uint16_t *redLED = (uint16_t*) RED;
const uint16_t *yellowLED = (uint16_t*) YELLOW;

void setup() {
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  xTaskCreate(ledControllerTask, "Red LED Task", 128, (void *)redLED , 1, NULL);
  xTaskCreate(ledControllerTask, "Green LED Task", 128, (void *)greenLED, 1, NULL);
  xTaskCreate(ledControllerTask, "Yellow LED Task", 128, (void *)yellowLED, 1, NULL);
  vTaskStartScheduler();
}

void ledControllerTask(void *pvParameters)
{
  int pin = (int)pvParameters;
  while(1)
  {
    digitalWrite(pin, !digitalRead(pin));
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

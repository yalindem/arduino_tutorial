#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#define YELLOW 6
#define GREEN 7
#define RED 8

typedef int TaskProfiler;

TaskProfiler RedLEDProfiler;
TaskProfiler YellowLEDProfiler;
TaskProfiler GreenLEDProfiler;

void setup()
{
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  xTaskCreate(
      redLEDControllerTask,
      "red LED Task",
      100,
      NULL,
      1,
      NULL
  );

  xTaskCreate(
    yellowLEDControllerTask,
    "yellow LED Task",
    100,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    greenLEDControllerTask,
    "green LED Task",
    100,
    NULL,
    1,
    NULL
  );
  vTaskStartScheduler();
}

void redLEDControllerTask(void* pvParameters)
{
  while(1)
  {
    Serial.println("This is RED");
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void yellowLEDControllerTask(void* pvParameters)
{
  while(1)
  {
    Serial.println("This is YELLOW");
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void greenLEDControllerTask(void* pvParameters)
{
  while(1)
  {
    Serial.println("This is GREEN");
    vTaskDelay(pdMS_TO_TICKS(500));  
  }
}

void loop()
{

}

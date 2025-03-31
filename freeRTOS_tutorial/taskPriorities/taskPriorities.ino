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
  Serial.begin(115200);

  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(13, OUTPUT); 

  BaseType_t redTask, greenTask, yellowTask;
  redTask = xTaskCreate(redLEDController, "Red LED Task", 128, NULL, 3, NULL);
  greenTask = xTaskCreate(greenLEDController, "Green LED Task", 128, NULL, 2, NULL);
  yellowTask = xTaskCreate(yellowLEDController, "Yellow LED Task", 128, NULL, 4, NULL);
  if (redTask != pdPASS) {
   pinMode(13, OUTPUT);
   digitalWrite(13, HIGH); // Eğer task oluşturulamazsa, LED 13'ü yak
  }

  Serial.println("Tasks are starting...");
  if (redTask == pdPASS) Serial.println("Red LED Task is created.");
  if (greenTask == pdPASS) Serial.println("Green LED Task is created.");
  if (yellowTask == pdPASS) Serial.println("Yellow LED Task is created.");

  if (redTask != pdPASS || greenTask != pdPASS || yellowTask != pdPASS) {
    Serial.println("ERROR: Task cannot be created!");
    digitalWrite(13, HIGH);
    while(1);
  }

  Serial.println("FreeRTOS Scheduler is starting...");
  vTaskStartScheduler();
}

void redLEDController(void *pvParameters)
{
  Serial.println("Red LED Task is running...");
  while(1)
  {
    digitalWrite(RED, HIGH);
    vTaskDelay(pdMS_TO_TICKS(500));
    digitalWrite(RED, LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void greenLEDController(void *pvParameters)
{
  while(1)
  {
    digitalWrite(GREEN, !digitalRead(GREEN));
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void yellowLEDController(void *pvParameters)
{
  while(1)
  {
    digitalWrite(YELLOW, !digitalRead(YELLOW));
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void loop()
{
  vTaskDelete(NULL);
}
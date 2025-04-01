#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#define RED 8
#define YELLOW 6
#define GREEN 7

typedef int TaskProfiler;
TaskProfiler RedLEDProfiler;
TaskProfiler YellowLEDProfiler;
TaskProfiler GreenLEDProfiler;

TaskHandle_t red_Handle, yellow_Handle, green_Handle;

u_int32_t suspend_monitor;

void setup()
{
  Serial.begin(9600);
  xTaskCreate(redLEDController, "RED LED Task", 100, NULL, 1, &red_Handle);
  xTaskCreate(yellowLEDController, "YELLOW LED Task", 100, NULL, 1, &yellow_Handle);
  xTaskCreate(greenLEDController, "GREEN LED Task", 100, NULL, 2, &green_Handle); 
  vTaskStartScheduler();
}

void redLEDController(void *pvParameters)
{
  pinMode(RED, OUTPUT);
  while(1)
  {
    digitalWrite(RED,HIGH);
    vTaskDelay(pdMS_TO_TICKS(500));
    digitalWrite(RED,LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
    const UBaseType_t taskPrio = uxTaskPriorityGet(red_Handle);
    Serial.print("RED TASK PRIO: ");
    Serial.println(taskPrio);

  }
}

void yellowLEDController(void *pvParameters)
{
  pinMode(YELLOW, OUTPUT);
  while(1)
  {
    digitalWrite(YELLOW, !digitalRead(YELLOW));
    vTaskPrioritySet(yellow_Handle, 2);
    vTaskDelay(pdMS_TO_TICKS(500));
    const UBaseType_t taskPrio = uxTaskPriorityGet(yellow_Handle);
    Serial.print("YELLOW TASK PRIO: ");
    Serial.println(taskPrio);
    Serial.print("suspend_monitor: ");
    Serial.println(suspend_monitor);
    if (suspend_monitor>50)
    {
      vTaskSuspend(yellow_Handle);
    }
  }
}

void greenLEDController(void *pvParameters)
{
  pinMode(GREEN, OUTPUT);
  while(1)
  {
    digitalWrite(GREEN, !digitalRead(GREEN));
    suspend_monitor++;
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void loop()
{
  vTaskDelete(NULL);

}
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#define YELLOW 6
#define GREEN 7
#define RED 8

typedef int TaskProfiler;
TaskProfiler RedLEDProfiler;
TaskProfiler YellowLEDProfiler;
TaskProfiler GreenLEDProfiler;

void redLEDControllerTask(void *pvParameters)
{
  
  while(1)
  {
    Serial.print("RedLEDProfiler: ");
    Serial.println(RedLEDProfiler);
    //digitalWrite(RED, HIGH);
    //vTaskDelay(pdMS_TO_TICKS(700));
    //digitalWrite(RED, LOW);
    //vTaskDelay(pdMS_TO_TICKS(700));
    RedLEDProfiler++;
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void yellowLEDControllerTask(void *pvParameters)
{
  
  while(1)
  {
     //digitalWrite(YELLOW, digitalRead(YELLOW)^1);
     //vTaskDelay(pdMS_TO_TICKS(700));
    Serial.print("YellowLEDProfiler: ");
    Serial.println(YellowLEDProfiler);
    YellowLEDProfiler++;
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void greenLEDControllerTask(void *pvParameters)
{
  
  while(1)
  {
     //digitalWrite(GREEN, digitalRead(GREEN)^1);
     //vTaskDelay(pdMS_TO_TICKS(700));
    Serial.print("GreenLEDProfiler: ");
    Serial.println(GreenLEDProfiler); 
    GreenLEDProfiler++;
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void setup() {

  Serial.begin(9600);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  xTaskCreate(redLEDControllerTask, "RED LED Task", 256, NULL, 1, NULL);
  xTaskCreate(yellowLEDControllerTask, "YELLOW LED Task", 256, NULL, 1, NULL);
  xTaskCreate(greenLEDControllerTask, "GREEN LED Task", 256, NULL, 1, NULL);  

  vTaskStartScheduler();
}

void loop() {
   
}

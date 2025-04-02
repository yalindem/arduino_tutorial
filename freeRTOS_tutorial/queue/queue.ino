#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

QueueHandle_t yearQueue;

void vSenderTask(void* pvParameters);
void vReceiverTask(void* pvParameters);

void setup()
{
  Serial.begin(9600);
  
  // Create a queue that can hold 5 integers
  yearQueue = xQueueCreate(5, sizeof(int32_t));

  if (yearQueue == NULL) {
    Serial.println("Queue creation failed!");
    while (1);
  }

  // Create sender and receiver tasks
  xTaskCreate(vSenderTask, "Sender Task", 100, NULL, 1, NULL);
  xTaskCreate(vReceiverTask, "Receiver Task", 100, NULL, 1, NULL);

  // Start the FreeRTOS scheduler
  vTaskStartScheduler();
}

void vSenderTask(void* pvParameters)
{
  BaseType_t qStatus;
  int32_t valueToSend = 2018;

  while (1)
  {
    qStatus = xQueueSend(yearQueue, &valueToSend, 0);

    if (qStatus == pdPASS) {
      Serial.println("Sent: 2018");
    } else {
      Serial.println("Queue Full, unable to send");
    }

    vTaskDelay(pdMS_TO_TICKS(200)); // Add delay to avoid spamming
  }
}

void vReceiverTask(void* pvParameters)
{
  int32_t valueReceived;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);

  while (1)
  {
    if (xQueueReceive(yearQueue, &valueReceived, xTicksToWait) == pdPASS) {
      Serial.print("Received value: ");
      Serial.println(valueReceived);
    } else {
      Serial.println("Queue empty");
    }

    vTaskDelay(pdMS_TO_TICKS(500)); // Delay to avoid flooding Serial
  }
}

void loop()
{
  // Nothing here since FreeRTOS is handling tasks
}
/**
 * \file
 * \brief Semaphore usage
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module demonstrating semaphores.
 */

#include "Platform.h" /* interface to the platform */
#if PL_HAS_SEMAPHORE
#include "FRTOS1.h"
#include "Sem.h"
#include "LED.h"
#if PL_HAS_RTOS_TRACE
  #include "RTOSTRC1.h"
#endif

#define USE_SEMAPHORES 	1
#define USE_TEST_TASKS	0

#if USE_SEMAPHORES

#if USE_TEST_TASKS
static portTASK_FUNCTION(vSlaveTask, pvParameters) {
  xSemaphoreHandle sem;

  sem = (xSemaphoreHandle)pvParameters;

  /*************SLAVE**LOOP*****************************/
  for(;;) {
    if (sem != NULL) {
      if (FRTOS1_xSemaphoreTake(sem, portMAX_DELAY)==pdTRUE) {
        LED1_Neg();
      }
    }
  }
}

static portTASK_FUNCTION(vMasterTask, pvParameters) {
  xSemaphoreHandle sem = NULL;

  (void)pvParameters; /* parameter not used */

  //Createas a Binary semaphore, so only one item is stored in this semaphore
  FRTOS1_vSemaphoreCreateBinary(sem);

  if (sem==NULL) { /* semaphore creation failed */
    for(;;){} /* error */
  }
  //Add the Queue to the Registry with the Name Sem
  FRTOS1_vQueueAddToRegistry(sem, "Sem");
#if PL_HAS_RTOS_TRACE
  RTOSTRC1_vTraceSetQueueName(sem, "IPC_Sem");
#endif
  /* create slave task */
  if (FRTOS1_xTaskCreate(vSlaveTask, "Slave", configMINIMAL_STACK_SIZE, sem, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }

  /*************MASTER**LOOP*****************************/
  //Endless loop for semaphore
  for(;;) {
    if (sem != NULL) { /* valid semaphore? */
      (void)xSemaphoreGive(sem); /* give control to other task */
      FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
    }
  }
}

#endif /*USE_TEST_TASKS*/
#endif /* USE_SEMAPHORES */

void SEM_Deinit(void) {
  /* nothing */
}

/*! \brief Initializes module */
void SEM_Init(void) {
#if USE_SEMAPHORES

#if US_TEST_TASKS
	//Creat the Master Task
  if (FRTOS1_xTaskCreate(vMasterTask, "Master", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif /*USE_TEST_TASKS*/
#endif
}
#endif /* PL_HAS_SEMAPHORE */

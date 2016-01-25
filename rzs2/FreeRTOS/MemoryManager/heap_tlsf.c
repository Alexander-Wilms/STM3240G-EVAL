#define MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#include "tlsf.h"

tlsf_t * __attribute__ ((section ("user_data"))) the_tlsf;

void vPortInitMemory(void)
{
   the_tlsf = tlsf_create_with_pool( &__FreeRTOS_heap_begin__, &__FreeRTOS_heap_end__ - &__FreeRTOS_heap_begin__);
}

void * pvPortMalloc(size_t xWantedSize)
{
   vTaskSuspendAll();
   void * res = tlsf_malloc( the_tlsf, xWantedSize);
   xTaskResumeAll();
   return res;
}

void vPortFree(void *pv)
{
   vTaskSuspendAll();
   tlsf_free( the_tlsf, pv);
   xTaskResumeAll();
}

void * pvPortRealloc(void *pv, size_t xWantedSize)
{
   vTaskSuspendAll();
   void * res = tlsf_realloc(the_tlsf, pv, xWantedSize);
   xTaskResumeAll();
   return res;
}

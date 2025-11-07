#include "main.h"
#include "stm32f3xx_hal.h"
#include <string.h>
#include <cstring>

extern UART_HandleTypeDef huart2;

int main()
{
    board_init();

    const char msg[] = "Hello World\n";

    while(true){
        
        HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
        HAL_Delay(1000);
    }

return 0;
}

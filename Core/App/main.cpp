#include "main.h"
#include "stm32f3xx_hal.h"
#include <string.h>
#include <cstring>
#include <span>
#include <array>
#include <cstdint>

#include "Uart.hpp"
#include "ArchUart.hpp"
#include "UartConfig.hpp"
#include "IUart.hpp"
#include "IComm.hpp"

extern UART_HandleTypeDef huart2;

int main()
{       
    board_init();

    const UartConfig my_config = {
        .baudrate = 115200,
        .wordLenght = 8,
        .parity = 0,
    };
    
    ArchUart stm_uart_hw(&huart2);
    Uart comm_port(my_config, stm_uart_hw);
    IComm& comm_interface = comm_port;
    
    if(comm_interface.init()){

        std::array<std::uint8_t, 4> arr{0x41,0x42,0x43,0x44};
        std::span<std::uint8_t> tx_span(
            arr
        );

        comm_interface.write(tx_span);

        std::array<std::uint8_t, 16> rx_array{};

        std::span<uint8_t>rx_span(
            rx_array
        );

        while(1){
            std::size_t received_count = comm_interface.read(rx_span);

            if(received_count > 0) {
    
                std::array<std::uint8_t, 4> reply{0x45,0x46,0x47,0x48};

                std::span<const uint8_t>reply_span(
                    reply
                );

                comm_interface.write(reply_span);
            } else {
                std::array<std::uint8_t, 4> reply{0x49,0x50,0x51,0x52};

                std::span<const uint8_t>reply_span(
                    reply
                );

                comm_interface.write(reply_span);
            }

            HAL_Delay(1000);
        }

    }
    
}

#include "ArchUart.hpp"
#include "stm32f3xx_hal.h"
#include <cstring>


ArchUart::ArchUart(UART_HandleTypeDef* huart_handle): m_huart(huart_handle)
{
    std::memset(m_tx_buffer, 0, sizeof(m_tx_buffer));
}

UART_HandleTypeDef* ArchUart::get_huart_handle() const {
    
    return m_huart;
}

bool ArchUart::init(const UartConfig&) {

    if (!m_huart) return false;

    return true;
}

bool ArchUart::write(std::span<const uint8_t> data) {

    if (!m_huart || data.empty()) return false;

    if (data.size() > UART_TX_BUFFER_SIZE) return false;

    std::memcpy(m_tx_buffer, data.data(), data.size());

    HAL_StatusTypeDef status = HAL_UART_Transmit_IT(

        m_huart,
        m_tx_buffer,
        static_cast<uint16_t>(data.size())
    );

    return (status == HAL_OK);
}

size_t ArchUart::read(std::span<uint8_t> buffer) {

    if (!m_huart || buffer.empty()) return 0;

    HAL_StatusTypeDef status = HAL_UART_Receive_IT(

        m_huart,
        buffer.data(),
        static_cast<uint16_t>(buffer.size())
    );

    if (status == HAL_OK) return buffer.size();
    return 0;

} 
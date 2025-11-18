#pragma once

#include "IUart.hpp"
#include "RingBuffer.hpp"
#include "stm32f3xx_hal.h" 
#include <cstring>
#include <span>
#include <cstdint>

#ifndef UART_TX_BUFFER_SIZE
#define UART_TX_BUFFER_SIZE 256
#endif

class ArchUart : public IUart {
public:
    ArchUart(UART_HandleTypeDef* huart_handle);
    UART_HandleTypeDef* get_huart_handle() const;
    bool init(const UartConfig& config) override;
    bool write(std::span<const uint8_t> data) override;
    size_t read(std::span<uint8_t> buffer) override;
    ArchUart(const ArchUart&) = delete;
    ArchUart& operator=(const ArchUart&) = delete;
private:
    UART_HandleTypeDef* m_huart;
    uint8_t m_tx_buffer[UART_TX_BUFFER_SIZE];

}; 
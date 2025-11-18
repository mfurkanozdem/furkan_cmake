#pragma once

#include "IComm.hpp"
#include "IUart.hpp"
#include "UartConfig.hpp"
#include <span>

class Uart : public IComm{
public:
    Uart(const UartConfig& config, IUart& uart_dev): m_config(config), m_uart_dev(uart_dev){}

    bool init() override {

        return m_uart_dev.init(m_config);
    }

    bool write(std::span<const uint8_t> data) override {

        return m_uart_dev.write(data);
    }

    size_t read(std::span<uint8_t> buffer) override {

        return m_uart_dev.read(buffer);
    }

private:
    const UartConfig m_config;
    IUart& m_uart_dev;
};
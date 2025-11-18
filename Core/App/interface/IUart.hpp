#pragma once

#include <span>
#include "IComm.hpp" 
#include "UartConfig.hpp"     
#include <cstdint> 
#include <cstddef>

class IUart{
public:
    virtual ~IUart() = default;
    virtual bool init(const UartConfig& uart_config) = 0;
    virtual bool write(std::span<const uint8_t> data) = 0;
    virtual size_t read(std::span<uint8_t> buffer) = 0;
};
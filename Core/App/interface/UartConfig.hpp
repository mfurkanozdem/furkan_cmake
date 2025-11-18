#pragma once

#include <cstddef>
#include <cstdint>

struct UartConfig {

    std::uint32_t baudrate;
    std::uint32_t wordLenght;
    std::uint32_t parity;
    //...
};
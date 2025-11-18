#pragma once

#include <cstdint>
#include <span>

class IComm {
public:
    virtual ~IComm() = default;
    virtual bool init() = 0;
    virtual bool write(std::span<const uint8_t> data) = 0;
    virtual size_t read(std::span<uint8_t> buffer) = 0;
};
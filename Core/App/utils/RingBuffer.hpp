#pragma once

#include <cstddef>
#include <cstdint>

template <size_t Capacity>
class RingBuffer {
public:
    RingBuffer() = default;
    auto push(uint8_t data) -> bool {

        size_t next_m_head = next_index(m_head);
        if(next_m_head == m_tail){

            return false;
        }

        m_rbuffer[m_head] = data;
        m_head = next_m_head;
        return true;
    }

    bool pop(uint8_t& data){
        
        if(m_head == m_tail){
        
            return false;
        }

        data = m_rbuffer[m_tail];
        m_tail = next_index(m_tail);
        return true;
    }

    bool pop(std::span<uint8_t> data){
        
        if(m_head == m_tail){
        
            return false;
        }

        data = m_rbuffer[m_tail];
        m_tail = next_index(m_tail);
        return true;
    }

    size_t get_size() const {
        
        return (m_head >= m_tail) ? (m_head - m_tail) : (Capacity - m_tail + m_head);
    }

    size_t get_remain() const {

        return (Capacity - 1) - get_size();
    }

private:
    uint8_t m_rbuffer[Capacity];  
    size_t m_head = 0;
    size_t m_tail = 0;
    
    size_t next_index(size_t index) const {
        
        return (index + 1) % Capacity;
    }
};
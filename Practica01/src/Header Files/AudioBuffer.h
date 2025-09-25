#pragma once

#include <cstdint>

class CAudioBuffer {
public:
    CAudioBuffer(uint32_t _uBuffer);
    ~CAudioBuffer();

    static CAudioBuffer* Load(const char* _sFilename);
    uint32_t GetAlBuffer() const;
private:
    uint32_t m_uBufferID;
};

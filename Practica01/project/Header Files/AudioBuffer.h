#pragma once

class CAudioBuffer {
public:
    CAudioBuffer(unsigned int _uBuffer);

    static CAudioBuffer* Load(const char* _sFilename);
    unsigned int GetAlBuffer() const;
private:
    unsigned int m_uBuffer;
};
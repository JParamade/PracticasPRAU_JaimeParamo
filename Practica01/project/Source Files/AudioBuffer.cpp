#include "../Header Files/AudioBuffer.h"

CAudioBuffer::CAudioBuffer(unsigned int _uBuffer) 
    : m_uBuffer(_uBuffer)
{}

CAudioBuffer* CAudioBuffer::Load(const char* _sFilename) {
    if (!_sFilename) return nullptr;
}

unsigned int CAudioBuffer::GetAlBuffer() const {

}
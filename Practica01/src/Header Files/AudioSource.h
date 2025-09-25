#pragma once

#include "AudioBuffer.h"

class CAudioSource {
public:
    CAudioSource(const CAudioBuffer* _pBuffer);
    ~CAudioSource();
    
    void SetPitch(float _fPitch);
    void SetGain(float _fGain);
    void SetLooping(bool _bLoop);
    
    void SetPosition(float _fX, float _fY, float _fZ);
    void SetVelocity(float _fX, float _fY, float _fZ);
    
    void Play();
    void Stop();
    void Pause();
    bool IsPlaying() const;
private:
    uint32_t m_uSourceID;
};

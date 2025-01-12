#pragma once

#include "AudioBuffer.h"

class CAudioSource {
public:
    CAudioSource(const CAudioBuffer* _pBuffer);
    ~CAudioSource();
    
    void SetPitch(float _fPitch) const;
    void SetGain(float _fGain) const;
    void SetLooping(bool _bLoop) const;
    
    void SetPosition(float _fX, float _fY, float _fZ) const;
    void SetVelocity(float _fX, float _fY, float _fZ) const;
    
    void Play() const;
    void Stop() const;
    void Pause() const;
    bool IsPlaying() const;
private:
    uint32_t m_uSourceID;
};

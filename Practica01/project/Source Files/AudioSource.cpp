#include "../Header Files/AudioSource.h"
#include "../openal/AL/al.h"

CAudioSource::CAudioSource(const CAudioBuffer* _pBuffer) {
    alGenSources(1, &m_uSourceID);

    SetPitch(1.0f);
    SetGain(1.0f);
    SetLooping(false);

    SetPosition(0, 0, 0);
    SetVelocity(0, 0, 0);

    if (_pBuffer) alSourcei(m_uSourceID, AL_BUFFER, static_cast<ALint>(_pBuffer->GetAlBuffer()));
}

CAudioSource::~CAudioSource() {
    alDeleteSources(1, &m_uSourceID);
}
    
void CAudioSource::SetPitch(float _fPitch) {
    alSourcef(m_uSourceID, AL_PITCH, _fPitch);
}

void CAudioSource::SetGain(float _fGain) {
    alSourcef(m_uSourceID, AL_GAIN, _fGain);
}

void CAudioSource::SetLooping(bool _bLoop) {
    alSourcei(m_uSourceID, AL_LOOPING, _bLoop ? AL_TRUE : AL_FALSE);
}
    
void CAudioSource::SetPosition(float _fX, float _fY, float _fZ) {
    alSource3f(m_uSourceID, AL_POSITION, _fX, _fY, _fZ);
}
void CAudioSource::SetVelocity(float _fX, float _fY, float _fZ) {
    alSource3f(m_uSourceID, AL_VELOCITY, _fX, _fY, _fZ);
}
    
void CAudioSource::Play() {
    alSourcePlay(m_uSourceID);
}

void CAudioSource::Stop() {
    alSourceStop(m_uSourceID);
}

void CAudioSource::Pause() {
    alSourcePause(m_uSourceID);
}

bool CAudioSource::IsPlaying() const {
    ALint iState;
    alGetSourcei(m_uSourceID, AL_SOURCE_STATE, &iState);
    return iState == AL_PLAYING;
}
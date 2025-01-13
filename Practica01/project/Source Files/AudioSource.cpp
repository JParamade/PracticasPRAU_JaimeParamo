#include "../Header Files/AudioSource.h"
#include "../openal/AL/al.h"

CAudioSource::CAudioSource(const CAudioBuffer* _pBuffer) {
    alGenSources(1, &m_uSourceID);

    alSourcef(m_uSourceID, AL_PITCH, 1);
    alSourcef(m_uSourceID, AL_GAIN, 1);
    alSourcei(m_uSourceID, AL_LOOPING, 0);

    alSource3f(m_uSourceID, AL_POSITION, 0, 0, 0);
    alSource3f(m_uSourceID, AL_VELOCITY, 0, 0, 0);

    alSourcei(m_uSourceID, AL_BUFFER, static_cast<ALint>(_pBuffer->GetAlBuffer()));
}

CAudioSource::~CAudioSource() {
    alDeleteSources(1, &m_uSourceID);
}
    
void CAudioSource::SetPitch(float _fPitch) const {
    alSourcef(m_uSourceID, AL_PITCH, _fPitch);
}

void CAudioSource::SetGain(float _fGain) const {
    alSourcef(m_uSourceID, AL_GAIN, _fGain);
}

void CAudioSource::SetLooping(bool _bLoop) const {
    alSourcei(m_uSourceID, AL_LOOPING, _bLoop ? AL_TRUE : AL_FALSE);
}
    
void CAudioSource::SetPosition(float _fX, float _fY, float _fZ) const {
    alSource3f(m_uSourceID, AL_POSITION, _fX, _fY, _fZ);
}
void CAudioSource::SetVelocity(float _fX, float _fY, float _fZ) const {
    alSource3f(m_uSourceID, AL_VELOCITY, _fX, _fY, _fZ);
}
    
void CAudioSource::Play() const {
    alSourcePlay(m_uSourceID);
}

void CAudioSource::Stop() const {
    alSourceStop(m_uSourceID);
}

void CAudioSource::Pause() const {
    alSourcePause(m_uSourceID);
}

bool CAudioSource::IsPlaying() const {
    ALint iState;
    alGetSourcei(m_uSourceID, AL_SOURCE_STATE, &iState);
    return iState == AL_PLAYING;
}
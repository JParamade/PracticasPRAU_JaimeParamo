#include "../Header Files/AudioListener.h"
#include "../openal/AL/al.h"

CAudioListener* CAudioListener::GetInstance() {
    if (!m_pInstance) m_pInstance = new CAudioListener();
    return m_pInstance;
}

void CAudioListener::DestroyInstance() {
    delete m_pInstance;
    m_pInstance = nullptr;
}

void CAudioListener::SetListenerPosition(float _fX, float _fY, float _fZ) const {
    alListener3f(AL_POSITION, _fX, _fY, _fZ);
}

void CAudioListener::SetListenerVelocity(float _fX, float _fY, float _fZ) const {
    alListener3f(AL_VELOCITY, _fX, _fY, _fZ);
}

void CAudioListener::SetListenerOrientation(float _fX, float _fY, float _fZ) const {
    alListener3f(AL_ORIENTATION, _fX, _fY, _fZ);
}

CAudioListener::CAudioListener() {
    alListener3f(AL_POSITION, 0, 0, 0);
    alListener3f(AL_VELOCITY, 0, 0, 0);
    alListener3f(AL_ORIENTATION, 0, 0, 0);
}

CAudioListener* CAudioListener::m_pInstance = nullptr;
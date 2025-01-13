#include "../openal/AL/al.h"
#include "../openal/AL/alc.h"

#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#include <glfw3.h>
#include <sstream>
#include <vector>

#include <fstream>     
#include <iterator>

#include "Header Files/AudioBuffer.h"
#include "Header Files/AudioListener.h"
#include "Header Files/AudioSource.h"

using namespace std;

int main() {
    ALCdevice* pDevice = alcOpenDevice(nullptr);
    ALCcontext* pContext = alcCreateContext(pDevice, nullptr);
    ALCboolean oCurrentContext = alcMakeContextCurrent(pContext);

    CAudioBuffer* oAudioBuffer = CAudioBuffer::Load("data/music.wav");
    CAudioSource oAudioSource(oAudioBuffer);
    CAudioListener* oAudioListener = CAudioListener::GetInstance();

    oAudioSource.Play();    
    
    alcDestroyContext(pContext);
    alcCloseDevice(pDevice);
    
    return 0;
}
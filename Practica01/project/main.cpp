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
#include <iostream>
#include <iterator>
#include <thread>

#include "Header Files/AudioBuffer.h"
#include "Header Files/AudioListener.h"
#include "Header Files/AudioSource.h" 

using namespace std;

int main() {
    ALCdevice* pDevice = alcOpenDevice(nullptr);
    ALCcontext* pContext = alcCreateContext(pDevice, nullptr);
    alcMakeContextCurrent(pContext);
    
    CAudioListener& oAudioListener = CAudioListener::GetInstance();
    CAudioBuffer* oAudioBuffer = CAudioBuffer::Load("data/file1.wav");
    CAudioSource oAudioSource(oAudioBuffer);

    alcMakeContextCurrent(nullptr);
    alcDestroyContext(pContext);
    alcCloseDevice(pDevice);
    
    return 0;
}
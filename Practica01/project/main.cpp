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

using namespace std;

int main() {
    ALCdevice* pDevice = alcOpenDevice(nullptr);
    ALCcontext* pContext = alcCreateContext(pDevice, nullptr);
    ALCboolean oCurrentContext = alcMakeContextCurrent(pContext);

    ALuint* aBuffer = new ALuint[10];
    alGenBuffers(10, aBuffer);
    
    alcDestroyContext(pContext);
    alcCloseDevice(pDevice);
    
    return 0;
}
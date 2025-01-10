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
    ALCdevice* oDevice = alcOpenDevice(nullptr);
    ALCcontext* oContext = alcCreateContext(oDevice, nullptr);
    alcMakeContextCurrent(oContext);


    
    alcDestroyContext(oContext);
    alcCloseDevice(oDevice);

    return 0;
}
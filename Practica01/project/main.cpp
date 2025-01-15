#include "../openal/AL/al.h"
#include "../openal/AL/alc.h"

#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#include <glfw3.h>

#include <fstream>     
#include <thread>

#include "Header Files/AudioBuffer.h"
#include "Header Files/AudioListener.h"
#include "Header Files/AudioSource.h" 

using namespace std;

int main() {
    if (!glfwInit()) {
        static_cast<void>(fprintf(stderr, "Failed to initialize GLFW3\n"));
        return -1;
    }

    GLFWwindow* pCurrentWindow = glfwCreateWindow(500, 500, "Audio Test", nullptr, nullptr);
    if (!pCurrentWindow) {
        static_cast<void>(fprintf(stderr, "Failed to open GLFW3 window.\n"));
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(pCurrentWindow);
    
    ALCdevice* pDevice = alcOpenDevice(nullptr);
    if (!pDevice) {
        static_cast<void>(fprintf(stderr, "Failed to open device.\n"));
        glfwTerminate();
        return -1;
    }
    
    ALCcontext* pContext = alcCreateContext(pDevice, nullptr);
    if (!pContext) {
        static_cast<void>(fprintf(stderr, "Failed to create context.\n"));
        glfwTerminate();
        return -1;
    }
    
    alcMakeContextCurrent(pContext);

    CAudioListener& oAudioListener = CAudioListener::GetInstance();
    CAudioBuffer* oAudioBuffer = CAudioBuffer::Load("data/music.wav");
    CAudioSource oAudioSource(oAudioBuffer);

    float fPitch = 1.0f;
    float fPosX = 0.0f;
    bool bKeyUpPressed = false;
    bool bKeyDownPressed = false;
    
    oAudioSource.Play();
    
    while (!glfwWindowShouldClose(pCurrentWindow)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Increase source pitch when UP key is pressed.
        if (glfwGetKey(pCurrentWindow, GLFW_KEY_UP) == GLFW_PRESS && !bKeyUpPressed) { bKeyUpPressed = true; fPitch += 0.1f; oAudioSource.SetPitch(fPitch); }
        if (glfwGetKey(pCurrentWindow, GLFW_KEY_UP) == GLFW_RELEASE) bKeyUpPressed = false;
        // Decrease source pitch when DOWN key is pressed.
        if (glfwGetKey(pCurrentWindow, GLFW_KEY_DOWN) == GLFW_PRESS && !bKeyDownPressed) { bKeyDownPressed = true; fPitch -= 0.1f; oAudioSource.SetPitch(fPitch); }
        if (glfwGetKey(pCurrentWindow, GLFW_KEY_DOWN) == GLFW_RELEASE) bKeyDownPressed = false;
        // Move source when LEFT or RIGHT key are pressed.
        if (glfwGetKey(pCurrentWindow, GLFW_KEY_LEFT) == GLFW_PRESS) { fPosX -= 0.005f; oAudioSource.SetPosition(fPosX, 0, 0); }
        if (glfwGetKey(pCurrentWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) { fPosX += 0.005f; oAudioSource.SetPosition(fPosX, 0, 0); }
        
        glfwSwapBuffers(pCurrentWindow);
        glfwPollEvents();
    }

    oAudioSource.Stop();
    
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(pContext);
    alcCloseDevice(pDevice);

    glfwDestroyWindow(pCurrentWindow);
    glfwTerminate();
    
    return 0;
}
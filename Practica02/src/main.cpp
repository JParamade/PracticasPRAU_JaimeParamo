// Vector
#include "Header Files/Vec2.h"

#include <fstream>     
#include <thread>

#include "Header Files/AudioBuffer.h"
#include "Header Files/AudioListener.h"
#include "Header Files/AudioSource.h" 

#include "../openal/AL/al.h"
#include "../openal/AL/alc.h"

#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#include <litegfx.h>
#include <glfw3.h>

using namespace std;

constexpr unsigned int WINDOW_WIDTH = 500u;
constexpr unsigned int WINDOW_HEIGHT = 500u;

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
  lgfx_setup2d(WINDOW_WIDTH, WINDOW_HEIGHT);

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

  // Figure Variables
  const unsigned int uOvalRadius = 25u;

  // Audio Variables
  CAudioListener& oAudioListener = CAudioListener::GetInstance();
  CVec2 vListenerPosition = CVec2((WINDOW_WIDTH * .5f) - uOvalRadius, WINDOW_HEIGHT - uOvalRadius);
  oAudioListener.SetListenerPosition(vListenerPosition.GetX(), vListenerPosition.GetY(), 0.f);

  CAudioBuffer* oAudioBuffer = CAudioBuffer::Load("data/engine.wav");
  CAudioSource oAudioSource(oAudioBuffer);

  oAudioSource.Play();

  // Time Variables
  double dCurrentTime;
  double dDeltaTime;
  double dLastTime = glfwGetTime();

  while (!glfwWindowShouldClose(pCurrentWindow)) {
    dCurrentTime = glfwGetTime();
    dDeltaTime = dCurrentTime - dLastTime;
    dLastTime = dCurrentTime;

    lgfx_clearcolorbuffer(0.f, 0.f, 0.f);

    vListenerPosition.SetX(vListenerPosition.GetX());
    vListenerPosition.SetY(vListenerPosition.GetY());

    lgfx_setcolor(1.f, 1.f, 1.f, 1.f);
    lgfx_drawoval(vListenerPosition.GetX(), vListenerPosition.GetY(), uOvalRadius * 2, uOvalRadius * 2);
    oAudioListener.SetListenerPosition(vListenerPosition.GetX(), vListenerPosition.GetY(), 0.f);

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
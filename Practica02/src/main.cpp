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
  alDopplerFactor(.5f);

  // Figure Variables
  const unsigned int uListenerRadius = 25u;
  const unsigned int uSourceRadius = 5u;

  // Audio Variables
  CAudioListener& oAudioListener = CAudioListener::GetInstance();
  oAudioListener.SetListenerOrientation(.0f, 1.f, .0f);
  CVec2 vListenerPosition = CVec2((WINDOW_WIDTH * .5f) - uListenerRadius, WINDOW_HEIGHT - uListenerRadius);
  oAudioListener.SetListenerPosition(vListenerPosition.GetX(), vListenerPosition.GetY(), .0f);

  CAudioBuffer* oAudioBuffer = CAudioBuffer::Load("data/engine.wav");
  CAudioSource oAudioSource(oAudioBuffer);
  oAudioSource.SetLooping(true);
  oAudioSource.SetGain(2.f);
  CVec2 vSourcePosition = CVec2((WINDOW_WIDTH * .5f) - uSourceRadius, (WINDOW_HEIGHT * .5f) - uSourceRadius);
  oAudioSource.SetPosition(vSourcePosition.GetX(), vSourcePosition.GetY(), .0f);

  oAudioSource.Play();

  // Movement Variables
  float fListenerSpeed = 100.f;
  float fSourceSpeed = 1.f;
  float fSourceAngle = .0f;
  CVec2 vMovementSourceCenter = CVec2(WINDOW_WIDTH * .5f, WINDOW_HEIGHT * .5f);
  float fMovementSourceRadius = WINDOW_HEIGHT * .25f;

  // Time Variables
  double dCurrentTime;
  double dDeltaTime;
  double dLastTime = glfwGetTime();

  while (!glfwWindowShouldClose(pCurrentWindow)) {
    dCurrentTime = glfwGetTime();
    dDeltaTime = dCurrentTime - dLastTime;
    dLastTime = dCurrentTime;

    float fHorizontalSpeed = .0f;
    if (glfwGetKey(pCurrentWindow, GLFW_KEY_LEFT) == GLFW_PRESS) {
      vListenerPosition.SetX(vListenerPosition.GetX() - fListenerSpeed * dDeltaTime);
      fHorizontalSpeed = -fListenerSpeed;
    }
    if (glfwGetKey(pCurrentWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) {
      vListenerPosition.SetX(vListenerPosition.GetX() + fListenerSpeed * dDeltaTime);
      fHorizontalSpeed = fListenerSpeed;
    }

    oAudioListener.SetListenerVelocity(fHorizontalSpeed, .0f, .0f);

    if (vListenerPosition.GetX() + uListenerRadius < 0) vListenerPosition.SetX(-1.f * uListenerRadius);
    if (vListenerPosition.GetX() + uListenerRadius > WINDOW_WIDTH) vListenerPosition.SetX(WINDOW_WIDTH - uListenerRadius);

    fSourceAngle += fSourceSpeed * dDeltaTime;

    vSourcePosition.SetX(vMovementSourceCenter.GetX() + fMovementSourceRadius * cos(fSourceAngle));
    vSourcePosition.SetY(vMovementSourceCenter.GetY() + fMovementSourceRadius * sin(fSourceAngle));

    oAudioSource.SetVelocity(
      -fMovementSourceRadius * sin(fSourceAngle) * fSourceSpeed, 
      fMovementSourceRadius * cos(fSourceAngle) * fSourceSpeed,
      .0f
    );

    lgfx_clearcolorbuffer(0.f, 0.f, 0.f); 

    lgfx_setcolor(1.f, 1.f, 1.f, 1.f);
    // Draw Listener Oval
    lgfx_drawoval(vListenerPosition.GetX(), vListenerPosition.GetY(), uListenerRadius * 2, uListenerRadius * 2);
    oAudioListener.SetListenerPosition(vListenerPosition.GetX(), vListenerPosition.GetY(), .0f);
    // Draw Source Oval
    lgfx_drawoval(vSourcePosition.GetX(), vSourcePosition.GetY(), uSourceRadius * 2, uSourceRadius * 2);
    oAudioSource.SetPosition(vSourcePosition.GetX(), vSourcePosition.GetY(), .0f);

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
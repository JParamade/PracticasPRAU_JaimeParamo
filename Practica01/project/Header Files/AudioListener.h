#pragma once

class CAudioListener {
public:
    CAudioListener(const CAudioListener&) = delete;
    CAudioListener& operator=(const CAudioListener&) = delete;
    
    static CAudioListener* GetInstance();
    static void DestroyInstance();

    void SetListenerPosition(float _fX, float _fY, float _fZ) const;
    void SetListenerVelocity(float _fX, float _fY, float _fZ) const;
    void SetListenerOrientation(float _fX, float _fY, float _fZ) const;
private:
    CAudioListener();
    ~CAudioListener() = default;
    
    static CAudioListener* m_pInstance;
};
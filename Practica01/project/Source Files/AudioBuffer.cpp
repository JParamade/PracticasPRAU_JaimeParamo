#include "../Header Files/AudioBuffer.h"
#include "../openal/AL/al.h"
#include <fstream>

CAudioBuffer::CAudioBuffer(uint32_t _uBuffer) 
    : m_uBufferID(_uBuffer)
{}

CAudioBuffer::~CAudioBuffer() {
    alDeleteBuffers(1, &m_uBufferID);
}

CAudioBuffer* CAudioBuffer::Load(const char* _sFilename) {
    FILE* pFile;
    int iFile = fopen_s(&pFile, _sFilename, "rb");
    if (iFile != 0) {
        static_cast<void>(fprintf(stderr, "The file \'%s\' could not be opened.\n", _sFilename));
        return nullptr;
    }
    
    char sBuffer[4];
    std::ifstream pStream(_sFilename, std::ios::binary);

    pStream.read(sBuffer, 4);
    if (strncmp(sBuffer, "RIFF", 4) != 0) {
        static_cast<void>(fprintf(stderr, "Non valid WAV file (RIFF is missing).\n"));
        static_cast<void>(fclose(pFile));
        return nullptr;
    }

    pStream.seekg(4, std::ios::cur);
    pStream.read(sBuffer, 4);
    if (strncmp(sBuffer, "WAVE", 4) != 0) {
        static_cast<void>(fprintf(stderr, "Non valid WAV file (WAVE is missing).\n"));
        static_cast<void>(fclose(pFile));
        return nullptr;
    }

    uint16_t uAudioFormat = 0, uChannelNumber = 0, uBitsPerSample = 0;
    uint32_t uChunkSize = 0, uSampleRate = 0, uDataSize = 0;
    char* sAudioData = nullptr;
    
    while (pStream.read(sBuffer, 4)) {
        pStream.read(reinterpret_cast<char*>(&uChunkSize), sizeof(uChunkSize));

        if (strncmp(sBuffer, "fmt ", 4) == 0) {
            pStream.read(reinterpret_cast<char*>(&uAudioFormat), sizeof(uAudioFormat));

            if (uAudioFormat != 1) {
                static_cast<void>(fprintf(stderr, "Non valid audio format (only PCM supported).\n"));
                static_cast<void>(fclose(pFile));
                return nullptr; 
            }
            
            pStream.read(reinterpret_cast<char*>(&uChannelNumber), sizeof(uChannelNumber));
            pStream.read(reinterpret_cast<char*>(&uSampleRate), sizeof(uSampleRate));

            pStream.seekg(6, std::ios::cur);

            pStream.read(reinterpret_cast<char*>(&uBitsPerSample), sizeof(uBitsPerSample));
        }
        else if(strncmp(sBuffer, "data", 4) == 0) {
            pStream.read(reinterpret_cast<char*>(&uDataSize), sizeof(uDataSize));

            sAudioData = new char[uDataSize];
            pStream.read(sAudioData, uDataSize);
            static_cast<void>(fclose(pFile));
        }
        else pStream.seekg(uChunkSize, std::ios::cur);
    }
    
    ALenum uFormatLabel = uChannelNumber == 1
        ? (uBitsPerSample == 8 ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16)
        : uBitsPerSample == 8 ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
    
    ALuint uBuffer;
    alGenBuffers(1, &uBuffer);
    alBufferData(uBuffer, uFormatLabel, sAudioData, static_cast<ALsizei>(uDataSize),static_cast<ALsizei>(uSampleRate));

    delete[] sAudioData;

    return new CAudioBuffer(uBuffer);
}

uint32_t CAudioBuffer::GetAlBuffer() const {
    return m_uBufferID;
}
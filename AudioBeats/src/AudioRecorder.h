#pragma once
#include <portaudio.h>

class AudioRecorder {
public:
    AudioRecorder();
    ~AudioRecorder();
    
    void startRecording();
    void stopRecording();
    bool isRecording() const;

private:
    PaStream *stream;
    bool recording;
    
    static int recordCallback(const void *inputBuffer, void *outputBuffer,
                              unsigned long framesPerBuffer,
                              const PaStreamCallbackTimeInfo *timeInfo,
                              PaStreamCallbackFlags statusFlags,
                              void *userData);
};
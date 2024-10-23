#include "AudioRecorder.h"
#include <iostream>

AudioRecorder::AudioRecorder() : stream(nullptr), recording(false) {
    Pa_Initialize();
}

AudioRecorder::~AudioRecorder() {
    if (stream) {
        Pa_CloseStream(stream);
    }
    Pa_Terminate();
}

void AudioRecorder::startRecording() {
    if (recording) return;
    
    PaError err = Pa_OpenDefaultStream(&stream,
                                       1,               // input channels
                                       0,               // output channels
                                       paFloat32,       // sample format
                                       44100,           // sample rate
                                       256,             // frames per buffer
                                       recordCallback,
                                       this);
    
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return;
    }
    
    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return;
    }
    
    recording = true;
}

void AudioRecorder::stopRecording() {
    if (!recording) return;
    
    PaError err = Pa_StopStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    }
    
    recording = false;
}

bool AudioRecorder::isRecording() const {
    return recording;
}

int AudioRecorder::recordCallback(const void *inputBuffer, void *outputBuffer,
                                  unsigned long framesPerBuffer,
                                  const PaStreamCallbackTimeInfo *timeInfo,
                                  PaStreamCallbackFlags statusFlags,
                                  void *userData) {
    // Here you would process the audio data
    // For now, we'll just print the max amplitude
    const float *input = static_cast<const float*>(inputBuffer);
    float maxAmplitude = 0.0f;
    
    for (unsigned long i = 0; i < framesPerBuffer; i++) {
        float amplitude = std::abs(input[i]);
        if (amplitude > maxAmplitude) {
            maxAmplitude = amplitude;
        }
    }
    
    std::cout << "Max amplitude: " << maxAmplitude << std::endl;
    
    return paContinue;
}
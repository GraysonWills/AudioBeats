#include "GUI.h"
#include "AudioRecorder.h"

int main(int argc, char *argv[]) {
    GUI gui(argc, argv);
    AudioRecorder recorder;
    
    gui.setRecordCallback([&recorder]() {
        if (recorder.isRecording()) {
            recorder.stopRecording();
        } else {
            recorder.startRecording();
        }
    });
    
    return gui.run();
}
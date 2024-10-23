cmake_minimum_required(VERSION 3.10)
project(AudioBeats)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
find_package(PortAudio REQUIRED)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(AudioBeats 
    src/main.cpp
    src/AudioRecorder.cpp
    src/GUI.cpp
)

target_link_libraries(AudioBeats ${GTK3_LIBRARIES} ${PORTAUDIO_LIBRARIES})

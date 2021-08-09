#ifndef Melody_h
#define Melody_h

#include "Arduino.h"
#include "Pitches.h"

class melody {
    public:
        melody(uint8_t tone_pin);
        void play();
        int next();

    private:
        uint8_t _tone_pin;
        int _current_playing;
        void play_melody(int notes[], size_t note_length, int note_durations[], float tempo);
        void play_melody(int notes[], size_t note_length, int note_duration, float tempo);
};

#endif
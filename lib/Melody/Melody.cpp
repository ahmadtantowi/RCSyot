#include "Melody.h"

melody::melody(uint8_t tone_pin) {
    _tone_pin = tone_pin;
    _current_playing = 1;
}

// He is a Pirate
int _pirate_notes[] = {
    NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4,
    NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, 
    NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4,  
    NOTE_A3, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_F4, 
    NOTE_F4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_D4,
    0, NOTE_A3, NOTE_C4, NOTE_B3, NOTE_D4, NOTE_B3, NOTE_E4, NOTE_F4,
    NOTE_F4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4,
    NOTE_D4, 0, 0, NOTE_A3, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_F4,
    NOTE_G4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_G4,
    NOTE_A4, NOTE_D4, 0, NOTE_D4, NOTE_E3, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_A4, 
    NOTE_D4, 0, NOTE_D4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_D4
};
int _pirate_durations[] = {
    4, 8, 4, 8, 4, 8, 8, 8, 8, 4, 8, 4, 8, 4, 8, 8, 8, 8, 4, 8, 4, 8,
    4, 8, 8, 8, 8, 4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 8, 8,
    8, 4, 8, 8, 8, 4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 8, 4,
    4, 8, 8, 8, 8, 4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 8, 8,
    8, 4, 8, 8, 8, 4, 4, 4, 8, 4, 8, 8, 8, 4, 4, 8
};
float _pirate_tempo = 1.05;

// Crazy Frog
int _crazy_frog_notes[] = {
    NOTE_D4, 0, NOTE_F4, NOTE_D4, 0, NOTE_D4, NOTE_G4, NOTE_D4, NOTE_C4,
    NOTE_D4, 0, NOTE_A4, NOTE_D4, 0, NOTE_D4, NOTE_AS4, NOTE_A4, NOTE_F4,
    NOTE_D4, NOTE_A4, NOTE_D5, NOTE_D4, NOTE_C4, 0, NOTE_C4, NOTE_A3, NOTE_E4, NOTE_D4,
    0, NOTE_D4, NOTE_D4
};
int _crazy_frog_durations[] = {
    8, 8, 6, 16, 16, 16, 8, 8, 8,
    8, 8, 6, 16, 16, 16, 8, 8, 8,
    8, 8, 8, 16, 16, 16, 16, 8, 8, 2,
    8, 4, 4
};
float _crazy_frog_tempo = 1.3;

// Mario Underworld
int _mario_uw_notes[] = {
    NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_AS3, NOTE_AS4, 0, 0,
    NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_AS3, NOTE_AS4, 0, 0,
    NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4, NOTE_DS3, NOTE_DS4, 0, 0,
    NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4, NOTE_DS3, NOTE_DS4, 0,
    0, NOTE_DS4, NOTE_CS4, NOTE_D4,
    NOTE_CS4, NOTE_DS4, NOTE_DS4, NOTE_GS3, NOTE_G3, NOTE_CS4,
    NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
    NOTE_GS4, NOTE_DS4, NOTE_B3, NOTE_AS3, NOTE_A3, NOTE_GS3, 0, 0, 0
};
int _mario_uw_durations[] = {
    12, 12, 12, 12, 12, 12, 6, 3,
    12, 12, 12, 12, 12, 12, 6, 3,
    12, 12, 12, 12, 12, 12, 6,
    3, 12, 12, 12, 12,
    12, 12, 6, 6, 18, 18, 18,
    6, 6, 6, 6, 6, 6,
    18, 18, 18, 18, 18, 18, 10, 10, 10,
    10, 10, 10, 3, 3, 3
};
float _mario_uw_tempo = 1.8;

// Coffin Dance
int _coffin_notes[] = {
    NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5,
    NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5,
    NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
    NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5,
    NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5,
    NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5,
    NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_F4,
    NOTE_G4, 0, NOTE_G4, NOTE_D5,
    NOTE_C5, 0, NOTE_AS4, 0,
    NOTE_A4, 0, NOTE_A4, NOTE_A4,
    NOTE_C5, 0, NOTE_AS4, NOTE_A4,
    NOTE_G4, 0, NOTE_G4, NOTE_AS5,
    NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
    NOTE_G4, 0, NOTE_G4, NOTE_AS5,
    NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
    NOTE_G4, 0, NOTE_G4, NOTE_D5,
    NOTE_C5, 0, NOTE_AS4, 0,
    NOTE_A4, 0, NOTE_A4, NOTE_A4,
    NOTE_C5, 0, NOTE_AS4, NOTE_A4,
    NOTE_G4, 0, NOTE_G4, NOTE_AS5,
    NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
    NOTE_G4, 0, NOTE_G4, NOTE_AS5,
    NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_G4
};
int _coffin_duration = 4;
float _coffin_tempo = 0.8;

void melody::play() {
    // play_melody();
    if (_current_playing == 1) {
        play_melody(_pirate_notes, sizeof(_pirate_notes) / sizeof(int), _pirate_durations, _pirate_tempo);
    }
    else if (_current_playing == 2) {
        play_melody(_crazy_frog_notes, sizeof(_crazy_frog_notes) / sizeof(int), _crazy_frog_durations, _crazy_frog_tempo);
    }
    else if (_current_playing == 3) {
        play_melody(_mario_uw_notes, sizeof(_mario_uw_notes) / sizeof(int), _mario_uw_durations, _mario_uw_tempo);
    }
    else if (_current_playing == 4) {
        play_melody(_coffin_notes, sizeof(_coffin_notes) / sizeof(int), _coffin_duration, _coffin_tempo);
    }
}

int melody::next() {
    if (_current_playing < 4) {
        _current_playing++;
    }
    else {
        _current_playing = 1;
    }

    return _current_playing;
}

void melody::play_melody(int notes[], size_t note_length, int note_durations[], float tempo) {
    for (size_t i = 0; i < note_length; i++)
    {
        // convert duration into time delay
        int duration = 1000 / note_durations[i];
        // play tone
        tone(_tone_pin, notes[i], duration);
        // calculate tempo with duration
        int pause_interval = duration * tempo;

        delay(pause_interval);
        noTone(_tone_pin);
    }
}

void melody::play_melody(int notes[], size_t note_length, int note_duration, float tempo) {
    // convert duration into time delay
    int duration = 1000 / note_duration;
    
    for (size_t i = 0; i < note_length; i++)
    {
        // play tone
        tone(_tone_pin, notes[i], duration);
        // calculate tempo with duration
        int pause_interval = duration * tempo;

        delay(pause_interval);
        noTone(_tone_pin);
    }
}
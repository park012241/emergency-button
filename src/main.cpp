#include <Arduino.h>
#include "../.pio/libdeps/leonardo/Keyboard/src/Keyboard.h"
#include "Debouncer.h"

#define WINDOWS

#define BUTTON_PIN 2

Debouncer debouncedHandler(BUTTON_PIN, 50, Debouncer::Active::H);

void onFall(__attribute__((unused)) int state);

void onRise(__attribute__((unused)) int state);

void onChange(__attribute__((unused)) int state);

__attribute__((unused)) void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    debouncedHandler.subscribe(Debouncer::Edge::FALL, onFall);
    debouncedHandler.subscribe(Debouncer::Edge::RISE, onRise);
    debouncedHandler.subscribe(Debouncer::Edge::CHANGED, onChange);
}

__attribute__((unused)) void loop() {
    // write your code here
    debouncedHandler.update();
}

volatile bool goRight = true;

void onFall(__attribute__((unused)) const int state) {
#ifdef WINDOWS
    // Press Windows Key to switch desktop
    Keyboard.press(KEY_LEFT_GUI);
#endif

    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(goRight ? KEY_RIGHT_ARROW : KEY_LEFT_ARROW);
    delay(50);
    Keyboard.releaseAll();

    // Flip bool variable
    goRight = !goRight;

#ifdef MACOS
    delay(1000);
#endif
}

void onRise(__attribute__((unused)) const int state) {}

void onChange(__attribute__((unused)) const int state) {}

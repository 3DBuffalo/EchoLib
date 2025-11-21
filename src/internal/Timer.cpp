#include "Timer.h"

Timer::Timer()
    : startTime(0),
      accumulatedTime(0),
      pauseAt(0),
      running(false),
      paused(false) {}

void Timer::start() {
    startTime = millis();
    accumulatedTime = 0;
    running = true;
    paused = false;
    setP = false;
}

void Timer::stop() {
    running = false;
    paused = false;
    accumulatedTime = 0;
}

void Timer::pause() {
    if (running && !paused) {
        accumulatedTime += millis() - startTime;
        paused = true;
    }
}

void Timer::reset() {
    startTime = millis();
    accumulatedTime = 0;
    paused = false;
    running = false;
    setP = false;
}

void Timer::setPause(unsigned long ms) {
    pauseAt = ms;
    setP = true;
}

void Timer::resume() {
    if (paused) {
        startTime = millis();
        paused = false;
        running = true;
        setP = false;
    }
}

bool Timer::isPaused() const {
    return paused;
}

unsigned long Timer::get() const {
    if (!running) {
        return accumulatedTime;
    }

    if (paused) {
        return accumulatedTime;
    }

    unsigned long current = accumulatedTime + (millis() - startTime);

    // Auto pause check
    if (pauseAt > 0 && current >= pauseAt && setP) {
        return pauseAt;
    }

    return current;
}

float Timer::getSeconds() const {
    return get() / 1000.0f;
}

#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer {
public:
    Timer();

    void start();                     // Start the timer
    void stop();                      // Stop the timer (reset state)
    void pause();                     // Pause the timer
    void reset();                     // Reset time to 0
    void setPause(unsigned long ms);  // Auto-pause when reaching ms
    void resume();                    // Continue after pause/stop
    bool isPaused() const;            // Is the timer paused?

    unsigned long get() const;        // Elapsed time in ms
    float getSeconds() const;         // Elapsed time in seconds

private:
    unsigned long startTime;          // Last time started
    unsigned long accumulatedTime;    // Total accumulated time
    unsigned long pauseAt;            // Auto pause threshold (ms)
    bool running;
    bool paused;
    bool setP;
};

#endif // TIMER_H

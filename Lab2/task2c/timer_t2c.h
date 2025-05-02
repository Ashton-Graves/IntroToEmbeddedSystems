#ifndef TIMER_H_
#define TIMER_H_

// initializes the proper registers and configures timer settings
void timerN_init(int n);

// turns on the timer to run at 1 Hz frequency
void timer_on(int timerN);

// turns off the timer
void timer_off(int timerN);

// Activates the timer for a specified n seconds
// void timer_n_secs(int n);

// Activates the timer for a specified n seconds
void timer_sec_repeat(int n, int timerN);

// reads if the timer has expired
int timer_expired(int timerN);

#endif //TIMER_H_
#ifndef TIMER_H_
#define TIMER_H_

// initializes the proper registers and configures timer settings
void timer_init(void);

// turns on the timer to run at 1 Hz frequency
void timer_on(void);

// turns off the timer
void timer_off(void);

// Activates the timer for a specified n seconds
void timer_n_secs(int n);

#endif //TIMER_H_
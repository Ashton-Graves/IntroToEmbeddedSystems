/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 05/01/25

* The purpose of this file is to provide function declarations to allow use of onboard timers
*/

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

// Activates the timer for a specified n seconds
void timer_sec_repeat(int n);

// reads if the timer has expired
int timer_expired(void);

#endif //TIMER_H_
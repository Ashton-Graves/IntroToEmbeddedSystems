/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 05/30/25

* The purpose of this file is to provide function declarations to allow use of on_board timers for lab 4 task 2a.
*/

#ifndef TIMER_H_
#define TIMER_H_

// initializes the proper registers and configures timer settings. Timer0A runs at .2 Hz (5 second timer),
// and Timer1A and Timer2A run at 1 Hz. Timer 0A is periodic, while the other timers are one-shot.
void timerN_init(int n);

// turns on the timer
void timer_on(int timerN);

// turns off the timer
void timer_off(int timerN);

// Activates timerN for a specified n seconds. 
void timer_sec_repeat(int n, int timerN);

// reads if timerN has expired.
int timer_expired(int timerN);

#endif //TIMER_H_
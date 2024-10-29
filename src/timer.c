#include <time.h>
#include "../include/timer.h"

void delay(int milliseconds) {
    long pause;
    clock_t now, then;
  
    pause = milliseconds * (CLOCKS_PER_SEC / 1000);
    now = then = clock();
    while((now - then) < pause)
        now = clock();
}
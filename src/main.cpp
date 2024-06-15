#include "clock.h"
#include "timer.h"

int main() {
    ATimer* t = new Timer;
    Clock p(winWithoutMs, hImg);
    p.run(*t);

    delete t;

    return 0;
}

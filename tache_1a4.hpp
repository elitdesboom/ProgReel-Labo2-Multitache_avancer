#ifndef TACHE_1A4_HPP
#define TACHE_1A4_HPP

#include "thread.hpp"
#include "screen.hpp"
#include "temps.hpp"
#include "sem.hpp"

struct StageShared
    {
    TSemaphore sem[4]; // 0=start,1=sleep1s,2=loops,3=end
    TTemps chrono;
    int cycle;
    StageShared(): sem{TSemaphore(1),TSemaphore(0),TSemaphore(0),TSemaphore(0)}, cycle(0) {}
    };

class TacheFifo : public TThread
    {
    private:
        TScreen *screen;
        StageShared *shared;
        int stage; // 0..3
    public:
    TacheFifo(const char *name, StageShared *shared, TScreen *screen, int stage, int policy, int priority, int32_t cpu);
    ~TacheFifo();
        void task(void);
    };

#endif // TACHE_1A4_HPP

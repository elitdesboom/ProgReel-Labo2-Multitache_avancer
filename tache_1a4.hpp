#ifndef TACHE_1A4_HPP
#define TACHE_1A4_HPP

#include "thread.hpp"
#include "screen.hpp"
#include "temps.hpp"
// #include "sem.hpp" // plus nécessaire si on n'utilise plus les sémaphores de chaîne

struct StageShared
    {
    TTemps chrono;
    int cycle;
    StageShared(): chrono(), cycle(0) {}
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

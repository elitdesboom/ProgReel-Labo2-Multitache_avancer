#ifndef TACHE_CLAVIER_HPP
#define TACHE_CLAVIER_HPP

#include "thread.hpp"
#include "screen.hpp"
#include "clavier.hpp"

extern volatile bool gQuitProgramme;

class TacheClavier : public TThread
    {
    private:
        TScreen *screen;
        TClavier *clavier;
        int curCol;
        int curLine;
    public:
        TacheClavier(const char *name, TScreen *screen,int policy,int priority,int32_t cpu = 0);
        ~TacheClavier();
        void task(void);
    };

#endif // TACHE_CLAVIER_HPP

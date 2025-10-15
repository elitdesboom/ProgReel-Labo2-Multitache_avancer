#include "tache_clavier.hpp"
#include <unistd.h>

volatile bool gQuitProgramme = false;

TacheClavier::TacheClavier(const char *name, TScreen *screen_,int policy,int priority,int32_t cpu) :
            TThread(name,screen_,policy,priority,cpu), screen(screen_), curCol(1), curLine(9)
    {
    clavier = TClavier::getInstance();
    }

TacheClavier::~TacheClavier() {}

void TacheClavier::task(void)
    {
    signalStart();
    if(screen)
        screen->dispStr(1,8,(char*)"Clavier (q/* pour quitter):");

    while(!gQuitProgramme)
        {
        if(clavier && clavier->kbhit())
            {
            int c = clavier->getch();
            if(c == '*') 
                {
                gQuitProgramme = true;
                break;
                }
            if(c == '\n' || c == '\r')
                {
                curLine++;
                curCol = 1;
                if(curLine > 20) curLine = 9; // wrap
                }
            else
                {
                if(screen)
                    {
                    char tmp[2]; tmp[0] = (char)c; tmp[1] = '\0';
                    screen->dispStr(curCol,curLine,tmp);
                    curCol++;
                    if(curCol > 78) { curCol = 1; curLine++; if(curLine > 20) curLine = 9; }
                    }
                }
            }
        usleep(20000); // 20 ms poll
        }
    }

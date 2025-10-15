#include "tache_1a4.hpp"
#include <unistd.h>

TacheFifo::TacheFifo(const char *name, StageShared *shared_, TScreen *screen_, int stage_, int policy, int priority, int32_t cpu) :
                                    TThread(name, shared_, policy, priority, cpu), screen(screen_), shared(shared_), stage(stage_)
    {}

TacheFifo::~TacheFifo() {}

void TacheFifo::task(void)
    {
    signalStart();
    while(1)
        {
        shared->sem[stage].take();

        int baseY = 2 + stage; // ligne dédiée par tâche
        if(screen)
            {
            screen->dispStr(1,baseY,(char*)"Tache");
            screen->dispStr(7,baseY,(int32_t)stage);
            screen->dispStr(10,baseY,(char*)":");
            }

        switch(stage)
            {
            case 0: // afficher temps départ
                if(screen) {
                    screen->dispStr(13,baseY,(char*)"Start");
                    screen->dispStr(20,baseY,shared->chrono.now());
                    screen->dispStr(1,7,(char*)"Cycle:");
                    screen->dispStr(8,7,(int32_t)shared->cycle);
                }
                break;
            case 1: // dormir 1s
                if(screen) screen->dispStr(13,baseY,(char*)"Sleep1s");
                sleep(1);
                break;
            case 2: // double boucle + affichage progression
                if(screen) screen->dispStr(13,baseY,(char*)"Boucles");
                {
                volatile unsigned long dummy=0;
                for(int i=0;i<100000;i++)
                    {
                    if( (i % 1000) == 0 && screen)
                        {
                        screen->dispStr(22,baseY,(char*)"i=");
                        screen->dispStr(25,baseY,(int32_t)i);
                        }
                    for(int j=0;j<5000;j++)
                        dummy += (i ^ j);
                    }
                if(screen)
                    {
                    screen->dispStr(22,baseY,(char*)"i=");
                    screen->dispStr(25,baseY,(int32_t)99999);
                    }
                }
                break;
            case 3: // afficher temps fin puis dormir 30s
                if(screen) {
                    screen->dispStr(13,baseY,(char*)"End");
                    screen->dispStr(20,baseY,shared->chrono.now());
                }
                sleep(30);
                shared->cycle++; // prochain cycle
                break;
            }
        shared->sem[(stage+1)%4].release();
        }
    }

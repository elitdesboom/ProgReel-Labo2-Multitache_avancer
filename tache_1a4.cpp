#include "tache_1a4.hpp"
#include <unistd.h>

TacheFifo::TacheFifo(const char *name, StageShared *shared_, TScreen *screen_, int stage_, int policy, int priority, int32_t cpu) :
                                    TThread(name, shared_, policy, priority, cpu), screen(screen_), shared(shared_), stage(stage_)
    {}

TacheFifo::~TacheFifo() {}

void TacheFifo::task(void)
{
    signalStart();
    // Chaque tâche exécute en boucle la séquence complète
    TTemps chrono; // local pour éviter les accès concurrents au tampon interne
    while(1)
    {
        int baseY = 2 + (stage * 2); // 2 lignes par tâche pour éviter tout chevauchement
        if(screen)
        {
            screen->dispStr(1,baseY,(char*)"Tache");
            screen->dispStr(7,baseY,(int32_t)stage);
            screen->dispStr(10,baseY,(char*)":");
        }

        // 1) Afficher temps départ (gauche)
        if(screen) {
            screen->dispStr(13,baseY,(char*)"Start:");
            screen->dispStr(20,baseY,chrono.now());
            // nettoyer la ligne (padding)
            screen->dispStr(40,baseY,(char*)"               ");
        }

    // 2) Dormir 1s
    if(screen) screen->dispStr(12,baseY+1,(char*)"End:                           ");
    if(screen) screen->dispStr(40,baseY+1,(char*)"State: Sleep1s        ");
        sleep(1);

    // 3) Double boucle (sans affichage de progression)
    if(screen) screen->dispStr(40,baseY+1,(char*)"State: Boucles   ");
        {
        volatile unsigned long dummy=0;
        for(int i=0;i<100000;i++)
        {
            for(int j=0;j<5000;j++)
            {
                dummy += (i ^ j);
            }
        }

        // 4) Afficher temps fin (droite) puis dormir 2s
            if(screen) 
            {
                    screen->dispStr(12,baseY+1,(char*)"End:");
                    screen->dispStr(17,baseY+1,chrono.now());
                    // padding pour effacer d'anciens restes
                    screen->dispStr(36,baseY+1,(char*)"           ");
                }
                sleep(2);
        }
   }
}

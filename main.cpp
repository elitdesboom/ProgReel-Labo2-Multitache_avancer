//============================================================================
// Name        : TemplateThreadCom.cpp
// Author      : SG
// Version     :
// Copyright   : Your copyright notice
// Description : Template Thread Com
//============================================================================

#include "clavier.hpp"
#include "screen.hpp"
#include "tache_1a4.hpp"
#include "tache_clavier.hpp"

extern volatile bool gQuitProgramme;

int main(int argc, char *argv[])
    {
    TThread::initTaskMain(SCHED_FIFO,0);

    // TClavier initialisé indirectement dans TacheClavier
    TScreen *screen  = new TScreen();
    screen->start();

    StageShared *shared = new StageShared();

    TacheFifo *s0 = new TacheFifo("Stage0",shared,screen,0,SCHED_FIFO,93,0);
    TacheFifo *s1 = new TacheFifo("Stage1",shared,screen,1,SCHED_FIFO,92,0);
    TacheFifo *s2 = new TacheFifo("Stage2",shared,screen,2,SCHED_FIFO,91,0);
    TacheFifo *s3 = new TacheFifo("Stage3",shared,screen,3,SCHED_FIFO,90,0);
    TacheClavier *tClav = new TacheClavier("Clavier",screen,SCHED_FIFO,89,0);

    s0->start(); s1->start(); s2->start(); s3->start();
    tClav->start();

    screen->dispStr(1,1,(char*)"Affichage des taches en fifo");

    while(!gQuitProgramme)
        usleep(50000);

    delete tClav; delete s0; delete s1; delete s2; delete s3; delete shared; delete screen;
    return 0;
    }

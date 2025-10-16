//============================================================================
// Name        : TemplateThreadCom.cpp
// Author      : SG
// Version     : 0.1
// Copyright   : Éliott Desbordes-Boom
// Description : Template Thread Com
//============================================================================

#include "clavier.hpp"
#include "screen.hpp"
#include "tache_1a4.hpp"

int main(int argc, char *argv[])
{
    TThread::initTaskMain(SCHED_FIFO,0);

    // TClavier géré depuis le main
    TScreen *screen  = new TScreen();
    screen->start();

    StageShared *shared = new StageShared();

    TacheFifo *s0 = new TacheFifo("Stage0",shared,screen,0,SCHED_FIFO,93,0);
    TacheFifo *s1 = new TacheFifo("Stage1",shared,screen,1,SCHED_FIFO,92,0);
    TacheFifo *s2 = new TacheFifo("Stage2",shared,screen,2,SCHED_FIFO,91,0);
    TacheFifo *s3 = new TacheFifo("Stage3",shared,screen,3,SCHED_FIFO,90,0);

    s0->start(); s1->start(); s2->start(); s3->start();

    // Affichage initial
    screen->dispStr(1,1,(char*)"Code à l'écoute sur le screen");
    screen->dispStr(1,8,(char*)"Clavier ('*' pour quitter):"); // label

    // Clavier via singleton
    TClavier *clavier = TClavier::getInstance();

    // Buffer circulaire (40 chars + '\0')
    char buffer[51] = {0};
    int index = 0;
    int car = 0;

    do
    {
        if(clavier && clavier->kbhit())
          {
          car = clavier->getch();
          if (car != '*') 
            {
            buffer[index] = (char)car;
            index = (index + 1) % 50; // Circulaire
            buffer[50] = '\0';
            // Afficher le buffer entier (col 11, ligne 7)
            screen->dispStr(29, 8, buffer);
            }
          }
        usleep(20000); // petit poll pour ne pas occuper 100% CPU
    }
    while(car != '*'); // Quitter si la touche '*' est pressée

    // Arrêt/cleanup
    delete s0; delete s1; delete s2; delete s3; delete shared; delete screen;
    return 0;
}

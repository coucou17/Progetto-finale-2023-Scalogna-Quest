#include "gamelib.h"
//funzione principale del gioco
int main(void){
  time_t t;
  srand((unsigned)time(&t));
  int a = 0;
    unsigned short scelta = 0;
    system("clear");
printf("\033[1;31m");
printf("\n\n");
printf("\t\t\t\t\t                                                                                                                                                                 \n");
printf("\033[1;32m\t\t\t\t\t    ███████╗ ██████╗ █████╗ ██╗      ██████╗  ██████╗ ███╗   ██╗ █████╗        ██████╗ ██╗   ██╗███████╗███████╗████████╗                               \n");
printf("\033[1;32m\t\t\t\t\t    ██╔════╝██╔════╝██╔══██╗██║     ██╔═══██╗██╔════╝ ████╗  ██║██╔══██╗      ██╔═══██╗██║   ██║██╔════╝██╔════╝╚══██╔══╝                                        \n");
printf("\033[1;37m\t\t\t\t\t    ███████╗██║     ███████║██║     ██║   ██║██║  ███╗██╔██╗ ██║███████║█████╗██║   ██║██║   ██║█████╗  ███████╗   ██║                                           \n");
printf("\033[1;37m\t\t\t\t\t    ╚════██║██║     ██╔══██║██║     ██║   ██║██║   ██║██║╚██╗██║██╔══██║╚════╝██║▄▄ ██║██║   ██║██╔══╝  ╚════██║   ██║                                           \n");
printf("\033[1;31m\t\t\t\t\t    ███████║╚██████╗██║  ██║███████╗╚██████╔╝╚██████╔╝██║ ╚████║██║  ██║      ╚██████╔╝╚██████╔╝███████╗███████║   ██║                                           \n");
printf("\033[1;31m\t\t\t\t\t    ╚══════╝ ╚═════╝╚═╝  ╚═╝╚══════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═╝       ╚══▀▀═╝  ╚═════╝ ╚══════╝╚══════╝   ╚═╝                                           \n");
printf("\t\t\t\t\t                                                                                                                                                                 \n");
printf("\n\n");
printf("\033[1;37m");
printf("\t\t\t||==========================================================================================================================================================||\n");
printf("\t\t\t||                                                   ****************************************                                                               ||\n");
printf("\t\t\t||                                                                                                                                                          ||\n");
printf("\t\t\t||                             Scalogna-Quest è un gioco in cui i giocatori giocano in turni. Il giocatore corrente può avanzare una volta                  ||\n");
printf("\t\t\t||            sola altrimenti si passa automaticamente ad un altro giocatore. Non si può giocare due volte nello stesso turno, per giocare di nuovo,        ||\n");
printf("\t\t\t||    devi aspettare che tutti gli altri giocatori abbiano giocato. Vince il primo giocatore che arriva fino all'ultima zona, cioè finisce il percorso      ||\n");
printf("\t\t\t||                                                                                                                                                          ||\n");
printf("\t\t\t||                                                                                                                                                          ||\n");
printf("\t\t\t||                                                           PENSI DI POTER FARCELA ???                                                                     ||\n");
printf("\t\t\t||==========================================================================================================================================================||\n");
printf("\033[1;37m");
    printf("\033[1;32m\n\n\n\t\t\t\t\t\t\t\t\t PREMI INVIO PER SAPERLO... \n");
//while (getchar() != '\n');
while((a = getchar()) != '\n' && a != EOF);//pulizia buffer
system("clear");
printf("\n");
  do{
     printf("\033[32m\n\n\t\t\t\t\t\t\t\t\tSCEGLI UN'OPZIONE \n\n");
     printf("\033[1;37m");
     printf(" 1°) imposta gioco\n\n 2°) gioca\n\n 3°) termina gioco\n\n");
     printf("\033[92mScelta:\033[0m ");
     scanf("%hu",&scelta);
     while (getchar() != '\n');
     system("clear");

   switch (scelta) {
       case 1:
          imposta_gioco();
          break;

       case 2:
          gioca();
          break;

       case 3:
          termina_gioco();
          break;

       default:
          printf("\033[1;31mscelta sbagliata!!!!!\n");
          break;
     }
}while(scelta!= 3);
return 0;

}

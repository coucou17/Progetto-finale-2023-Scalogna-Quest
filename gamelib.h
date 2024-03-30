#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

void imposta_gioco();
void gioca();
void termina_gioco();
void menu2();

enum RisultatoDado {teschio, scudo_bianco, scudo_nero};
enum classe_giocatore{barbaro, nano, elfo, mago};
enum Tipo_tesoro{nessun_tesoro, veleno, guarigione, doppia_guarigione};
enum Tipo_porta{nessuna_porta, porta_normale, porta_da_scassinare};
enum Tipo_zona {
  corridoio,
  scala,
  sala_banchetto,
  magazzino,
  giardino,
  posto_guardia,
  prigione,
  cucina,
  armeria,
  tempio,
};


struct Giocatore {
     char nome_giocatore[50];
     enum classe_giocatore classe;
     struct Zona_segrete* posizione;
     unsigned char p_vita;
     unsigned char dadi_attaco;
     unsigned char dadi_difesa;
     unsigned char mente;
     unsigned char potere_speciale;
};

struct Zona_segrete {
     struct Zona_segrete* zona_successiva;
     struct Zona_segrete* zona_precedente;
     enum Tipo_zona zona;
     char nome_z[50];
     enum Tipo_tesoro tesoro;
     enum Tipo_porta porta;
};

struct AbitanteSegrete {
  char name[50];
  unsigned char p_vita;
  unsigned char dadi_attaco;
  unsigned char dadi_difesa;
};

#include "gamelib.h"
#define NUMZONE 15



struct AbitanteSegrete* abitante[] = {NULL};
struct Giocatore* giocatori[4]={NULL};
static unsigned short impostato= 0; // verifica se il gioco è stato impostato prima
static int num_giocatori; // variabile per il numero di giocatore
static int count_zone= 0; // variabile che contolla il numero totale di zone nella mappa
static int termina; // la partita termina quando è uguale a 1
static int avanzato = 0; // variabile per controllare che il giocatore avanza una volta sola
static int scappato = 0; // diventa 1 se c'è un abitante cioè il diocatore può scappare altrimenti diventa 0
static int turno = 0;
 bool gioco = false; // controlla se dopo aver impostato il gioco, il giocatore ha giocato o no 
 bool riavvia = false;
 bool abitante_apparso = false; // controlla se c'è l'abitante nella stanza
 bool preso= false; // controlla se il tesoro è stato preso
 // printf("\n\033[1;37m") tipologia di print che userò su tutto il progetto per impostare i colori


//dichiarazione dei puntatori globali
static struct Zona_segrete* pFirst= NULL;
static struct Zona_segrete* pLast= NULL;

// Funzioni statistiche
static void count_tipo();
static void abitante_attack();
static void sei_morto();
static void hai_vinto();
static void game_over();
static void riavvia_gioco();
static void genera_mappa();
static void cancella_zona();
static void inserisci_zona();
static void chiudi_mappa();
static void stampa_mappa();
static void stampa_giocatore();
static void avanza();
static void combatti();
static void indietreggia();
static void prendi_tesoro();
static void apri_porta();
static void stampa_zona();
static void scappa();
static void gioca_potere_speciale(struct Giocatore* giocatore);
static void passa();
static void appaia_abitante();
static void caratteristiche_Abitanti();
static void rimuoviGiocatore();
static void turno_giocatore();

// genera un numero casuale tra il min e il max
static int numero_casuale(int min, int max) {
   return rand() % (max - min +1) + min;
}



void main2() {
  //menu
  int menù;
  do {
    printf("\n\n\033[1;35mMenù\n");
    printf("\n\033[1;39m> 1) genera_mappa()\n");
    printf("\n\033[1;35m> 2) inserisci_zona()\n");
    printf("\n\033[1;39m> 3) cancella_zona()\n");
    printf("\n\033[1;35m> 4) stampa_mappa()\n");
    printf("\n\033[1;39m> 5) chiudi_mappa()\n");
    printf("\n\n\033[92mScelta:\033[0m ");
    scanf("%d", &menù);
    while (getchar() != '\n');
  switch (menù) {
    case 1:
     genera_mappa();
     break;
    case 2:
     inserisci_zona();
     break;
    case 3:
     cancella_zona();
     break;
    case 4:
     stampa_mappa();
     break;
    case 5:
     chiudi_mappa();
     break;
    default:
    system("clear");
     printf("\n\033[31mATTENZIONE!!! SCELTA SBAGLIATA INSERISCI UN NUMERO DA 1 A 5.\n");
    }
  } while(menù != 5);
  system("clear");
  return ;
}


// funzione per visualizzare i nomi delle zone
static const char* StringZone(enum Tipo_zona zona) {
  switch (zona) {
    case corridoio:
    return "corridoio";
    case scala:
    return "scala";
    case sala_banchetto:
    return "sala_banchetto";
    case magazzino:
    return "magazzino";
    case giardino:
    return "giardino";
    case posto_guardia:
    return "posto_guardia";
    case prigione:
    return "prigione";
    case cucina:
    return "cucina";
    case armeria:
    return "armeria";
    case tempio:
    return "tempio";
    default:
    return "sconosciuto";
  }
}


// funzione che converte il valore dell'enum in una stringa leggibile
static const char* StringTesoro(enum Tipo_tesoro tesoro) {
switch (tesoro) {
  case nessun_tesoro:
    return "nessun_tesoro";
  case veleno:
    return "veleno";
  case guarigione:
    return "guarigione";
  case doppia_guarigione:
    return "doppia_guarigione";
  default:
  return "tesoro sconosciuto";
 }
}




// funzione per visualizzare i nomi delle porte
static const char* StringPorta(enum Tipo_porta porta) {
switch (porta) {
  case nessuna_porta:
    return "nessuna_porta";
  case porta_normale:
    return "porta_normale";
  case porta_da_scassinare:
    return "porta_da_scassinare";
  default:
   return "niente";
 }
}



// funzione per visualizzare i nomi delle classe
static const char* classeToString(enum classe_giocatore classe) {
switch (classe) {
  case barbaro:
  return "barbaro";
  case nano:
  return "nano";
  case elfo:
  return "elfo";
  case mago:
  return "mago";
  default:
  return "classe sconosciuto";
 }
}







void genera_mappa(){
  srand(time(NULL));
for(int i = 0; i < 15; i++) {
    struct Zona_segrete* pNew = (struct Zona_segrete*)malloc(sizeof(struct Zona_segrete));
if(pNew == NULL) {
    printf("errore nell'allocazione in memoria.\n");
    return;
  }
//assegno i valori casuali ai campi della zona
snprintf(pNew -> nome_z, sizeof(pNew -> nome_z), "Zona%d", i + 1);
pNew -> zona = rand() % 10;
//uso un numero casuale da 0 a 9 per le zone
pNew -> tesoro = rand() % 4;
//uso un numero casuale da 0 a 3 per i tesori
pNew -> porta = rand() % 3;
//uso un numero casuale da 0 a 2 per le porte

//collega la zona nella lista
pNew -> zona_precedente = pLast;
pNew -> zona_successiva = NULL;

if(pNew == pFirst) {
pNew -> zona_precedente = NULL;
 }

if (pLast != NULL) { // se la lista non è vuota
  pLast -> zona_successiva = pNew; //inserisco la nuova zona alla fine della lista
} else {
  pFirst = pNew;
}
pLast = pNew; //aggiorna pLast;
 }
count_zone += 15; // numero di zone presente nella mappa più le 15 zone generate in questa funzione
system("clear");
printf("\n\t\t\tFATTO... PREMI 4 PER VEDERLE\n");
}





void inserisci_zona(char nome[], int posizione) {
system("clear");
struct Zona_segrete* pNew= (struct Zona_segrete*)malloc(sizeof(struct Zona_segrete));
printf("in che posizione vuoi inserire la nuova zona ?\n\n");
printf("\033[92mScelta:\033[0m ");
scanf("%d", &posizione);
  while (getchar() != '\n');

//assegno i valori casuali ai campi della zona
strncpy(pNew -> nome_z, nome, sizeof(pNew -> nome_z));
pNew -> zona = rand() % 10;
//uso un numero casuale da 0 a 9 per le zone
pNew -> tesoro = rand() % 4;
//uso un numero casuale da 0 a 3 per i tesori
pNew -> porta = rand() % 3;
//uso un numero casuale da 0 a 2 per le porte

if (posizione > count_zone ) {
  printf("\033[1;31mLista con %d zone, impossibile inserire in posizione %d\n", count_zone, posizione);
  return;
} else
if (posizione <= 1) {
  //inserisco in testa
  pNew -> zona_precedente = NULL;
  pNew -> zona_successiva = pFirst;

  if(pFirst != NULL){
    pFirst -> zona_precedente = pNew;
  }
  pFirst = pNew;
if(pLast == NULL) {
  // se la lista è vuota, aggiono anche pLast
  pLast = pNew;
}
} else {
  struct Zona_segrete* pScan = pFirst;
  for(int i = 0; i < posizione -1 && pScan != NULL; i++) {
    pScan = pScan -> zona_successiva;
    }
//inserisco in posizione i
pNew -> zona_precedente = pScan;
pNew -> zona_successiva = pScan -> zona_successiva;
if(pScan -> zona_successiva != NULL){
  pScan -> zona_successiva-> zona_precedente = pNew;
}
  pScan = pScan -> zona_successiva= pNew;
  }
  count_zone++; // incrementa ogni volta che la funzione "inserisci_zona()" viene chiamata, cosi so esattamente quante zone ho in memoria
  printf("\t\t\tZONA INSERITA CON SUCCESO... PREMI 4 PER VEDERLA\n");
}



void cancella_zona(int posizione) {
system("clear");
struct Zona_segrete* temp = pFirst;
if (pFirst == NULL){
   printf("lista vuota\n");
}else {
  printf("in che posizione vuoi cancellare una zona ?\n\n");
printf("\n\t\t\t\t\t\tSAPENDO CHE NON SI PUÒ INIZIARE IL GIOCO CON MENO DI 15 ZONE... \n");
printf("considerando che la zona 1 sta in posizione 0 e l'ultima zona della lista in posizione %d\n\n", (count_zone-1));
  printf("scegli tra 0 e %d\n\n", (count_zone-1));
printf("\033[92mScelta:\033[0m ");
scanf("%d", &posizione);
while (getchar() != '\n');

if (posizione > count_zone) {
  printf("\033[1;31mLista con %d zone, impossibile cancellare in posizione %d\n", count_zone-1, posizione);
    return;
}

for (int i = 0; i < posizione && temp != NULL; i++) {
  temp = temp -> zona_successiva;
}
if (temp == NULL) {
  printf("\033[1;31mposizione non valida.\n");
    printf("\033[1;37m");
  return;
}
if (temp -> zona_precedente != NULL) {
  temp -> zona_precedente -> zona_successiva = temp -> zona_successiva;
} else {
  //se la zona da cancellare è in testa
  pFirst = temp -> zona_successiva;
}
if (temp -> zona_successiva != NULL) {
  temp -> zona_successiva -> zona_precedente = temp -> zona_precedente;
}else {
  //se la zona da cancellare è in fondo
  pLast = temp -> zona_precedente;
}
free(temp);
}
  count_zone--;
  printf("\t\t\tZONA CANCALLATA CON SUCCESO... PREMI 4 PER VEDERE QUELLI CHE SONO RIMASTI\n");
}



 void chiudi_mappa(){
  if (impostato == 0) {//mostra che la mappa è stata creata
      impostato = 1;
      return;
  } else {
      printf("la mappa è stata creata in precedenza.\n");
      return;
  }
}



void stampa_mappa(){
system("clear");
struct Zona_segrete* temp= pFirst;
int i = 1;
do {
  printf("zona %d= %s\n", i, StringZone(temp -> zona));
  i++;
  temp = temp -> zona_successiva;
}while(temp != NULL);
return;
}





//funzione per inizializzare le classe
static void inizializza(struct Giocatore *giocatore ,enum classe_giocatore classe) {
  giocatore -> classe = classe;
  switch (classe) {
       case barbaro:
                giocatore -> dadi_attaco= 3;
                giocatore -> dadi_difesa= 2;
                giocatore -> p_vita= 8;
                giocatore -> potere_speciale= 0;
                giocatore -> mente = numero_casuale(1,2);
            break;
      case nano:
                giocatore -> dadi_attaco= 2;
                giocatore -> dadi_difesa= 2;
                giocatore -> p_vita= 7;
                giocatore-> potere_speciale= 1;
                giocatore -> mente = numero_casuale(2,3);
                break;
       case elfo:
                giocatore -> dadi_attaco= 2;
                giocatore -> dadi_difesa= 2;
                giocatore -> p_vita= 6;
                giocatore -> potere_speciale= 2;
                giocatore -> mente = numero_casuale(3,4);
                break;
      case mago:
                giocatore -> dadi_attaco= 1;
                giocatore -> dadi_difesa= 2;
                giocatore -> p_vita= 4;
                giocatore -> potere_speciale= 3;
                giocatore -> mente = numero_casuale(4,5);
                break;
         default:
        printf("classe sconosciuta\n");
                break;
  }
}






void imposta_gioco(struct Giocatore* giocatore){
  time_t t;
  srand((unsigned)time(&t));
  int control;
if (impostato== 1) {
    printf("\nIL GIOCO È GIÀ STATO IMPOSTATO IN PRECEDENZA, SEI SICURO(A) DI VOLER REIMPOSTARLO ?\n");
    printf("\n PREMI (1) PER *SI E (2) PER *NO\n");
    scanf("%d", &control);
    while (getchar() != '\n');
    if(control == 1){
      impostato = 0;
      riavvia_gioco(giocatore, num_giocatori);
    } else if(control == 2) {
      return;}
}
    printf("\n\n\033[1;37mQUANTI GIOCATORI CI SONO(DA 1 A 4)?");
    printf("\033[1;32m\n\n\t\tRISPOSTA: ");
    printf("\033[1;37m");
    scanf("%d", &num_giocatori);
    while (getchar() != '\n');
if (num_giocatori < 1 || num_giocatori > 4) {
  system("clear");
      printf("\n\033[1;31m\t\t\t\t\tNUMERO INSERITO NON VALIDO!!!!!!.\n");
      return imposta_gioco(giocatore);
}
//inizializzazione dei giocatori
for (int i= 0; i < num_giocatori; i++) {
   giocatori[i] = (struct Giocatore*)malloc(sizeof(struct Giocatore));
if (giocatori[i] == NULL) {
   printf("ERRORE!!!\n");
   return; }
   printf("\nINSERISCI IL NOME DEL GIOCATORE %d: ",(i + 1));
   scanf("%s", giocatori[i] -> nome_giocatore);
       while (getchar() != '\n');
int choose;
do {
printf("\n\033[1;37mSCEGLI LA CLASSE PER IL GIOCATORE %d: (0: barbaro, 1: nano, 2: elfo, 3: mago): ", i + 1);
printf("\n\n\033[92mScelta:\033[0m ");
scanf("%d", &choose);
while (getchar() != '\n');

if(choose < 0 || choose > 3) {
  system("clear");
  printf("\n\033[1;31m\t\t\t\t\tNUMERO INSERITO NON VALIDO, SCEGLI TRA 0 E 3!!!!!!.\n");
}
  inizializza(giocatori[i], choose);
} while(choose < 0 || choose > 3);

int risposta;
do {
  printf("\n\033[1;37m %s, HAI LA POSSIBILITÀ DI SACRIFICARE 1 PUNTO MENTE AUMENTANDO DI 1 I PUNTI VITA E VICEVERSA.\n\n", giocatori[i] -> nome_giocatore);
  printf("QUESTA OFFERTA T'INTERESSA?... PREMI (1) PER *SI E (2) PER *NO\n\n");
  printf("\033[92mScelta:\033[0m ");
  scanf("%d", &risposta);
      while (getchar() != '\n');
  system("clear");
if (risposta == 1) {
  int numero;
  do {
  printf("\n\033[1;37mCHE VUOI FARE?\n");
  printf("\nPREMI:\n (1) PER *SACRIFICARE UN PUNTO MENTE\n (2) PER *SACRIFICARE UN PUNTO VITA\n (0) PER *NIENTE. \n");
  printf("\033[92mScelta:\033[0m ");
  scanf("%d", &numero);
      while (getchar() != '\n');
if(numero == 1) {
 giocatori[i] -> mente -= 1;
 giocatori[i] -> p_vita += 1;
        }
else if(numero == 2) {
           giocatori[i] -> p_vita -= 1;
           giocatori[i] -> mente += 1;
        }
else if(numero == 0){
  system("clear");
  printf("\nOK!"); }
  else if (numero < 0 || numero > 2){
  system("clear");
  printf("\n\033[1;31m\t\t\t\t\tERRORE!!! RISPONDI CON UN (1) O (2) O (0).\n");
  }
} while (numero < 0 || numero > 2);
system("clear");
} else if (risposta == 2){
          printf("\nOK!");
        } else if (risposta < 1 || risposta > 2){
          printf("\n\033[1;31m\t\t\t\t\tERRORE!!! RISPONDI CON UN *1 OPPURE CON UN *2.\n");
        }
  } while(risposta < 1 || risposta > 2);
}
  system("clear");
main2();
impostato= 1;
printf("GIOCO IMPOSTATO... !\n");
if(impostato == 1 && riavvia == true) {
  gioca(giocatore);
}
printf("\n");
return;
}











void turno_giocatore() {
  while(termina == 0) {
    if (num_giocatori == 1) {
    turno = 0;
     } else {
    turno = (rand() % (num_giocatori - 1) + 1);
     }
  for(int i = turno; i <= num_giocatori; turno++){
    if (turno == num_giocatori) {
      turno = 0;
    }

  while(giocatori[turno] -> p_vita == 0) {
    //se il giocatore è morto, suo turno viene saltato
    turno++;
    if (turno == num_giocatori) {
      turno = 0;
    }
  }
  preso = false;
    int va_bene = 0;
    //cicla attraverso tutti i giocatori
    while(va_bene == 0) {

            printf("\n\n");
            printf("|=================================|");
            printf("\n\033[37m|TURNO DI %s.\n", giocatori[turno] -> nome_giocatore);
            printf("|=================================|");
            printf("\n\n");
            printf("\n\033[95mSCEGLI UN'OPZIONE.\033[ 0m\n\n");
            printf("1: avanza\n\n");
            printf("2: indietreggia\n\n");
            printf("3: stampa_giocatore\n\n");
            printf("4: stampa_zona\n\n");
            printf("5: apri_porta\n\n");
            printf("6: prendi_tesoro\n\n");
            printf("7: scappa\n\n");
            printf("8: combatti\n\n");
            printf("9: gioca_potere_speciale\n\n");
            printf("10: passa\n\n");
            printf("11: count_tipo\n");
            printf("\033[92mScelta:\033[0m ");
          scanf("%d", &va_bene);
          while (getchar() != '\n');
          stdin = freopen (NULL, "r", stdin);
          //esegue la funzione scelta dal giocatore
          switch (va_bene) {
            case 1:
            if (avanzato == 0) {
              avanzato = 1;
              avanza(giocatori[turno]);
              va_bene = 0;
            } else {
                passa(giocatori[turno]);
               }
              break;
            case 2:
              indietreggia(giocatori[turno]);
              va_bene = 0;
              break;
            case 3:
              stampa_giocatore(giocatori[turno]);
              va_bene = 0;
              break;
            case 4:
              stampa_zona(giocatori[turno]);
              va_bene = 0;
              break;
            case 5:
              apri_porta(giocatori[turno]);
              va_bene = 0;
              break;
            case 6:
              prendi_tesoro(giocatori[turno]);
              va_bene = 0;
              break;
            case 7:
              scappa(giocatori[turno]);
              va_bene = 0;
              break;
            case 8:
              combatti(giocatori[turno]);
              va_bene = 0;
              break;
            case 9:
              gioca_potere_speciale(giocatori[turno]);
              va_bene = 0;
              break;
            case 10:
            passa(giocatori[turno]);
            break;
           case 11:
           count_tipo();
           break;
           default:
              system("clear");
              printf("\n\n\033[1;31m\t\t\t\t\tSCELTA SBAGLIATA INSERISCI UN NUMERO TRA 1 E 10\n\n");
              printf("\033[1;37m");
               va_bene = 0;
              break;
           }
        }
      }
    if (giocatori[turno] -> posizione == pLast) {
      hai_vinto();
      printf("%s CONGRATULATIONS HAI VINTO LA PARTITA\n", giocatori[turno] -> nome_giocatore);
      termina_gioco();
      return;
    }

   }
}














void gioca(struct Giocatore* giocatore) {
  //metto tutti i giocatori nella prima zona
  for(int i = 0; i < num_giocatori; i++) {
    giocatori[i] -> posizione = pFirst;
  }
  gioco = true;
 if (impostato == 0) {
   printf("\n\033[1;31m\t\t\t\t\tATTENZIONE!!! DEVI IMPOSTARE IL GIOCO PRIMA DI GIOCARE\n");
   return imposta_gioco(giocatore);
} else if (count_zone < NUMZONE) {
   printf("\n\033[1;31m\t\t\t\t\tNON puoi iniziare il gioco con meno di 15 zone, inserisci altre zone\n");
   return main2();
} else if (pFirst == NULL || pLast == NULL){
  printf("il gioca non è stato impostato correttamente.\n");
  return;
}
if (impostato == 1){
turno_giocatore();
    //termina = 1;
    termina_gioco();
 }
}



void count_tipo(enum Tipo_zona zona){
  system("clear");
   int count = 0;
   int a = 0;
   int b = 0;
   int c = 0;
   int d = 0;
   int e = 0;
   int f = 0;
   int g = 0;
   int h = 0;
   int i = 0;
  struct Zona_segrete* temp= pFirst;
do {
if (temp -> zona == corridoio) {
  count++;
} else if (temp -> zona == scala){
  a++;
}else if (temp -> zona == sala_banchetto){
  b++;
}else if (temp -> zona == magazzino){
  c++;
}else if (temp -> zona == giardino){
  d++;
}else if (temp -> zona == posto_guardia){
  e++;
}else if (temp -> zona == prigione){
  f++;
}else if (temp -> zona == cucina){
  g++;
}else if (temp -> zona == armeria){
  h++;
}else if (temp -> zona == tempio){
  i++;
}
  temp = temp -> zona_successiva;
}while(temp != NULL);
  printf("ci sono %d corridoio\n", count);
  printf("ci sono %d scala\n", a);
  printf("ci sono %d sala_banchetto\n", b);
  printf("ci sono %d magazzino\n", c);
  printf("ci sono %d giardino\n", d);
  printf("ci sono %d posto_guardia\n", e);
  printf("ci sono %d prigione\n", f);
  printf("ci sono %d cucina\n", g);
  printf("ci sono %d armeria\n", h);
  printf("ci sono %d tempio\n", i);
return;
}








void stampa_giocatore(struct Giocatore* giocatore){
  system("clear");
  printf("\nINFORMAZIONI SUL GIOCATORE CORRENTE: \n\n");
  printf("GIOCATORE: %s\n\n", giocatori[turno] -> nome_giocatore);
  printf("CLASSE: %s\n\n", classeToString(giocatori[turno] -> classe));
  printf("DADI ATTACCO: %hu\n\nPUNTI VITA: %hu\n\n",giocatori[turno] -> dadi_attaco, giocatori[turno] -> p_vita);
  printf("DADI DIFESA: %hu\n\nMENTE: %hu\n\n", giocatori[turno] -> dadi_difesa, giocatori[turno] -> mente);
  printf("POTERE_SPECIALE: %hu\n\n", giocatori[turno] -> potere_speciale);
  if (preso == true) {
    printf("TESORO: %s\n\n", StringTesoro(giocatori[turno] -> posizione -> tesoro));
  } else {
    printf("NON HAI NESSUN TESORO\n\n");
  }
}



void stampa_zona(struct Zona_segrete* segrete) {
system("clear");
  printf("zona attuale: %s\n\n", StringZone(giocatori[turno] -> posizione -> zona));
  printf("tesoro ? %s\n\n", StringTesoro(giocatori[turno] -> posizione -> tesoro));
  printf("porta ? %s\n\n", StringPorta(giocatori[turno] -> posizione -> porta));
  printf("Prossima zona: %s\n\n", StringZone((giocatori[turno] -> posizione -> zona_successiva) -> zona));
  if(giocatori[turno] -> posizione -> zona_precedente == NULL) {
    printf("sei nella prima zona della mappa\n\n");
  } else {
  printf("Zona precedente: %s\n\n", StringZone((giocatori[turno] -> posizione -> zona_precedente) -> zona));
}}




int lancioDado() {
  return rand() % 6;  //assume un dado a sei facce
}


enum RisultatoDado risultatoAttacoDifesa() {
  int result = lancioDado();
if (result <= 2) {
  return teschio;
} else if (result > 2 && result <= 4) {
  return scudo_bianco;
}else {
  return scudo_nero;
 }
}




void apri_porta(struct AbitanteSegrete* abitante){
system("clear");
if (giocatori[turno] -> posizione -> porta == nessuna_porta) {
  printf("non c'è nessuna porta qui\n");
  return;
} else if (giocatori[turno] -> posizione -> porta == porta_normale) {
  printf("la porta è aperta\n\n");
  return;
} else if (giocatori[turno] -> posizione -> porta == porta_da_scassinare) {
  printf("%s prova ad aprire la porta.\n\n", giocatori[turno] -> nome_giocatore);
  int dado = lancioDado();
printf("Risultato del dado per scassinare la porta: %d\n", dado);
if (dado <= giocatori[turno] -> mente) {
  printf("\nla porta è stata scassinata! Puoi avanzare nella zona successiva.\n");
  giocatori[turno] -> posizione -> porta = 1;
  return;
}else {
  int probabilita = rand() % 100;
  if (probabilita <= 10) {
    printf("\nhai fallito la scassina e devi ricominciare dalla prima stanza delle segrete.\n");
 giocatori[turno] -> posizione = pFirst;
}else if(probabilita > 10 && probabilita < 40){
printf("\nhai fallito la scassina... è apparso un abittante delle segrete!\n");
appaia_abitante(abitante);
} else {
    printf("\nhai fallito la scassina e perdi un punto vita.\n");
giocatori[turno] -> p_vita--;
}}
}
return;
}




 void caratteristiche_Abitanti(struct AbitanteSegrete* abitante) {
   // Funzione per generare un abitante colle sue caratteristiche
  abitante -> p_vita = numero_casuale(1, (num_giocatori + 8));
  abitante -> dadi_attaco = numero_casuale(1, ((num_giocatori*2) + 3));
  abitante -> dadi_difesa = numero_casuale(1, (num_giocatori + 4));
snprintf(abitante -> name, sizeof(abitante -> name), "abitante%d", rand() % 1000);
printf("\nnome: %s\n", abitante -> name);
printf("\np_vita: %d\n", abitante -> p_vita);
printf("\ndadi_attaco: %d\n", abitante -> dadi_attaco);
printf("\ndadi_difesa: %d\n\n", abitante -> dadi_difesa);
return;
}




void combatti(struct Giocatore* giocatore, struct AbitanteSegrete* abitante) {
  time_t t;
  srand((unsigned)time(&t));
  system("clear");
int dado_giocatore = 0;
int dado_abitante = 0;
  caratteristiche_Abitanti(abitante);

printf("%s inizia il combattimento con %s.\n\n", giocatori[turno] -> nome_giocatore, abitante -> name);
printf("%s lancia %d e %s lancia %d per determinare chi inizia.\n\n", giocatori[turno] -> nome_giocatore, dado_giocatore, abitante -> name, dado_abitante);

while (abitante -> p_vita > 0 && giocatore -> p_vita > 0) {
  dado_giocatore = lancioDado();
  dado_abitante = lancioDado();
  int attacco_riuscito = 0;
  int parati = 0;

  enum RisultatoDado risultato = risultatoAttacoDifesa();
  if (dado_giocatore >= dado_abitante) {
   printf("\n%s inizia il combattimento.\n\n", giocatore -> nome_giocatore);

for (int i = 0; i < giocatore -> dadi_attaco; i++) { //lancio dei dadi di attacco per giocatore
if(risultato == teschio) {
  attacco_riuscito++;
}
  }

for (int i = 0; i < abitante -> dadi_difesa; i++) {
  if(risultato == scudo_nero) {
    parati++;
  }
}

if((attacco_riuscito - parati) > 0) {
  if (abitante -> p_vita < (attacco_riuscito - parati)) {
    abitante -> p_vita = 0;
  } else {
  abitante -> p_vita -= attacco_riuscito - parati; }
}

attacco_riuscito = 0;
parati = 0;
for (int i = 0; i < abitante -> dadi_attaco; i++) { //lancio dei dadi di attacco per giocatore
if(risultato == teschio) {
  attacco_riuscito++;
}
  }

  for (int i = 0; i < giocatore -> dadi_difesa; i++) {
    if(risultato == scudo_bianco) {
      parati++;
    }
  }

  if((attacco_riuscito - parati) > 0) {
    if (giocatore -> p_vita < (attacco_riuscito - parati)) {
      giocatore -> p_vita = 0;
    } else {
    giocatore -> p_vita -= attacco_riuscito - parati; }
  }

} else {

  attacco_riuscito = 0;
  parati = 0;
  for (int i = 0; i < abitante -> dadi_attaco; i++) { //lancio dei dadi di attacco per giocatore
  if(risultato == teschio) {
    attacco_riuscito++;
  }
    }

    for (int i = 0; i < giocatore -> dadi_difesa; i++) {
      if(risultato == scudo_bianco) {
        parati++;
      }
    }

    if((attacco_riuscito - parati) > 0) {
      if (giocatore -> p_vita < (attacco_riuscito - parati)) {
        giocatore -> p_vita = 0;
      } else {
      giocatore -> p_vita -= attacco_riuscito - parati; }
    }

    int parati = 0;
    int attacco_riuscito = 0;

  for (int i = 0; i < giocatore -> dadi_attaco; i++) { //lancio dei dadi di attacco per giocatore
  if(risultato == teschio) {
    attacco_riuscito++;
  }
    }

  for (int i = 0; i < abitante -> dadi_difesa; i++) {
    if(risultato == scudo_nero) {
      parati++;
    }
  }

  if((attacco_riuscito - parati) > 0) {
    if (abitante -> p_vita < (attacco_riuscito - parati)) {
      abitante -> p_vita = 0;
    } else {
    abitante -> p_vita -= attacco_riuscito - parati;
  } }
}
}

//rimuove la vittima dal gioco
if (giocatori[turno] -> p_vita <= 0) {
 if (num_giocatori == 1 ) {
    game_over();
    printf("\n%s È STATO SCONFITTO E VIENE RIMOSSO DAL GIOCO.\n", giocatori[turno]-> nome_giocatore);
    printf("\033[95m\n\n\t\t\t\t\t\t%s ERI L'ULTIMO GIOCATORE RIMASTO\n\n", giocatori[turno] -> nome_giocatore);
    printf("\033[1;37m");
    termina_gioco();
    return;
  } else {
    sei_morto();
    printf("\n%s È STATO SCONFITTO E VIENE RIMOSSO DAL GIOCO.\n", giocatori[turno]-> nome_giocatore);
    printf("\033[95m\n\n\t\t\t\t\t\t%s RIMANERAI PER SEMPRE NEI NOSTRI CUORI\n", giocatori[turno] -> nome_giocatore);
    printf("\033[1;37m");
 rimuoviGiocatore(num_giocatori);
 return turno_giocatore();
}
}else {
  printf("\033[1;32m%s SEMPRE VIVO\n", giocatori[turno] -> nome_giocatore);
}
if (abitante -> p_vita <= 0){
  printf("\033[1;31m\n%s è stato sconfitto e viene rimosso dal gioco.\n", abitante -> name);
  printf("\033[1;37m");
  return turno_giocatore();
}
 system("clear");
 return;
}






void avanza(struct Giocatore* temp) {
  time_t t;
  srand((unsigned)time(&t));
  system("clear");
if(giocatori[turno] -> posizione -> porta == 2) {
  printf("la porta è chiusa devi scassinarla\n");
  avanzato = 0;
  return;
} else {
    giocatori[turno] -> posizione = giocatori[turno] -> posizione -> zona_successiva;
    if (giocatori[turno] -> posizione -> zona_successiva == pLast) {
      hai_vinto();
    printf("CONGRATULATIONS %s HAI VINTO LA PARTITA\n", giocatori[turno] -> nome_giocatore);
    termina = 1;
    termina_gioco();
  } else {
    printf("\n%s, sei entrato in %s.\n\n", giocatori[turno] -> nome_giocatore, StringZone((giocatori[turno] -> posizione) -> zona));
struct AbitanteSegrete* abitante;
int P_Abitante = rand() % 3;
if (P_Abitante == 0 || giocatori[turno]-> posizione == pLast) {
appaia_abitante(&abitante);
} else {
printf("\nNESSUN ABITANTE IN VISTO\n");
return;
}}
}
system("clear");
return;
}



void gioca_potere_speciale(struct Giocatore* giocatore) {
  time_t t;
  srand((unsigned)time(&t));
  system("clear");
  if (abitante_apparso == false) {
    printf("\033[1;31m\nNON PUOI USARE IL POTERE SPECIALE, PERCHE NON C'È NESSUN ABITANTE IN QUESTA STANZA\n");
    printf("\033[1;37m\n");
  } else {
   if (giocatori[turno] -> potere_speciale > 0) {
      printf("\033[1;35m\n\t\t\tuhff... SALVO!!!\n");
      printf("\033[1;37m");
//Simulazione dell'uccisione immediata dell'abitante
      printf("\nL'abitante è stato ucciso\n");
   giocatori[turno] -> potere_speciale--; //Decremento il numero di potere speciale

} else {
      printf("\033[1;35m\nNON PUOI USARE UN OGGETTO CHE NON HAI!!\n");
      printf("\033[1;37m");
      appaia_abitante(abitante);
 } }
 return turno_giocatore();
}



void abitante_attack(struct Giocatore* giocatore,struct AbitanteSegrete* abitante) {
  system("clear");
while (abitante -> p_vita > 0 && giocatore -> p_vita > 0) {
    enum RisultatoDado risultato = risultatoAttacoDifesa();
int attacco_riuscito, parati;
    attacco_riuscito = 0;
    parati = 0;
    for (int i = 0; i < abitante -> dadi_attaco; i++) { //lancio dei dadi di attacco per giocatore
    if(risultato == teschio) {
      attacco_riuscito++;
    }
      }
      for (int i = 0; i < giocatore -> dadi_difesa; i++) {
        if(risultato == scudo_bianco) {
          parati++;
        }
      }
      if((attacco_riuscito - parati) > 0) {
        if (giocatore -> p_vita < (attacco_riuscito - parati)) {
          giocatore -> p_vita = 0;
        } else {
        giocatore -> p_vita -= attacco_riuscito - parati; }
      }
       parati = 0;
       attacco_riuscito = 0;

    for (int i = 0; i < giocatore -> dadi_attaco; i++) { //lancio dei dadi di attacco per giocatore
    if(risultato == teschio) {
      attacco_riuscito++;
    }
      }
    for (int i = 0; i < abitante -> dadi_difesa; i++) {
      if(risultato == scudo_nero) {
        parati++;
      }
    }

    if((attacco_riuscito - parati) > 0) {
      if (abitante -> p_vita < (attacco_riuscito - parati)) {
        abitante -> p_vita = 0;
      } else {
      abitante -> p_vita -= attacco_riuscito - parati;
    } }
  }

  //rimuove la vittima dal gioco
if (giocatore -> p_vita <= 0) {
    if (num_giocatori == 1) {
      game_over();
      printf("\n%s È STATO SCONFITTO E VIENE RIMOSSO DAL GIOCO.\n", giocatori[turno]-> nome_giocatore);
      printf("\033[95m\n\n\t\t\t\t\t\t%s ERI L'ULTIMO GIOCATORE RIMASTO\n\n", giocatori[turno] -> nome_giocatore);
      printf("\033[1;37m");
      termina_gioco();
    } else {
      sei_morto();
      printf("\n%s è stato sconfitto e viene rimosso dal gioco.\n", giocatori[turno]-> nome_giocatore);
      printf("\033[95m\n\n\t\t\t\t\t\t%s RIMANERAI PER SEMPRE NEI NOSTRI CUORI\n", giocatori[turno] -> nome_giocatore);
      printf("\033[1;37m");
   rimuoviGiocatore(num_giocatori); }
  }else {
    printf("\033[1;32m%s SEMPRE VIVO\n", giocatori[turno] -> nome_giocatore);
  }
  if (abitante -> p_vita <= 0){
   printf("\033[1;31m\n%s è stato sconfitto e viene rimosso dal gioco.\n", abitante -> name);
   printf("\033[1;37m");
   }
   return turno_giocatore();
//  scappato = 1;
}







void scappa(struct Giocatore* giocatore, struct AbitanteSegrete* abitante){
  system("clear");
  if (scappato == 0) {
    printf("\033[1;31m\t\t\t\nPERCHÉ VUOI SCAPPARE, NON C'È NESSUN ABITANTE IN QUESTA STANZA...\n");
    printf("\033[1;37m\nSEI AL SICURO PER IL MOMENTO, PUOI AVANZARE\n");
    return;
  } else {
 printf(" %s tenta di scappare !!!\n", giocatori[turno] -> nome_giocatore);
int dado = lancioDado();
printf("\nrisultato del dado: %d\n\n", dado);

if (dado <= giocatore -> mente) {
  printf("\nLa fuga ha avuto successo! Il giocatore indietreggia nella zona precedente\n");
indietreggia(giocatore);
}else {
  printf("\nLa fuga non ha avuto successo! Il giocatore subisce un attaco\n");
caratteristiche_Abitanti(abitante);
 giocatore -> dadi_difesa /= 2;
abitante_attack(giocatore,abitante);
  }
 }
 return turno_giocatore();
}



void appaia_abitante(struct AbitanteSegrete* abitante) {
  abitante_apparso = true;
  scappato = 1;
    printf("\n\033[37mc'è un abitante\n\n");
  int premi;
  do {
  printf("\nPOI COMBATTERLO OPPURE GIOCARE UN POTERE SPECIALE PER UCCIDERLO IMMEDIATAMENTE");
  printf("\tO SCAPPARE\n\n");
  printf("PREMI: \n");
  printf("(1) per combattere\n\n");
  printf("(2) per giocare un potere speciale\n\n");
  printf("(3) per scappare\n\n");
  printf("\033[92mScelta:\033[0m ");
  scanf("%d", &premi);
  while (getchar() != '\n');
  if (premi < 1 || premi > 3) {
    system("clear");
    printf("\n\033[1;31m\t\t\t\t\tNUMERO INSERITO NON VALIDO, SCEGLI TRA 1 E 3\n.");
    printf("\n\n\033[1;37m");
  }
}while(premi < 1 || premi > 3);
switch (premi) {
  case 1:
   combatti(giocatori[turno], abitante);
   break;
  case 2:
   gioca_potere_speciale(giocatori[turno]);
   break;
  case 3:
   scappa(giocatori[turno], abitante);
   break;
  default:
  printf("errore\n");
}
return;
   }




void indietreggia(struct Giocatore* giocatore, struct AbitanteSegrete* abitante) {
  system("clear");
  if (scappato == 1) {
    printf("\nLa fuga ha avuto successo! indietreggi nella zona precedente\n");
  }
if (giocatori[turno] -> posizione -> zona_precedente != NULL) {
  giocatori[turno] -> posizione = giocatori[turno] -> posizione -> zona_precedente;
  printf("\n%s sei di nuovo in: %s.\n", giocatori[turno] -> nome_giocatore, StringZone((giocatori[turno] -> posizione) -> zona));
  int P_Abitante = rand() % 3;

  if (scappato == 1) {
    P_Abitante = 1;
  }
   if (P_Abitante == 0) {
  appaia_abitante(abitante);
  } else {
  printf("\nNESSUN ABITANTE IN VISTO\n");
  return;
  }
} else {
  printf("non c'è nessuna zona in precedenza\n");
}
system("clear");
return;
}




void prendi_tesoro() {
  system("clear");
  if(giocatori[turno] -> posizione -> tesoro == nessun_tesoro) {
    printf("non c'è nessun tesoro in quella stanza\n");
  } else if (giocatori[turno] -> posizione -> tesoro == veleno) {
    printf(" hai preso il veleno\n");
    giocatori[turno] -> p_vita -= 2;
  } else if (giocatori[turno] -> posizione -> tesoro == guarigione) {
    printf(" hai preso la guarigione\n");
    giocatori[turno] -> p_vita += 1;
 } else if (giocatori[turno] -> posizione -> tesoro == doppia_guarigione) {
    printf(" hai preso la doppia_guarigione\n");
    giocatori[turno] -> p_vita += 2;
}
  preso = true;
  return;
}


void rimuoviGiocatore(int indice_corrente) {
  for (int i = turno; i < indice_corrente - 1; ++i) {
    giocatori[i] = giocatori[i + 1];  }
  (indice_corrente)--;
  num_giocatori--;
  printf("\nnumero dei giocatori rimasti: %d\n", num_giocatori);
  return;
}




void passa(struct Giocatore* giocatore){
 system("clear");
 if(avanzato == 1) {
 printf("\nNON PUOI AVANZARE DUE VOLTE\n");
 avanzato = 0;
 return;
} else {
printf("\n%s ha deciso di passare il turno \n", giocatori[turno] -> nome_giocatore);
return; }
return;
}

























void sei_morto() {
  system("clear");
printf("\033[1;31m");
printf("\n\n");
printf("\t\t\t\t\t                                                                                                                          \n");
printf("\033[1;31m\t\t\t\t\t    ▄████████    ▄████████  ▄█          ▄▄▄▄███▄▄▄▄    ▄██████▄     ▄████████     ███      ▄██████▄             \n");
printf("\033[1;31m\t\t\t\t\t    ███    ███   ███    ███ ███       ▄██▀▀▀███▀▀▀██▄ ███    ███   ███    ███ ▀█████████▄ ███    ███            \n");
printf("\033[1;31m\t\t\t\t\t    ███    █▀    ███    █▀  ███▌      ███   ███   ███ ███    ███   ███    ███    ▀███▀▀██ ███    ███            \n");
printf("\033[1;31m\t\t\t\t\t    ███         ▄███▄▄▄     ███▌      ███   ███   ███ ███    ███  ▄███▄▄▄▄██▀     ███   ▀ ███    ███            \n");
printf("\033[1;31m\t\t\t\t\t    ▀███████████ ▀▀███▀▀▀   ███▌      ███   ███   ███ ███    ███ ▀▀███▀▀▀▀▀       ███     ███    ███            \n");
printf("\033[1;31m\t\t\t\t\t          ███   ███         ███       ███   ███   ███ ███    ███ ▀███████████     ███     ███    ███            \n");
printf("\033[1;31m\t\t\t\t\t    ▄█    ███   ███         ███       ███   ███   ███ ███    ███   ███    ███     ███     ███    ███            \n");
printf("\033[1;31m\t\t\t\t\t    ▄████████▀    ██████████ █▀        ▀█   ███   █▀   ▀██████▀    ███    ███    ▄████▀    ▀██████▀             \n");
printf("\033[1;31m\t\t\t\t\t                                                                   ███    ███                                   \n");
printf("\t\t\t\t\t                                                                                                                          \n");
printf("\n\n");
printf("\033[1;37m");
return;
}








void hai_vinto() {
system("clear");
printf("\033[1;32m");
printf("\n\n");
printf("\t\t\t\t\t                                                                                                    \n");
printf("\033[1;32m\t\t\t\t\t    ██░ ██  ▄▄▄       ██▓    ██▒   █▓ ██▓ ███▄    █ ▄▄▄█████▓ ▒█████                      \n");
printf("\033[1;32m\t\t\t\t\t    ▓██░ ██▒▒████▄    ▓██▒   ▓██░   █▒▓██▒ ██ ▀█   █ ▓  ██▒ ▓▒▒██▒  ██▒                   \n");
printf("\033[1;32m\t\t\t\t\t    ▒██▀▀██░▒██  ▀█▄  ▒██▒    ▓██  █▒░▒██▒▓██  ▀█ ██▒▒ ▓██░ ▒░▒██░  ██▒                   \n");
printf("\033[1;32m\t\t\t\t\t    ░▓█ ░██ ░██▄▄▄▄██ ░██░     ▒██ █░░░██░▓██▒  ▐▌██▒░ ▓██▓ ░ ▒██   ██░                   \n");
printf("\033[1;32m\t\t\t\t\t    ░▓█▒░██▓ ▓█   ▓██▒░██░      ▒▀█░  ░██░▒██░   ▓██░  ▒██▒ ░ ░ ████▓▒░                   \n");
printf("\033[1;32m\t\t\t\t\t    ▒ ░░▒░▒ ▒▒   ▓▒█░░▓        ░ ▐░  ░▓  ░ ▒░   ▒ ▒   ▒ ░░   ░ ▒░▒░▒░                     \n");
printf("\033[1;32m\t\t\t\t\t    ▒ ░▒░ ░  ▒   ▒▒ ░ ▒ ░      ░ ░░   ▒ ░░ ░░   ░ ▒░    ░      ░ ▒ ▒░                     \n");
printf("\033[1;32m\t\t\t\t\t    ░  ░░ ░  ░   ▒    ▒ ░        ░░   ▒ ░   ░   ░ ░   ░      ░ ░ ░ ▒                      \n");
printf("\033[1;32m\t\t\t\t\t    ░  ░  ░      ░  ░ ░           ░   ░           ░              ░ ░                      \n");
printf("\033[1;32m\t\t\t\t\t                                 ░                                                        \n");
printf("\t\t\t\t\t                                                                                                    \n");
printf("\n\n");
printf("\033[1;37m");
return;
}













void game_over() {
system("clear");
printf("\033[1;31m");
printf("\n\n");
printf("\t\t\t\t\t                                                                                                                                                                 \n");
printf("\033[1;31m\t\t\t\t\t░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓██████████████▓▒░░▒▓████████▓▒░       ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░▒▓███████▓▒░                                  \n");
printf("\033[1;31m\t\t\t\t\t░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░                                \n");
printf("\033[1;31m\t\t\t\t\t░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░                                \n");
printf("\033[1;31m\t\t\t\t\t░▒▓█▓▒▒▓███▓▒░▒▓████████▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓██████▓▒░        ░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒▒▓█▓▒░░▒▓██████▓▒░ ░▒▓███████▓▒░                                 \n");
printf("\033[1;31m\t\t\t\t\t░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▓█▓▒░ ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░                                \n");
printf("\033[1;31m\t\t\t\t\t░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▓█▓▒░ ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░                                \n");
printf("\033[1;31m\t\t\t\t\t░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░       ░▒▓██████▓▒░   ░▒▓██▓▒░  ░▒▓████████▓▒░▒▓█▓▒░░▒▓█▓▒░                                 \n");
printf("\t\t\t\t\t                                                                                                                                                                 \n");
printf("\n\n");
printf("\033[1;37m");
return;
}









void termina_gioco() {
if(gioco == true){
  printf("\nGRAZIE D'AVER GIOCATO... !\n\n");
int risposta;
do {
  printf("NUOVA PARTITA ? PREMI: \n");
  printf("(1) PER SI\n");
  printf("(2) PER NO\n\n");
  printf("\033[92mScelta:\033[0m ");
  scanf("%d", &risposta);
  while (getchar() != '\n');
} while (risposta != 1 && risposta != 2);

if (risposta == 1) {
riavvia_gioco();
} else {
  printf("ARRIVEDERCI !!!!!\n");
  exit(EXIT_SUCCESS);
 }
} else {
  printf("\nGRAZIE DI NON AVER GIOCATO... ARRIVEDERCI !\n\n");
  }
  for (int i = 0; i < num_giocatori; i++){
  free(giocatori[i]);}
 return;
 }


void riavvia_gioco(struct Giocatore* giocatore, int num_giocatori) {
  time_t t;
  srand((unsigned)time(&t));
  system("clear");
  riavvia = true;
// Dealloca la memoria dinamica allocata per i giocatori e le zone
 for( int i = 0; i < num_giocatori; i++) {
   free(giocatori[i]);
 }
struct Zona_segrete* tmp;
while(tmp != NULL) {  // Inizializza il linked list
  tmp = pFirst -> zona_successiva;
  free(pFirst);
  pFirst = tmp;
}
struct Zona_segrete* ptmp;
while(ptmp != NULL) {  // Inizializza il linked list
  ptmp = pLast -> zona_precedente;
  free(pLast);
  pLast = ptmp;
}
pFirst = NULL;
pLast = NULL;
tmp = NULL;
 impostato = 0;
num_giocatori = 0;
avanzato = 0;
termina = 0;
count_zone= 0;
gioco = false;
//chiama la funzione menu gioco per iniziare una nuova partita
return imposta_gioco(giocatore);
}

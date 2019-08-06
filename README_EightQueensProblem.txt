DESCRIZIONE DEL PROGETTO
NOTE:
****Decommentando le righe da 71 a 76 e da 79 a 84 viene stampato l'elenco dei nodi presenti.****
****Parallelamente si possono decommentare le righe da 39 a 47 nel file EightQueensLoop.cpp e commentare quelle da 48 a 52 per vedere il risultato di una espansione di nodo per volta ********

Il progetto è strutturato in questo modo.

COSTANTI, ENUMERATION CLASSES E TIPI DI DATO: file constants.h
INTERFACCIA GRAFICA E INPUT: classi Display.h e InputManager.h
LOOP: classe EightQueensLoop.h
PATHFINDER: classe PathFinderAStar.h

Le classi EightQueensLoop e InputManager sono dei 'singleton' che implementano rispettivamente il 'game loop' e il 'sampling' dei comandi da tastiera.
La classe Display serve a gestire un buffer di tipo wstring che memorizza il display, ma non usa il design pattern 'singleton'.

- classe Display:
contiene i metodi
- printBuffer per mostrare a video il contenuto del membro di tipo wstring di nome buffer.
- cls per rimuovere dallo schermo il contenuto precedente (clear screen)

- classe InputManager:
questa classe sfrutta i metodi della libreria conio.h per il campionamento dei segnali da tastiera; i metodi definiti in questa classe sono:

- Input : è il metodo che campiona il dato del tasto premuto, e viene chiamato all'interno del metodo Input() del game loop
- ButtonPressed: restituisce il valore della variabile membro di tipo char 'm_ButtonPressed' castata a booleano
- GetButtonPressed: restituisce uno dei possibili valori della enumeration class definita in constant.h 
(gli ultimi due metodi vengono chiamati all'interno del metodo Update del game loop).

- classe EightQueensLoop

Contiene i metodi Start() e Loop(). Il metodo Start inizializza tre oggetti, rispettivamente di tipo "Display", "InputManager"  e "PathFinderAStar". 
Successivamente chiama i metodi per mostrare a schermo la prima schermata a riga 22 e 23 ( myDisplay->cls() e myDisplay->printBuffer(myPathFinderEightQs->PrintDisplay() ).
Infine il metodo Loop().
Il metodo Loop() chiama in un ciclo while infinito i metodi Input(), Update() e Render() definiti nella stessa classe EightQueensLoop.

- metodo Input() della classe EightQueensLoop: campiona il dato in input da tastiera memorizzandolo nel membro della classe InputManager
- metodo Update() della classe EightQueensLoop: legge il tasto premuto usando i due metodi della classe InputManager(); chiama il metodo PathFinderStep() se
 vi sono ancora nodi aperti (metodo GetOpenNodeRecordsLength()
- metodo Render(): aggiorna il display se il booleano 'displayToRefresh' è true.
-------
Il metodo Update() comunica all'oggetto di classe PathFinderAStar attraverso il settaggio del booleano 'solutionViewingStarted' l'inizio di un 'cambio di scena'
che avviene quando finisce l'analisi di tutti gli 'OpenNodeRecords';
---------
Il metodo Update() comunica al metodo Render() che il display deve essere aggiornato, attraverso il booleano 'displayToRefresh'
--------

CLASSI DEL PATHFINDER:

Le classi che costituiscono la logica del programma sono 'PathFinderAStar', 'Node', 'Connection', 'NodeRecord'.

Le classi Node e NodeRecord hanno entrambe due costruttori.

Il costruttore senza argomenti della classe Node viene usato per costruire l'oggetto Node iniziale e viene usato nel corrispondente costruttore senza argomenti della classe NodeRecord,
che costruisce il NodeRecord iniziale.
Il costruttore con argomenti della classe Node costruisce un oggetto Node a partire da un array di 8 oggetti di tipo QueenPosition.
Questo secondo costruttore, effettua il Sorting delle regine nell'array e conta quante regine sono state posizionate (righe da 12 a 20 del file Node.cpp).
Entrambi i costruttori chiamano il metodo GenerateConnections().
-------
La struct QueenPosition è definita nel file constants.h e possiede due costruttori e gli operatori logici == e != opportunamente ridefiniti.
--------

Nel file Node.h si può vedere che i dati fondamentali di un oggetto Node sono: 
- il numero di regine posizionate
- un array delle loro posizioni (di lunghezza fissa) - se qualche regina non è stata posizionata, le sue coordinate (r,c) sono (8,8) - normalmente hanno valori tra 0 e 7
- il vector delle Connections

La classe Node implementa i metodi SortQueensArray() e SwapQueens(), necessari a mantenere ordinato l'array delle regine. Questo viene fatto immediatamente, appena
si crea un nuovo nodo (l'ordinamento serve a confrontare due nodi tra loro).

--- GenerateConnections() ---
I due metodi che seguono vengono usati nel metodo GenerateConnections().
- FillAllowedCellsTable(int*, int, int)
- CountNotAllowedPositsOfTable(int*)
Il metodo FillAllowedCellsTable(int*, int, int) serve a settare a 1 gli elementi di una matrice di interi inizializzata a 0 quando corrispondono a una posizione NON OCCUPABILE.
Il metodo CountNotAllowedPositsOfTable(int*) fa un conteggio delle posizioni NON OCCUPABILI (quelle inizializzate a 1)

Il metodo GenerateConnection() dichiara un array bidimensionale di int e assegna a 1 alle celle non occupabili; in seguito conta tutte le celle non occupabili; poi
crea una copia di questo array e aggiunge una regina ( chiama ancora una volta il metodo FillAllowedCellsTable  a riga 133). Infine conta le posizioni non occupabili.

COSTO DELLA CONNESSIONE: Il costo della singola Connection che viene così creata corrisponde "Numero celle NON occupabili dopo - Numero celle NON occupabili prima"

---- Classe Connection------
Possiede un costruttore 
Possiede i membri: 
- puntatore a oggetto tipo Node  originNode
- QueenPosition nextQueen
- int connectionCost

------------ classe NodeRecord -------------
Questa classe fa da wrapper della classe Node e ha i seguenti membri:
- Node* node
- int costSoFar
- int estimatedTotalCost

Come già detto, i costruttori sono due: quello senza argomenti viene usato per il NodeRecord iniziale e chiama al suo interno il costruttore senza argomenti della classe Node().

Sono presenti il metodo GenerateNodeRecords() e un membro di tipo vector<NodeRecord*>*.
Questi servono a generare e immagazzinare i nuovi oggetti NodeRecord.
Il valore che assume costSoFar è semplicemente il numero delle posizioni NON OCCUPABILI. All'interno del metodo GenerateNodeRecords() viene ottenuto sommando il valore costSoFar del
nodo attuale e il valore connectionCost.
A differenza del metodo GenerateConnections(), questo metodo non viene chiamato nei costruttori di nuovi oggetti di classe NodeRecord.

--------------classe PathFinderAstar ----------------
PREMESSE:
- il costo fino all'arrivo dato dall'euristica è per ogni nodo il numero delle regine ancora non posizionate: non sono riuscito a trovare altri valori numerici migliori e
ho pensato che fosse una stima per difetto del costo complessivo delle mosse successive
- il costo della connessione è dato dal numero di posizioni non più occupabili in seguito al posizionamento della n-esima regina nella posizione scelta
- il 'costo fino all'ultimo posizionamento' è il numero di posizioni non occupabili su tutta la scacchiera

- l'algoritmo è stato ideato per espandere tutti i nodi prodotti dal posizionamento della regina successiva in tutte le posizioni occupabili sull'intera scacchiera
(mi sono reso conto di stare sbagliando perchè l'algoritmo non arrivava alla fine e ho semplificato assumendo che ogni regina debba necessariamente avere un indice di colonna e di riga diversi da quelli di tutte quelle
posizionate prima, quindi ho preso in considerazione solo le 'posizioni occupabili sulla colonna successiva: fare questa correzione è stato più semplice del previsto: è bastato commentare la riga 124 del file Node.cpp (il metodo GenerateConnections() )

- ho preso spunto dall'algoritmo in pseudo codice alle pagine 223 - 230 del libro Millington - Funge "AI for Games"

- è necessario sottolineare che ogni oggetto Node prodotto ha tutte le regine dell'array già ordinate e inoltre il Node è identico a un altro qualsiasi che ha le regine uguali:
oltre a tutto ciò, anche se si arriva allo stesso Node da percorsi differenti, in questo caso abbiamo la certezza che il costo dei cammini sarà lo stesso, in quanto dipendente solo
dalla posizione delle regine e non dall'ordine in cui sono state posizionate; se le regine non posizionate sono le stesse anche il costo totale stimato è lo stesso;
quindi non serve confrontare il costo stimato se il nodo in questione è stato già espanso o chiuso.

Questa classe gestisce due oggetti vector di puntatori a NodeRecord (openNodeRecords e closedNodeRecords) e implementa il metodo PathFinderStep() che espande uno dei nodi presenti nel vector openNodeRecords.

------metodo PathFinderStep() ----------
Questa classe chiama il metodo SelectNRWithLowestEstimatedCost() che non fa altro che scegliere un Open Node Record dal vector e restituire il suo puntatore; l'indice del Node Record
scelto viene assegnato all'interno currentNRindex (passato per reference). Viene aggiornato il membro wstring 'nOfQueensCurrentNode'.

--- una sola struttura if - else ---
-if
Molto semplicemente, se il NodeRecord ha un numero di regine pari a 8, ho trovato una soluzione e la copio (de-referenziando il puntatore a oggetto Node) nel vector 'solutions'; faccio
poi tutta una serie di operazioni (inserisco il NodeRecord in 'closedNodeRecords' e lo rimuovo da  'openNodeRecords'). In questo caso non serve fare altro, e la soluzione è già trovata e conservata.
-else
Altrimenti, se il numero di regine è inferiore, posso chiamare GenerateNodeRecords() e iterare sul vector 'childNodeRecords'. Per ciascuno dei due vector, controllo se il Node è già contenuto in essi.
(uso il metodo NRListContainsNode() - il vector è chiamato impropriamente 'list'); se trovo che il Node è già presente, do il comando 'continue'; se il Node non è presente, inserisco
il NodeRecord corrispondente in 'openNodeRecords'.

Dopo aver iterato su tutti i childNodeRecords, rimuovo il NodeRecord dagli open e lo inseriscon nei closed (all'interno del ciclo else - queste istruzioni sono state portate fuori da if e da else, essendo uguali).

------- metodo PrintDisplay()----------

Il metodo PrintDisplay() è quello che 'interagisce' con i valori letti da tastiera grazie all'InputManager.
Durante l'espansione del grafo stampa il numero di 'open Node Records' e quello di 'closed Node Records' (la size() dei due vector.
****Decommentando le righe da 71 a 76 e da 79 a 84 viene stampato l'elenco dei nodi presenti.****
****Parallelamente si possono decommentare le righe da 39 a 47 nel file EightQueensLoop.cpp e commentare quelle da 48 a 52  per vedere il risultato di una espansione di nodo per volta ********
Nel seguito, quando viene svuotato il vector degli open Node Records, viene stampato un messaggio che richiede la pressione di un tasto per visualizzare le soluzioni.
A riga 56 del file EightQueensLoop si assegna true al booleano solutionViewingStarted, quindi parte la visualizzazione delle soluzioni.
Con le 4 frecce si possono scorrere le soluzioni ( il metodo ShiftSolutionIndex(char) ).

Vengono espansi in tutto 2057 - 92 = 1965 nodi e trovate 92 soluzioni (come era da aspettarsi). Tra queste esistono alcune soluzioni identiche a se stesse perchè ruotate di 90 gradi per 3 volte
consecutive e/o riflesse rispetto a un asse o una diagonale.


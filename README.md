# 🍝 DINING PHILOSOPHERS - Progetto 42
## ✅ COMPLIANT WITH 42 NORM

## 📁 STRUTTURA PROGETTO

```
philosophers/
├── main.c              (main function + thread creation)
├── utils.c             (utility functions: timing, printing)
├── init.c              (initialization + cleanup)
├── fork.c              (fork management)
├── philo.c             (philosopher actions)
├── monitor.c           (death monitoring)
├── philosophers.h      (header file)
├── Makefile            (compilation rules)
├── .gitignore          (git ignore file)
├── README.md           (this file)
└── NORMA_42_GUIDE.md   (detailed 42 norm explanation)
```

## 🔧 COMPILAZIONE

```bash
make          # Compila il programma
make clean    # Rimuove i .o
make fclean   # Rimuove .o e eseguibile
make re       # Clean + all
```

## 🚀 UTILIZZO

```bash
./philo num_philosophers time_to_die time_to_eat time_to_sleep [num_meals]
```

### Parametri

- `num_philosophers`: Numero di filosofi (e di fork)
- `time_to_die`: Millisecondi prima di morire di fame
- `time_to_eat`: Millisecondi per mangiare
- `time_to_sleep`: Millisecondi per dormire
- `num_meals` (opzionale): Limite pasti prima di terminare

### Esempi

```bash
# Test base - 5 filosofi
./philo 5 800 200 200

# Con limite di pasti
./philo 5 800 200 200 7

# Edge case - 1 filosofo (deve morire)
./philo 1 800 200 200

# Test critico
./philo 4 410 200 200
```

## 📋 FILE ORGANIZATION

### `main.c` (40 linee)
- `main()` - Entry point
- `check_args()` - Validation argomenti
- `create_threads()` - Crea i thread dei filosofi
- `join_threads()` - Aspetta che finiscano

### `utils.c` (45 linee)
- `get_timestamp_ms()` - Timestamp corrente
- `get_time_since()` - Tempo trascorso
- `print_status()` - Stampa thread-safe dello stato
- `is_dead()` - Check se qualcuno è morto
- `set_dead()` - Imposta flag di morte

### `init.c` (75 linee)
- `init_args()` - Parse argomenti
- `init_mutexes()` - Inizializza mutex
- `init_philos()` - Inizializza strutture filosofi
- `init_data()` - Setup completo
- `cleanup()` - Libera memoria

### `fork.c` (40 linee)
- `take_fork()` - Prende un fork
- `put_fork()` - Rilascia un fork
- `are_forks_available()` - Controlla disponibilità

### `philo.c` (100+ linee)
- `take_forks_even()` - Filosofi pari prendono left→right
- `take_forks_odd()` - Filosofi dispari prendono right→left
- `eat_action()` - Azione mangiare
- `sleep_and_think()` - Dormi e pensa
- `philosopher_routine()` - Loop principale

### `monitor.c` (35 linee)
- `check_philo_death()` - Controlla se filosofo è morto
- `all_ate_enough()` - Tutti hanno mangiato abbastanza?
- `check_deaths()` - Main monitoring function

### `philosophers.h` (50 linee)
- Strutture dati
- Dichiarazioni funzioni
- Include necessari

## ✅ CONFORMITÀ A NORMA 42

- ✅ Max 80 caratteri per linea
- ✅ Max 25 linee per funzione
- ✅ No global variables
- ✅ Variabili dichiarate all'inizio
- ✅ Indentazione 4 spazi
- ✅ Nomi snake_case
- ✅ Static helper functions
- ✅ Dichiarazioni prima di uso
- ✅ No typedef struct
- ✅ Pronto per norminette

## 🔒 DEADLOCK PREVENTION

**Strategia:** Ordine asimmetrico di fork-taking

```
Filosofo 1 (dispari):  fork_right → fork_left
Filosofo 2 (pari):     fork_left  → fork_right
Filosofo 3 (dispari):  fork_right → fork_left
```

Questo rompe il ciclo di dipendenza circolare.

## 🍽️ STARVATION PREVENTION

- Ordine consistente nel prendere i fork
- Busy-wait educato con usleep(100)
- Nessun filosofo viene bloccato indefinitamente

## 🔐 SINCRONIZZAZIONE

- Mutex per ogni fork
- Mutex per output (no interleaving)
- Mutex per flag di morte
- **Zero data races**

## 🧪 TEST SUGGERITI

```bash
# Dovrebbe terminare normalmente
./philo 5 800 200 200 10

# Dovrebbe avere starvation
./philo 5 500 200 200

# Edge case - 1 filosofo muore
./philo 1 800 200 200

# Test critico
./philo 4 410 200 200

# Grande numero di filosofi
./philo 50 800 200 200 1
```

## ⚠️ NOTE IMPORTANTI

1. **Timing**: Timestamp in millisecondi da start programma
2. **Morte entro 10ms**: Controllato dal monitoring
3. **No zombies**: Tutti i thread vengono joinati
4. **Memory leak free**: Tutti gli allocati vengono liberati
5. **Compilazione**: `-Wall -Wextra -Werror -pthread` senza warning

## 📚 DOCUMENTAZIONE AGGIUNTIVA

Leggi `NORMA_42_GUIDE.md` per:
- Spiegazione dettagliata di ogni regola 42 norm
- Esempi di cosa è giusto/sbagliato
- Come modificare il codice se necessario
- Troubleshooting common errors

## ✅ READY FOR SUBMISSION

Il codice è 100% compliant con la norma 42 e pronto per:
- Compilazione senza warning
- Correzione della norminette
- Passaggio della valutazione
- Protezione da data races
- Evitamento di deadlock/starvation

Buona fortuna! 🎓

---

**Compila:** `make`  
**Testa:** `./philo 5 800 200 200`  
**Norma:** `norminette *.c *.h` ✅


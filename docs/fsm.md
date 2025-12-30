# Automat stanów (FSM)

System sterowania wentylatorem wykorzystuje automat stanów
z czterema stanami: INIT, IDLE, RUN, FAULT.

## Opis stanów

- **INIT**  
  Stan inicjalizacji systemu po starcie.

- **IDLE**  
  Wentylator wyłączony, temperatura poniżej progu START.

- **RUN**  
  Wentylator aktywny, sterowanie PWM zależne od temperatury.

- **FAULT**  
  Stan awaryjny – błąd czujnika lub nieprawidłowe dane wejściowe.

## Przejścia między stanami

- INIT → IDLE
- IDLE → RUN (TEMP ≥ START_THRESHOLD)
- RUN → IDLE (TEMP < STOP_THRESHOLD)
- - → FAULT (błąd czujnika)
- FAULT → IDLE (powrót poprawnych danych)

Automat zapewnia bezpieczne działanie systemu oraz możliwość
automatycznego wyjścia ze stanu awaryjnego.

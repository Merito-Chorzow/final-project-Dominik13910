# Testy funkcjonalne systemu sterowania wentylatorem (ESP32)

## Test 1 – Inicjalizacja systemu

Polecenie: `GET STATUS`  
Oczekiwane: `PWM = 0`, `FAULTS = 0`  
Wynik: PASS

---

## Test 2 – Odczyt z czujnika temperatury

Czynność: Obrót potencjometru  
Oczekiwane: Zmiana wartości `TEMP_RAW`  
Wynik: PASS

---

## Test 3 – Przejście FSM IDLE → RUN

Czynność: `TEMP_RAW > START_THRESHOLD`  
Oczekiwane: `PWM > 0`  
Wynik: PASS

---

## Test 4 – Przejście FSM RUN → IDLE

Czynność: `TEMP_RAW < STOP_THRESHOLD`  
Oczekiwane: `PWM = 0`  
Wynik: PASS

---

## Test 5 – Aktualizacja danych telemetrycznych

Polecenie: `GET STATUS`  
Oczekiwane: Aktualizacja wartości `TEMP_RAW` oraz `PWM`  
Wynik: PASS

---

## Test 6 – Obsługa protokołu UART

Polecenie: `SET START 2500`  
Oczekiwane: Aktualizacja wartości `START_THRESHOLD`  
Wynik: PASS

---

## Test 7 – Stan FAULT (błąd czujnika)

Czynność: Ustawienie potencjometru na minimum (`TEMP_RAW ≈ 0`)  
Polecenie: `GET STATUS`  
Oczekiwane: `PWM = 0`, `FAULTS ≥ 1`  
Wynik: PASS

---

## Test 8 – Wyjście ze stanu FAULT (recovery)

Czynność: Zwiększenie temperatury powyżej `START_THRESHOLD`  
Polecenie: `GET STATUS`  
Oczekiwane: `PWM > 0`, system powraca do normalnej pracy  
Wynik: PASS

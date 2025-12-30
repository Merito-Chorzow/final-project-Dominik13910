# Testy funkcjonalne systemu sterowania wentylatorem (ESP32)

Celem testów jest weryfikacja poprawności działania systemu sterowania wentylatorem
opartego na ESP32, w szczególności:
- logiki automatu stanów (FSM),
- obsługi danych z czujnika temperatury,
- reakcji systemu na błędy czujnika (stan FAULT),
- poprawności komunikacji UART oraz telemetrii.

Testy zostały przeprowadzone jako testy funkcjonalne i integracyjne
z wykorzystaniem interfejsu UART oraz fizycznych elementów wejściowych
(potencjometr symulujący czujnik temperatury).

---

## Test 1 – Inicjalizacja systemu

**Warunki początkowe:**  
System uruchomiony, brak interakcji użytkownika.

**Polecenie:**  
`GET STATUS`

**Oczekiwany rezultat:**  
- `PWM = 0`  
- `FAULTS = 0`  
- system w stanie IDLE

**Wynik:** PASS

---

## Test 2 – Odczyt z czujnika temperatury

**Warunki początkowe:**  
System w stanie IDLE.

**Czynność:**  
Płynny obrót potencjometru symulującego czujnik temperatury.

**Oczekiwany rezultat:**  
- zmiana wartości `TEMP_RAW` widoczna w odpowiedzi `GET STATUS`

**Wynik:** PASS

---

## Test 3 – Przejście FSM z IDLE do RUN

**Warunki początkowe:**  
System w stanie IDLE, `TEMP_RAW < START_THRESHOLD`.

**Czynność:**  
Zwiększenie temperatury powyżej wartości `START_THRESHOLD`.

**Oczekiwany rezultat:**  
- przejście FSM do stanu RUN  
- `PWM > 0` (uruchomienie wentylatora)

**Wynik:** PASS

---

## Test 4 – Przejście FSM z RUN do IDLE

**Warunki początkowe:**  
System w stanie RUN.

**Czynność:**  
Zmniejszenie temperatury poniżej wartości `STOP_THRESHOLD`.

**Oczekiwany rezultat:**  
- przejście FSM do stanu IDLE  
- `PWM = 0` (zatrzymanie wentylatora)

**Wynik:** PASS

---

## Test 5 – Aktualizacja danych telemetrycznych

**Warunki początkowe:**  
System pracujący w dowolnym stanie.

**Polecenie:**  
`GET STATUS`

**Oczekiwany rezultat:**  
- aktualne wartości `TEMP_RAW`  
- aktualna wartość `PWM`  
- spójność danych telemetrycznych z rzeczywistym stanem systemu

**Wynik:** PASS

---

## Test 6 – Obsługa protokołu UART (zmiana konfiguracji)

**Warunki początkowe:**  
System w stanie IDLE.

**Polecenie:**  
`SET START 2500`

**Oczekiwany rezultat:**  
- zmiana wartości `START_THRESHOLD` na 2500  
- potwierdzenie poprawnej obsługi polecenia przez UART

**Wynik:** PASS

---

## Test 7 – Stan FAULT (błąd czujnika)

**Warunki początkowe:**  
System w stanie IDLE lub RUN.

**Czynność:**  
Ustawienie potencjometru na minimum (symulacja błędu czujnika, `TEMP_RAW ≈ 0`).

**Polecenie:**  
`GET STATUS`

**Oczekiwany rezultat:**  
- przejście FSM do stanu FAULT  
- `PWM = 0` (tryb bezpieczny)  
- `FAULTS ≥ 1` (zarejestrowane zdarzenie błędu)

**Wynik:** PASS

---

## Test 8 – Wyjście ze stanu FAULT (recovery)

**Warunki początkowe:**  
System w stanie FAULT.

**Czynność:**  
Zwiększenie temperatury powyżej wartości `START_THRESHOLD`.

**Polecenie:**  
`GET STATUS`

**Oczekiwany rezultat:**  
- wyjście FSM ze stanu FAULT  
- powrót do normalnej pracy systemu  
- `PWM > 0` (jeżeli spełnione są warunki uruchomienia wentylatora)

**Wynik:** PASS

---

## Podsumowanie testów

Wszystkie testy funkcjonalne zakończyły się wynikiem **PASS**.  
System poprawnie realizuje logikę automatu stanów, obsługuje błędy czujnika,
umożliwia rekonfigurację przez UART oraz zapewnia bezpieczne działanie
w przypadku sytuacji awaryjnych.

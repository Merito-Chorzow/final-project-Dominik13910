# Architektura systemu

System został zaprojektowany w sposób modułowy. Każdy komponent
odpowiada za jedno, jasno określone zadanie.

## Główne moduły

- **Sensor**  
  Odpowiada za odczyt surowej wartości temperatury (`TEMP_RAW`).

- **FanController**  
  Implementuje automat stanów (FSM) oraz sterowanie PWM wentylatora.

- **CommandHandler**  
  Obsługuje polecenia przesyłane przez interfejs UART.

- **Telemetry**  
  Przechowuje aktualne dane diagnostyczne i statystyki systemu.

- **Config**  
  Zawiera parametry konfiguracyjne (progi temperatury, zakres PWM).

## Przepływ danych

Sensor → FanController → PWM  
UART → CommandHandler → Config  
FanController → Telemetry → UART

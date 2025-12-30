# System sterowania wentylatorem – ESP32

Projekt przedstawia system sterowania wentylatorem oparty na mikrokontrolerze ESP32.
Sterowanie odbywa się na podstawie odczytu temperatury, z wykorzystaniem
automatu stanów (FSM).

System umożliwia:

- automatyczne sterowanie prędkością wentylatora (PWM),
- obsługę stanów IDLE, RUN oraz FAULT,
- rekonfigurację progów temperatury przez UART,
- diagnostykę i telemetrię pracy systemu.

Projekt został zrealizowany w ramach przedmiotu
**Programowanie niskopoziomowe**.

# Weather station with 2-axis solar tracking system

### Team members

* Šimon Roubal 
* Petr Medek 
* Jakub Socha 
* Ondřej Ryšavý 


Link to this file in your GitHub repository:

[https://github.com/Simon-Roubal/Meteo-station](https://github.com/Simon-Roubal/Meteo-station)

### Table of contents

* [Project objectives](#objectives)
* [Hardware description](#hardware)
* [Libraries description](#libs)
* [Main application](#main)
* [Video](#video)
* [References](#references)

<a name="objectives"></a>

## Project objectives

The goal of the project is to develop a weather station with 2-axis solar panel tracking using various sensors and servos. Project will be based on Arduino uno board with Atmega328p microcontroler and wtritten in C language.

<a name="hardware"></a>

## Hardware description

Základem celého hardwaru je Arduino UNO s osazeným čipem ATMEGA328P. K němu jsou následně připojeny 3 typy sensorů. Čidlo pro měření teploty [TMP36](https://www.analog.com/media/en/technical-documentation/data-sheets/TMP35_36_37.pdf), snímač vlhkosti [HIH5030](https://sensing.honeywell.com/honeywell-sensing-hih5030-5031-series-product-sheet-009050-2-en.pdf) a 4ks [fotorezistorů](https://dratek.cz/arduino/1073-fotorezistor-5mm-gl5539.html). Dále se zde nachází 2 servo motory, které slouží v kombinaci s fotorezistory k natáčení solárního panelu. K zobrazení údajů o venkovní teplotě a vlhkosti je k Arduinu připojen LCD displej LM016L. 

![your figure]()

HIH5030, přes dělič zapojeno aby výstupní napští nebylo větší jako napětí refernční (1.1V)

![HIH5030](images/HIH-5030.png) 
 
Funkce natáčení FV panelu, funguje na principu 4 fotoprvků (v našem případě fotorezistory), které jsou od sebe rozděleny světelnou zábranou. 
Fotorezistory jsou zapojeny do napěťového děliče. 
Výstupní napětí tohoto děliče nám určuje intenzitu osvětlení fotorezistoru. 
Pokud se napětí, s určitou odchylkou, shoduje na všech čtyřech děličích, potom je panel natočen směrem ke slunci.
Podmínka pro prvotní instalaci: Při prvotní instalaci musí uživatel natočit panel směrem ke slunci.

V rámci simulace byli vašak fotoodpory nahrazeny potenciometry.

![solar sensor](images/solar_sensor.png) 

Video with princip of solar sensor: [https://www.youtube.com/watch?v=_6QIutZfsFs](https://www.youtube.com/watch?v=_6QIutZfsFs)


<a name="libs"></a>

## Libraries description

Write your text here.

<a name="main"></a>

## Main application

Write your text here.

<a name="video"></a>

## Video

Write your text here

<a name="references"></a>

## References

1. Write your text here.

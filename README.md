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

The basic of the whole hardware is the Arduino UNO board with an Atmega328p microcontroller. Three types of sensors are connected to this board. Temperature sensor [TMP36](https://www.analog.com/media/en/technical-documentation/data-sheets/TMP35_36_37.pdf), humidity sensor[HIH5030](https://sensing.honeywell.com/honeywell-sensing-hih5030-5031-series-product-sheet-009050-2-en.pdf) and four pieces of [photoresistors](https://dratek.cz/arduino/1073-fotorezistor-5mm-gl5539.html). There are also two servo motors that serve in combination with photoresistors to move a solar panel and follow the sun. For showing information about temperature and humidity is here LCD display [LM016L](https://www.datasheet-pdf.info/entry/LM016L).

![your figure]()

HIH5030 is connected to the board through a voltage divider because of output voltage would not be higher than a reference voltage. (1.1V).

![HIH5030](images/HIH-5030.png) 

The function of moving solar panel works on the principle four photo elements (in our case photoresistors), which are separated with some light barrier. Photoresistors are connected in a voltage divider. The output voltage of this divider says how much light intensity is on photoresistors at the moment. If the voltage on every photoresistor, with some deviation, is the same then is panel turned to the sun.

Condition for the first installation: In the first installation user must turn the panel to the sun.

In the case of simulation, the photoresistors were replaced by potentiometers.

![solar sensor](images/solar_sensor.png) 

Video with principle of solar sensor: [https://www.youtube.com/watch?v=_6QIutZfsFs](https://www.youtube.com/watch?v=_6QIutZfsFs)


<a name="libs"></a>

## Libraries description

Most of the libraries were used for DE2 laboratory lessons:
[https://github.com/tomas-fryza/Digital-electronics-2/tree/master/Labs/library](https://github.com/tomas-fryza/Digital-electronics-2/tree/master/Labs/library)
 - uart
 - twi
 - gpio
 - lcd 
 - timer


Then here is one library made for spinning PWM servo motors. Functions in this library will say to the servo motor to which angle it has to move. It includes 19 functions for angles from -90° to +90°. 

Example of function for +90°:
```c
void servo_move_plus_ninety(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num)
{
	uint16_t x = 1250;
	uint16_t y = 20000-x;
	*reg_name = *reg_name | (1<<pin_num);
	*port_name = *port_name & ~(1<<pin_num);
	*port_name = *port_name |(1<<pin_num);
	_delay_us(x);
	*port_name = *port_name & ~(1<<pin_num);
	_delay_us(y);
}
```

<a name="main"></a>

## Main application

[flow1](flowcharts/flow1.png)
[flow2](flowcharts/flow2.png)

The core of the code:
```c
int main(void)
{
    // Initialize LCD display
    lcd_init(LCD_DISP_ON);

    // Put servos to default position
    default_servo_pos ();

    // Put default strings
    lcd_gotoxy(0, 0);
    lcd_puts("Temp: 00.0 C");
    lcd_gotoxy(0, 1);
    lcd_puts("Hum: 00.0");

    // Set pointer to beginning of CGRAM memory
    lcd_command(1 << LCD_CGRAM);
    for (uint8_t i = 0; i < 56; i++)
    {
        // Store all new chars to memory line by line
        lcd_data(customChar[i]);
    }
    // Set DDRAM address
    lcd_command(1 << LCD_DDRAM);

    // Display custom chars
    lcd_gotoxy(10,0);
    lcd_putc(0);
    lcd_gotoxy(9,1);
    lcd_putc(1);

    // Configure ADC to convert PC0[A0] analog value
    // Set input channel to ADC0
    ADMUX=0xC0;
    // Enable ADC module
    ADCSRA|=(1<<ADEN);
    // Enable conversion complete interrupt
    ADCSRA|=(1<<ADIE);
    // Set clock prescaler to 128
    ADCSRA|=(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);


    // Configure timers and interrupts
    TIM1_overflow_262ms();
    TIM1_overflow_interrupt_enable();

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}
```

<a name="video"></a>

## Video

Write your text here

<a name="references"></a>

## References

1. Write your text here.

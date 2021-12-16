
/* Defines -----------------------------------------------------------*/
#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif

// Pins for solar panel servos
#define SERVO_1_PIN PB4
#define SERVO_2_PIN PB5

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <util/delay.h>		// Delay library
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function
#include "pwm_servo.h"      // Our servo movement library


/* Variables ---------------------------------------------------------*/
// Custom character definition using https://omerk.github.io/lcdchargen/
uint8_t customChar[16] = {
	0b01110, // Degree custom char
	0b01010,
	0b01110,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
    0b00000, // Percentage custom char
	0b11010,
	0b11010,
	0b00100,
	0b00100,
	0b01011,
	0b01011,
	0b00000
};

/* Global variables --------------------------------------------------*/
int8_t servo_1_pos = 0;	 // Position of servo 1
int8_t servo_2_pos = 0;	 // Position of servo 2

/* Function declarations ----------------------------------------------*/
void write_temp (char lcd_string[], float value);	// Displays temperature to LCD correctly
void write_hum (char lcd_string[], float value);	// Displays humidity to LCD correctly
void calculate_movement_servo_1 (uint16_t value_right_bot, uint16_t value_left_bot, uint16_t value_right_top, uint16_t value_left_top);	// Calculates movement of first servo
void calculate_movement_servo_2 (uint16_t value_avg_top, uint16_t value_avg_bot);	// Calculates movement of second servo
void default_servo_pos ();	// Moves servo to default position
void move_to_night_pos ();	// Moves servo to starting position for next day

/* Function definitions ----------------------------------------------*/
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

// Displays temperature to LCD correctly
void write_temp (char lcd_string[], float value) 
{
	// temp greater 60°C
	if (value >= 60)		
	{
		// Write "Over", no need for temperatures grater than 60°C, 
		// current world record for temperature is around 56.7°C
		lcd_gotoxy(5,0);
		lcd_putc(' ');
		lcd_puts("Over");	
	}
	else
	{	
		// temp between 10°C and 60°C
		if (value>=10)		
		{
			lcd_gotoxy(5,0);
			lcd_putc(' ');
			lcd_putc(lcd_string[0]);
			lcd_putc(lcd_string[1]);
			lcd_putc('.');
			lcd_putc(lcd_string[2]);
		}
		else
		{ 
			// temp between 10°C and 1°C
			if (value < 10 && value >= 1)	
			{
				lcd_gotoxy(5,0);
				lcd_putc(' ');
				lcd_putc('0');
				lcd_putc(lcd_string[0]);
				lcd_putc('.');
				lcd_putc(lcd_string[1]);
			}
			else
			{
				// temp between 1°C and 0°C
				if (value < 1 && value >=0)	
				{
					lcd_gotoxy(5,0);
					lcd_putc(' ');
					lcd_putc('0');
					lcd_putc('0');
					lcd_putc('.');
					lcd_putc(lcd_string[0]);
				}
				else
				{
					// temp between 0°C and -1°C
					if (value < 0 && value > -1)
					{
						lcd_gotoxy(5,0);
						lcd_putc(lcd_string[0]);
						lcd_putc('0');
						lcd_putc('0');
						lcd_putc('.');
						lcd_putc(lcd_string[1]);
					}
					else
					{
						// temp between -1°C and -10°C
						if (value <= -1 && value > -10)
						{
							lcd_gotoxy(5,0);
							lcd_putc(lcd_string[0]);
							lcd_putc('0');
							lcd_putc(lcd_string[1]);
							lcd_putc('.');
							lcd_putc(lcd_string[2]);
						}
						// temp smaller than -10°C
						else
						{
							lcd_gotoxy(5,0);
							lcd_putc(lcd_string[0]);
							lcd_putc(lcd_string[1]);
							lcd_putc(lcd_string[2]);
							lcd_putc('.');
							lcd_putc(lcd_string[3]);
						}
					}
				}
			}
		}
	}
}

// Displays humidity to LCD correctly
void write_hum (char lcd_string[], float value)
{
	// humidity equals 100%
	if (value == 100)
	{
		lcd_gotoxy(4,1);
		lcd_puts("100");
		lcd_putc('.');
		lcd_putc('0');
	} 
	else
	{
			// humidity between 100 and 10%
			if (value>=10)
			{
				lcd_gotoxy(4,1);
				lcd_putc(' ');
				lcd_putc(lcd_string[0]);
				lcd_putc(lcd_string[1]);
				lcd_putc('.');
				lcd_putc(lcd_string[2]);
			}
			// humidity smaller than 10%
			else
			{
				lcd_gotoxy(4,1);
				lcd_putc(' ');
				lcd_putc('0');
				lcd_putc(lcd_string[0]);
				lcd_putc('.');
				lcd_putc(lcd_string[1]);
			}
	}
}

// Calculates movement of first servo
void calculate_movement_servo_1 (uint16_t value_right_bot, uint16_t value_left_bot, uint16_t value_right_top, uint16_t value_left_top)
{
	//  Positions of photo resistors

	//	4 - value_left_top  ||  3 - value_right_top
	//  -------------------------------------------
	//  2 - value_left_bot  ||  1 - value_right_bot
	
	uint16_t values[4] = {value_right_bot, value_left_bot, value_right_top, value_left_top}; // Array of values for determining max value
	uint16_t max = 0; // Variable for max value
	uint8_t servo_with_max = 0; // Servo with max value
	int16_t toleration = 0;	// Value for toleration calculation
	uint16_t value_avg_top = (value_left_bot + value_right_bot)/2;	// Average value of top row for passing further
	uint16_t value_avg_bot = (value_left_top + value_right_top)/2;	// Average value of bottom row for passing further
	// Getting max value
	for (uint8_t i=0; i < 4; i++)
	{
		if (values[i] > max)
		{
			max = values[i];
			servo_with_max = i;
		}
	}
	// Adding 1 to correspond with given order
	servo_with_max = servo_with_max + 1;
	
	// Deciding in which row is the sensor with max value
	if (servo_with_max == 1 || servo_with_max == 2)
	{
		// Deciding if it is the right or the left one
		if (servo_with_max == 1)
		{
			// Calculating toleration
			toleration = value_right_bot*0.9;
			// Comparing with toleration
			if (toleration <= value_left_bot)
			{
				// Toleration OK, calling function for movement of second servo
				calculate_movement_servo_2(value_avg_top, value_avg_bot);
			} 
			else
			{
				// Value is smaller than given toleration, turning servo one
				// Determining the position of second servo for correct movement
				if (servo_2_pos >= 0)
				{
					// Servo 2 in front position
					// Checking if movement is possible
					if (servo_1_pos >= -80 && servo_1_pos <=90)
					{
						// Update position variable
						servo_1_pos = servo_1_pos - 10;
						// Move servo
						servo_turn_to_postion(servo_1_pos, &DDRB, &PORTB, SERVO_1_PIN);
					}
				} 
				else
				{
					// Servo 2 in back position
					// Checking if movement is possible
					if (servo_1_pos >= -90 && servo_1_pos <=80)
					{
						// Update position variable
						servo_1_pos = servo_1_pos + 10;
						// Move servo
						servo_turn_to_postion(servo_1_pos, &DDRB, &PORTB, SERVO_1_PIN);
					}
				}
			}
		} 
		else
		{
			// Calculating toleration
			toleration = value_left_bot*0.9;
			// Comparing with toleration
			if (toleration <= value_right_bot)
			{
				// Toleration OK, calling function for movement of second servo
				calculate_movement_servo_2(value_avg_top, value_avg_bot);
			}
			else
			{
				// Value is smaller than given toleration, turning servo one
				// Determining the position of second servo for correct movement
				if (servo_2_pos >= 0)
				{
					// Servo 2 in front position
					// Checking if movement is possible
					if (servo_1_pos >= -80 && servo_1_pos <=90)
					{
						// Update position variable
						servo_1_pos = servo_1_pos + 10;
						// Move servo
						servo_turn_to_postion(servo_1_pos, &DDRB, &PORTB, SERVO_1_PIN);
					}
				}
				else
				{
					// Servo 2 in back position
					// Checking if movement is possible
					if (servo_1_pos >= -90 && servo_1_pos <=80)
					{
						// Update position variable
						servo_1_pos = servo_1_pos - 10;
						// Move servo
						servo_turn_to_postion(servo_1_pos, &DDRB, &PORTB, SERVO_1_PIN);
					}
				}
			}
		}
	} 
	else
	{
		// Deciding if it is the right or the left one
		if (servo_with_max == 3)
		{
			// Calculating toleration
			toleration = value_right_top*0.9;
			// Comparing with toleration
			if (toleration <= value_left_top)
			{
				// Toleration OK, calling function for movement of second servo
				calculate_movement_servo_2(value_avg_top, value_avg_bot);
			}
			else
			{
				// Value is smaller than given toleration, turning servo one
				// Determining the position of second servo for correct movement
				if (servo_2_pos >= 0)
				{
					// Servo 2 in front position
					// Checking if movement is possible
					if (servo_1_pos >= -80 && servo_1_pos <=90)
					{
						// Update position variable
						servo_1_pos = servo_1_pos - 10;
						// Move servo
						servo_turn_to_postion(servo_1_pos, &DDRB, &PORTB, SERVO_1_PIN);
					}
				}
				else
				{
					// Servo 2 in back position
					// Checking if movement is possible
					if (servo_1_pos >= -90 && servo_1_pos <=80)
					{
						// Update position variable
						servo_1_pos = servo_1_pos + 10;
						// Move servo
						servo_turn_to_postion(servo_1_pos, &DDRB, &PORTB, SERVO_1_PIN);
					}
				}
			}
		}
		else
		{
			// Calculating toleration
			toleration = value_left_top*0.9;
			// Comparing with toleration
			if (toleration <= value_right_top)
			{
				// Toleration OK, calling function for movement of second servo
				calculate_movement_servo_2(value_avg_top, value_avg_bot);
			}
			else
			{
				// Value is smaller than given toleration, turning servo one
				// Determining the position of second servo for correct movement
				if (servo_2_pos >= 0)
				{
					// Servo 2 in front position
					// Checking if movement is possible
					if (servo_1_pos >= -80 && servo_1_pos <=90)
					{
						// Update position variable
						servo_1_pos = servo_1_pos + 10;
						// Move servo
						servo_turn_to_postion(servo_1_pos, &DDRB, &PORTB, SERVO_1_PIN);
					}
				}
				else
				{
					// Servo 2 in back position
					// Checking if movement is possible
					if (servo_1_pos >= -90 && servo_1_pos <=80)
					{
						// Update position variable
						servo_1_pos = servo_1_pos - 10;
						// Move servo
						servo_turn_to_postion(servo_1_pos, &DDRB, &PORTB, SERVO_1_PIN);
					}
				}
			}
		}
	}
}

// Calculates movement of second servo
void calculate_movement_servo_2 (uint16_t value_avg_top, uint16_t value_avg_bot)
{
	uint16_t max = 0; // Variable for max value
	int16_t toleration = 0; // Value for toleration calculation
	// Getting max value
	if (value_avg_bot <= value_avg_top)
	{
		max = value_avg_top;
	}
	else
	{
		max = value_avg_bot;
	}
	// Deciding which row has higher value
	if (max == value_avg_top)
	{
		// Top row has bigger value
		// Calculating toleration
		toleration = value_avg_top*0.9;
		// Comparing with toleration
		if (toleration >= value_avg_bot)
		{
			// Checking if movement is possible
			if (servo_2_pos >= -40 && servo_2_pos <= 30)
			{
				// Update position variable
				servo_2_pos = servo_2_pos + 10;
				// Move servo
				servo_turn_to_postion(servo_2_pos, &DDRB, &PORTB, SERVO_2_PIN);
			}
		} 
	} 
	else
	{
		// Bottom row has bigger value
		// Calculating toleration
		toleration = value_avg_bot*0.9;
		// Comparing with toleration
		if (toleration >= value_avg_top)
		{
			// Checking if movement is possible
			if (servo_2_pos >= -30 && servo_2_pos <= 40)
			{
				// Update position variable
				servo_2_pos = servo_2_pos - 10;
				// Move servo
				servo_turn_to_postion(servo_2_pos, &DDRB, &PORTB, SERVO_2_PIN);
			}
		}
	}
	
}

// Moves servo to default position
void move_to_night_pos ()
{
	// Move servo 2 to default position for next day, keep servo 1 the same
	servo_move_minus_fourty(&DDRB, &PORTB, SERVO_2_PIN);
	// Update position variable
	servo_2_pos = -40;
}

// Moves servo to starting position for next day
void default_servo_pos ()
{
	// Move servo 1 to default position
	servo_move_zero(&DDRB, &PORTB, SERVO_1_PIN);
	// Update position variable
	servo_1_pos = 0;
	// Move servo 2 to default position
	servo_move_minus_fourty(&DDRB, &PORTB, SERVO_2_PIN);
	// Update position variable
	servo_2_pos = -40;
}

/* Interrupt service routines ----------------------------------------*/
ISR(TIMER1_OVF_vect)
{
	// ADC conversion
	ADCSRA|=(1<<ADSC);
}

ISR(ADC_vect)
{
	// Variables for photo resistors
	static uint16_t r_value_right_bot = 0;
	static uint16_t r_value_left_bot = 0;
	static uint16_t r_value_right_top = 0;
	static uint16_t r_value_left_top = 0;
	
	uint16_t avg = 0;			 // Variable for counting average
	
	float value = 0;			 // Calculated value for temperature and humidity
	float value_s = 0;			 // Calculated value shifted by 1 decimal
	
	char lcd_string[4] = "0000"; // Empty string for LCD

	// ADC input multiplex
	switch(ADMUX)
	{
		// ADC0 temperature
		case 0xC0:
		{
			value = ((((float)ADC/(1023/1.1))*100)-50); // Calculation of temperature
			value_s = value*10;							// Decimal shift for string conversion

			itoa(value_s, lcd_string, 10);	 // Convert decimal value to string
			write_temp(lcd_string, value);	 // Call the write to LCD function
			
			ADMUX =0xC1;	// Change address for next conversion
			
			break;
		}
		// ADC1 humidity
		case 0xC1:
		{
			value = ((((((ADC/(1023/1.1)))*4)/5)-0.1515)/0.00636)+0.4;	// Calculation of temperature
			value_s = value*10;											// Decimal shift for string conversion

			itoa(value_s, lcd_string, 10);	// Convert decimal value to string
			write_hum(lcd_string, value);	// Call the write to LCD function
			
			ADMUX =0xC2;	// Change address for next conversion
			
			break;
		}
		// ADC2 photo resistor bottom right
		case 0xC2:
		{
			value = ADC/(1023/1.1)*1000;	// Convert to voltage
			
			r_value_right_bot = value;		// Save to static variable
			
			ADMUX =0xC3;	// Change address for next conversion
			
			break;
		}
		// ADC3 photo resistor bottom left
		case 0xC3:
		{
			value = ADC/(1023/1.1)*1000;	// Convert to voltage
			
			r_value_left_bot = value;		// Save to static variable
			
			ADMUX =0xC4;	// Change address for next conversion
			
			break;
		}
		// ADC4  photo resistor top right
		case 0xC4:
		{
			value = ADC/(1023/1.1)*1000;	// Convert to voltage
			
			r_value_right_top = value;		// Save to static variable
			
			ADMUX =0xC5;	// Change address for next conversion
			
			break;
		}
		// ADC  photo resistor top left
		case 0xC5:
		{
			value = ADC/(1023/1.1)*1000;	// Convert to voltage
			
			r_value_left_top = value;		// Save to static variable
			
			// Calculate average value
			avg = (r_value_left_bot + r_value_left_top + r_value_right_bot + r_value_right_top)/4;
			
			// Decide if there is sufficient amount of light
			if (avg >= 550)
			{
				// Calculate movement of first servo
				calculate_movement_servo_1(r_value_right_bot, r_value_left_bot, r_value_right_top, r_value_left_top);
			}
			else
			{
				// Set to default position for next day
				move_to_night_pos();
			}
			
			ADMUX =0xC0;	// Change address for next conversion
			
			break;
		}
	}
}
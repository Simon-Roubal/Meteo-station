/*
 * DHT22.h
 *
 * Created: 12.12.2021 19:03:43
 *  Author: Antix
 */ 
#ifndef DHT_22
	#define DHT_22
#endif

#include "gpio.h"
#include <util/delay.h>
#include <stdlib.h> 

volatile uint8_t *ddr_reg, *port_reg, *pin_reg, pin_num;

//dht22_init(DDR

void dht22_init (volatile uint8_t *ddr_reg_inp, volatile uint8_t *port_reg_inp,  volatile uint8_t *pin_reg_inp, uint8_t pin_num_inp)
{
	ddr_reg = ddr_reg_inp;
	port_reg = port_reg_inp;
	pin_reg = pin_reg_inp;
	pin_num = pin_num_inp;
	
	GPIO_config_output(ddr_reg,pin_num);
	GPIO_write_high(port_reg,pin_num);
}

void dht22_read (uint8_t *temp, uint8_t *temp_dec, uint8_t * humid, uint8_t *humid_dec, uint8_t *checksum)
{
	char lcd_string[4] = "0000";
	double time = 0;
	// uint8_t calibration;
	GPIO_write_low(port_reg,pin_num);
	_delay_ms(20);
	GPIO_write_high(port_reg,pin_num);
	_delay_us(30);
	GPIO_write_low(port_reg,pin_num);
	GPIO_config_input_nopull(pin_reg,pin_num);
	while (GPIO_read(pin_reg,pin_num) == 0)
	{
		time++;
		_delay_us(1);
	}
	while(GPIO_read(pin_reg,pin_num) != 0)
	{
		time++;
		_delay_us(1);
	}
	itoa(time, lcd_string, 10);
	lcd_gotoxy(0, 0);
	lcd_puts(lcd_string);
}
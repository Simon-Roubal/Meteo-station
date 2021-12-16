/*/***********************************************************************
 * 
 * PWM SERWO library for AVR-GCC.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include "pwm_servo.h"
#include <avr/sfr_defs.h>
#include <stdio.h>
#include <util/delay.h>

/* Defines -----------------------------------------------------------*/
#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: turn_to_postion()
 * Purpose:  Decide which turning function to call.
 * Input:	 position - Position to which to turn
 *           reg_name - Address of Data Direction Register, such as &DDRB
 *			 port_name - Address of Data Direction Register, such as &PORTB
 *           pin_num - Pin designation in the interval 0 to 7
 * Returns:  none
 **********************************************************************/
void servo_turn_to_postion (int8_t position, volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num)
{
	switch (position)
	{
		case 90:
		{
			servo_move_plus_ninety(reg_name, port_name, pin_num);
			break;
		}
		case 80:
		{
			servo_move_plus_eighty(reg_name, port_name, pin_num);
			break;
		}
		case 70:
		{
			servo_move_plus_seventy(reg_name, port_name, pin_num);
			break;
		}
		case 60:
		{
			servo_move_plus_sixty(reg_name, port_name, pin_num);
			break;
		}
		case 50:
		{
			servo_move_plus_fifty(reg_name, port_name, pin_num);
			break;
		}
		case 40:
		{
			servo_move_plus_fourty(reg_name, port_name, pin_num);
			break;
		}
		case 30:
		{
			servo_move_plus_thirty(reg_name, port_name, pin_num);
			break;
		}
		case 20:
		{
			servo_move_plus_twenty(reg_name, port_name, pin_num);
			break;
		}
		case 10:
		{
			servo_move_plus_ten(reg_name, port_name, pin_num);
			break;
		}
		case 0:
		{
			servo_move_zero(reg_name, port_name, pin_num);
			break;
		}
		case -10:
		{
			servo_move_minus_ten(reg_name, port_name, pin_num);
			break;
		}
		case -20:
		{
			servo_move_minus_twenty(reg_name, port_name, pin_num);
			break;
		}
		case -30:
		{
			servo_move_minus_thirty(reg_name, port_name, pin_num);
			break;
		}
		case -40:
		{
			servo_move_minus_fourty(reg_name, port_name, pin_num);
			break;
		}
		case -50:
		{
			servo_move_mimus_fifty(reg_name, port_name, pin_num);
			break;
		}
		case -60:
		{
			servo_move_minus_sixty(reg_name, port_name, pin_num);
			break;
		}
		case -70:
		{
			servo_move_minus_seventy(reg_name, port_name, pin_num);
			break;
		}
		case -80:
		{
			servo_move_minus_eighty(reg_name, port_name, pin_num);
			break;
		}
		case -90:
		{
			servo_move_minus_ninety(reg_name, port_name, pin_num);
			break;
		}
		default:
		{
			break;
		}
	}
}

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: servo_move_plus_ninety()
 * Purpose:  Rotate servo to +90 degree position.
 * Input:    reg_name - Address of Data Direction Register, such as &DDRB
 *			 port_name - Address of Data Direction Register, such as &PORTB
 *           pin_num - Pin designation in the interval 0 to 7
 * Returns:  none
 **********************************************************************/
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

/**********************************************************************
 * Function: servo_move_plus_eighty()
 * Purpose:  Rotate servo to +80 degree position.
 * Input:    reg_name - Address of Data Direction Register, such as &DDRB
 *			 port_name - Address of Data Direction Register, such as &PORTB
 *           pin_num - Pin designation in the interval 0 to 7
 * Returns:  none
 **********************************************************************/
void servo_move_plus_eighty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num)
{
	uint16_t x = 1184;
	uint16_t y = 20000-x;
	*reg_name = *reg_name | (1<<pin_num);
	*port_name = *port_name & ~(1<<pin_num);
	*port_name = *port_name |(1<<pin_num);
	_delay_us(x);
	*port_name = *port_name & ~(1<<pin_num);
	_delay_us(y);
}

/**********************************************************************
 * Function: servo_move_plus_seventy()
 * Purpose:  Rotate servo to +70 degree position.
 * Input:    reg_name - Address of Data Direction Register, such as &DDRB
 *			 port_name - Address of Data Direction Register, such as &PORTB
 *           pin_num - Pin designation in the interval 0 to 7
 * Returns:  none
 **********************************************************************/
void servo_move_plus_seventy(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num)
{
	uint16_t x = 1118;
	uint16_t y = 20000-x;
	*reg_name = *reg_name | (1<<pin_num);
	*port_name = *port_name & ~(1<<pin_num);
	*port_name = *port_name |(1<<pin_num);
	_delay_us(x);
	*port_name = *port_name & ~(1<<pin_num);
	_delay_us(y);
}

/**********************************************************************
 * Function: servo_move_plus_sixty()
 * Purpose:  Rotate servo to +60 degree position.
 * Input:    reg_name - Address of Data Direction Register, such as &DDRB
 *			 port_name - Address of Data Direction Register, such as &PORTB
 *           pin_num - Pin designation in the interval 0 to 7
 * Returns:  none
 **********************************************************************/
void servo_move_plus_sixty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num)
{
	uint16_t x = 1052;
	uint16_t y = 20000-x;
	*reg_name = *reg_name | (1<<pin_num);
	*port_name = *port_name & ~(1<<pin_num);
	*port_name = *port_name |(1<<pin_num);
	_delay_us(x);
	*port_name = *port_name & ~(1<<pin_num);
	_delay_us(y);
}

/**********************************************************************
 * Function: servo_move_plus_fifty()
 * Purpose:  Rotate servo to +50 degree position.
 * Input:    reg_name - Address of Data Direction Register, such as &DDRB
 *			 port_name - Address of Data Direction Register, such as &PORTB
 *           pin_num - Pin designation in the interval 0 to 7
 * Returns:  none
 **********************************************************************/
void servo_move_plus_fifty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num)
{
	uint16_t x = 986;
	uint16_t y = 20000-x;
	*reg_name = *reg_name | (1<<pin_num);
	*port_name = *port_name & ~(1<<pin_num);
	*port_name = *port_name |(1<<pin_num);
	_delay_us(x);
	*port_name = *port_name & ~(1<<pin_num);
	_delay_us(y);
}

/**********************************************************************
 * Function: servo_move_plus_fourty()
 * Purpose:  Rotate servo to +40 degree position.
 * Input:    reg_name - Address of Data Direction Register, such as &DDRB
 *			 port_name - Address of Data Direction Register, such as &PORTB
 *           pin_num - Pin designation in the interval 0 to 7
 * Returns:  none
 **********************************************************************/
void servo_move_plus_fourty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num)
{
	uint16_t x = 920;
	uint16_t y = 20000-x;
	*reg_name = *reg_name | (1<<pin_num);
	*port_name = *port_name & ~(1<<pin_num);
	*port_name = *port_name |(1<<pin_num);
	_delay_us(x);
	*port_name = *port_name & ~(1<<pin_num);
	_delay_us(y);
}

/**********************************************************************
 * Function: servo_move_plus_thirty()
 * Purpose:  Rotate servo to +30 degree position.
 * Input:    reg_name - Address of Data Direction Register, such as &DDRB
 *			 port_name - Address of Data Direction Register, such as &PORTB
 *           pin_num - Pin designation in the interval 0 to 7
 * Returns:  none
 **********************************************************************/
void servo_move_plus_thirty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num)
{
	uint16_t x = 854;
	uint16_t y = 20000-x;
	*reg_name = *reg_name | (1<<pin_num);
	*port_name = *port_name & ~(1<<pin_num);
	*port_name = *port_name |(1<<pin_num);
	_delay_us(x);
	*port_name = *port_name & ~(1<<pin_num);
	_delay_us(y);
}

/**********************************************************************
 * Function: servo_move_plus_twenty()
 * Purpose:  Rotate servo to +20 degree position.
 * Input:    reg_name - Address of Data Direction Register, such as &DDRB
 *			 port_name - Address of Data Direction Register, such as &PORTB
 *           pin_num - Pin designation in the interval 0 to 7
 * Returns:  none
 **********************************************************************/
void servo_move_plus_twenty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num)
{
	uint16_t x = 788;
	uint16_t y = 20000-x;
	*reg_name = *reg_name | (1<<pin_num);
	*port_name = *port_name & ~(1<<pin_num);
	*port_name = *port_name |(1<<pin_num);
	_delay_us(x);
	*port_name = *port_name & ~(1<<pin_num);
	_delay_us(y);
}

/**********************************************************************
 * Function: servo_move_plus_ten()
 * Purpose:  Rotate servo to +10 degree position.
 * Input:    reg_name - Address of Data Direction Register, such as &DDRB
 *			 port_name - Address of Data Direction Register, such as &PORTB
 *           pin_num - Pin designation in the interval 0 to 7
 * Returns:  none
 **********************************************************************/
void servo_move_plus_ten(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num)
{
	uint16_t x = 722;
	uint16_t y = 20000-x;
	*reg_name = *reg_name | (1<<pin_num);
	*port_name = *port_name & ~(1<<pin_num);
	*port_name = *port_name |(1<<pin_num);
	_delay_us(x);
	*port_name = *port_name & ~(1<<pin_num);
	_delay_us(y);
}

/**********************************************************************
 * Function: servo_move_zero()
 * Purpose:  Rotate servo to 0 degree position.
 * Input:    reg_name - Address of Data Direction Register, such as &DDRB
 *			 port_name - Address of Data Direction Register, such as &PORTB
 *           pin_num - Pin designation in the interval 0 to 7
 * Returns:  none
 **********************************************************************/
void servo_move_zero(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num)
{
	uint16_t x = 656;
	uint16_t y = 20000-x;
	*reg_name = *reg_name | (1<<pin_num);
	*port_name = *port_name & ~(1<<pin_num);
	*port_name = *port_name |(1<<pin_num);
	_delay_us(x);
	*port_name = *port_name & ~(1<<pin_num);
	_delay_us(y);
}

/**********************************************************************
 * Function: servo_move_minus_ten()
 * Purpose:  Rotate servo to -10 degree position.
 * Input:    reg_name - Address of Data Direction Register, such as &DDRB
 *			 port_name - Address of Data Direction Register, such as &PORTB
 *           pin_num - Pin designation in the interval 0 to 7
 * Returns:  none
 **********************************************************************/
void servo_move_minus_ten(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num)
{
	uint16_t x = 590;
	uint16_t y = 20000-x;
	*reg_name = *reg_name | (1<<pin_num);
	*port_name = *port_name & ~(1<<pin_num);
	*port_name = *port_name |(1<<pin_num);
	_delay_us(x);
	*port_name = *port_name & ~(1<<pin_num);
	_delay_us(y);
}

/**********************************************************************
 * Function: servo_move_minus_twenty()
 * Purpose:  Rotate servo to -20 degree position.
 * Input:    reg_name - Address of Data Direction Register, such as &DDRB
 *			 port_name - Address of Data Direction Register, such as &PORTB
 *           pin_num - Pin designation in the interval 0 to 7
 * Returns:  none
 **********************************************************************/
void servo_move_minus_twenty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num)
{
	uint16_t x = 524;
	uint16_t y = 20000-x;
	*reg_name = *reg_name | (1<<pin_num);
	*port_name = *port_name & ~(1<<pin_num);
	*port_name = *port_name |(1<<pin_num);
	_delay_us(x);
	*port_name = *port_name & ~(1<<pin_num);
	_delay_us(y);
}

/**********************************************************************
 * Function: servo_move_minus_thirty()
 * Purpose:  Rotate servo to -30 degree position.
 * Input:    reg_name - Address of Data Direction Register, such as &DDRB
 *			 port_name - Address of Data Direction Register, such as &PORTB
 *           pin_num - Pin designation in the interval 0 to 7
 * Returns:  none
 **********************************************************************/
void servo_move_minus_thirty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num)
{
	uint16_t x = 458;
	uint16_t y = 20000-x;
	*reg_name = *reg_name | (1<<pin_num);
	*port_name = *port_name & ~(1<<pin_num);
	*port_name = *port_name |(1<<pin_num);
	_delay_us(x);
	*port_name = *port_name & ~(1<<pin_num);
	_delay_us(y);
}

/**********************************************************************
 * Function: servo_move_minus_fourty()
 * Purpose:  Rotate servo to -40 degree position.
 * Input:    reg_name - Address of Data Direction Register, such as &DDRB
 *			 port_name - Address of Data Direction Register, such as &PORTB
 *           pin_num - Pin designation in the interval 0 to 7
 * Returns:  none
 **********************************************************************/
void servo_move_minus_fourty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num)
{
	uint16_t x = 392;
	uint16_t y = 20000-x;
	*reg_name = *reg_name | (1<<pin_num);
	*port_name = *port_name & ~(1<<pin_num);
	*port_name = *port_name |(1<<pin_num);
	_delay_us(x);
	*port_name = *port_name & ~(1<<pin_num);
	_delay_us(y);
}

/**********************************************************************
 * Function: servo_move_mimus_fifty()
 * Purpose:  Rotate servo to -50 degree position.
 * Input:    reg_name - Address of Data Direction Register, such as &DDRB
 *			 port_name - Address of Data Direction Register, such as &PORTB
 *           pin_num - Pin designation in the interval 0 to 7
 * Returns:  none
 **********************************************************************/
void servo_move_mimus_fifty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num)
{
	uint16_t x = 326;
	uint16_t y = 20000-x;
	*reg_name = *reg_name | (1<<pin_num);
	*port_name = *port_name & ~(1<<pin_num);
	*port_name = *port_name |(1<<pin_num);
	_delay_us(x);
	*port_name = *port_name & ~(1<<pin_num);
	_delay_us(y);
}

/**********************************************************************
 * Function: servo_move_minus_sixty()
 * Purpose:  Rotate servo to -60 degree position.
 * Input:    reg_name - Address of Data Direction Register, such as &DDRB
 *			 port_name - Address of Data Direction Register, such as &PORTB
 *           pin_num - Pin designation in the interval 0 to 7
 * Returns:  none
 **********************************************************************/
void servo_move_minus_sixty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num)
{
	uint16_t x = 260;
	uint16_t y = 20000-x;
	*reg_name = *reg_name | (1<<pin_num);
	*port_name = *port_name & ~(1<<pin_num);
	*port_name = *port_name |(1<<pin_num);
	_delay_us(x);
	*port_name = *port_name & ~(1<<pin_num);
	_delay_us(y);
}

/**********************************************************************
 * Function: servo_move_minus_seventy()
 * Purpose:  Rotate servo to -70 degree position.
 * Input:    reg_name - Address of Data Direction Register, such as &DDRB
 *			 port_name - Address of Data Direction Register, such as &PORTB
 *           pin_num - Pin designation in the interval 0 to 7
 * Returns:  none
 **********************************************************************/
void servo_move_minus_seventy(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num)
{
	uint16_t x = 194;
	uint16_t y = 20000-x;
	*reg_name = *reg_name | (1<<pin_num);
	*port_name = *port_name & ~(1<<pin_num);
	*port_name = *port_name |(1<<pin_num);
	_delay_us(x);
	*port_name = *port_name & ~(1<<pin_num);
	_delay_us(y);
}

/**********************************************************************
 * Function: servo_move_minus_eighty()
 * Purpose:  Rotate servo to -80 degree position.
 * Input:    reg_name - Address of Data Direction Register, such as &DDRB
 *			 port_name - Address of Data Direction Register, such as &PORTB
 *           pin_num - Pin designation in the interval 0 to 7
 * Returns:  none
 **********************************************************************/
void servo_move_minus_eighty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num)
{
	uint16_t x = 128;
	uint16_t y = 20000-x;
	*reg_name = *reg_name | (1<<pin_num);
	*port_name = *port_name & ~(1<<pin_num);
	*port_name = *port_name |(1<<pin_num);
	_delay_us(x);
	*port_name = *port_name & ~(1<<pin_num);
	_delay_us(y);
}
/**********************************************************************
 * Function: servo_move_minus_ninety()
 * Purpose:  Rotate servo to -90 degree position.
 * Input:    reg_name - Address of Data Direction Register, such as &DDRB
 *			 port_name - Address of Data Direction Register, such as &PORTB
 *           pin_num - Pin designation in the interval 0 to 7
 * Returns:  none
 **********************************************************************/
void servo_move_minus_ninety(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num)
{
	uint16_t x = 62;
	uint16_t y = 20000-x;
	*reg_name = *reg_name | (1<<pin_num);
	*port_name = *port_name & ~(1<<pin_num);
	*port_name = *port_name |(1<<pin_num);
	_delay_us(x);
	*port_name = *port_name & ~(1<<pin_num);
	_delay_us(y);
}

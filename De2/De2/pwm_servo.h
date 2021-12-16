#ifndef PWM_SERVO
# define PWM_SERVO

/***********************************************************************
 * 
 * PWM SERVO library for AVR-GCC.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 **********************************************************************/

/**
 * @file 
 * @code #include "pwm_servo.h" @endcode
 *
 * @brief PWM SERWO control library for AVR-GCC.
 *
 * The library contains functions for controlling PWM servos by 10 degree steps.
 *
 */


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>

/* Defines -----------------------------------------------------------*/
#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif

/* Function prototypes -----------------------------------------------*/
/**
 * @name Functions
 */
/**
 * @brief  Decide which turning function to call.
 * @param  position Position to which to turn
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  port_name Address of Port Register, such as &PORTB
 * @param  pin_num  Pin designation in the interval 0 to 7
 * @return none
 */
void servo_turn_to_postion (int8_t position, volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num);

/**
 * @brief  Rotate servo to +90 degree position.
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  port_name Address of Port Register, such as &PORTB
 * @param  pin_num  Pin designation in the interval 0 to 7
 * @return none
 */
void servo_move_plus_ninety(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num);

/**
 * @brief  Rotate servo to +80 degree position.
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  port_name Address of Port Register, such as &PORTB
 * @param  pin_num  Pin designation in the interval 0 to 7
 * @return none
 */
void servo_move_plus_eighty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num);

/**
 * @brief  Rotate servo to +70 degree position.
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  port_name Address of Port Register, such as &PORTB
 * @param  pin_num  Pin designation in the interval 0 to 7
 * @return none
 */
void servo_move_plus_seventy(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num);

/**
 * @brief  Rotate servo to +60 degree position.
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  port_name Address of Port Register, such as &PORTB
 * @param  pin_num  Pin designation in the interval 0 to 7
 * @return none
 */
void servo_move_plus_sixty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num);

/**
 * @brief  Rotate servo to +50 degree position.
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  port_name Address of Port Register, such as &PORTB
 * @param  pin_num  Pin designation in the interval 0 to 7
 * @return none
 */
void servo_move_plus_fifty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num);

/**
 * @brief  Rotate servo to +40 degree position.
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  port_name Address of Port Register, such as &PORTB
 * @param  pin_num  Pin designation in the interval 0 to 7
 * @return none
 */
void servo_move_plus_fourty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num);

/**
 * @brief  Rotate servo to +30 degree position.
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  port_name Address of Port Register, such as &PORTB
 * @param  pin_num  Pin designation in the interval 0 to 7
 * @return none
 */
void servo_move_plus_thirty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num);

/**
 * @brief  Rotate servo to +20 degree position.
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  port_name Address of Port Register, such as &PORTB
 * @param  pin_num  Pin designation in the interval 0 to 7
 * @return none
 */
void servo_move_plus_twenty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num);

/**
 * @brief  Rotate servo to +10 degree position.
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  port_name Address of Port Register, such as &PORTB
 * @param  pin_num  Pin designation in the interval 0 to 7
 * @return none
 */
void servo_move_plus_ten(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num);

/**
 * @brief  Rotate servo to 0 degree position.
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  port_name Address of Port Register, such as &PORTB
 * @param  pin_num  Pin designation in the interval 0 to 7
 * @return none
 */
void servo_move_zero(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num);

/**
 * @brief  Rotate servo to -10 degree position.
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  port_name Address of Port Register, such as &PORTB
 * @param  pin_num  Pin designation in the interval 0 to 7
 * @return none
 */
void servo_move_minus_ten(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num);

/**
 * @brief  Rotate servo to -20 degree position.
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  port_name Address of Port Register, such as &PORTB
 * @param  pin_num  Pin designation in the interval 0 to 7
 * @return none
 */
void servo_move_minus_twenty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num);

/**
 * @brief  Rotate servo to -30 degree position.
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  port_name Address of Port Register, such as &PORTB
 * @param  pin_num  Pin designation in the interval 0 to 7
 * @return none
 */
void servo_move_minus_thirty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num);

/**
 * @brief  Rotate servo to -40 degree position.
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  port_name Address of Port Register, such as &PORTB
 * @param  pin_num  Pin designation in the interval 0 to 7
 * @return none
 */
void servo_move_minus_fourty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num);

/**
 * @brief  Rotate servo to -50 degree position.
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  port_name Address of Port Register, such as &PORTB
 * @param  pin_num  Pin designation in the interval 0 to 7
 * @return none
 */
void servo_move_mimus_fifty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num);

/**
 * @brief  Rotate servo to -60 degree position.
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  port_name Address of Port Register, such as &PORTB
 * @param  pin_num  Pin designation in the interval 0 to 7
 * @return none
 */
void servo_move_minus_sixty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num);

/**
 * @brief  Rotate servo to -70 degree position.
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  port_name Address of Port Register, such as &PORTB
 * @param  pin_num  Pin designation in the interval 0 to 7
 * @return none
 */
void servo_move_minus_seventy(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num);

/**
 * @brief  Rotate servo to -80 degree position.
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  port_name Address of Port Register, such as &PORTB
 * @param  pin_num  Pin designation in the interval 0 to 7
 * @return none
 */
void servo_move_minus_eighty(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num);

/**
 * @brief  Rotate servo to -90 degree position.
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  port_name Address of Port Register, such as &PORTB
 * @param  pin_num  Pin designation in the interval 0 to 7
 * @return none
 */
void servo_move_minus_ninety(volatile uint8_t *reg_name, volatile uint8_t *port_name, uint8_t pin_num);

/** @} */

#endif
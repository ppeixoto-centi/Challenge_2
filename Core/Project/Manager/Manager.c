/**
 * Path:    Project/Manager
 * File:    Manager.c
 * Author:  
 */

/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */

#include <stdio.h>

/* STM32 HAL libraries. */

#include "gpio.h"
#include "tim.h"
#include "i2c.h"
#include "stdbool.h"
#include "SHT31.H"

/* MAnager header file. */
#include "Manager.h"

/* APIs libraries. */
#include "../UI/UI.h"

/* ************************************************************************************ */
/* * Defines                                                                          * */
/* ************************************************************************************ */

#define NUM_LEDS 					(	4	)

/* Led pins*/
#define LED0_PIN					( GPIO_PIN_7 )
#define LED0_PORT					(   GPIOC    )

#define LED1_PIN					( GPIO_PIN_8 )
#define LED1_PORT					(   GPIOC    )

#define LED2_PIN					( GPIO_PIN_9 )
#define LED2_PORT					(   GPIOC    )

#define LED3_PIN					( GPIO_PIN_8 )
#define LED3_PORT					(   GPIOA    )

/* Button Pin */
#define BUTTON_PIN					( GPIO_PIN_3 )
#define BUTTON_PORT					(   GPIOC    )

/* Slider Pin */
#define SLIDER_PIN					( GPIO_PIN_2 )
#define SLIDER_PORT					(   GPIOC    )

/* I2C Pins */
#define SDA_PIN						( GPIO_PIN_7 )
#define SDA_PORT					(   GPIOB    )
#define SCL_PIN						( GPIO_PIN_6 )
#define SCL_PORT					(   GPIOB    )

/* ************************************************************************************ */
/* * Global Variables                                                                 * */
/* ************************************************************************************ */

static bool period_elapsed = false;
static float hcoded_temp = 24;

/* ************************************************************************************ */
/* * Macros                                                                           * */
/* ************************************************************************************ */

/* TODO: Add macros here. */
// ...

/* ************************************************************************************ */
/* * Private Functions Prototypes                                                     * */
/* ************************************************************************************ */

/**
 * @brief Led 0 low level driver function
 *
 * @param   state -> State of the led
 *
 * @return  None.
 */
static void LED0_SetPin(bool state);

/**
 * @brief Led 1 low level driver function
 *
 * @param   state -> State of the led
 *
 * @return  None.
 */
static void LED1_SetPin(bool state);

/**
 * @brief Led 02low level driver function
 *
 * @param   state -> State of the led
 *
 * @return  None.
 */
static void LED2_SetPin(bool state);

/**
 * @brief Led 3 low level driver function
 *
 * @param   state -> State of the led
 *
 * @return  None.
 */
static void LED3_SetPin(bool state);

/**
 * @brief Butten low level driver
 *
 * @param   None.
 *
 * @return  Bool. Button state.
 *                - False: 	Button Pressed;
 *                - True: 	Button Unpressed.
 */
static bool Button_GetPin (void);

/**
 * @brief Dummy Function
 *
 * @param   None.
 *
 * @return  0.
 */
static bool Slider_GetPin (void);

/**
 * @brief Pressed Button logic Handler
 *
 * @param   led_index -> Pointer to the leds index that stores the current position
 *
 * @return  None.
 */
static void button_pressed_logic (uint8_t *led_index);

/**
 * @brief Unpressed Button logic Handler
 *
 * @param   led_index -> Pointer to the leds index that stores the current position
 *
 * @return  None.
 */
static void button_unpressed_logic (uint8_t *led_index);




static void button_unpressed_logic (uint8_t *led_index);
static void I2C_Write (uint8_t i2c_address, uint8_t * tx_vec, uint8_t   tx_vec_size);
static void I2C_Read (uint8_t i2c_address, uint8_t * rx_vec, uint8_t   rx_vec_size);
static uint8_t CRC_Calculate (const uint8_t * data, uint8_t data_size);
static void Delay_ms (uint16_t msec);

static void update_leds(float temp);
/* ************************************************************************************ */
/* * HAL Functions                                                                    * */
/* ************************************************************************************ */

//Callback of the External Interrupt
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

	if (GPIO_Pin == GPIO_PIN_3)
		UI_ISR_Button();

	else if (GPIO_Pin == GPIO_PIN_2)
		UI_ISR_Slider();
}

//Signals thats the time has elapsed
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	period_elapsed = true;
}

/************************************************************************************* */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */

void Manager_Initialize(void)
{
	st_UI_CONFIG config = {};

	config.LED0_SetPin = LED0_SetPin;
	config.LED1_SetPin = LED1_SetPin;
	config.LED2_SetPin = LED2_SetPin;
	config.LED3_SetPin = LED3_SetPin;

	config.Button_GetPin = Button_GetPin;
	config.Slider_GetPin = Slider_GetPin;
	UI_Initialize(config);

	st_SHT31_CONFIG sensor_config = {};
	sensor_config.i2c_address = SHT31_I2C_ADDRESS_GND << 1;
	sensor_config.I2C_Read = I2C_Read;
	sensor_config.I2C_Write = I2C_Write;
	sensor_config.Delay_ms = Delay_ms;
	sensor_config.CRC_Calculate = CRC_Calculate;

	SHT31_Initialize(sensor_config);
	HAL_TIM_Base_Start_IT(&htim2);

}

void Manager_Loop(void)
{
	float temp = 0.0, hum = 0.0;
	static uint8_t led_index = 0;

	if (UI_GetSliderState() == SLIDER_ACTIVE && period_elapsed == true){ //Checks for the elapsed time and ensures that the led index is within range
		period_elapsed = false; //Clears the elapsed time flag

		if(UI_GetButtonState() == BUTTON_PRESSED ){
			button_pressed_logic (&led_index); //Handles the logic when the button is pressed
		}

		else if (UI_GetButtonState() == BUTTON_RELEASED ){
			button_unpressed_logic(&led_index); //Handles the logic when the button is not pressed
		}
	}

	else if (UI_GetSliderState() == SLIDER_INACTIVE && period_elapsed == true){
		period_elapsed = false; //Clears the elapsed time flag

		SHT31_GetData(&temp, &hum); //Reads the data from the semsor

		if (UI_GetButtonState() == BUTTON_PRESSED)
			hcoded_temp = temp; //Logs the new temp into memory

		update_leds(temp);
	}


}

/* ************************************************************************************ */
/* * Private Functions                                                                * */
/* ************************************************************************************ */

static void LED0_SetPin(bool state){
	HAL_GPIO_WritePin(LED0_PORT, LED0_PIN, (GPIO_PinState)state);
}

static void LED1_SetPin(bool state){
	HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, (GPIO_PinState)state);
}

static void LED2_SetPin(bool state){
	HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, (GPIO_PinState)state);
}

static void LED3_SetPin(bool state){
	HAL_GPIO_WritePin(LED3_PORT, LED3_PIN, (GPIO_PinState)state);
}

static bool Button_GetPin (void){
	return (bool)HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN);
}

static bool Slider_GetPin (void){
	return (bool)HAL_GPIO_ReadPin(SLIDER_PORT, SLIDER_PIN);
}

static void button_pressed_logic (uint8_t *led_index){
	static uint8_t virtual_clk = 0;

	virtual_clk++;

	if (virtual_clk >= 2){ //The pressed logic period is 2x the unpressed logic
		virtual_clk = 0; //Resets the virtual Clock
		UI_SetLEDState(*led_index, LED_ON);

		if (*led_index < NUM_LEDS)
			*led_index = *led_index  + 1; //Points the led index to the next led
	}
}

static void button_unpressed_logic (uint8_t *led_index){
	UI_SetLEDState(*led_index, LED_OFF);

	if (*led_index > 0)
		*led_index = *led_index  - 1; //Points the led index to the next led
}

static void I2C_Write (uint8_t i2c_address, uint8_t * tx_vec, uint8_t   tx_vec_size){
	HAL_I2C_Master_Transmit(&hi2c1, i2c_address, tx_vec, tx_vec_size, HAL_MAX_DELAY);
}

static void I2C_Read (uint8_t i2c_address, uint8_t * rx_vec, uint8_t   rx_vec_size){
	HAL_I2C_Master_Receive(&hi2c1, i2c_address, rx_vec, rx_vec_size, HAL_MAX_DELAY);
}


static uint8_t CRC_Calculate (const uint8_t * data, uint8_t data_size){
	if (data == NULL || data_size == 0) {
		return 0; // Return 0 for invalid input
	}

	const uint8_t POLYNOMIAL = 0x31;
	uint8_t crc = 0xFF;

	for (size_t j = 0; j < data_size; j++) {
		crc ^= data[j];
		for (uint8_t i = 0; i < 8; i++) {
			if (crc & 0x80) {
				crc = (crc << 1) ^ POLYNOMIAL;
			} else {
				crc <<= 1;
			}
		}
	}
	return crc;
}

static void Delay_ms (uint16_t msec){
	HAL_Delay(msec);
}

static void update_leds(float temp){
	float drift = temp - hcoded_temp;

	if (drift <= -1){
		UI_SetLEDState(0, LED_OFF);
		UI_SetLEDState(1, LED_OFF);
		UI_SetLEDState(2, LED_OFF);
		UI_SetLEDState(3, LED_OFF);
	}

	else if (drift > -1 && drift < 0.5){
		UI_SetLEDState(0, LED_ON);
		UI_SetLEDState(1, LED_OFF);
		UI_SetLEDState(2, LED_OFF);
		UI_SetLEDState(3, LED_OFF);
	}

	else if (drift >= 0.5 && drift < 1){
		UI_SetLEDState(0, LED_ON);
		UI_SetLEDState(1, LED_ON);
		UI_SetLEDState(2, LED_OFF);
		UI_SetLEDState(3, LED_OFF);
	}

	else if (drift >= 1 && drift < 1.5){
		UI_SetLEDState(0, LED_ON);
		UI_SetLEDState(1, LED_ON);
		UI_SetLEDState(2, LED_ON);
		UI_SetLEDState(3, LED_OFF);
	}

	else if (drift >= 1.5 ){
		UI_SetLEDState(0, LED_ON);
		UI_SetLEDState(1, LED_ON);
		UI_SetLEDState(2, LED_ON);
		UI_SetLEDState(3, LED_ON);
	}
}
/* -- End of file -- */

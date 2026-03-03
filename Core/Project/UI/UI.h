/**
 * Path:    Project/UI
 * File:    UI.h
 * Author:  CeNTI
 */

#ifndef __PROJECT_UI_UI_H__
#define __PROJECT_UI_UI_H__

/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */

#include <stdbool.h>
#include <stdint.h>

#include "stdbool.h"
#include "gpio.h"

/* ************************************************************************************ */
/* * Defines                                                                          * */
/* ************************************************************************************ */

/* LEDs states. */
#define LED_ON                      false
#define LED_OFF                     true

/* Button states. */
#define BUTTON_PRESSED              false
#define BUTTON_RELEASED             true

/* Slider states. */
#define SLIDER_ACTIVE               true
#define SLIDER_INACTIVE             false


/* ************************************************************************************ */
/* * Function types                                                                   * */
/* ************************************************************************************ */

/* GPIO set/get functions typedefs. */
typedef void (*t_GPIO_SetPin)(bool state);
typedef bool (*t_GPIO_GetPin)(void);

/* ************************************************************************************ */
/* * Structure types                                                                  * */
/* ************************************************************************************ */

/* UI configuration structure. */
typedef struct {
    t_GPIO_SetPin   LED0_SetPin;
    t_GPIO_SetPin   LED1_SetPin;
    t_GPIO_SetPin   LED2_SetPin;
    t_GPIO_SetPin   LED3_SetPin;

    t_GPIO_GetPin   Button_GetPin;
    t_GPIO_GetPin   Slider_GetPin;
}st_UI_CONFIG;

/* ************************************************************************************ */
/* * Public Functions Prototypes                                                      * */
/* ************************************************************************************ */

/**
 * @brief Initialize the UI module.
 *
 * @note The functions UI_ISR_Button and UI_ISR_Slider must be called in the GPIO external
 *       interrupt handlers.
 *
 * @param[in]   config  UI configuration.
 *
 * @return  None.
 */
void UI_Initialize(st_UI_CONFIG config);

/**
 * @brief Get the actual button state.
 *
 * @param   None.
 *
 * @return  Button state.
 * @retval  BUTTON_PRESSED      Button is pressed.
 * @retval  BUTTON_RELEASED     Button is released.
 *  */
bool UI_GetButtonState(void);

/**
 * @brief Get the actual slider state.
 *
 * @param   None.
 *
 * @return  Slider state.
 * @retval  SLIDER_ACTIVE       Slider is in the active state.
 * @retval  SLIDER_INACTIVE     Slider is in the inactive state.
 */
bool UI_GetSliderState(void);

/**
 * @brief Set the LED state.
 *
 * @param[in]   led     LED number (between 0 and 3).
 * @param[in]   state   LED state.
 *                      - LED_ON: Turn on;
 *                      - LED_OFF: Turn off.
 *
 * @return  None.
 */
void UI_SetLEDState(uint8_t led,
                    bool    state);

/**
 * @brief Button external interrupt handler.
 *
 * @note This function must be called in the GPIO external interrupt handler.
 *       The GPIO external interrupt must be configured to trigger on the rising and
 *       falling edges.
 *
 * @param   None.
 *
 * @return  None.
 */
void UI_ISR_Button(void);

/**
 * @brief Slider external interrupt handler.
 *
 * @note This function must be called in the GPIO external interrupt handler.
 *       The GPIO external interrupt must be configured to trigger on the rising and
 *       falling edges.
 *
 * @param   None.
 *
 * @return  None.
 */
void UI_ISR_Slider(void);


#endif /* __PROJECT_UI_UI_H__ */

/* -- End of file -- */

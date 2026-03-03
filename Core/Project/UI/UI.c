/**
 * Path:    Project/UI
 * File:    UI.h
 * Author:  CeNTI
 */

/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */

#include "UI.h"

/* ************************************************************************************ */
/* * Global Variables                                                                 * */
/* ************************************************************************************ */

/* UI configuration. */
static st_UI_CONFIG g_config = {};

/* Button and slider states. */
static bool g_button_pressed  = false;
static bool g_slider_position = false;

/* ************************************************************************************ */
/* * ISR Functions                                                                    * */
/* ************************************************************************************ */

void UI_ISR_Button(void)
{
    g_button_pressed = g_config.Button_GetPin();
}

void UI_ISR_Slider(void)
{
    g_slider_position = g_config.Slider_GetPin();
}

/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */

void UI_Initialize(st_UI_CONFIG config)
{
    /* Save configuration. */
    g_config = config;

    /* Get initial state for button and slider. */
    g_button_pressed  = config.Button_GetPin();
    g_slider_position = config.Slider_GetPin();

    /* Initialize LEDs Off*/
    config.LED0_SetPin(LED_OFF);
    config.LED1_SetPin(LED_OFF);
    config.LED2_SetPin(LED_OFF);
    config.LED3_SetPin(LED_OFF);
}

bool UI_GetButtonState(void)
{
    return g_button_pressed;
}

bool UI_GetSliderState(void)
{
    return g_slider_position;
}

void UI_SetLEDState(uint8_t led,
                    bool    state)
{
    switch (led)
    {
        case 0:
            g_config.LED0_SetPin(state);
            break;
        case 1:
            g_config.LED1_SetPin(state);
            break;
        case 2:
            g_config.LED2_SetPin(state);
            break;
        case 3:
            g_config.LED3_SetPin(state);
            break;
        default:
            break;
    }
}

/* -- End of file -- */

/**
 * Path:    Project/Sensors
 * File:    SHT31.c
 * Author:  CeNTI
 */

/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */

#include <stdio.h>

#include "SHT31.h"

/* ************************************************************************************ */
/* * Global Variables                                                                 * */
/* ************************************************************************************ */

/* SHT31 configuration. */
static st_SHT31_CONFIG g_config = {};

/* ************************************************************************************ */
/* * Conversion Functions                                                             * */
/* ************************************************************************************ */

static inline float TemperatureConverter(uint16_t raw_temp)
    { return (float)((175.72*((float)raw_temp/65536))-46.85); }

static inline float HumidityConverter(uint16_t raw_hum)
    { return ((125*((float)raw_hum/65536))-6); }

/* ************************************************************************************ */
/* * Macros                                                                           * */
/* ************************************************************************************ */

/* Manager debug. */
#if ((defined(SHT31_DEBUG_LEVEL)  && (SHT31_DEBUG_LEVEL > 0))    )
    #define SHT31_DEBUG(...) printf("[D]: " __VA_ARGS__)
#else
    #define SHT31_DEBUG(...)
#endif

/* Delay. */
#define Delay_ms(_ms) g_config.Delay_ms(_ms)

/* ************************************************************************************ */
/* * Communication Functions                                                          * */
/* ************************************************************************************ */

void COM_WriteRegister(et_SHT31_CMD reg_address)
{
    uint8_t tx_data_vec[2] = {};

    tx_data_vec[0] = (uint8_t)((reg_address >> 8) & 0xFF);
    tx_data_vec[1] = (uint8_t)(reg_address & 0xFF);

    g_config.I2C_Write(g_config.i2c_address, tx_data_vec, 2);
}

void COM_Read6Bytes(uint16_t * data_1_ptr,
                    uint16_t * data_2_ptr)
{
    uint8_t rx_data_vec[6] = {};

    g_config.I2C_Read(g_config.i2c_address, rx_data_vec, 6);

    if ((rx_data_vec[2] == g_config.CRC_Calculate(&rx_data_vec[0], 2)) &&
        (rx_data_vec[5] == g_config.CRC_Calculate(&rx_data_vec[3], 2)) )
    {
        *data_1_ptr = (uint16_t)((rx_data_vec[0] << 8) | rx_data_vec[1]);
        *data_2_ptr = (uint16_t)((rx_data_vec[3] << 8) | rx_data_vec[4]);
    }
    else
    {
        *data_1_ptr = 0;
        *data_2_ptr = 0;
    }
}

/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */

void SHT31_Initialize(st_SHT31_CONFIG config)
{
    SHT31_DEBUG("SHT31: Initializing...\n");

    g_config = config;

    SHT31_SoftReset();

    SHT31_DEBUG("SHT31: ... Initialized.\n");
}

void SHT31_SoftReset(void)
{
    SHT31_DEBUG("SHT31: Doing SoftReset ...\n");

    COM_WriteRegister(SHT31_CMD_SOFTRESET);

    Delay_ms(15);

    SHT31_DEBUG("SHT31: ... SoftReset done.\n");
}

void SHT31_GetData(float * temp_ptr,
                   float * hum_ptr)
{
    uint16_t raw_temp, raw_hum = 0;

    COM_WriteRegister(SHT31_CMD_SINGLE_MEDIUM_STRETCH);

    COM_Read6Bytes(&raw_temp, &raw_hum);

    *temp_ptr = TemperatureConverter(raw_temp);
    *hum_ptr  = HumidityConverter(raw_hum);

    SHT31_DEBUG("SHT31: Temperature: %f\n", *temp_ptr);
    SHT31_DEBUG("SHT31: Humidity: %f\n", *hum_ptr);
}

/* -- End of file -- */

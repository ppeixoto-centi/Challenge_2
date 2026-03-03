/**
 * Path:    Project/Sensors
 * File:    SHT31.h
 * Author:  CeNTI
 */

#ifndef __PROJECT_SENSORS_SHT31_H__
#define __PROJECT_SENSORS_SHT31_H__

/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */

#include <stdbool.h>
#include <stdint.h>

/* ************************************************************************************ */
/* * Configurations                                                                   * */
/* ************************************************************************************ */

/* SHT31 debug. 0: Disabled; 1: Enabled. */
#define SHT31_DEBUG_LEVEL   (0)

/* ************************************************************************************ */
/* * Enumeration types                                                                * */
/* ************************************************************************************ */

/* SHT31 I2C address configurations. */
typedef enum {
    SHT31_I2C_ADDRESS_GND           = 0x44,
    SHT31_I2C_ADDRESS_VDD           = 0x45,
}et_SHT31_I2C_ADDRESS;

/* SHT31 register addresses. */
typedef enum {
    SHT31_CMD_SINGLE_HIGH_STRETCH   = 0x2400,
    SHT31_CMD_SINGLE_MEDIUM_STRETCH = 0x240B,
    SHT31_CMD_SINGLE_LOW_STRETCH    = 0x2416,
    SHT31_CMD_REPEAT_HIGH_STRETCH   = 0x2C06,
    SHT31_CMD_REPEAT_MEDIUM_STRETCH = 0x2C0D,
    SHT31_CMD_REPEAT_LOW_STRETCH    = 0x2C10,
    SHT31_CMD_SOFTRESET             = 0x30A2,
}et_SHT31_CMD;

/* ************************************************************************************ */
/* * Function types                                                                   * */
/* ************************************************************************************ */

/* I2C Write function type. */
typedef void    (*t_I2C_Write)      (uint8_t   i2c_address,
                                     uint8_t * tx_vec,
                                     uint8_t   tx_vec_size);
/* I2C Read function type. */
typedef void    (*t_I2C_Read)       (uint8_t   i2c_address,
                                     uint8_t * rx_vec,
                                     uint8_t   rx_vec_size);
/* CRC Calculate function type. */
typedef uint8_t (*t_CRC_Calculate)  (const uint8_t * data,
                                     uint8_t   data_size);
/* Delay function type. */
typedef void    (*t_Delay_ms)       (uint16_t msec);

/* ************************************************************************************ */
/* * Structure types                                                                  * */
/* ************************************************************************************ */

/* SHT31 configuration structure. */
typedef struct {
    et_SHT31_I2C_ADDRESS i2c_address;

    t_I2C_Write         I2C_Write;
    t_I2C_Read          I2C_Read;
    t_CRC_Calculate     CRC_Calculate;
    t_Delay_ms          Delay_ms;
}st_SHT31_CONFIG;

/* ************************************************************************************ */
/* * Public Functions Prototypes                                                      * */
/* ************************************************************************************ */

/**
 * @brief Initialize the SHT31 module.
 *
 * @param[in]   config  SHT31 configuration.
 *
 * @return  None.
 */
void SHT31_Initialize(st_SHT31_CONFIG config);

/**
 * @brief Perform a soft reset of the SHT31 sensor.
 *
 * @param  None.
 *
 * @return  None.
 */
void SHT31_SoftReset(void);

/**
 * @brief Get the temperature and humidity data from the SHT31 sensor.
 *
 * @param[out]  temp_ptr   Pointer to the temperature data.
 * @param[out]  hum_ptr    Pointer to the humidity data.
 *
 * @return  None.
 */
void SHT31_GetData(float * temp_ptr,
                   float * hum_ptr);


#endif /* __PROJECT_SENSORS_SHT31_H__ */

/* -- End of file -- */

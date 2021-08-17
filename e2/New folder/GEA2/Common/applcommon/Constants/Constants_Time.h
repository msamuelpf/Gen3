/*!
 * @file
 * @brief Header file for all time-specific constant macro definitions
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef CONSTANTS_TIME_H
#define CONSTANTS_TIME_H

#include <stdint.h>

#define USEC_SEC (uint32_t)(1000000)
#define MSEC_PER_SEC (uint16_t)(1000)
#define SECONDS_PER_MINUTE (uint8_t)(60)
#define MINUTES_PER_HOUR (uint8_t)(60)
#define HOURS_PER_DAY (uint8_t)(24)

#define USEC_PER_MIN ((uint32_t)SECONDS_PER_MINUTE * USEC_SEC)
#define MSEC_PER_MIN ((uint16_t)SECONDS_PER_MINUTE * MSEC_PER_SEC)
#define SECONDS_PER_DAY ((uint32_t)HOURS_PER_DAY * MINUTES_PER_HOUR * SECONDS_PER_MINUTE)
#define SECONDS_PER_HOUR ((uint16_t)MINUTES_PER_HOUR * SECONDS_PER_MINUTE)
#define SECONDS_IN_AM ((uint16_t)12 * MINUTES_PER_HOUR * SECONDS_PER_MINUTE)
#define MINUTES_PER_DAY ((uint16_t)HOURS_PER_DAY * MINUTES_PER_HOUR)

#endif

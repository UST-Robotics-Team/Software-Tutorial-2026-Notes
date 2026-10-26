#ifndef ADC_LAB_CONFIG_H
#define ADC_LAB_CONFIG_H

#define LAB_POLLING 1
#define LAB_DMA 2
#define LAB_CALIBRATION 3
#ifndef LAB_STAGE
#define LAB_STAGE LAB_POLLING
#endif
#define LAB_AXIS_COUNT 4U
#define LAB_REFERENCE_MV 3300U
#define LAB_POLL_TIMEOUT_MS 10U

/* Starting values only. Replace them with your measurement record. */
#define LAB_MINIMA {0U, 0U, 0U, 0U}
#define LAB_CENTRES {2048U, 2048U, 2048U, 2048U}
#define LAB_MAXIMA {4095U, 4095U, 4095U, 4095U}
#define LAB_DEADBAND 120U
/* Logical J1X, J1Y, J2X, J2Y -> DMA buffer entries. Verify experimentally. */
#define LAB_AXIS_INDICES {0U, 1U, 2U, 3U}
#define LAB_AXIS_DIRECTIONS {1, -1, 1, -1}
#endif

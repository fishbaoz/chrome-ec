/* Copyright 2016 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* Configuration for Nuvoton M4 EB */

#ifndef __CROS_EC_BOARD_H
#define __CROS_EC_BOARD_H

/* Optional modules */
#define CONFIG_ADC
#define CONFIG_CHIPSET_RK3399
#define CONFIG_HOSTCMD_SPS
#define CONFIG_I2C
#define CONFIG_I2C_MASTER
#define CONFIG_POWER_COMMON
#define CONFIG_PWM
#define CONFIG_PWM_DISPLIGHT
#ifdef BOARD_KEVIN
#define CONFIG_LED_COMMON
#endif
#define CONFIG_SPI
#define CONFIG_SPI_MASTER

#define CONFIG_SYSTEM_UNLOCKED /* Allow dangerous commands for testing */

/*
 * We are code space-constrained on kevin, so take 4K that is normally used
 * as data RAM (was 30K, now 26K) and use it for code RAM (was 96K, now 100K)
 */
#define RAM_SHIFT_SIZE (4 * 1024)
#undef  CONFIG_RO_SIZE
#define CONFIG_RO_SIZE (NPCX_PROGRAM_MEMORY_SIZE + RAM_SHIFT_SIZE)
#undef  CONFIG_RAM_BASE
#define CONFIG_RAM_BASE (0x200C0000 + RAM_SHIFT_SIZE)
#undef  CONFIG_RAM_SIZE
#define CONFIG_RAM_SIZE (0x00008000 - 0x800 - RAM_SHIFT_SIZE)

/* Optional features */
#define CONFIG_BOARD_VERSION
#define CONFIG_BOARD_SPECIFIC_VERSION
#define CONFIG_BUTTON_COUNT        2
#define CONFIG_FLASH_SIZE          0x00080000 /* 512KB spi flash */
#define CONFIG_KEYBOARD_BOARD_CONFIG
#define CONFIG_KEYBOARD_COL2_INVERTED
#define CONFIG_KEYBOARD_PROTOCOL_MKBP /* Instead of 8042 protocol of keyboard */
#define CONFIG_LTO
#define CONFIG_POWER_BUTTON
#define CONFIG_VBOOT_HASH

#define CONFIG_CHARGER
#define CONFIG_CHARGER_BD99955
#define CONFIG_CHARGER_INPUT_CURRENT 512
#define CONFIG_CHARGER_V2
#define CONFIG_USB_CHARGER

/* Motion Sensors */
#define CONFIG_ACCEL_BMA255
#define CONFIG_ACCELGYRO_BMI160
#undef CONFIG_ACCEL_INTRRUPTS
#define CONFIG_LID_ANGLE
#define CONFIG_LID_ANGLE_SENSOR_BASE    BASE_ACCEL
#define CONFIG_LID_ANGLE_SENSOR_LID     LID_ACCEL

/* USB PD config */
#define CONFIG_CHARGE_MANAGER
#define CONFIG_USB_POWER_DELIVERY
#define CONFIG_USB_PD_5V_EN_ACTIVE_LOW
#define CONFIG_USB_PD_ALT_MODE
#define CONFIG_USB_PD_ALT_MODE_DFP
#define CONFIG_USB_PD_CUSTOM_VDM
#define CONFIG_USB_PD_DUAL_ROLE
#define CONFIG_USB_PD_LOGGING
#define CONFIG_USB_PD_LOG_SIZE 512
#define CONFIG_USB_PD_PORT_COUNT 2
#define CONFIG_USB_PD_TCPM_FUSB302
#define CONFIG_USB_PD_VBUS_DETECT_CHARGER
/* TODO: Enable TRY_SRC */
#undef CONFIG_USB_PD_TRY_SRC

#define CONFIG_BATTERY_CUT_OFF
#define CONFIG_BATTERY_PRESENT_GPIO GPIO_EC_BATT_PRES_L
#define CONFIG_BATTERY_SMART

/* TODO: Allow higher voltage charging */
#define PD_OPERATING_POWER_MW 15000
#define PD_MAX_POWER_MW       15000
#define PD_MAX_CURRENT_MA     3000
#define PD_MAX_VOLTAGE_MV     5000

/* TODO: determine the following board specific type-C power constants */
#define PD_POWER_SUPPLY_TURN_ON_DELAY  30000  /* us */
#define PD_POWER_SUPPLY_TURN_OFF_DELAY 250000 /* us */

/* start as a sink in case we have no other power supply/battery */
#define PD_DEFAULT_STATE PD_STATE_SNK_DISCONNECTED

/* Optional features for test commands */
#define CONFIG_CMD_ACCELS
#define CONFIG_CMD_ACCEL_INFO
#define CONFIG_CMD_TASKREADY
#define CONFIG_CMD_STACKOVERFLOW
#define CONFIG_CMD_JUMPTAGS
#define CONFIG_CMD_SPI_XFER

#define CONFIG_UART_HOST                0

/* Optional feature - used by nuvoton */
#define NPCX_UART_MODULE2    1 /* 0:GPIO10/11 1:GPIO64/65 as UART */
#define NPCX_JTAG_MODULE2    0 /* 0:GPIO21/17/16/20 1:GPIOD5/E2/D4/E5 as JTAG*/
#define NPCX_TACH_SEL2       0 /* 0:GPIO40/A4 1:GPIO93/D3 as TACH */
/* Enable SHI PU on transition to S0. Disable the PU otherwise for leakage. */
#define NPCX_SHI_CS_PU
#define NPCX_SHI_BYPASS_OVER_256B

/* Optional for testing */
#undef  CONFIG_PECI
#undef  CONFIG_PSTORE
#undef  CONFIG_LOW_POWER_IDLE           /* Deep Sleep Support */

#define I2C_PORT_TCPC0    NPCX_I2C_PORT0_0
#define I2C_PORT_TCPC1    NPCX_I2C_PORT0_1
#define I2C_PORT_ACCEL    NPCX_I2C_PORT1
#define I2C_PORT_CHARGER  NPCX_I2C_PORT2
#define I2C_PORT_BATTERY  NPCX_I2C_PORT3

/* Enable Accel over SPI */
#define CONFIG_SPI_ACCEL_PORT    0  /* SPI master port (SPIP) form BMI160 */

#define CONFIG_MKBP_EVENT
/* Define the MKBP events which are allowed to wakeup AP in S3. */
#define CONFIG_MKBP_WAKEUP_MASK \
		(EC_HOST_EVENT_MASK(EC_HOST_EVENT_LID_CLOSED) |\
		 EC_HOST_EVENT_MASK(EC_HOST_EVENT_LID_OPEN) |\
		 EC_HOST_EVENT_MASK(EC_HOST_EVENT_POWER_BUTTON) |\
		 EC_HOST_EVENT_MASK(EC_HOST_EVENT_KEY_PRESSED) |\
		 EC_HOST_EVENT_MASK(EC_HOST_EVENT_RTC))

#ifndef __ASSEMBLER__

enum adc_channel {
	/* No VBUS ADC channel on kevin */
	ADC_VBUS = -1,
	/* Real ADC channels begin here */
	ADC_BOARD_ID = 0,
	ADC_PP900_AP,
	ADC_PP1200_LPDDR,
	ADC_PPVAR_CLOGIC,
	ADC_PPVAR_LOGIC,
	ADC_CH_COUNT
};

enum pwm_channel {
#ifdef BOARD_KEVIN
	PWM_CH_LED_GREEN,
#endif
	PWM_CH_DISPLIGHT,
	PWM_CH_LED_RED,
#ifdef BOARD_KEVIN
	PWM_CH_LED_BLUE,
#endif
	/* Number of PWM channels */
	PWM_CH_COUNT
};

/* power signal definitions */
enum power_signal {
	PP5000_PWR_GOOD = 0,
	SYS_PWR_GOOD,
	AP_PWR_GOOD,
	SUSPEND_DEASSERTED,

	/* Number of signals */
	POWER_SIGNAL_COUNT,
};

/* Motion sensors */
enum sensor_id {
	BASE_ACCEL = 0,
	BASE_GYRO,
	LID_ACCEL,
};

#include "gpio_signal.h"
#include "registers.h"

void board_reset_pd_mcu(void);
int board_get_version(void);

#endif /* !__ASSEMBLER__ */

#endif /* __CROS_EC_BOARD_H */

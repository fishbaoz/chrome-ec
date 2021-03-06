/* -*- mode:c -*-
 *
 * Copyright 2016 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* Declare symbolic names for all the GPIOs that we care about.
 * Note: Those with interrupt handlers must be declared first. */

/* Outputs */
GPIO(LED_GREEN,   PIN(B, 2), GPIO_OUT_LOW)
GPIO(LED_RED,    PIN(C, 1), GPIO_OUT_LOW)

/* Unimplemented signals which we need to emulate for now */
UNIMPLEMENTED(ENTERING_RW)
UNIMPLEMENTED(WP_L)

ALTERNATE(PIN_MASK(B, 0xC0), GPIO_ALT_F7, MODULE_UART,  0) /* USART1: PB6/7 */
ALTERNATE(PIN_MASK(G, 0x0180), GPIO_ALT_F8, MODULE_UART,  0) /* LPUART: PG7/8 */
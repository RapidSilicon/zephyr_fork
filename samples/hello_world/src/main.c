/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>

int main(void)
{
	int Cnt = 0;

	while(true) {
		printf("%d - Hello World! %s\n", Cnt++, CONFIG_BOARD_TARGET);
		k_msleep(1000);
	}

	return 0;
}

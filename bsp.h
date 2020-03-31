/*
 * bsp.h
 *
 *  Created on: Mar 31, 2020
 *      Author: burak.kirazli
 */

#ifndef BSP_H_
#define BSP_H_

//todo: implement according to your architecture

#include <stdio.h>

static inline void led_on(void)
{
	printf("LED ON\r\n");
}

static inline void led_off(void)
{
	printf("LED OFF\r\n");
}

static inline void led_toggle(void)
{

}

#endif /* BSP_H_ */

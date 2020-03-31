/*
 * main.c
 *
 *  Created on: Mar 31, 2020
 *      Author: burak.kirazli
 */

#include "sm.h"
#include "bsp.h"

//1-define event ids
enum event_id
{
	EVT_ID_TIMEOUT = EVT_ID_APP,
};

//2-declare handlers
DECLHANDLER(top);
DECLHANDLER(on);
DECLHANDLER(off);

//3-define states using handler declarations.
DEFSTATE(NO_PARENT, 	top);
DEFSTATE(STATEREF(top), on);
DEFSTATE(STATEREF(top), off);

//4-create state table
const state_t* table[] =
{
		STATEREF(top),
		STATEREF(on),
		STATEREF(off)
};

//5-top most initial handler
int topmost_initial_handler(machine_t* mach)
{
	return TRANSIT(STATE(on));
}

//6-create instance
machine_t machine;

//7-define handlers
DEFHANDLER(top)
{
	int result = UNHANDLED();

	switch(e.id)
	{

	default:
		break;
	}

	return result;
}

DEFHANDLER(on)
{
	int result = UNHANDLED();

	switch(e.id)
	{

	case EVT_ID_ENTRY:
	{
		led_on();
	}
		break;

	case EVT_ID_TIMEOUT:
	{
		result = TRANSIT(STATE(off));
	}
		break;

	default:
		break;
	}

	return result;
}

DEFHANDLER(off)
{
	int result = UNHANDLED();

	switch(e.id)
	{

	case EVT_ID_ENTRY:
	{
		led_off();
	}
		break;

	case EVT_ID_TIMEOUT:
	{
		result = TRANSIT(STATE(on));
	}
		break;

	default:
		break;
	}

	return result;
}


int main(void)
{
	//8-initialize machine
	sm_init(&machine, table, sizeof(table)/sizeof(table[0]), topmost_initial_handler);

	//9-start machine
	sm_start(&machine);

	//10-post events sequentially, assume timeout occured
	event_t e = MAKE_NAKED_EVT(EVT_ID_TIMEOUT);
	sm_process(&machine, e);
	sm_process(&machine, e);
	sm_process(&machine, e);
	sm_process(&machine, e);
	sm_process(&machine, e);
	sm_process(&machine, e);

	return 0;
}


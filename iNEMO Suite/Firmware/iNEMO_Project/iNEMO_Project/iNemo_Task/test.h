/**
 * \file test.h
 *
 *  Created on: Oct 9, 2009
 *      Author: Stefano Oliveri
 */

#ifndef TEST_H_
#define TEST_H_

/* Task priorities. */
#define TEST_TASK_PRIORITY			( configMAX_PRIORITIES-1 )

/* Task stack. */
#define TEST_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE )


void testInitTask(void *pvParameters);
void testStartTask(void *pvParameters);

#endif /* TEST_H_ */

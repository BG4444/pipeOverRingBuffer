/*
 * ringBuffer.h
 *
 *  Created on: 20 окт. 2014 г.
 *      Author: bg
 */

#ifndef INC_RINGBUFFER_H_
#define INC_RINGBUFFER_H_
#include <inttypes.h>

typedef struct _block
{
	char data[128];
} block;

typedef struct _ringbuffer
{
	volatile int32_t head;
	volatile int32_t tail;
	int32_t size;
	block* first;
} ringBuffer;

void initRingBuffer(ringBuffer* rb,uint32_t size,block* first);

block* consume(ringBuffer* rb);

block* getCurrent(ringBuffer* rb);

void commitCurrent(ringBuffer* rb);

int32_t getReadyCount(ringBuffer* rb);

void commitConsumer(ringBuffer* rb);

inline void cycle(int32_t* in,int32_t max);
#endif /* INC_RINGBUFFER_H_ */

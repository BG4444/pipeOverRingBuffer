#include "ringBuffer.h"
#include "assert.h"
void initRingBuffer(ringBuffer* rb,uint32_t size,block* first)
{
	rb->size=size;
	rb->head=0;
	rb->tail=0;
	rb->first=first;
}

void cycle(int32_t* volatile in,int32_t max)
{
	(*in)++;
	if(*in==max)
	{
		*in=0;
	}

}


block* consume(ringBuffer* rb)
{
	block* ret=&rb->first[rb->head];
    cycle(&(rb->head),rb->size);
	return(ret);

}

block* getCurrent(ringBuffer* rb)
{
	return(&rb->first[rb->tail]);
}


int32_t getReadyCount(ringBuffer* rb)
{
	volatile const int32_t head=rb->head;
	volatile const int32_t tail=rb->tail;
	int32_t count=(tail-head) % rb->size;
	if(count < 0)
	{
		count+=rb->size;
	}
	return(count);
}

void commitCurrent(ringBuffer* rb)
{
	const int32_t count=getReadyCount(rb);
	if ( count <(rb->size-1))
	{
		cycle(&rb->tail,rb->size);
	}
}

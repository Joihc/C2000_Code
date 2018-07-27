#define QUEUE_C_
#include "queue.h"

void QueueInit(struct FifoQueue *Queue)
{
    Queue->front = Queue->rear;
    Queue->count = 0;
}
// Queue In
Uint8 QueueIn(struct FifoQueue *Queue,Uint8 sdat)
{
    if((Queue->front == Queue->rear) && (Queue->count == QueueSize))
    {                    // full
        return QueueFull;
    }else
    {                    // in
        Queue->dat[Queue->rear] = sdat;
        Queue->rear = (Queue->rear + 1) % QueueSize;
        Queue->count = Queue->count + 1;
        return QueueOperateOk;
    }
}
// Queue Out
Uint8 QueueOut(struct FifoQueue *Queue,Uint8 *sdat)
{
    if((Queue->front == Queue->rear) && (Queue->count == 0))
    {                    // empty
        return QueueEmpty;
    }else
    {                    // out
        *sdat = Queue->dat[Queue->front];
        Queue->front = (Queue->front + 1) % QueueSize;
        Queue->count = Queue->count - 1;
        return QueueOperateOk;
    }
}
void QueueCheckOut(struct FifoQueue *Queue,Uint8 sdat)
{
	Uint8 temp = QueueOperateOk;
	if((Queue->front == Queue->rear) && (Queue->count == 0))
	{                    // empty
	       return;
	}
	while(Queue->dat[Queue->front] != sdat && temp!=QueueEmpty)
	{
		temp = QueueOut(Queue,&temp);
	}
}
///////////////////////////////////////////////////////////////////////
void FirQueueInit(struct FirQueue *Queue)
{
	Uint8 i;
    Queue->pdata = 0;
    Queue->pmax = 0;
    Queue->pmin = 0;
    for(i=0;i<FIR_LEN;i++)
    {
    	Queue->dat[i] = 0;
    }
}

Uint16 FirQueueCal(struct FirQueue *Queue)
{
	Uint8 i;
	Uint32 average=0;
	for(i=0;i<FIR_LEN;i++)
		average+=Queue->dat[i];
	average=average-Queue->dat[Queue->pmax]-Queue->dat[Queue->pmin];

	return (average>>FIR_SHIFT);
}
void FirQueueIn(struct FirQueue *Queue,Uint16 data)
{
	Uint8 i;
	Queue->pdata=(Queue->pdata+1)%FIR_LEN;
	Queue->dat[Queue->pdata]=data;

	if(data>Queue->dat[Queue->pmax])
		Queue->pmax=Queue->pdata;
	else if(data<Queue->dat[Queue->pmin])
		Queue->pmin=Queue->pdata;

	if(Queue->pdata==Queue->pmax)
	{
		for(i=0;i<FIR_LEN;i++)
          if(Queue->dat[i]>Queue->dat[Queue->pmax])
        	  Queue->pmax=i;
	}
	else if(Queue->pdata==Queue->pmin)
	{
		for(i=0;i<FIR_LEN;i++)
          if(Queue->dat[i]<Queue->dat[Queue->pmin])
        	  Queue->pmin=i;
	}
}

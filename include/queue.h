#ifndef QUEUE_H_
#define QUEUE_H_

#include "config.h"

#ifndef QUEUE_C_
#endif

#define QueueSize      20
#define QueueFull      0
#define QueueEmpty     1
#define QueueOperateOk 2
struct FifoQueue
{
    Uint16 front;
    Uint16 rear;
    Uint16 count;
    Uint8  dat[QueueSize];
};
//Queue Initalize
extern void QueueInit(struct FifoQueue *Queue);
// Queue In
extern Uint8 QueueIn(struct FifoQueue *Queue,Uint8 sdat);
// Queue Out
extern Uint8 QueueOut(struct FifoQueue *Queue,Uint8 *sdat);

extern void QueueCheckOut(struct FifoQueue *Queue,Uint8 sdat);

/////////////////////////////////////////////////////////////////
//FIR_LEN=2^FIR_SHIFT+2， k为整数
#define FIR_LEN  18   //移动算术平均的个数+2=SHIFT<<2+2
#define FIR_SHIFT 4   //2^SHIFT

struct FirQueue
{
    Uint16 pdata;
    Uint16 pmin;
    Uint16 pmax;
    Uint16 dat[FIR_LEN];
};
void FirQueueInit(struct FirQueue *Queue);
Uint16 FirQueueCal(struct FirQueue *Queue);
void FirQueueIn(struct FirQueue *Queue,Uint16 data);
#endif


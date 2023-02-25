#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct queuenode {
  void* info;
  struct queuenode* next;
} QueueNode;

typedef struct{
  QueueNode* front;
  QueueNode* back;
} Queue;

extern void  QueueInsert(Queue* queue, void* info);
extern void* QueueDelete(Queue* queue);
extern int   QueueEmpty (Queue* queue);

#endif
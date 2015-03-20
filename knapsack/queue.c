/***************************************************************************
 *             queue.c
 * 
 *   Mon Jul 13 20:13:22 2009
 *   Copyright  2009  Pedro Henrique Neves da Silva
 *   Email: ptersnow@gmail.com
 *
 ***************************************************************************/

#ifndef __QUEUE_H
#include "queue.h"
#endif

void begin(int n)
{
  size = 0;
  q = (node *)calloc(n, sizeof(node));
}

void pop()
{
  size--;
}

void print()
{
  int i;

  for(i = 0; i < size; i++)
    printf("%d %d %d %d %f\n", i, q[i].l, q[i].v, q[i].w, q[i].bound);
}

void push(node n)
{
  q[size].l = n.l;
  q[size].v = n.v;
  q[size].w = n.w;
  q[size++].bound = n.bound;
}


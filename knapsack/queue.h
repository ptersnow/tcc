/***************************************************************************
 *             queue.h
 * 
 *   Mon Jul 13 20:13:22 2009
 *   Copyright  2009  Pedro Henrique Neves da Silva
 *   Email: ptersnow@gmail.com
 *
 ***************************************************************************/

#ifndef __QUEUE_H
#define __QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int l, v, w;
  float bound;
} node;

node *q;
int size;


void pop();
void print();
void push(node n);
void begin(int n);


#endif

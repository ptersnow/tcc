/***************************************************************************
 *             knapgen.h
 * 
 *   Mon Jul 13 21:00:22 2009
 *   Copyright  2009  Pedro Henrique Neves da Silva
 *   Email: ptersnow@gmail.com
 *
 ***************************************************************************/

#ifndef __KNAPGEN_H
#define __KNAPGEN_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct pheno{
  u_short *cromo;
  int profit, weight;
  double pfitness, wfitness;
} pheno;

pheno *cur, *old;
int csize, gsize, psize;

int *v, *w, W, n;
int maxprofit;

void swap();
void print();
void begin();
int roulette();
void selection();
void cross_over();
void sort(int psize);
int compare(const void *va, const void *vb);

#endif

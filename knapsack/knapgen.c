/***************************************************************************
 *             Genetic Knapsack
 * 
 *   Fri Mai 15 09:22:22 2009
 *   Copyright  2009  Pedro Henrique Neves da Silva
 *   Email: ptersnow@gmail.com
 *
 ***************************************************************************/

#ifndef __KNAPGEN_H
#include "knapgen.h"
#endif

void swap()
{
  pheno *tmp;

  tmp = cur;
  cur = old;
  old = tmp;
}

void begin()
{
  int i, j;

  csize = n;

  cur = (pheno *)calloc(psize+1, sizeof(pheno));
  old = (pheno *)calloc(psize+1, sizeof(pheno));

  srand(time(NULL));

  for(i = 0; i < psize; i++) {
    
    cur[i].cromo = (u_short *)calloc(csize+1, sizeof(u_short));
    old[i].cromo = (u_short *)calloc(csize+1, sizeof(u_short));

    j = 1;
    cur[i].weight = 0;
    while((j < csize) && (cur[i].weight <= W)) {
      if((rand() % 2) && (cur[i].weight + w[j] <= W)) {
	cur[i].cromo[j] = 1;
	cur[i].weight += w[j];
      }
      j++;
    }
  }

  cur[psize].cromo = (u_short *)calloc(csize+1, sizeof(u_short));
  old[psize].cromo = (u_short *)calloc(csize+1, sizeof(u_short));
}

void cross_over()
{
  int i, j, k;
  u_short temp;

  for(i = 0; i < psize; i+=2) {
    if((rand() % 101) <= 75) {
      k = rand() % csize + 1;
      for(j = 1; j <= k; j++) {
	temp = cur[i].cromo[j];
	cur[i].cromo[j] = cur[i+1].cromo[j];
	cur[i+1].cromo[j] = temp;
      }
    }

    for(j = 1; j <= csize; j++)
      if((rand() % 101) <= 5)
	cur[i].cromo[j] = 1 - cur[i].cromo[j];
  }
}

void selection()
{
  int i, j;
  int *sel;

  sel = (int *)calloc(psize, sizeof(int));
  for(i = 0; i < psize; i++)
    sel[i] = roulette();
  
  for(i = 0; i < psize; i++)
    for(j = 1; j <= csize; j++)
      cur[i].cromo[j] = old[sel[i]].cromo[j];

  free(sel);
}

int roulette()
{
  int i;
  double p, w;

  p = ((double)(rand()%10000)/10000.0) * (maxprofit / psize);
  w = ((double)(rand()%10000)/10000.0) * (W / psize);
  for(i = 0; i < psize; i++) {
    if((old[i].pfitness < p) && (old[i].wfitness < w))
      return i;
  }
  
  return psize-1;
}

void sort(int size)
{
  int i, j;

  maxprofit = 0;

  for(i = 0; i < size; i++) {
    cur[i].pfitness = 0;
    cur[i].wfitness = 0;
    cur[i].profit = 0;
    cur[i].weight = 0;
    for(j = 1; j <= csize; j++) {
      if(cur[i].cromo[j]) {
	cur[i].profit += v[j];
	cur[i].weight += w[j];
      }
    }
      
    if(cur[i].weight > W)
      cur[i].weight = -(cur[i].weight - W);

    if(maxprofit < cur[i].profit)
      maxprofit = cur[i].profit;
  }

  for(i = 0; i < size; i++) {
    cur[i].pfitness = 1 - (cur[i].profit / maxprofit) / psize;
    cur[i].wfitness = (cur[i].weight / W) / psize;
  }

  qsort(cur, size, sizeof(pheno), compare);
}

int compare(const void *va, const void *vb)
{
  pheno a = *(pheno *)va;
  pheno b = *(pheno *)vb;

  if((a.weight < 0) || (a.weight > W)) {
    if((b.weight < 0) || (b.weight > W))
      return 0;
    else return 1;
  }

  if((b.weight < 0) || (b.weight > W))
    return -1;

  return -(a.profit - b.profit);
}

int main(int argc, char *args[])
{
  FILE *in;
  int i, j, **knap;
  float mili, nano;
  struct timespec tm, tm2;

  if(argc != 4) {
    printf("Usage: ./gen <file> <psize> <gsize>\n");
    return 0;
  }

  in = fopen(args[1], "r+");
  if(in == NULL)
    perror("Error opening file");

  psize = atoi(args[2]);
  gsize = atoi(args[3]);

  fscanf(in, "%d", &W);
  fscanf(in, "%d", &n);

  printf("%-4d\n", W);

  while(n != 0) {
    v = (int*)calloc (n+1, sizeof(int));
    w = (int*)calloc (n+1, sizeof(int));

    for(i = 1; i <= n; i++)
      fscanf(in, "%d, %d", &v[i], &w[i]);

    knap = (int**)calloc (n+1, sizeof(int));
    for(i = 0; i <= n; i++)
      knap[i] = (int*)calloc (W+1, sizeof(int));

    for(j = 0; j < W; j++)
      knap[0][j] = 0;
    for(i = 1; i <= n; i++) {
      knap[i][0] = 0;
      for(j = 1; j <= W; j++) {
	if(w[i] <= j) {
	  if(v[i] + knap[i-1][j-w[i]] > knap[i-1][j])
	    knap[i][j] = v[i] + knap[i-1][j-w[i]];
	  else knap[i][j] = knap[i-1][j];
	}
	else knap[i][j] = knap[i-1][j];
      }
    }

    clock_gettime(CLOCK_REALTIME, &tm);

    begin();
    sort(psize);
    for(i = 1; i < gsize; i++) {
      swap();
      selection();
      cross_over();
      cur[psize] = old[0];
      sort(psize + 1);

      if(((float)knap[n][W] / (float)cur[0].profit) < 1.5)
	break;
    }
    
    clock_gettime(CLOCK_REALTIME, &tm2);
        
    mili = (float)( ( tm2.tv_sec - tm.tv_sec ) * 1000.0 );
    nano = (float)( ( tm2.tv_nsec - tm.tv_nsec ) / 1000000.0 );
    printf("\t n=%-4d \t cur=%-4d wt=%-4d \t time=%f \t", n, cur[0].profit, cur[0].weight, (nano+mili)/1000.0f);
    printf("knap=%-4d \t div=%2.5f \n", knap[n][W], ((float)knap[n][W] / (float)cur[0].profit));

    free(v);
    free(w);
    
    for(i = 0; i <= n; i++)
      free(knap[i]);

    free(knap);
    free(cur);
    free(old);

    fscanf(in, "%d", &n);
  }
  fclose(in);

  return 0;
}

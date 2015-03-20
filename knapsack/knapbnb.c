/***************************************************************************
 *             Branch and Bound Knapsack
 * 
 *   Mon Jul 13 20:13:22 2009
 *   Copyright  2009  Pedro Henrique Neves da Silva
 *   Email: ptersnow@gmail.com
 *
 ***************************************************************************/

#include <time.h>

#include "queue.h"

float bound(node u, int *v, int *w, int n, int W)
{
  float result;
  int i, j, total;
  
  if(u.w >= W)
    return 0;
  else {
    result = u.v;
    i = u.l + 1;
    total = u.w;

    while(i <= n && (total + w[i] <= W)) {
      total += w[i];
      result += v[i];
      i++;
    }

    j = i;
    if(j <= n)
      result += (W - total) * v[j]/w[j];

    return result;
  }
}

int bnb(int *p, int *w, int n, int W)
{
  node u, v;
  int maxprof;

  begin(n);
  v.l = v.v = v.w = 0;
  maxprof = 0;
  v.bound = bound(v, p, w, n, W);
  push(v);

  while(size != 0) {

    pop();
    v.v = q[size].v;
    v.w = q[size].w;
    v.l = q[size].l;
    v.bound = q[size].bound;

    if(v.bound > maxprof) {
      u.l = v.l + 1;
      u.w = v.w + w[u.l];
      u.v = v.v + p[u.l];

      if(u.w <= W && u.v > maxprof)
	maxprof = u.v;

      u.bound = bound(u, p, w, n, W);
      if(u.bound > maxprof)
	push(u);

      u.w = v.w;
      u.v = v.v;
      u.bound = bound(u, p, w, n, W);
      if(u.bound > maxprof)
	push(u);
    }
  }
  
  return maxprof;
}

int main(int argc, char *args[])
{
  FILE *in;
  int *v, *w;
  float mili, nano;
  struct timespec tm, tm2;
  int a = 0, i, n, W;

  in = fopen(args[1], "r+");
  if(in == NULL)
    perror("Error opening file");

  fscanf(in, "%d", &W);
  fscanf(in, "%d", &n);

  printf("%d\n", W);
	
  while(n) {

    v = (int*)calloc (n+1, sizeof(int));
    w = (int*)calloc (n+1, sizeof(int));

    for(i = 1; i <= n; i++)
      fscanf(in, "%d, %d", &v[i], &w[i]);

    clock_gettime(CLOCK_REALTIME, &tm);
    a = bnb(v, w, n, W);
    clock_gettime(CLOCK_REALTIME, &tm2);
    mili = (float)( ( tm2.tv_sec - tm.tv_sec ) * 1000.0 );
    nano = (float)( ( tm2.tv_nsec - tm.tv_nsec ) / 1000000.0 );
    printf("\t %-4d \t %-4d \t %f\n", n, a, (nano+mili)/1000.0f);
		
    free(v);
    free(w);

    fscanf(in, "%d", &n);
  }
  fclose(in);

  return 0;
}

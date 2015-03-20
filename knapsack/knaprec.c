/***************************************************************************
 *             Recursive Knapsack
 * 
 *   Tue Mar 10 17:33:22 2009
 *   Copyright  2009  Pedro Henrique Neves da Silva
 *   Email: ptersnow@gmail.com
 *
 ***************************************************************************/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int knapsack(int a, int b, int *v, int *w, int n, int W)
{
  if(n == 0)
    return 0;

  a = knapsack(a, b, v, w, n-1, W);
  if(w[n] > W)
    return a;
  else {
    b = v[n] + knapsack(a, b, v, w, n-1, W-w[n]);
    if(a > b)
      return a;
    else return b;
  }
}

int main(int argc, char *args[])
{
  FILE *in;
  int *v, *w;
  float mili, nano;
  int a = 0, b = 0, i, W, n;
  struct timespec tm, tm2;

  in = fopen(args[1], "r+");
  if(in == NULL)
    perror("Error opening file");

  fscanf(in, "%d", &W);
  fscanf(in, "%d", &n);

  printf("%-4d\n", W);

  while(n != 0) {

    v = (int*)calloc (n+1, sizeof(int));
    w = (int*)calloc (n+1, sizeof(int));

    for(i = 1; i <= n; i++)
      fscanf(in, "%d, %d", &v[i], &w[i]);

    clock_gettime(CLOCK_REALTIME, &tm);
    a = knapsack(a, b, v, w, n, W);

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

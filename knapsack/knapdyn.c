/***************************************************************************
 *             Dynamic Knapsack
 * 
 *   Tue Mar 10 17:33:22 2009
 *   Copyright  2009  Pedro Henrique Neves da Silva
 *   Email: ptersnow@gmail.com
 *
 ***************************************************************************/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *args[])
{
  FILE *in;
  int i, j, W, n;
  int **knap, *v, *w;
  float mili, nano;
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
    knap = (int**)calloc (n+1, sizeof(int));
    for(i = 0; i <= n; i++)
      knap[i] = (int*)calloc (W+1, sizeof(int));
    for(i = 1; i <= n; i++)
      fscanf(in, "%d, %d", &v[i], &w[i]);

    clock_gettime(CLOCK_REALTIME, &tm);

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
    
    clock_gettime(CLOCK_REALTIME, &tm2);
    mili = (float)( ( tm2.tv_sec - tm.tv_sec ) * 1000.0 );
    nano = (float)( ( tm2.tv_nsec - tm.tv_nsec ) / 1000000.0 );
    printf("\t %-4d \t %-4d \t %f\n", n, knap[n][W], (nano+mili)/1000.0f);

    for(i = 0; i <= n; i++)
      free(knap[i]);
    free(v);
    free(w);

    fscanf(in, "%d", &n);
  }
  fclose(in);

  return 0;
}

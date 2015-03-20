/***************************************************************************
 *             generator.c
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
  FILE *out, *app;
  int i, j, k, n = 10, nc, *v, *w, *pw, W, tmp;

  out = fopen("sample", "w+");
  app = fopen("sample1", "a+");
  if(out == NULL)
    perror("Error opening file");
  if(app == NULL)
    perror("Error opening file");
  
  srand(time(NULL));
  W = rand() % 100 + 50; /* Tamanho da mochila. */
  fprintf(out, "%d\n", W);
  fprintf(app, "%d\n", W);

  for(i = 0; i < n; i++) { /* Número de caso de teste. n == 10*/
    nc = rand() % W + 5; /* Número de objetos. */
    fprintf(out, "%d\n", nc);
    fprintf(app, "%d\n", nc);
    v = (int *)calloc(nc, sizeof(int));
    w = (int *)calloc(nc, sizeof(int));
    pw = (int *)calloc(nc, sizeof(int));

    for(j = 0; j < nc; j++) {
      v[j] = rand() % 100 + 10; /* Benefício de cada objeto. */
      w[j] = rand() % (W/2) + 10; /* Peso de cada objeto. */
      pw[j] = v[j]/w[j];
    }

    for(j = 0; j < nc; j++)
      for(k = j; k < nc; k++)
	if(pw[j] < pw[k]) {
	  tmp = pw[j];
	  pw[j] = pw[k];
	  pw[k] = tmp;

	  tmp = w[j];
	  w[j] = w[k];
	  w[k] = tmp;

	  tmp = v[j];
	  v[j] = v[k];
	  v[k] = tmp;
	}
    
    for(j = 0; j < nc; j++) {
      fprintf(out, "%d, %d\n", v[j], w[j]);
      fprintf(app, "%d, %d\n", v[j], w[j]);
    }
  }
  fprintf(out, "0\n");
  fprintf(app, "0 <===================\n");
  fclose(out);
  fclose(app);

  return 0;
}

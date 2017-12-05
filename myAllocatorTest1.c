#include "stdio.h"
#include "stdlib.h"
#include "myAllocator.h"
#include "sys/time.h"
#include <sys/resource.h>
#include <unistd.h>

double diffTimeval(struct timeval *t1, struct timeval *t2) {
  double d = (t1->tv_sec - t2->tv_sec) + (1.0e-6 * (t1->tv_usec - t2->tv_usec));
  return d;
}

void getutime(struct timeval *t)
{
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  *t = usage.ru_utime;
}

int main() 
{
  void *p1, *p2, *p3, *p4, *p5,*p6,*p7;
  arenaCheck();
  p1 = firstFitAllocRegion(254);
  arenaCheck();
  p2 = firstFitAllocRegion(180);
  arenaCheck();
  p3 = firstFitAllocRegion(254);
  //printf("%8zx %8zx %8zx\n", p1, p2, p3);
  arenaCheck();
  //freeRegion(p2);
  //arenaCheck();
  //p1 = resizeRegion(p1,1000);
  //arenaCheck();
  p4 = firstFitAllocRegion(100);
  arenaCheck();
  p5 = firstFitAllocRegion(254);
  arenaCheck();
  freeRegion(p2);
  arenaCheck();
  freeRegion(p4);
  arenaCheck();
  printf("\n This is bestFit of 100 gets placed in 4 slot\n\n");
  p6 = bestFitAllocRegion(100); //it gets added to best fit which is where p4 use to be
  arenaCheck();
  freeRegion(p6);
  arenaCheck();
  printf("\n This is firstFit of 100 gets placed in 2 slot\n\n");
  p6 = bestFitAllocRegion(100);
  arenaCheck();
  printf("\n This is resize of 100 to 168 gets placed in 2 slot insted of bottom\n\n");
  p6 = resizeRegion(p6,168);//if you put any higher than 168 it will allocate in new memory slot becuase currently it has 104 and since next block only has 64 usable mem while the rest is use for prefix and sufix a total of 184. so when allocated 168 it will dispaly 184 since it getting rid of one prefix and sufix for extra 16 mem
  arenaCheck();
  p7 = bestFitAllocRegion(2000);
  arenaCheck();
  freeRegion(p6);
  arenaCheck();
  freeRegion(p1);
  arenaCheck();
  freeRegion(p3);
  arenaCheck();
  freeRegion(p5);
  arenaCheck();
  freeRegion(p7);
  arenaCheck();
  {				/* measure time for 10000 mallocs */
    struct timeval t1, t2;
    int i;
    getutime(&t1);
    for(i = 0; i < 10000; i++)
      if (firstFitAllocRegion(4) == 0) 
	break;
    getutime(&t2);
    printf("%d firstFitAllocRegion(4) required %f seconds\n", i, diffTimeval(&t2, &t1));
  }
  return 0;
}




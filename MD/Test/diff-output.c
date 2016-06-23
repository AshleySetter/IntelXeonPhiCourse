/*
 * $Id: control.f,v 1.2 1994/11/10 17:36:33 spb Exp $
 *
 * program to diff the output of the MD program
 *
 */
#include <stdio.h>
#include <math.h>

#define  Nbody 4*1024

int main(int argc, char *argv[]){
int i;
double q1,q2,q3,q4,q5,q6,q7,q8;
double t1,t2,t3,t4,t5,t6,t7,t8;
double d1,d2,d3,d4,d5,d6,d7,d8, dt;
double max;
FILE *in, *in2;
int status=0;

  if(argc != 3 ){
    fprintf(stderr,"useage:%s file1 file2\n",argv[0]);
    exit(1);
  }
/* read the initial data from a file */

  in = fopen(argv[1],"r");

  if( ! in ){
    perror(argv[1]);
    exit(1);
  }

  in2 = fopen(argv[2],"r");

  if( ! in2 ){
    perror(argv[2]);
    exit(1);
  }



  max=0.0;
  for(i=0;i<Nbody;i++){
    fscanf(in,"%13le%13le%13le%13le%13le%13le%13le%13le\n",
      &q1,&q2,&q3,&q4,&q5,&q6,&q7,&q8);

    fscanf(in2,"%13le%13le%13le%13le%13le%13le%13le%13le\n",
      &t1,&t2,&t3,&t4,&t5,&t6,&t7,&t8);
      
        d1 = fabs((t1 -  q1)/q1);
        d2 = fabs((t2 -  q2)/ q2);
        d3 = fabs((t3 -  q3)/ 2000.0);
        d4 = fabs((t4 -  q4)/ 2000.0);
        d5 = fabs((t5 -  q5)/ 2000.0);
        d6 = fabs((t6 -  q6)/ 10.0);
        d7 = fabs((t7 -  q7)/ 10.0);
        d8 = fabs((t8 -  q8)/ 10.0);
        dt = d1+d2+d3+d4+d5+d6+d7+d8;

        if( dt > max ){ max = dt; }
    if( dt > 0.05 ){ 
    printf("%d< %13.5E%13.5E%13.5E%13.5E%13.5E%13.5E%13.5E%13.5E\n",i,
      q1,q2,q3,q4,q5,q6,q7,q8);
    printf("%d> %13.5E%13.5E%13.5E%13.5E%13.5E%13.5E%13.5E%13.5E\n",i,
      t1,t2,t3,t4,t5,t6,t7,t8);
    printf("%d: %13.5E%13.5E%13.5E%13.5E%13.5E%13.5E%13.5E%13.5E\n",i,
      d1,d2,d3,d4,d5,d6,d7,d8);
    printf("%d:%f %13.5E%13.5E%13.5E%13.5E%13.5E%13.5E%13.5E%13.5E\n",i,dt,
      q1-t1,q2-t2,
      q3-t3,q4-t4,q5-t5,q6-t6,q7-t7,q8-t8);
	}
  }
  fclose(in);
  fclose(in2);

  printf("max=%f\n",max);
  if( max > 0.05 ){
     return 1;
  }else{
    return 0;
  }
}

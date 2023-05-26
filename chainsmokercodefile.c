#include <stdio.h>
#include <unistd.h> /* Symbolic Constants */
#include <sys/types.h> /* Primitive System Data Types */
#include <errno.h> /* Errors */
#include <stdio.h> /* Input/Output */
#include <stdlib.h> /* General Utilities */
#include <pthread.h> /* POSIX Threads */
#include <string.h> /* String handling */
#include <semaphore.h> /* Semaphore */
#include <sys/syscall.h>
#include <linux/kernel.h>

sem_t more_needed;
sem_t match;
sem_t paper;
sem_t tobacco;


void *agent ()
{
int i=0;
int sm=1;
int s=0,p=0,m=0;
 while (1)
    {
      int number = rand() % 3;
	if(i==10){
		printf("\n\t\t-------------------------------------------+");
		printf("\n\t\tTotal [TIME] smoker with ciggerete smoked: %d   |",s);
		printf("\n\t\tTotal [TIME] smoker with paper smoked: %d         |",p);
		printf("\n\t\tTotal [TIME] smoker with match smoked: %d         |",m);
		printf("\t\t-------------------------------------------+\n");
		exit(0);
	}
	sleep(1);
      switch (number)
        {
           case 0: sem_post (&match); /* match and paper */
                   sem_post (&paper);
		   char st[500];
		   sprintf(st,"\t\tAgent has put match and paper on the table\n");
                   long sta = syscall(335,st,100);


			//printf("Agent has put match and paper on the table\n");
			printf("\t\t=> Smoking %d time\n", sm++);
			s++;
                   break;


           case 1: sem_post (&match); /* match and tobacco */
                   sem_post (&tobacco);

		   char st1[500];
		   sprintf(st1,"\t\tAgent has put match and tobacco on the table\n");
                   long sta1 = syscall(335,st1,100);
		
		//printf("Agent has put match and tobacco on the table\n");
		printf("\t\t=> Smoking %d time\n", sm++);
			p++;
                   break;


           case 2: sem_post (&paper); /* tobacco and paper */
                   sem_post (&tobacco);

		   char st2[500];
		syscall(st2,"\t\tAgent has put paper and tobacco on the table\n");
                   long sta2 = syscall(335,st2,100);
			
			//printf("Agent has put paper and tobacco on the table\n");
				printf("\t\t=> Smoking %d time\n", sm++);
			m++;
                   break;
        }
      sem_wait (&more_needed); /* wait for request for more */
	i++;
    }
}

void *smoker_with_tobacco ()
{
  while (1)
    {
      sem_wait (&match); /* grab match from table */
      if (sem_trywait (&paper) == 0) /* grab paper */
        {
          /* roll cigarette and smoke */


 		char st3[500];
		syscall(st3,"\t\tmatch and paper feched\n");
                long sta3 = syscall(335,st3,100);



		char st4[500];
		syscall(st4,"\t\tsmoker with tobacco is smoking\n");
                long sta4 = syscall(335,st4,100);



		//printf("tobacco smoking\n");
		sleep(0.5);
          	sem_post (&more_needed); /* signal to agent */
        }
      else sem_post (&match); /* drop the match */
    }
}

void *
smoker_with_match ()
{
  while (1)
    {
      sem_wait (&paper); /* grab match from table */
      if (sem_trywait (&tobacco) == 0) /* grab paper */
        {
          /* roll cigarette and smoke */



 		char st5[500];
		syscall(st5,"\t\ttobacco and paper feched\n");
                long sta5 = syscall(335,st5,100);



		char st6[500];
		syscall(st6,"\t\tsmoker with match is smoking\n");
                long sta6 = syscall(335,st6,100);




		//printf("match smoking\n");
		sleep(0.5);
          	sem_post (&more_needed); /* signal to agent */
        }
      else sem_post (&paper); /* drop the match */
    }
}

void *
smoker_with_paper ()
{
  while (1)
    {
      sem_wait (&tobacco); /* grab match from table */
      if (sem_trywait (&match) == 0) /* grab paper */
        {
		/* roll cigarette and smoke */



 		char st7[500];
		syscall(st7,"\t\tmatch and tobacco feched\n");
                long sta7 = syscall(335,st7,100);



		char st8[500];
		syscall(st8,"\t\tsmoker with paper is smoking\n");
                long sta8 = syscall(335,st8,100);


		//printf("paper smoking\n");
		sleep(0.5);
         	sem_post (&more_needed); /* signal to agent */
        }
      else sem_post (&tobacco); /* drop the match */
    }
}

int main() {


printf(\n\t\t****************************************************************************\n);
printf(\n\t\t********************** CHAIN SMOKER USING SYSTEMCALL ***********************\n);
printf(\n\t\t****************************************************************************\n);

	pthread_t th_1, th_2, th_3, th_4;
	sem_init(&more_needed,0,1);
	sem_init(&match,0,0);
	sem_init(&paper,0,0);
	sem_init(&tobacco,0,0);
pthread_create(&th_1,NULL,agent,NULL); // Here 6 threads equals to 6 cars on the road.
	pthread_create(&th_2,NULL,smoker_with_tobacco,NULL); // 3 cars are on the North road ready to move to south
	pthread_create(&th_3,NULL,smoker_with_paper,NULL); // 3 cars are on the east road ready to move to west
        pthread_create(&th_4,NULL,smoker_with_match,NULL);


        pthread_join(th_1,NULL);
        pthread_join(th_2,NULL);
	pthread_join(th_3,NULL);
	pthread_join(th_4,NULL);
	
	return 0;

}
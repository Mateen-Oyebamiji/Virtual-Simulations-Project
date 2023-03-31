#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>



int main(int argc, char *argv[])
{
  srand( (unsigned)time( NULL ) );     // for randomization 
  int numInc;                          // number of runs
  
  /*Handling command line arguments*/
  if (argc < 2)                            
    numInc = 100;                    
  else
    numInc = atoi(argv[1]);
    
  StatsType statArr[NUM_SCENARIOS];
  for(int i=0;i<NUM_SCENARIOS;++i){
    initStats(&statArr[i]);
     
  }
  for(int i=0; i<numInc;++i){
    runScenario(statArr);         //runningScenarios
  }
  
  
  for(int i=0;i<NUM_SCENARIOS;++i){
    computeStats(&statArr[i],numInc);    //computing statsType 
     
  }
  printf("For %d runs:\n",numInc);
   
  
  printStatsTable(statArr);    //printingStatsType
  
  return(0);
}



/*
  Function:  randm
  Purpose:   returns a pseudo randomly generated number, 
             in the range 0 to (max - 1), inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [0, max-1) 
*/
int randm(int max)
{
  double r = ( (double)rand() / ((double)(RAND_MAX)+(double)(1)) ); 

  return (int)(r * max);
}


/*
Function: runExe
purpose:  thread, thread function for each runs
in:       void, but takes in a RunspecsType used for the run
*/
void *runExe(void *arg){
  RunSpecsType rs= *((RunSpecsType *)arg);
  fightExe(rs);
  //printStats(rs.stats);
  
  return(0);
}

/*
Function: removeP (Remove pirates)
purpose:  thread, the fight Thread function, removes pirates from the given DequeTYpe one they are defeated
in:       void, but takes in FightSpecsType
out:      

*/
void *removeP(void *arg){
  FightSpecsType fs= *((FightSpecsType *)arg);
   
  int h_death,p_death;
  while(isEmpty(fs.pirates) == 0){
  FighterType *champ;
     
    
    if(isEmpty(fs.pirates) == 0){
      if(fs.dir == 0){
        removeFront(fs.pirates,&champ);
        if(fightSim(fs.hero,champ) == 0){
          ++h_death;
          fs.dir=4;
        }
        else {
          //free(champ);       //freeing
          //printf("FRONT:\n");
          //printFighter(champ);
        }
        usleep(100);
        
      }
      else if (fs.dir == 1){
        removeBack(fs.pirates,&champ);
        if(fightSim(fs.hero,champ) == 0){
          ++h_death;
          fs.dir=6;
        }
        else{
          //free(champ);       //freeing
          //printf("BACK: \n");
          //printFighter(champ);
        }
        usleep(100);
      }
      else {
        break;    
      }
    }
     
  }
   
  return 0;
}





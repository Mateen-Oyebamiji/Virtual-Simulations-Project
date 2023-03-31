#include "defs.h"
/*
Function: initRunSpecs
purpose:  initializes a given runspecs type structures with all its fields
in:        A given RunspecsType
out:         an initialized RunspecsType
*/
void initRunSpecs(DequeType *p,FighterType *t,FighterType *h,StatsType *stats,RunSpecsType **run){
  RunSpecsType *run_temp;
  run_temp= malloc(sizeof(RunSpecsType));
  
  (run_temp)->pirates=p;
  (run_temp)->tort=t;
  (run_temp)->hare=h;
  (run_temp)->stats=stats;
  
  *run=run_temp;
  
}

/*
Function: initFightSpecs
purpose:  initializes a given Fightspecs type structures with all its fields
in:        A given FightspecsType
out:         an initialized FightspecsType
*/
void initFightSpecs(FighterType *h,DequeType *p,DirectionType dir,sem_t *dqmutex,FightSpecsType **fight){
  FightSpecsType *fight_temp;
  fight_temp=malloc(sizeof(FightSpecsType));
  
  (fight_temp)->hero=h;
  (fight_temp)->pirates=p;
  (fight_temp)->dir=dir;
  (fight_temp)->dqMutex=dqmutex;
  
  *fight=fight_temp;
}

/*
Function: initstats
purpose:  initializes a given Statstype structures by setting its fields to zero
in:        A given StasType
out:       an initialized StatsType
*/
void initStats(StatsType *s){
  s->numSuccess=0;
  s->numPartSuccess=0;
  s->numFailure=0;
}

/*
Function: UpdateStats
purpose:  sets all the properties of a statsType to the geiven fields
in:       multiple statsType Fields
out:      updated stasType
*/
void updateStats(StatsType *s,int succ, int part, int fail){
  int su=s->numSuccess+succ;
  int pa=s->numPartSuccess+part;
  int fa=s->numFailure+fail;
  s->numSuccess=su;
  s->numPartSuccess=pa;
  s->numFailure=fa;
}

/*
Function: updatesuccess
purpose:  adds one  to the value of the field representing the number of successes in the statsType
in:      takes in a given statsType
out:     An updated StatsType
*/
void updateSuccess(StatsType *s){
  ++(s->numSuccess);
}

/*
Function: updatepart
purpose:  adds one to the value of the field representing the number of partial success in the statsType
in:      takes in a given statsType
out:     An updated StatsType
*/
void updatePart(StatsType *s){
  ++(s->numPartSuccess);
}

/*
Function: updateFail
purpose:  adds one to the value of the field representing the number of Failures in the statsType
in:      takes in a given statsType
out:     An updated StatsType
*/
void updateFail(StatsType *s){
  ++(s->numFailure);
}

/*
Function: printStats
purpose:  print StatsType fields to the screen
in:       takes in agiven StatsType Structure
*/
void printStats(StatsType *s){
  printf(" Success: %d\n Partial: %d\n Failure: %d\n",s->numSuccess,s->numPartSuccess,s->numFailure);
}

/*
Function: computeStats
purpose:  convert the properties of the statsType to an appropriate percen tage form using the number of runs
in:       a StatsType and an Int represnting the number of runs
out:      a StatsType with the fields in their proper form
*/
void computeStats(StatsType *s,int num){
  int s_temp= ((s->numSuccess * 100)/num);
  int p_temp = ((s->numPartSuccess * 100)/num);
  int f_temp = ((s->numFailure * 100)/num);
  
  s->numSuccess=s_temp;
  s->numPartSuccess =p_temp;
  s->numFailure=f_temp;
}

/*
Function: printStatsTable
purpose:  prints out the statstype  fields in a table according to hero with the sword
in:  A statsType Array
*/
void printStatsTable(StatsType statArr[NUM_SCENARIOS]){
  printf("+----------------------------------------------------------+\n");
  printf("| Hero with the sword | %% sucess | %% partial  |  %%failure  |\n");
  printf("+----------------------------------------------------------+\n");
  printf("|   Tortoise          |   %-2d     |     %-2d     |     %-2d     |\n",statArr[0].numSuccess,statArr[0].numPartSuccess,statArr[0].numFailure);
  printf("+----------------------------------------------------------+\n");
  printf("|   Hare              |   %-2d     |     %-2d     |     %-2d     |\n",statArr[2].numSuccess,statArr[2].numPartSuccess,statArr[2].numFailure);
  printf("+----------------------------------------------------------+\n");
  printf("|   None              |   %-2d     |     %-2d     |     %-2d     |\n",statArr[1].numSuccess,statArr[1].numPartSuccess,statArr[1].numFailure);
  printf("+----------------------------------------------------------+\n");
}


/*
Function: runScenario
purpose:  initialize collections of scenario data , and runs and terminates scenario thereads for each scenario
in:       An array of StatsType structures initialized in the  main function
out:      Updated StatsType for each scenario gotten from FightThreads
*/
void runScenario(StatsType statArr[NUM_SCENARIOS])
{
  //srand( (unsigned)time( NULL ) );
  sem_t mutex;
  pthread_t thread[NUM_SCENARIOS];
  pthread_t t1, t2, t3;
  
  if (sem_init(&mutex, 0, 1) < 0) {
    printf("semaphore initialization error\n");
    exit(1);
  }
   
  
  DequeType list;
  initPirates(&list);
  DequeType *PirateArr;
  PirateArr = malloc(NUM_SCENARIOS * sizeof(DequeType));
  FighterType *TortArr[NUM_SCENARIOS];
  FighterType *HareArr[NUM_SCENARIOS];
  RunSpecsType *RunArr[NUM_SCENARIOS];
  
  // initializing deque of pirates
  for(int i=0;i<NUM_SCENARIOS;++i){
    copyDeque(&list,&PirateArr[i]);
     
  }
  //initializing array of tortoise heroes
  initFighter(TORT_STRENGTH + SWORD_STRENGTH,TORT_ARMOUR,HERO_HEALTH,&TortArr[0]);
  for(int i=1;i<NUM_SCENARIOS;++i){
    initFighter(TORT_STRENGTH,TORT_ARMOUR,HERO_HEALTH,&TortArr[i]);
     
  }
   
  //initializing array of hare heroes
  initFighter(HARE_STRENGTH + SWORD_STRENGTH,HARE_ARMOUR,HERO_HEALTH,&HareArr[NUM_SCENARIOS-1]);
  for(int i=0;i<NUM_SCENARIOS-1;++i){
    initFighter(HARE_STRENGTH,HARE_ARMOUR,HERO_HEALTH,&HareArr[i]);
     
  }
  //printing
  for(int i=0;i<NUM_SCENARIOS;++i){
     
  }
  //initializing RunSpecsType Array
  for(int i=0;i<NUM_SCENARIOS;++i){
    initRunSpecs(&PirateArr[i],TortArr[i],HareArr[i],&statArr[i],&RunArr[i]);
     
  }
   
  
  for(int i=0;i<NUM_SCENARIOS;++i){
    pthread_create(&thread[i], NULL, runExe, RunArr[i]);
    pthread_join(thread[i], NULL);
  }
  
  
   
   
  //Clean up
   
  
  for(int i=0;i<NUM_SCENARIOS;++i){
    cleanUpRun(RunArr[i]);
  }
  free(PirateArr);
  
   
}
/*
Function: CleanUpRun
purpose:  deallocates RunSpecsType Data
in:       a given runspecsType
out:     a cleaned RunspecsType

*/
void cleanUpRun(RunSpecsType *run){
  cleanUpDeque(run->pirates);
  free(run);
}

/*
Function:  CleanUpFight
purpose:   deallocates FightSpecsType
in:       a given fightSpecsspecsType
out:     a cleaned fightSpecsspecsType
*/
void cleanUpFightSpecs(FightSpecsType *fs){
  cleanUpFighter(fs->hero);
   
  free(fs);
}









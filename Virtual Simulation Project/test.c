#include "defs.h"




int main(){
  /*
  // Testing deque and fighter stuff----------------------------------------------------------
  
  FighterType *f;
  DequeType list;
  initDeque(&list);
  
  initFighter(5,8,9,&f);
  addDeque(&list,f);
  initFighter(10,11,12,&f);
  addDeque(&list,f);
  initFighter(13,14,15,&f);
  addDeque(&list,f);
  initFighter(16,17,18,&f);
  addDeque(&list,f);
  
  removeBack(&list,&f);
  removeFront(&list,&f);
  printDeque(&list);
  printf("Removed:\n");
  printFighter(f);
  printf("is empty: %d\n",isEmpty(&list));
  
  //-------------------------------------------------------------------------------------------------------------------
  */
  
  /*
  //testing rando functions---------------------------
  int num1 = randomStrength(10);
  int num2= randomStrength(10);
  printf("rando: %d\n",num1);
  printf("rando: %d\n",num2);
  //------------------------------------------------
  
  //Testing init pirates -------------------
  FighterType *f1;
  DequeType list2,list3;
  initPirates(&list2);
  copyDeque(&list2,&list3);
  removeFront(&list2,&f1);
  
  printDeque(&list2);
  
   
  printf("Copied Deque:\n");
  printDeque(&list3);
  
  
  
  //--------------------------------------------------
  */
  
  /*
  //--------------------Testing initialization---------------
  
  FighterType *tort;
  initFighter(5,8,9,&tort);
  FighterType *hare;
  initFighter(6,7,8,&hare);
  DequeType deq,deku;
  initPirates(&deku);
  StatsType numbers;
  initStats(&numbers);
  RunSpecsType *runner;
  initRunSpecs(&deku,tort,hare,&numbers,&runner);
  printFighter(runner->tort);
  printStats(runner->stats);
  printDeque(runner->pirates);
  printf("Tail:\n");
  printFighter(runner->pirates->tail->data);
  
  
  //---------------------------------------------------------------------
  */
  
  
  //------------Testing Fight functions------------
  FighterType *batman;
  FighterType *joker;
  initFighter(5,8,20,&batman);
  initFighter(8,3,10,&joker);
  printf("Before: \n");
  printf("Batman: ");
  printFighter(batman);
  printf("Joker: ");
  printFighter(joker);
  
  printf("After: \n");
  if(fightSim(batman,joker) == 1){
    printf("BATMAN WINS\n");
  }
  else{
    printf("THE JOKER WINS\n");
  }
  printf("Batman: ");
  printFighter(batman);
  printf("Joker:  ");
  printFighter(joker);
  
  
  //----------------------------------------
  
  
  return 0;
}





/*

void fightExe(RunSpecsType *scenario)
{
  //srand( (unsigned)time( NULL ) );
  sem_t mutex;
  pthread_t t1, t2;
  
  if (sem_init(&mutex, 0, 1) < 0) {
    printf("semaphore initialization error\n");
    exit(1);
  }
  
  //initialization of structures
  FightSpecsType *one,*two;
  DequeType pir;
  initPirates(&pir);
  FighterType *tort,*hare;
  initFighter(5,8,20,&tort);
  initFighter(8,5,20,&hare);
  initFightSpecs(tort,&pir, FRONT,&mutex,&one);
  initFightSpecs(hare,&pir, BACK,&mutex,&two);
  
  pthread_create(&t1, NULL, removeP, one);
  //pthread_join(t1, NULL);
  pthread_create(&t2, NULL, removeP, two);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  
  printf("STATS: \n");
  printFighter(one->hero);
  printFighter(two->hero);
  
  

   
}*/
/*
int main(int argc, char *argv[])
{
  srand( (unsigned)time( NULL ) );
  sem_t mutex;
  pthread_t thread[NUM_SCENARIOS];
  pthread_t t1, t2, t3;
  
  if (sem_init(&mutex, 0, 1) < 0) {
    printf("semaphore initialization error\n");
    exit(1);
  }
  StatsType temp;
  initStats(&temp);
  
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
    //printDeque(&PirateArr[i]);
  }
  //initializing array of tortoise heroes
  initFighter(TORT_STRENGTH+2,TORT_ARMOUR,HERO_HEALTH,&TortArr[0]);
  for(int i=1;i<NUM_SCENARIOS;++i){
    initFighter(TORT_STRENGTH,TORT_ARMOUR,HERO_HEALTH,&TortArr[i]);
    //printFighter(TortArr[i]);
  }
   
  //initializing array of hare heroes
  initFighter(HARE_STRENGTH+2,HARE_ARMOUR,HERO_HEALTH,&HareArr[NUM_SCENARIOS-1]);
  for(int i=0;i<NUM_SCENARIOS-1;++i){
    initFighter(HARE_STRENGTH,HARE_ARMOUR,HERO_HEALTH,&HareArr[i]);
    //printFighter(HareArr[i]);
  }
  //printing
  for(int i=0;i<NUM_SCENARIOS;++i){
    //printf("Tort: ");
    //printFighter(TortArr[i]);
    //printf("Hare: ");
    //printFighter(HareArr[i]);
    //printDeque(&PirateArr[i]);
  }
  //initializing RunSpecsType Array
  for(int i=0;i<NUM_SCENARIOS;++i){
    initRunSpecs(&PirateArr[i],TortArr[i],HareArr[i],&temp,&RunArr[i]);
    //printDeque(RunArr[i]->pirates);
  }
  //pthread_create(&t1, NULL, runExe, test);
  //pthread_join(t1, NULL);
  
  for(int i=0;i<NUM_SCENARIOS;++i){
    pthread_create(&thread[i], NULL, runExe, RunArr[i]);
    pthread_join(thread[i], NULL);
  }
  
  
  
  
  
  
  //pthread_create(&t1, NULL, removeP, one);
  
  /*
  RunSpecsType *run;
  DequeType list1,list2,list3;
  initPirates(&list1);
  copyDeque(&list1,&list2);
  copyDeque(&list1,&list3);
  FighterType *tort1,*tort2,*tort3;
  FighterType *hare1,*hare2,*hare3;
  RunSpecsType *run1,*run2,*run3;*/
  
  /*
  DequeType pir;
  //initPirates(&pir);
  FighterType *tort,*hare;
  //initFighter(5,8,20,&tort);
  //initFighter(8,5,20,&hare);
  StatsType stats;
  initStats(&stats);
  RunSpecsType *test;
  initRunSpecs(&pir,tort,hare,&stats,&test);
  /*
  for(int i=0;i<100;++i){
    pthread_create(&t1, NULL, runExe, test);
    pthread_join(t1, NULL);
  }*/
  //pthread_create(&t1, NULL, runExe, test);
  //pthread_join(t1, NULL);
  //fightExe(test);
  
/*
  return(0);
}*/









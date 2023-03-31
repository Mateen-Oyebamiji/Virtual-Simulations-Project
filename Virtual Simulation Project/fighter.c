#include "defs.h"
/*
Function: initFighter
purpose: initializes a given fighterType with the given fields
in:      a fightertype to be returned, specified fields for the fighterType
out:     a new initialized fighterType
*/
void initFighter(int s,int a,int h,FighterType **champ){
  FighterType *champ_temp;
  champ_temp= malloc(sizeof(FighterType));
  //static int nextId=1001;
  (champ_temp)->strength = s;
  (champ_temp)->armour= a;
  (champ_temp)->health=h;
  *champ=champ_temp;
 
  
}

/*
Function: printFighter
purpose:  prints the fields of  a given fighterType
in:       a given FighterType
*/
void printFighter(FighterType *champ){
  printf("Strength: %d; Armour: %d; Health: %d;\n",champ->strength,champ->armour,champ->health);
}



/*
Function: initPirates
purpose:  initializes  several FighterType pirates with random properties into a deque
in:       A given Deque
out:      A Deque with the pirate Types
*/
void initPirates(DequeType *list){
  initDeque(list);
  
  FighterType *f;
  int strength,armour;
  int health=10;
  
  for(int i=0;i<10;++i){
    strength= randomStrength(10);
    armour= randomArmour(5);
    initFighter(strength,armour,health,&f);
    addDeque(list,f);
  }
}

/*Helper function*/
/*
Function: randomStrength
purpose:  computes a random value between 5 and a given max value -1, this is specifically for the pirates strength
in:       upper end of the range
returns:   the randomly generated int
*/
int randomStrength(int max){
  while(1){
    int rand= randm(max);
    if(rand>4){
      return rand;
    }
  }
}

/*
Function: randomArmour
purpose:  computes a random value between 5 and a given max value -1, this is specifically for thhe pirates armour property
in:       upper end of the range
returns:   the randomly generated int
*/
int randomArmour(int max){
  while(1){
    int rand= randm(max);
    if(rand>0){
      return rand;
    }
  }
}

/*
Function: randomTemp
purpose:  computes a random value between 5 and a given max value -1, this is specifically for the pirates temporary Strength
in:       upper end of the range
returns:   the randomly generated int
*/
int randomTemp(int max){
  while(1){
    int rand= randm(max);
    if(rand>=0){
      return rand;
    }
  }
}

/*
function: heroHit
purpose:  implements the Functionality of a hero hitting a  pirate
in:        2 FighterType, one for the hero, the other for the pirate
out:       hero and piratet fighterTypes with changes in their properties due to hits 
*/
void heroHit(FighterType *H,FighterType *p){
  int H_Damage=H->strength - p->armour;
  if(H_Damage < 0){
    H_Damage = 0;
  }
  p->health=p->health - H_Damage;
  if(p->health < 0){
    p->health =0;
  }
}

/*
Function: pirateHit
purpose:  implements the Functionality of a pirate hitting a  hero
in:        2 FighterType, one for the hero, the other for the pirate
out:       hero and piratet FighterTypes with changes in their properties due to hits 
*/
void pirateHit(FighterType *H,FighterType *p){
  int p_strength=p->strength + randomTemp(p->strength - 1);
  int p_Damage= p_strength - H->armour;
  if(p_Damage < 0){
    p_Damage =0;
  }
  H->health=H->health - p_Damage;
  if(H->health < 0){
    H->health = 0;
  }
}


/*
function: fightSim
purpose:  simulates a fight between a hero and a pirate a fighterType
in:       2 FighterType, one for the hero, the other for the pirate
returns:   an int as a flag to declare the winner
*/
int fightSim(FighterType *hero,FighterType *pirate){
  while(1){
    heroHit(hero,pirate);
    if(pirate->health <= 0){
      hero->health= hero->health + 3;
      if(hero->health > 20){
        hero->health = 20;
      }
      return HERO_WIN;
    }
    
    pirateHit(hero,pirate);
    if(hero->health <=0){
      return PIR_WIN;
    }
  }
  free(pirate);   //freeing
}




/*
Function: fightExe
purpose:  create and terminates 2 threads for each of the hero fights
in:       A runSpecsType containing hero data
out:      The  runspecsType containing the statistic data after each thread terminates
*/
void fightExe(RunSpecsType scenario)
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
  initFightSpecs(scenario.tort,scenario.pirates, FRONT,&mutex,&one);
  initFightSpecs(scenario.hare,scenario.pirates, BACK,&mutex,&two);
  
  pthread_create(&t1, NULL, removeP, one);
  pthread_create(&t2, NULL, removeP, two);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  
  //printf("STATS: \n");
  //printFighter(one->hero);
  //printFighter(two->hero);
  
  if(one->hero->health > 0 && two->hero->health >0 ){
    updateSuccess(scenario.stats);
  }
  else if(one->hero->health <1 && two->hero->health <1 ){
    updateFail(scenario.stats);
  }
  else{
    updatePart(scenario.stats);
  }
  
  
  cleanUpFightSpecs(one);  //clean
  cleanUpFightSpecs(two);  //clean
  

   
}
/*
Function: cleanUpfighter
purpose:  Deallocates the given  fighterType data
in:       given FighterType
*/
void cleanUpFighter(FighterType *champ){
  free(champ);
}




#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_RUNS       100
#define NUM_PIRATES     10
#define NUM_SCENARIOS    3

#define TORT_STRENGTH    5
#define TORT_ARMOUR      8
#define HARE_STRENGTH    8
#define HARE_ARMOUR      5
#define HERO_HEALTH     20
#define PIRATE_HEALTH   10
#define SWORD_STRENGTH   2

#define MAX_STR         64

#define C_OK            0
#define C_NOK           -1
#define HERO_WIN         1
#define PIR_WIN          0
#define IS_TRUE          1
#define IS_FALSE         0

typedef enum { SUCCESS, FAILURE, PART_SUCCESS, RES_UNKNOWN } ResultType;
typedef enum { FRONT, BACK } DirectionType;

typedef struct {	// Stats for one scenario, accumulated over all runs
  int numSuccess;
  int numPartSuccess;
  int numFailure;
} StatsType;

typedef struct {	// One fighter:  Tortoise, Hare, or Pirate
  int  strength;
  int  armour;
  int  health;
} FighterType;

typedef struct Node {
  FighterType  *data;
  struct Node  *next;
} NodeType;

typedef struct {	// Stores the fighting pirates for one scenario
  NodeType *head;
  NodeType *tail;
} DequeType;

typedef struct {	// Specs for one scenario of one run
  DequeType   *pirates;
  FighterType *tort;
  FighterType *hare;
  StatsType   *stats;
} RunSpecsType;

typedef struct {	// Specs for one fight of one scenario of one run
  FighterType  *hero;
  DequeType    *pirates;
  DirectionType dir;
  sem_t        *dqMutex;
} FightSpecsType;


int randm(int);		// Pseudo-random number generator function

/* FighterType manipulation functions*/
void initFighter(int s,int a,int h,FighterType **champ);
void printFighter(FighterType *champ);
void initPirates(DequeType *list);
void fightExe(RunSpecsType scenario);
/*Thread functions*/
void *removeP(void*);       
void *runExe(void *arg);
void runScenario(StatsType *s);

/*DequeType manipulation functions*/
void initDeque(DequeType *list);
void addDeque(DequeType *list,FighterType *champ);
int genPos(DequeType *list);
int removeFront(DequeType *list,FighterType **champ);
int removeBack(DequeType *list,FighterType **champ);
void printDeque(DequeType *list);
void copyDeque(DequeType *source,DequeType *dest);
int isEmpty(DequeType *list);

/*initialization  and data manipulation functions*/
void initRunSpecs(DequeType *p,FighterType *t,FighterType *h,StatsType *stats,RunSpecsType **run);
void initFightSpecs(FighterType *h,DequeType *p,DirectionType dir,sem_t *dqmutex,FightSpecsType **fight);
void initStats(StatsType *s);
void updateStats(StatsType *s,int succ, int part, int fail);
void updateSuccess(StatsType *s);
void updatePart(StatsType *s);
void updateFail(StatsType *s);
void printStats(StatsType *s);
void printStatsTable(StatsType statArr[NUM_SCENARIOS]);
void heroHit(FighterType *H,FighterType *p);
int randomTemp(int max);
void pirateHit(FighterType *H,FighterType *p);
int fightSim(FighterType *hero,FighterType *pirate);
void computeStats(StatsType *s,int num);


/*CleanUp Functions*/
void cleanUpFighter(FighterType *champ);
void cleanUpDeque(DequeType *list);
void cleanUpRun(RunSpecsType *run);
void cleanUpFightSpecs(FightSpecsType *fs);

/*Helper functions*/
int randomStrength(int max);
int randomArmour(int max);
void *tester1(void *arg);
void *tester2(void *arg);


#endif


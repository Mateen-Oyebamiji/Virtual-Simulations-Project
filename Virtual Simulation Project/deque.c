#include "defs.h"
/*
Function: initDeque
Purpose:  initializes a DequeType Structure
in:       uninitialized DequeTYpe Structure
out:      an initialized DequeType Structure, which has it's head and tail set to null
*/
void initDeque(DequeType *list){
  list->head=NULL;
  list->tail=NULL;
}

/*
Function: addDeque
Purpose:  adds a given fighterType to the back of a given Deque
in:       FighterType to be added, DequeType 
out:      DequeType with fighterType added to it
*/
void addDeque(DequeType *list,FighterType *champ){
  NodeType *currNode;
  NodeType *prevNode;
  NodeType *newNode;
  int currPos = 0;
  int pos= genPos(list);
  
  currNode=list->head;
  prevNode=NULL;
  
  while (currNode != NULL) {
    if (currPos == pos)
      break;
    ++currPos;
    prevNode = currNode;
    currNode = currNode->next;
  }
  
  newNode= malloc(sizeof(NodeType));
  newNode->data=champ;
  newNode->next= NULL;
  
  if(prevNode==NULL)
    list->head=newNode;
  else
    prevNode->next = newNode;

//-----------------------------------------------------------    
  if(newNode->next == NULL)
    list->tail= newNode;
//-----------------------------------------------------------------  
  
  newNode->next=currNode;
}

/*
Function: genPos
Purpose: counts the number of elements in a given deque
in:     DequeType
returns:   an int that represents the number of fighters in a given deque
*/
int genPos(DequeType *list){
  NodeType *currNode;
  int pos=0;
  currNode=list->head;
  
  while(currNode != NULL){
    ++pos;
    currNode= currNode->next;
  }
  return pos;
}

/*
Function: removeFront
Purpose:  removes the first fighterType from a given deque
in :      the given DequeType
out:      returns the fighter that is removed from the deque
returns:   A flag for success or failure in the case of an empty Deque
*/
int removeFront(DequeType *list,FighterType **champ){
  NodeType *currNode;
  NodeType *prevNode;
  int pos=0;
  int currPos=0;
  
  currNode=list->head;
  prevNode=NULL;
  
  while( currNode != NULL){
    if(currPos == pos)
      break;
    ++currPos;
    prevNode=currNode;
    currNode = currNode->next;
  }
  
  if(currNode == NULL){
    return 0;
  }
  
  if(prevNode == NULL)
    list->head=currNode->next;
  else
    prevNode->next = currNode->next;
    
  *champ=currNode->data;
  
  return -1;
}

/*
Function: RemoveBack
purpose:  removes the last fighterType from the back of a given deque 
in:       the given DequeType
out:      returns the fighter that is removed from the deque
returns:  A flag for success or failure in the case of an empty Deque
*/
int removeBack(DequeType *list,FighterType **champ){
  NodeType *currNode;
  NodeType *prevNode;
  int pos= genPos(list);
  int currPos=0;
  
  currNode=list->head;
  prevNode=NULL;
  
  while( currNode != NULL){
    if(currPos == pos-1)
      break;
    ++currPos;
    prevNode=currNode;
    currNode = currNode->next;
  }
  
  if(currNode == NULL){
    return 0;
  }
  
  if(prevNode == NULL)
    list->head=currNode->next;
  else
    prevNode->next = currNode->next;
    
  *champ=currNode->data;
  
  //freeing
  //free(currNode->data);
  free(currNode);
  
  return -1;
}

/*
Function: printDeque
Purpose:  prints out all the fighterTypes in a given deque
in:       the given DequeType
*/
void printDeque(DequeType *list){
  NodeType *currNode = list->head;
  
  printf("Deque:\n");
  while(currNode !=NULL){
    printFighter(currNode->data);
    currNode= currNode->next;
  }
}

 



/*
Function: copyDeque
Purpose: makes a deep copy of a given deque
in:      a source and a destination deque
out:     a deep copy of the source Deque as the destination deque
:       
*/
void copyDeque(DequeType *source,DequeType *dest){
  initDeque(dest);
  
  NodeType *currNode1,*currNode2;
  NodeType *newNode1,*newNode2;
  FighterType *f;
  int strength,armour,health;
  
  currNode1=source->head;
  //newNode2= malloc(sizeof(NodeType));
  currNode2=dest->head;
  
  while(currNode1 != NULL){
    strength= currNode1->data->strength;
    armour=currNode1->data->armour;
    health= currNode1->data->health;
    initFighter(strength,armour,health,&f);
    
    addDeque(dest,f);
    currNode1=currNode1->next;
     
  }
  
}


/*
Function: isEmpty
Purpose:  Checks if a given Deque is empty
in:       a given DequeType
returns:  an int flag for true or false
*/
int isEmpty(DequeType *list){
  if(list->head ==NULL){
  return 1;
  }
  return 0;
}

/*
Function: cleanUpDeque
Purpose:   deallocates memory in a given deque
in:       a given DequeType
*/
void cleanUpDeque(DequeType *list){
  NodeType *currNode;
  NodeType *nextNode;
  
  currNode=list->head;
  if(isEmpty(list) == 0){
    while (currNode != NULL) {
      nextNode = currNode->next;
      //free(currNode->data);
      //free(currNode);
      cleanUpFighter(currNode->data);
      currNode = nextNode;
    }
  }
   
}





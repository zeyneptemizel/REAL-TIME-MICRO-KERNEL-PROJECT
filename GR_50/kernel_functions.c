#include <stdio.h>
#include "kernel_functions.h"
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int Ticks; /* global sysTick counter */
int KernelMode;
TCB *PreviousTask, *NextTask; /* Pointers to previous and next running tasks */
list *ReadyList, *WaitingList, *TimerList;

void taskdelete(list **name, listobj *obj);
void mailboxMsgDelete(mailbox* mBox, msg *msg);
void mailboxMsgAdd(mailbox *mBox, msg* msg);
bool memberCheck(list ** name, listobj *obj);
msg* mailboxOldDelete(mailbox *mBox);
void listSorting(list **name);
void addTask(list **name, listobj *task);
void addTaskAfter(list **name, listobj *task1, listobj *task2);



void idle_task() {    /** DONE **/
	while (1);
}

exception init_kernel(){   /** DONE **/
  Ticks=0;                                      // We set the ticks to 0.
  
  ReadyList= (list *) malloc(sizeof(list));
  if(ReadyList==NULL)
    return FAIL;
  WaitingList= (list*) malloc(sizeof(list));
  if(WaitingList == NULL)
    return FAIL;
  TimerList= (list *) malloc(sizeof(list));
   if(TimerList==NULL)
     return FAIL; 
   
   ReadyList->pTail = NULL;
   ReadyList->pHead = NULL;
   WaitingList->pTail = NULL;
   WaitingList->pHead = NULL;
   TimerList->pTail = NULL;
   TimerList->pHead = NULL;                     //We initialize the kernel and its data structers.And set their head and tail to null.

    if(!create_task(idle_task,UINT_MAX))
     return FAIL;                              //idle task creation
   
   KernelMode = INIT;
   return OK;

}

exception create_task (void (*taskBody)(), unsigned int deadline){
  TCB *new_tcb;
  new_tcb = (TCB *) calloc (1, sizeof(TCB));
  if(new_tcb == NULL)
    return FAIL;
  new_tcb->PC = taskBody;
  new_tcb->SPSR = 0x21000000;
  new_tcb->Deadline = deadline;
  new_tcb->StackSeg [STACK_SIZE - 2] = 0x21000000;
  new_tcb->StackSeg [STACK_SIZE - 3] = (unsigned int) taskBody;
  new_tcb->SP = &(new_tcb->StackSeg [STACK_SIZE - 9]);
  
    // In this section we create the obj and initialize their properties 
    listobj *obj=(listobj*)malloc(sizeof(listobj));    
     if (obj == NULL){
     return FAIL;
     }
     obj->pTask = new_tcb;
     obj->nTCnt = 0;
     obj->pMessage = NULL;
     obj->pNext = NULL;
     obj->pPrevious = NULL;
     
     if(obj==NULL){
       free(new_tcb);
       return FAIL;
     }
  
  // If kernelmode is init then we insert new task in the readylist
  if(KernelMode == INIT){
    addTask(&ReadyList, obj);
    return OK;
  }
  else{
    isr_off();                                  // Disable interrupts
    PreviousTask = ReadyList ->pHead ->pTask;   // Update Previous task
    addTask(&ReadyList,obj);               // Insert new task in readylist
    NextTask = ReadyList ->pHead ->pTask;       // Update Next Task
    SwitchContext();
  }
  return OK;
}


void run (void){     /** DONE **/
  Ticks =0;                                     //We set the ticks to 0
  KernelMode = RUNNING;                                // We set the kernel to running mode
  NextTask= ReadyList -> pHead ->pTask;      //We set NextTask to be the equal of TCB of the task to be loaded
  LoadContext_In_Run();                         //Then we load the contenxt 
}

void terminate (void){   /** DONE **/
  isr_off();                    //We fisable the interrupts.
  
  listobj *running_task;                  //We took the running_task
  listobj *temp = ReadyList -> pHead;
  taskdelete(&ReadyList, temp);
  running_task = temp;                   //end terminate it.
 
  NextTask = ReadyList->pHead->pTask;           //We set the next task
  switch_to_stack_of_next_task();
  
  free(running_task->pTask);                //We delete the data that terminated
  free(running_task);
  LoadContext_In_Terminate();
}


void TimerInt(void) {       /** DONE **/
  Ticks++;
  listobj* temp, *temp2, *temp3;
  temp = TimerList->pHead; 
  while (temp != NULL)
  {if (Ticks >= temp ->nTCnt) {
      taskdelete(&TimerList, temp);
      addTask(&ReadyList, temp);
      temp = TimerList->pHead;
    }
    else
      temp = temp->pNext;
  }
  temp2 = WaitingList->pHead;
  //and now we check the waiting list for deadlines
  while (temp2 != NULL) {
    if (temp2->pTask->Deadline == Ticks) {
      taskdelete(&WaitingList, temp2);
      addTask(&ReadyList, temp2);		
      temp2 = temp2->pNext;
    }
    else
      break;
  }
  temp3 = TimerList->pHead;
  //now the timerlist
  while (temp3 != NULL) {
    if (Ticks >= temp3->pTask->Deadline) {
      taskdelete(&TimerList, temp3);
      addTask(&ReadyList, temp3);
    }
    temp3 = temp3->pNext;
  }
  NextTask = ReadyList->pHead->pTask;
}

void set_ticks(uint nTicks) {  /** DONE **/
  Ticks = nTicks;
}

uint ticks(void) {              /** DONE **/
  return Ticks;
}

uint deadline(void) {           /** DONE **/
  return NextTask->Deadline;
}

void set_deadline(uint deadline) {          /** DONE **/
  isr_off();
  NextTask->Deadline = deadline;            //we set deadline
  PreviousTask = ReadyList->pHead->pTask;       //updating 
  listSorting(&ReadyList);                //reschedule
  NextTask = ReadyList->pHead->pTask;           //updating
  SwitchContext();
}



mailbox* create_mailbox(uint nof_msg, uint size_of_msg){   /** DONE **/
  mailbox* mbox;
  mbox = (mailbox*)malloc(sizeof(mailbox));
  if (mbox == NULL)
    return NULL;        
  mbox->pHead = NULL;    // We initialize mailbox structure 
  mbox->pTail = NULL;
  mbox->nDataSize = size_of_msg;
  mbox->nMessages = 0;
  mbox->nMaxMessages = nof_msg;
  mbox->nBlockedMsg = 0;
  
  return mbox;
}

exception remove_mailbox(mailbox* mBox){        /** DONE **/
  if(!(mBox->nMessages)){               // We check to see if it is empty
    free(mBox ->pHead);                 // if empty we clear 
    free(mBox->pTail);
    free(mBox);
    return OK;
  }
  else                  // If not empty we reurt here
    return NOT_EMPTY;
}


exception send_wait(mailbox* mBox, void* Data){     /** DONE **/
  
  isr_off();            // We disable interrups
  msg* receivingTask = mBox ->pHead;
  if(receivingTask -> Status == RECEIVER){              // If receiving task is waiting then,
    memcpy(receivingTask ->pData,Data, mBox ->nDataSize);      //We copy sender's data
    mailboxMsgDelete(mBox, receivingTask);              //Remove receiving task's message struct from mailbox
    PreviousTask = ReadyList ->pHead ->pTask;           //We update previous task
    taskdelete(&WaitingList, receivingTask ->pBlock);
    addTask(&ReadyList, receivingTask->pBlock);        // We insert it to the ready list
    NextTask = ReadyList ->pHead ->pTask;                       // and then we update the next task
  }
  else{
    msg* new = (msg*)malloc(sizeof(msg));
    if(new == NULL)
      return FAIL;
    new->pData = (char*)malloc(mBox->nDataSize);            // We set the data pointer
    if(new->pData == NULL){
      free(new);
      return FAIL;
    }
    memcpy(new ->pData,Data, mBox ->nDataSize);       
    //We initalize it
    new ->Status = SENDER;     
    new ->pNext = NULL;
    new ->pPrevious = NULL; 
    new->pBlock = ReadyList ->pHead;
    
    mailboxMsgAdd(mBox,new);            //We add msg to mailboxx

    PreviousTask = ReadyList ->pHead ->pTask;          // We update previos task       
    taskdelete(&ReadyList, new->pBlock);                //We delete it from ready list
    addTask(&WaitingList, new->pBlock);             // and insert it into waiting list
    NextTask = ReadyList ->pHead ->pTask;               // finally we update the next task
  }
  SwitchContext();
  if(Ticks >= NextTask ->Deadline){     //If deadline is reached
    isr_off();          
    //remove send message?
    mailboxMsgDelete(mBox, ReadyList ->pHead ->pMessage);      //we remove send message

    isr_on();
    return DEADLINE_REACHED;
  }
  else
    return OK;
}

exception receive_wait(mailbox* mBox, void* Data){      /** DONE **/
  isr_off();
  msg* sendingMsg = mBox ->pHead;
  if(sendingMsg ->Status == SENDER){            //if send message is waiting then 
    //We copy sender's data 
    memcpy(Data, sendingMsg ->pData, mBox ->nDataSize);
     mailboxMsgDelete(mBox, sendingMsg);        // We remove msg
    
    if(memberCheck(&WaitingList, sendingMsg->pBlock)){          //If message is waiting list item
      PreviousTask = ReadyList ->pHead ->pTask;                 // We update previous task
      taskdelete(&WaitingList, sendingMsg ->pBlock);            
      addTask(&ReadyList, sendingMsg->pBlock);              // we took it from waiting and send it to the ready list
      NextTask = ReadyList ->pHead ->pTask;                     //We update ReadyList
    }
    else
      free(sendingMsg ->pData);
  }
  else{
    msg* new = (msg*)malloc(sizeof(msg));
    if(new == NULL)
      return FAIL;
    new ->pNext = NULL;
    new ->pPrevious = NULL;
    new ->pData = Data;
    new ->Status = RECEIVER;     
    new->pBlock = ReadyList->pHead;
    ReadyList->pHead->pMessage = new;
    mailboxMsgAdd(mBox,new);            // We add the message to the mailbox
    PreviousTask = ReadyList ->pHead ->pTask;           //then update previous task
    taskdelete(&ReadyList, new ->pBlock);               //move it from ready list waiting list
    addTask(&WaitingList, new ->pBlock);
    NextTask = ReadyList ->pHead ->pTask;               // update next taesk
  }
  SwitchContext();
  if(Ticks >= NextTask ->Deadline){             //if deadline is reached 
    isr_off();
    mailboxMsgDelete(mBox, ReadyList ->pHead ->pMessage);      //we remove receive message
    isr_on();
    return DEADLINE_REACHED;
  }
  else
    return OK;
}

exception send_no_wait(mailbox* mBox, void* Data){      /** DONE **/
  isr_off();            //We disable the intteryup
  msg* receivingTask = mBox ->pHead;
  if(receivingTask -> Status == RECEIVER){              // if receiving task is waiting then 
    //we copy sender's data 
    memcpy(receivingTask ->pData,Data, mBox ->nDataSize);
    mailboxMsgDelete(mBox, receivingTask);      // We remove receiving task msg strtuct 
    
    PreviousTask = ReadyList ->pHead ->pTask;           //then update previous task
    taskdelete(&WaitingList, receivingTask->pBlock);
    addTask(&ReadyList, receivingTask->pBlock);             // then we move receiving task to readylist
    NextTask = ReadyList ->pHead ->pTask;               //and update nexttask
    SwitchContext();
  }
  else{
    msg* new = (msg*)malloc(sizeof(msg));
    if(new == NULL)
      return FAIL;
    new ->pNext = NULL;
    new ->pPrevious = NULL;
    new->pData = (char*)malloc(mBox->nDataSize);
    if(new->pData == NULL){
      free(new);
      return FAIL;
    }
    memcpy(new ->pData, Data, mBox ->nDataSize);
    new ->pBlock = NULL;
    new ->Status = SENDER;
    
    if(mBox->nMaxMessages <= mBox->nMessages){  // if mailbox is full then we remove the oldest message strtuct
      mailboxOldDelete(mBox);
    }
    mailboxMsgAdd(mBox, new);           //we add the  mesg to mailboc
    isr_on();
  }
  return OK;
}

exception receive_no_wait(mailbox* mBox, void* Data){   /** DONE **/
        isr_off();

  msg* sendingMsg = mBox ->pHead;
  if(sendingMsg ->Status == SENDER){ // if sebd nessage is waiting then

    memcpy(Data, sendingMsg ->pData, mBox ->nDataSize);
    mailboxMsgDelete(mBox, sendingMsg);         //we remove the senfing tasks message struct    
    if(memberCheck(&WaitingList, sendingMsg->pBlock)){  //if messafe was of wait type then
      PreviousTask = ReadyList ->pHead ->pTask;                //We update previous task
      taskdelete(&WaitingList, sendingMsg ->pBlock); 
      addTask(&ReadyList, sendingMsg->pBlock);              //then we move sending task to readlylist
      NextTask = ReadyList ->pHead ->pTask;                     //update nexttask
      SwitchContext();
    }
    else
      free(sendingMsg ->pData);
  }
  else{
    return FAIL;
  }
  return OK;
}

exception wait(uint nTicks){
  isr_off();
  PreviousTask = ReadyList ->pHead ->pTask;            //update previous task
  listobj * obj = ReadyList ->pHead;
  obj ->nTCnt = nTicks;
  taskdelete(&ReadyList, obj);
  addTask(&TimerList, obj);                //we place task in the timer list
  NextTask = ReadyList ->pHead ->pTask;
  SwitchContext();
  
  if(Ticks >= NextTask ->Deadline)
    return DEADLINE_REACHED;
  else
    return OK;
}




/**                 helping functions                             **/

bool memberCheck(list ** name, listobj *obj){
  list *temp = *name;
  listobj *tempObj = temp->pHead;
  while (tempObj != NULL) {
    if (tempObj == obj) {
      return true;
    }
    tempObj = tempObj->pNext;
  }
  return false;
}

void taskdelete(list **name, listobj *obj){

  if ((*name)->pHead == NULL || obj == NULL)
    return;
      //if the node is the head
  if ((*name)->pHead == obj){
      //if the node is the only task
      //The list should be empty so we null them all.
    if((*name)->pTail == obj){
      (*name) -> pHead -> pNext= NULL;
      (*name) -> pHead -> pPrevious = NULL;
      (*name) -> pTail -> pNext = NULL;
      (*name) -> pTail -> pPrevious = NULL;
      (*name) -> pHead = NULL;
      (*name) -> pTail = NULL;
    }
    //if not 
    else{
      (*name) -> pHead = (*name) -> pHead -> pNext;             //we set the head to the next
      (*name) -> pHead -> pPrevious = NULL;                     //and previous to null.
    }
  }
  // If node is the tail
  else if((*name)->pTail == obj){
    (*name)->pTail = (*name)->pTail ->pPrevious;        //tail becomes the previous one.
    (*name)->pTail ->pNext = NULL;              //There is no next.
  }
  //else
  else{
    obj ->pPrevious ->pNext = obj ->pNext  ;         
    obj -> pNext -> pPrevious = obj -> pPrevious;
  }
  obj -> pNext = NULL;                 //We delete them.
  obj -> pPrevious = NULL;
  return;
}

void mailboxMsgAdd(mailbox *mBox, msg* msg){
  if (mBox->pHead == NULL) {   // If the head is null so its empty
    mBox->pHead = msg;          // We set the head and tail as msg
    mBox->pTail = msg;
  }
  else {                        // if it is not empty we simply add msg to it
    msg->pPrevious = mBox->pTail;
    mBox->pTail->pNext = msg;
    mBox->pTail = msg;
  }
  (mBox->nMessages)++;
  
}

void mailboxMsgDelete(mailbox* mBox, msg *msg){
  if (mBox->pHead == msg) {  // If the msg is head
    if(mBox -> pTail == msg){   // and also the tail (so the only msg)
      mBox ->pHead = NULL;       // We clear them
      mBox ->pTail = NULL;
    }
    else{               // if it is just the head 
      mBox->pHead = msg->pNext;         //We set head to the next task 
      mBox->pHead->pPrevious = NULL;    //and clear.
    }
  }
  else if (mBox->pTail == msg) {        // if msg is tail
    mBox->pTail = msg->pPrevious;       // We set tail to prev.
    mBox->pTail->pNext = NULL;          //then clear
  }
  else {
    msg->pPrevious->pNext = msg->pNext;
    msg->pNext->pPrevious = msg->pPrevious;
  }
 (mBox->nMessages)--;
}

msg* mailboxOldDelete(mailbox *mBox){
  msg *temp = mBox->pHead;
  mailboxMsgDelete(mBox, temp);
  return temp;
}

void listSorting(list **name){
  list *temp = (list*)malloc(sizeof(list));
  listobj *movingTask = NULL;
  
  while ((*name) ->pHead != NULL)
  {
  listobj *temp2 = (*name) -> pHead;
  taskdelete(name, temp2);
  movingTask = temp2;

    addTask(&temp, movingTask);
  }
  *name = temp;
}


void addTask(list **name, listobj *task){
  //Check if head is empty
  if ((*name)->pHead == NULL) {
    (*name)->pHead = task;
    (*name)->pTail = task;
    return;
  }
  //Check if new task is larger than tail
  if (task->pTask->Deadline > (*name)->pTail->pTask->Deadline) {
    addTaskAfter(name, (*name)->pTail, task);
    return;
  }
  listobj *temp;
  for (temp = (*name)->pHead; temp->pNext != NULL; temp = temp->pNext) {
    //When temp deadline is larger than new deadline, break
    if (temp->pTask->Deadline > task->pTask->Deadline) {
      break;
    }
  }
  if ((*name)->pHead == temp) {
    (*name)->pHead = task;
  }
  else{
    temp->pPrevious->pNext = task;
  }
  task->pPrevious = temp->pPrevious;
  temp->pPrevious = task;
  task->pNext = temp;
}


void addTaskAfter(list **name, listobj *task1, listobj *task2){
  if ((*name)->pTail == task1) {
    (*name)->pTail = task2;
  }
  else {
    task1->pNext->pPrevious = task2;
  }
  task2->pNext = task1->pNext;
  task1->pNext = task2;
  task2->pPrevious = task1;
}


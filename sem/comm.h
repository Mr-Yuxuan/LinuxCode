#pragma once

#include<stdio.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdlib.h>
#define KEY_PATH "."
#define PRO_ID 0
union semun
{
   int val;
   struct semid_ds* buf;
   unsigned short* array;
   struct seminfo* _buf;
};
void op_sem(int semid,int op,int which);
int comm_sem();
int creat_sem();
int get_sem();
void destory_sem(int semid);
void P(int semid,int which);
void V(int semid,int which);
void init_sem(int semid,int which);

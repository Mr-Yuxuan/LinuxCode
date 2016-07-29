#pragma once

#include<stdio.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/ipc.h>
#define PATH "."
#define PRO_ID 0
#define SIZE 4096
int comm_shm(int flag);
int create_shm();
int get_shm();
char* at_shm(int shmid);
int dt_shm(const void*shmaddr);
void destory(int shmid);

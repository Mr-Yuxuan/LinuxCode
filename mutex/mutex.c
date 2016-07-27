#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
pthread_mutex_t lock,_lock;
pthread_cond_t cond;
typedef struct ListNode
{
	int data;
    struct ListNode* next;
}node,*node_p, **node_pp;

node_p head=NULL;
void alloc_list(node_pp head,int _data)
{
	*head=(node_p)malloc(sizeof(node));
	(*head)->data=_data;
    (*head)->next=NULL;
	
	return;
}
void PushFront(node_p list,int _data)
{
   node_p tmp;
   alloc_list(&tmp,_data);
   tmp->next=list->next;
   list->next=tmp;
}
int isempty(node_p list)
{
	return list->next==NULL?1:0;
}
void PopFront(node_p list,int *data)
{
	if(!isempty(list))
	{
		node_p del=list->next;
	    list->next=del->next;
		*data=del->data;
	    free(del);
	}

}
void show(node_p list)
{
    node_p start=list->next;
	while(start)
	{
		printf("%d ",start->data);
		start=start->next;
	}
	printf("\n");
}

void *consum(void* arg)
{
	while(1)
	{
	  pthread_mutex_lock(&lock);
	  while(isempty(head))
	  {
	     pthread_cond_wait(&cond,&lock);
	  }
	  int data=0;
	  PopFront(head,&data);
	  printf("%x: %d\n",pthread_self(),data);
	  
	  pthread_mutex_unlock(&lock);
	  sleep(1);
	}

}
void *consum1(void* arg)
{
	while(pthread_mutex_lock(&_lock)==0)
	{while(1)
	{
	  pthread_mutex_lock(&lock);
	  while(isempty(head))
	  {
	     pthread_cond_wait(&cond,&lock);
	  }
	  int data=0;
	  PopFront(head,&data);
	  printf("th1: %d\n",data);
	  
	  pthread_mutex_unlock(&lock);
	  pthread_mutex_unlock(&_lock);
	  sleep(1);
	}
	}

}
void *product(void *arg)
{
	while(pthread_mutex_lock(&_lock)==0)
	{while(1)
	{
		pthread_mutex_lock(&lock);
		int data=rand()%1234;
		PushFront(head,data);
		printf("%x: %d\n",pthread_self(),data);
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&lock);
		pthread_mutex_unlock(&_lock);
		sleep(5);
	}}

}
void *product1(void *arg)
{
	while(pthread_mutex_lock(&_lock)==0)
	{
		while(1)
		{
		pthread_mutex_lock(&lock);
		int data=-1;
		PushFront(head,data);
		printf("pro1: %d\n",data);
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&lock);
		pthread_mutex_unlock(&_lock);
		sleep(5);
	}
	}

}
int main()
{
	int i=0;
    alloc_list(&head,0);
    pthread_mutex_init(&lock,NULL);
    pthread_mutex_init(&_lock,NULL);
	pthread_cond_init(&cond,NULL);
	pthread_t id1,id2,id3,id4;
    pthread_create(&id1,NULL,consum,NULL);
    pthread_create(&id4,NULL,consum,NULL);
	pthread_create(&id2,NULL,product,NULL);
	pthread_create(&id3,NULL,product,NULL);
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	pthread_join(id3,NULL);
	pthread_join(id4,NULL);
	pthread_mutex_destroy(&lock);
	pthread_mutex_destroy(&_lock);
	pthread_cond_destroy(&cond);
	return 0;
}

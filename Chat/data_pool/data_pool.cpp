#include"data_pool.h"

data_pool::data_pool(int _size)
	:pool(_size)
	 ,cap(_size)
	 ,index_pro(0)
	 ,index_com(0)
{
	sem_init(&blank_sem,0,_size);
    sem_init(&data_sem,0,0);


}
void data_pool::data_get(std::string& _msg_out)
{
	sem_wait(&data_sem);
	_msg_out=pool[index_com];

	index_com++;
	if(index_com>=cap)
		index_com%=cap;
	sem_post(&blank_sem);



}
void data_pool::data_put(std::string &msg)
{
	sem_wait(&blank_sem);
	pool[index_pro]=msg;
	index_pro++;
	if(index_pro>cap)
		index_pro%=cap;
	sem_post(&data_sem);


}
data_pool::~data_pool()
{
	sem_destroy(&blank_sem);
	sem_destroy(&data_sem);


}

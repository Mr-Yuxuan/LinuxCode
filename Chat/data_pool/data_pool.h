#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<semaphore.h>
class data_pool
{
public:
	data_pool(int _size=128);
	void data_get(std::string& _msg_out);
	void data_put(std::string &msg);
	~data_pool();

private:
	std::vector<std::string> pool;
	int cap;
	int index_pro;
	int index_com;
	sem_t blank_sem;
	sem_t data_sem;
};

#include"comm.h"
void print_log(const char*error,const char*fun,int line)
{
	std::cout<<error<<" "<<'['<<fun<<']'<<" "<<line<<std::endl;
	return;
}

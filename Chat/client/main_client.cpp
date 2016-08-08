#include"client.h"

chat_win *win_p = NULL;

std::string _nick_name;
std::string _school;
std::string _cmd = "None";

static void usage(const char *proc)
{
	std::cout<<"Usage: "<<proc<<"[remote_ip] [port]"<<std::endl;
}

void *draw_header(void *arg)
{
	Client *cli_p = (Client*)arg;
	win_p->creat_header();
	curs_set(0);
	wattrset(win_p->header,A_NORMAL);
	win_p->flush_window(win_p->header);
	
	int max_y,max_x;
	getmaxyx(win_p->header,max_y,max_x);
	std::string head_line = "WE CHAT";
	
	int index = 1;
	while(1)
	{
		wattron(win_p->header,A_BOLD);
		win_p->put_str(win_p->header,max_y/2,index++,head_line);
		if(index >= (max_x*3)/4)
			index = 1;
		win_p->flush_window(win_p->header);
		usleep(500000);
	    //wbkgd(win_p->header,COLOR_WHITE);
		win_p->clear_win_line(win_p->header,max_y/2,1);
		//wattroff(win_p->header,A_BLINK);
	}
	return NULL;
}
void *draw_input(void *arg)
{
	Client *cli_p = (Client *)arg;
	
	std::string cmd_str = "please enter# ";
	win_p->creat_input();
	std::string _win_str;
	std::string send_str;
	
	udp_data data;
	
	while(1)
	{
		wattron(win_p->input,A_REVERSE);
		win_p->put_str(win_p->input,1,1,cmd_str);
		win_p->flush_window(win_p->input);
		wattroff(win_p->input,A_REVERSE);
		win_p->get_str(win_p->input,_win_str);
		if(_win_str=="quit"||_win_str=="Q")
		{
           _cmd="q";
		}
		win_p->clear_win_line(win_p->input,1,1);
		
		data.set_nick_name(_nick_name);
		data.set_school(_school);
		data.set_cmd(_cmd);
		data.set_msg(_win_str);
		
		data.to_str(send_str);
		cli_p->_send(send_str);
		beep();
		if(_cmd=="q")
		{
			

			delwin(win_p->header);
            delwin(win_p->output);
            delwin(win_p->flist);
            delwin(win_p->input);
			endwin();
			exit(0);
	

		}
		usleep(100);
	}
	return NULL;
}

void *draw_output(void *arg)
{
	Client *cli_p =(Client*)arg;
	
	win_p->creat_output();
	win_p->creat_flist();
	win_p->flush_window(win_p->flist);
	win_p->flush_window(win_p->output);
	
	std::string _recv_str;
	udp_data data;
	
	std::string _nn;
	std::string _s;
	std::string _c;
	std::string _m;

	int max_y,max_x;
	getmaxyx(win_p->output,max_y,max_x);

	int max_fy,max_fx;
	getmaxyx(win_p->flist,max_fy,max_fx);

	std::string flist_str;
	int index = 1;
	while(1)
	{
		cli_p->_recv(_recv_str);
		data.to_val(_recv_str);
		
		data.get_nick_name(_nn);
		data.get_school(_s);
		data.get_cmd(_c);
		data.get_msg(_m);
		

		std::string _win_str = _nn;
		_win_str += "-";
		_win_str += _s;
		
		flist_str = _win_str;
		_win_str += "#";
		_win_str +=' ';
		_win_str += _m;

		//std::cout<<_c<<std::endl;
		
		if(_c=="q")
		{
			cli_p->del_flist(flist_str);
			win_p->clear_win_line(win_p->flist,1,max_y-1);

			win_p->flush_window(win_p->flist);
		}
		else
		{
			cli_p->add_flist(flist_str);
		}
	    wrefresh(win_p->flist);	
		wattron(win_p->output,A_BLINK);
		win_p->put_str(win_p->output,index++,1,_win_str);
		if(index >= max_y -1)
		{
			win_p->flush_window(win_p->output);
			sleep(2);
			index = 1;
			win_p->clear_win_line(win_p->output,1,max_y-1);
			box(win_p->output,'!','=');
		}
		int sizes=cli_p->flist.size();
		int page=max_fy-4;
		int nums=sizes/page;
		if(sizes%page>0)
			nums++;
		int pages=nums;
		std::stringstream sstr;
		std::stringstream ss1tr;
		std::string p;
		std::string ps;
		std::string str;
		sstr<<pages;
		sstr>>ps;


		int i = 0;
		int index;
		for(i=0;i<nums;++i)
		{
			ss1tr<<(i+1);
			ss1tr>>p;
			str+=p;
			str+="/";
			str+=ps;
			if(i==nums-1)
			{
               for(index=0;index<(sizes%page);++index)
			   {
			     win_p->put_str(win_p->flist,index+1,3,cli_p->flist[index+i*page]);
			     win_p->put_str(win_p->flist,max_fy-2,5,str);

			   }
			   break;
			}
			for(index=0;index<page;index++)
		   {
			win_p->put_str(win_p->flist,index+1,3,cli_p->flist[index+i*page]);
			win_p->put_str(win_p->flist,max_fy-2,5,str);
		   }
		win_p->flush_window(win_p->flist);
		win_p->flush_window(win_p->output);
		}
		
		win_p->flush_window(win_p->flist);
		win_p->flush_window(win_p->output);
		wattroff(win_p->output,A_BLINK);
			
	}
	return NULL;
}

void *draw_flist(void *arg)
{
	usleep(100);
	Client *cli_p = (Client *)arg;
	win_p->creat_flist();
	win_p->flush_window(win_p->flist);
	while(1)
	{
		sleep(1);
	}
	return NULL;
}
int main(int argc,char *argv[])
{
	if(argc != 3 )
	{
		std::cout<<"please enter ip & port"<<std::endl;
		return 0;
	}
	std::string _ip = argv[1];
	std::string _port = argv[2];
	Client cli(_ip,atoi(_port.c_str()));
	std::string _sstr;
	std::cout<<"Please enter you nick_name# ";
	fflush(stdout);
	std::cin>>_nick_name;
	std::cout<<"please enter your school# ";
	std::cin>>_school;
	fflush(stdout);
	cli.init();
	chat_win win;
	win_p = &win;
	pthread_t header,output,flist,input;
	pthread_create(&header,NULL,draw_header,(void *)&cli);
	pthread_create(&output,NULL,draw_output,(void *)&cli);
	pthread_create(&flist,NULL,draw_flist,(void *)&cli);
	pthread_create(&input,NULL,draw_input,(void *)&cli);
	
	pthread_join(header,NULL);
	pthread_join(output,NULL);
	pthread_join(flist,NULL);
	pthread_join(input,NULL);
      return 0;
}

/*int main(int argc,char* argv[])
{
	if(argc<3)
		std::cout<<"error:woring parameter"<<std::endl;
	std::string ip=argv[1];
	int port=atoi(argv[2]);
	Client cli(ip,port);
	cli.init();
	std::cout<<"Enter your name: ";
	std::cin>>
	char buf[1024];
	std::string bf;
	std::string in;
	while(1)
	{
	    memset(buf,'\0',sizeof(buf));
		std::cout<<"Client: ";
		gets(buf);
		bf=buf;
		cli._send(bf);
		cli._recv(in);
		std::cout<<"Server: "<<in<<std::endl;
		fflush(stdout);
	}

	return 0;
}*/

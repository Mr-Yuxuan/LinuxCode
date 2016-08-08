#include"chat_win.h"

chat_win::chat_win()
{
	initscr();
    sem_init(&lock,0,1);
}
	void chat_win::flush_window(WINDOW* _win)
{
	sem_wait(&lock);
	wrefresh(_win);
	sem_post(&lock);

}
	void chat_win::put_str(WINDOW*_win,int _y,int _x,std::string &str)
{
     mvwaddstr(_win,_y,_x,str.c_str());
	 return;
}
	void chat_win::get_str(WINDOW*_win,std::string &str)
{
     char msg[1024];
	 memset(msg,'\0',sizeof(msg));
	 wgetnstr(_win,msg,1024);
	 str=msg;
	 return;
}
	void chat_win::clear_win_line(WINDOW* _win,int begin_y,int nums)
{
     while(nums--)
	 {
		 wmove(_win,begin_y++,0);
		 wclrtoeol(_win);
	 }
	 return;
}

	void chat_win::creat_header()
{
	int x=0;
	int y=0;
    int weight=COLS;
	int height=LINES/5;
	header=newwin(height,weight,y,x);
	box(header,'+','+');
	flush_window(header);
}
	void chat_win::creat_output()
{
	int x=0;
	int y=LINES/5;
    int weight=(COLS*3)/4;
	int height=(LINES*3)/5;
	output=newwin(height,weight,y,x);
	box(output,'!','=');
	flush_window(output);

}
	void chat_win::creat_input()
{
	int x=0;
	int y=(LINES*4)/5;
    int weight=COLS;
	int height=LINES/5;
	input=newwin(height,weight,y,x);
	box(input,'&','&');
	flush_window(input);

}
    void chat_win::creat_flist()
{
	int x=(COLS*3)/4;
	int y=LINES/5;
    int weight=COLS/4;
	int height=(LINES*3)/5;
	flist=newwin(height,weight,y,x);
	box(flist,'@','*');
	flush_window(flist);

}
	
	chat_win::~chat_win()
{
	delwin(header);
	delwin(output);
	delwin(input);
	delwin(flist);
	endwin();
}

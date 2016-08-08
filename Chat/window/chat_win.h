#pragma once
#include<iostream>
#include<string>
#include<ncurses.h>
#include<string.h>
#include <semaphore.h>
class chat_win
{
public:
	chat_win();
	void flush_window(WINDOW* _win);
	void get_str(WINDOW*_win,std::string &str);
	void put_str(WINDOW*_win,int _y,int _x,std::string &str);
	void clear_win_line(WINDOW* _win,int begin_y,int nums);

	void creat_header();
	void creat_output();
	void creat_input();
    void creat_flist();
	
	~chat_win();

public:
	WINDOW* header;
	WINDOW* output;
	WINDOW* input;
	WINDOW* flist;
	sem_t lock;
};

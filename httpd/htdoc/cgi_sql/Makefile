ROOT_PATH=$(shell pwd)
SQL_PATH=../../lib/include/mysql
LIB_PATH=../../lib/mysql 

CC=g++
INS=insert_sql
SEL=select_sql
DEL=delete_sql

FIND_INCLUDE=-I$(SQL_PATH)
FIND_LIB=-L$(LIB_PATH)-lmysqlclient

INS_OBJ=insert_sql.o
SEL_OBJ=select_sql.o
DEL_OBJ=delete_sql.o
SQL_OBJ=my_sql.o
#
#.PHONY:test
#test:my_sql.o delete_sql.o
#	@g++ -o $@ $^ $(FIND_LIB)  
#my_sql.o:my_sql.cpp
#	@$(CC) -c $< $(FIND_INCLUDE) 
#delete_sql.o:delete_sql.cpp
#	@$(CC) -c $< $(FIND_INCLUDE)
	
.PHONY:all
all:$(INS) $(SEL) $(DEL)
$(INS):$(INS_OBJ) $(SQL_OBJ)
	@$(CC) -o $@ $^ $(FIND_LIB) 
	@echo "Linking [$^] to [$@]... done"
$(SEL):$(SEL_OBJ) $(SQL_OBJ)
	@$(CC) -o $@ $^ $(FIND_LIB)
	@echo "Linking [$^] to [$@]... done"
$(DEL):$(DEL_OBJ) $(SQL_OBJ) 
	@$(CC) -o $@ $^ $(FIND_LIB)
	@echo "Linking [$^] to [$@]... done"
%.o:%.cpp
	@$(CC) -c $< $(FIND_INCLUDE) $(FIND_LIB)
	

.PHONY:clean
clean:
	@rm -rf $(INS) $(SEL) $(DEL) *.o
	@echo "clean... done"



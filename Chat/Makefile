ROOT_PATH=$(shell pwd)
SERVER_PATH=$(ROOT_PATH)/server
CLIENT_PATH=$(ROOT_PATH)/client
COMM_PATH=$(ROOT_PATH)/comm
POOL_PATH=$(ROOT_PATH)/data_pool
LIB_PATH=$(ROOT_PATH)/lib
WINDOW_PATH=$(ROOT_PATH)/window

SER=udp_server
CLI=udp_client
CC=g++
FIND_INCLUDE=-I$(COMM_PATH) -I$(POOL_PATH) -I$(WINDOW_PATH) -I$(LIB_PATH)
FIND_LIB=-L$(ROOT_PATH)/lib
LDFLGAS=-pthread -ljsoncpp

SER_SRC=$(shell ls $(SERVER_PATH)|grep -E "*.cpp")
SER_SRC+=$(shell ls $(COMM_PATH)|grep -E "*.cpp")
SER_SRC+=$(shell ls $(POOL_PATH)|grep -E "*.cpp")
SER_OBJ=$(SER_SRC:.cpp=.o)


CLI_SRC=$(shell ls $(CLIENT_PATH)|grep -E "*.cpp")
CLI_SRC+=$(shell ls $(COMM_PATH)|grep -E "*.cpp")
CLI_SRC+=$(shell ls $(WINDOW_PATH)|grep -E "*.cpp")
CLI_OBJ=$(CLI_SRC:.cpp=.o)

.PHONY:all
all:$(SER) $(CLI)

$(SER):$(SER_OBJ)
	@$(CC) -o $@ $^  $(LDFLGAS) $(FIND_LIB)
	@echo "Linking [$^]to[$@]...done"
$(CLI):$(CLI_OBJ)
	@$(CC) -o $@ $^  $(FIND_LIB) $(LDFLGAS) -lncurses
	@echo "Linking [$^]to[$@]...done"
%.o:$(SERVER_PATH)/%.cpp
	@$(CC) -c $< $(FIND_INCLUDE) -pthread
	@echo "Compling [$<]to[$@]...done"
%.o:$(CLIENT_PATH)/%.cpp
	@$(CC) -c $< $(FIND_INCLUDE)
	@echo "Compling [$<]to[$@]...done"
%.o:$(COMM_PATH)/%.cpp
	@$(CC) -c $< $(FIND_INCLUDE) 
	@echo "Compling [$<]to[$@]...done"
%.o:$(POOL_PATH)/%.cpp
	@$(CC) -c $< $(FIND_INCLUDE)
	@echo "Compling [$<]to[$@]...done"
%.o:$(WINDOW_PATH)/%.cpp
	@$(CC) -c $< $(FIND_INCLUDE)
	@echo "Compling [$<]to[$@]...done"
.PHONY:clean
clean:
	@rm -f $(SER) $(CLI) *.o
	@echo "clean.......done"
.PHONY:debug
debug:
	@echo $(ROOT_PATH) 
	@echo $(SER_SRC)
	@echo $(SER_OBJ)

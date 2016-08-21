ROOT_PATH=$(shell pwd)

CC=g++
SUM=Sum
SUB=Sub
DIV=Div
MUL=Mul


SUM_OBJ=Sum.o
SUB_OBJ=Sub.o
DIV_OBJ=Div.o
MUL_OBJ=Mul.o
BIG_OBJ=BigDataReverse.o
.PHONY:all
all:$(SUM) $(SUB) $(DIV) $(MUL)
$(SUM):$(SUM_OBJ) $(BIG_OBJ)
	@$(CC) -o $@ $^
	@echo "Linking [$^] to [$@]... done"
$(SUB):$(SUB_OBJ) $(BIG_OBJ)
	@$(CC) -o $@ $^ 
	@echo "Linking [$^] to [$@]... done"
$(DIV):$(DIV_OBJ) $(BIG_OBJ)
	@$(CC) -o $@ $^ 
	@echo "Linking [$^] to [$@]... done"
$(MUL):$(MUL_OBJ) $(BIG_OBJ)
	@$(CC) -o $@ $^ 
	@echo "Linking [$^] to [$@]... done"
%.o:%.cpp
	@$(CC) -c $<
	

.PHONY:clean
clean:
	@rm -rf $(SUM) $(SUB) $(DIV) $(MUL) *.o
	@echo "clean... done"



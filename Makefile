CC=g++
CFLAG=-I/home/yikangle/桌面/ara/俄罗斯方块 -I/usr/include/SDL 
LIB=-lSDL -lX11 -lSDL_image -lSDL_ttf -lSDL_mixer -pthread 
object=gui.cpp  teris.cpp
obj=$(object:.cpp=.o)


	


.SUFFIXES :   .o  .cpp 
all:teris 

.cpp.o:
	$(CC) -g $<  -c   $(CFLAG) 
 


teris:$(obj)
	$(CC) -g   $^  -o   $@   $(LIB) 

.PHONY:clean

clean:
	rm -rf *.o  teris  

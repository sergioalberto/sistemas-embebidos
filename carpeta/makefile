APP=reproducir_mp3
SRC=$(APP).c
OBJ=$(APP).o
CC=gcc
CROSS_COMPILE=/home/sergio/ti-sdk-beagleboard-06.00.00.00/linux-devkit/sysroots/i686-arago-linux/usr/bin/arm-linux-gnueabihf-
LIB= `pkg-config --cflags --libs gstreamer-0.10`

all: $(APP)

$(APP): $(OBJ)
		$(CROSS_COMPILE)$(CC) -o $(APP) $(OBJ)

$(OBJ): $(SRC)
		$(CROSS_COMPILE)$(CC) -c $(SRC) $(LIB)

xBB: 
		$(CROSS_COMPILE)$(CC) -o $(APP) $(SRC) $(LIB)

x86: 
		$(CC) -o $(APP) $(SRC) $(LIB)
clean:
		rm $(APP) #$(OBJ)

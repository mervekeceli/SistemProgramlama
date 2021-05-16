
INC="./inc"
LIB="./lib"
TARGET=kripto

all: $(TARGET)


$(TARGET): ./lib/libfdr.a ./src/main.c
	gcc -no-pie -I$(INC) ./src/main.c -o $@ -L$(LIB) -lfdr

clean:
	rm -rf $(TARGET)

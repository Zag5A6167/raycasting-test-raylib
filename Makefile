TARGET = horror-game



LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11


all:
	gcc main.c $(LDFLAGS) -o $(TARGET)


clean: 
	rm -f $(TARGET)
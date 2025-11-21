CC = gcc
CFLAGS = -Wall -O2
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm -limm32 -lole32 -luuid -lcomdlg32 -loleaut32 -lkernel32

SRC = editor.c
OBJ = $(SRC:.c=.o)
EXEC = editor.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXEC)
	./$(EXEC)

clean:
	del $(OBJ) $(EXEC)

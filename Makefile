CC		= gcc
CFLAGS		= -c -ansi -pedantic -Wall
LIBS		= -lglut -lGL -lm
SOURCES		= particles_OpenGL.c particle.c
OBJECTS		= $(SOURCES:.c=.o)
HEADER		= particle.h
EXECUTABLE	= particle

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LIBS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o $(EXECUTABLE)

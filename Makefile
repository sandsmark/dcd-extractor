CFILES=$(wildcard *.c)
OBJECTS=$(CFILES:.c=.o)
DEPS=$(CFILES:.c=.d)
EXECUTABLE=extractor

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

-include $(DEPS)

clean:
	rm -f $(EXECUTABLE) $(OBJECTS) $(DEPS)

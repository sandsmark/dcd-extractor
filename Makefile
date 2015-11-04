CFILES=$(wildcard *.c)
OBJECTS=$(patsubst %.c, %.o, $(CFILES))
EXECUTABLE=extractor

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

DEPS=$(OBJECTS:.o=.d)
-include $(DEPS)

clean:
	rm -f $(EXECUTABLE) $(OBJECTS) $(DEPS)

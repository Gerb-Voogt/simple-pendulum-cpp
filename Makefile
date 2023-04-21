TARGET=pendulum

CXX=g++
CFLAGS=-Wall

all: $(TARGET).out

%.out : %.cpp
	$(CXX) $(CFLAGS) $< -o $@

clean:
	rm $(TARGET).out

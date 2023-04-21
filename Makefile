TARGET=pendulum

CXX=g++
CFLAGS=-Wall -g

all: $(TARGET).out

%.out : %.cpp
	$(CXX) $(CFLAGS) $< -o $@

clean:
	rm $(TARGET).out *.log

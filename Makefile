CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -Wall --std=c++11
LDLIBS=-lncurses

TARGET=nsnake

SRCS=src/main.cpp src/snake.cpp src/game.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)
	$(RM) $(TARGET)
	$(RM) *~ .depend

include .depend

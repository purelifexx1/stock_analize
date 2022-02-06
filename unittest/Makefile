CC=gcc
CXX=g++
RM= rm -f
IDIR=../
CXXFLAGS=-I$(IDIR) -std=c++17
LDDFLAGS=-g -lgtest -lgtest_main -lpthread

SRC_FILES=\
	./startTest.cc \
	./stockAnalizeTest.cc \
	../stockData.cc \
	../stockDataAlg.cc \
	../command.cc

all: $(SRC_FILES)
	$(CXX) $(SRC_FILES) $(CXXFLAGS) $(LDDFLAGS)
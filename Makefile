CC=gcc
CXX=g++
RM= rm -f
IDIR=./
CXFLAGS=-I$(IDIR) -std=c++17

SRC_FILES=\
	stockAnalize.cc \
	stockData.cc \
	stockDataAlg.cc \
	command.cc

all: $(SRC_FILES)
	$(CXX) $(SRC_FILES) $(CXFLAGS)

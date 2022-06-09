
ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs) 

CFLAGS = -Wall $(ROOTFLAGS) 
LIBS = $(ROOTLIBS) 

PROG = EventDisplay 
CXX = event_display.C  $(wildcard *.cc)

#PROG = MirrorFinder 
#CXX = mirror_finder.C 


all: $(PROG) 

$(PROG): $(CXX) 
	g++ $(CFLAGS) $(CXX) $(LIBS) -o $(PROG)

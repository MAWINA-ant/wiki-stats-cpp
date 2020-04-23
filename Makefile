cc=g++
param=-c -std=c++11

all: app

clean:
	rm -rf wiki *.o

app: wiki_stats.o wiki_graph.o utf8.o
	$(cc) -o wiki wiki_stats.o wiki_graph.o utf8.o

wiki_stats.o: wiki_stats.cpp
	$(cc) $(param) -o wiki_stats.o wiki_stats.cpp

wiki_graph.o: wiki_graph.cpp
	$(cc) $(param) -o wiki_graph.o wiki_graph.cpp
	
utf8.o: utf8.cpp
	$(cc) $(param) -o utf8.o utf8.cpp
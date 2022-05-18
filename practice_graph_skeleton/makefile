all: graph_skeleton

graph_skeleton: graph_skeleton.cpp
	g++ -std=c++11 -o graph_skeleton graph_skeleton.cpp

run: graph_skeleton
	./graph_skeleton input.txt output.txt

clean: graph_skeleton
	rm graph_skeleton
	rm output.txt
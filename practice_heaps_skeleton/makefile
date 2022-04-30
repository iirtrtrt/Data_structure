all: most_similar_websites_skeleton

most_similar_websites_skeleton: most_similar_websites_skeleton.cpp
	g++ -std=c++11 -o most_similar_websites_skeleton most_similar_websites_skeleton.cpp

run: most_similar_websites_skeleton
	./most_similar_websites_skeleton input1.txt output1.txt
	./most_similar_websites_skeleton input2.txt output2.txt

clean: most_similar_websites_skeleton
	rm most_similar_websites_skeleton
	rm output1.txt
	rm output2.txt
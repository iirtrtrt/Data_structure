all: use_hash_table_skeleton

use_hash_table_skeleton: use_hash_table_skeleton.cpp
	g++ -std=c++11 -o use_hash_table_skeleton use_hash_table_skeleton.cpp

run: use_hash_table_skeleton
	./use_hash_table_skeleton input1.txt output1.txt
	./use_hash_table_skeleton input2.txt output2.txt

clean: use_hash_table_skeleton
	rm use_hash_table_skeleton
	rm output1.txt
	rm output2.txt
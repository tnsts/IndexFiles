#include <iostream>
#include <fstream>
#include <ctime>
#include <limits.h>
using namespace std;

class  Index_files
{
public:
	int **main_data;
	int **index;
	int size;
	int proc, amount; // percentage of expansion, amount of blocks
	int block_interval;
	int *filled;

	Index_files();
	~Index_files();
	void insert(int key, int data);
	int search(int key);
	void change(int key, int new_data);
	void delete_key(int key);

private:
	int **temp_index;
	int **temp_main;
};

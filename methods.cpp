#include "files.h"

Index_files::Index_files(){
	proc = 5, amount = 10; // proc of zapas, amount of blocks
	block_interval = 1000;
	size = 0;
}

Index_files::~Index_files(){
	for(int i = 0; i < proc*amount; i++){
		delete [] index[i];
	}
	delete [] index;

	for(int i = 0; i < size; i++){
		delete [] main_data[i];
	}
	delete [] main_data;

	delete [] filled;
}

void Index_files::insert(int key, int data){
	if (filled[key / block_interval] >= proc){

		Index_files::temp_index = new int*[(proc + 1)*amount];
		for(int i = 0; i < (proc + 1)*amount; i++){
			Index_files::temp_index[i] = new int[2];
		}

		for(int i = 0; i < proc*amount; i++){
			Index_files::temp_index[i + i/proc][0] = index[i][0];
			Index_files::temp_index[i + i/proc][1] = index[i][1];
		}

		for(int i = 0; i < proc*amount; i++){
			delete [] index[i];
		}
		delete [] index;

		proc++;

		index = new int*[proc*amount];
		for(int i = 0; i < proc*amount; i++){
			index[i] = new int[2];
		}

		for(int i = 0; i < proc*amount; i++){
			index[i][0] = Index_files::temp_index[i][0];
			index[i][1] = Index_files::temp_index[i][1];
		}

		for (int i = 1; i <= amount; i++){
			index[i*proc - 1][0] = INT_MAX;
			index[i*proc - 1][1] = INT_MAX;
		}

		for(int i = 0; i < proc*amount; i++){
			delete [] Index_files::temp_index[i];
		}
		delete [] Index_files::temp_index;
	}

	if (filled[key / block_interval] == 0){
		index[proc*(key/block_interval)][0] = key;
		index[proc*(key/block_interval)][1] = size;
	} else {

		int curr = 0;
		for(int i = proc*(key/block_interval); i < proc*(key/block_interval + 1); i++){
				curr = i;
				if (index[i][0] > key){
				break;
			}
		}

		for(int i = proc*(key/block_interval + 1) - 1; i > curr; i--){
			index[i][0] = index[i - 1][0];
			index[i][1] = index[i - 1][1];
		}

		index[curr][0] = key;
		index[curr][1] = size;

	}

	if (size == 0){
			main_data = new int*[1];
			main_data[0] = new int[2];
			main_data[0][1] = data;
			main_data[0][0] = key;
			size++;
		}
		else {
			Index_files::temp_main = new int*[++size];
			for(int i = 0; i < size; i++){
				Index_files::temp_main[i] = new int[2];
			}

			for(int i = 0; i < size - 1; i++){
				Index_files::temp_main[i][0] = main_data[i][0];
				Index_files::temp_main[i][1] = main_data[i][1];
			}

			for(int i = 0; i < size - 1; i++){
				delete [] main_data[i];
			}
			delete [] main_data;

			main_data = new int*[size];
			for(int i = 0; i < size; i++){
				main_data[i] = new int[2];
			}

			for(int i = 0; i < size; i++){
				main_data[i][0] = Index_files::temp_main[i][0];
				main_data[i][1] = Index_files::temp_main[i][1];
			}

			for(int i = 0; i < size; i++){
				delete [] Index_files::temp_main[i];
			}
			delete [] Index_files::temp_main;

			main_data[size-1][0] = key;
			main_data[size-1][1] = data;

		filled[key/block_interval]++;
	}
}

int Index_files::search(int key){
	int count = 0;

	int mid;
	int left = (key/block_interval)*proc;
	int right = (key/block_interval)*proc + proc - 1;

	while (index[left][0] <= key && index[right][0] >= key){
		mid = left + ((key - index[left][0])*(right - left))/(index[right][0] - index[left][0]);
		count++;

		if (index[mid][0] < key) left = mid+1;
		else if (index[mid][0] > key) right = mid - 1;
		else{
	//		cout << "Count of comparing: " << count << endl;
			return mid;
		 }
	}
	if (index[left][0] == key){
	//	cout << ++count << endl;
		return left;
	}
	else return -1;
}

void Index_files::change(int key, int new_data){
	main_data[index[search(key)][1]][1] = new_data;
}

void Index_files::delete_key(int key){
	int block = key/block_interval;
	int index_to_delete = search(key);

	if (index_to_delete != proc*(block + 1) - 1){
		for(int i = index_to_delete; i < proc*(block + 1) - 1; i++){
			index[i][0] = index[i + 1][0];
			index[i][1] = index[i + 1][1];
		}
		index[proc*(block + 1) - 1][0] = INT_MAX;
		index[proc*(block + 1) - 1][1] = INT_MAX;
	} else {
		index[index_to_delete][0] = INT_MAX;
		index[index_to_delete][1] = INT_MAX;
	}
}

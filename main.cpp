#include "methods.cpp"
using namespace std;

int main(){

	srand(time(0));
	Index_files a;

	ofstream index_out("index.txt");
	ofstream data_out("data.txt");

  int key, data;

	a.index = new int*[a.proc*a.amount];
	for(int i = 0; i < a.proc*a.amount; i++){
		a.index[i] = new int[2];
	}

	for(int i = 0; i < a.proc*a.amount; i++){
		a.index[i][0] = INT_MAX;
		a.index[i][1] = INT_MAX;
	}

	a.filled = new int[a.amount];
	for(int i = 0; i < a.amount; i++){
		a.filled[i] = 0;
	}

for (int i = 0; i < 1000; i++){
	int in_key = rand()%100*100 + rand()%100;
	int in_data = rand()%10000;
	int s = a.search(in_key);
	if (s == -1) a.insert(in_key, in_data);
}

for(int i = 0; i < a.proc*a.amount; i++){
	index_out << a.index[i][0] << " " << a.index[i][1] << endl;
}

for (int i = 0; i < a.size; i++){
	data_out << a.main_data[i][0] << " " << a.main_data[i][1] << endl;
}

int menu;
while (true){
	cout<<"Choose:\n1 to insert, 2 to search, 3 to remove, 4 to change, 5 to update, 0 to exit" << endl;
	cin >> menu;

	if(menu == 1){
		int in_key, in_data;
		cin>>in_key>>in_data;
		int s = a.search(in_key);
		if (s == -1) a.insert(in_key, in_data);
		else cout << "Error of key" << endl;
	} else if(menu == 2){
		int s_key, s;
		cin >> s_key;
		s = a.search(s_key);
		if(s != -1) cout << a.main_data[a.index[s][1]][1] << endl;
		else cout << -1 <<endl;
	} else if(menu == 3){
		int r_key;
		cin>>r_key;
		a.delete_key(r_key);
	} else if(menu == 4){
		int in_key, in_data;
		cin>>in_key>>in_data;
		a.change(in_key, in_data);
	} else if (menu == 5){
		index_out.seekp(index_out.beg);
		for(int i = 0; i < a.proc*a.amount; i++){
			index_out << a.index[i][0] << " " << a.index[i][1] << endl;
		}
		data_out.seekp(data_out.beg);
		for (int i = 0; i < a.size; i++){
			data_out << a.main_data[i][0] << " " << a.main_data[i][1] << endl;
		}
	} else if (menu == 0) break;
}
return 0;
}

#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> esProductoDeTresConsecutivos(int N){
	vector<int> vec(3,0);
	for(int i=0; ;i++){
		int producto = i * (i+1) * (i+2);
		
		if(producto == N){
			vec[0] = i;
			vec[1] = i+1;
			vec[2] = i+2;
			return vec;
		}
		else if(producto > N){
			break;
		}
		
	}
	return vec; 
}

int main(int argc, char** argv){
	int N;
	vector<int> vec(3,0);
	
	if(argc < 2){
		cerr << "Error, introduce el numero del que quieres encontrar el producto." << endl;
	}else{
		N = stoi(argv[1]);
		vec = esProductoDeTresConsecutivos(N);
	}
	
	if(vec[0]!=0){
		cout << "El numero es producto de tres consecutivos." << endl;
		for(int i=0; i<3; i++){
			cout << vec[i] << endl;
		}
	}else{
	
		cout << "El numero no es producto de tres consecutivos." << endl;
	}
	
	return 0; 
}

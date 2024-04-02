#include <iostream>
#include <string>
using namespace std;

bool esProductoDeTresConsecutivos(int N) {
	for(int i=1; ;i++){
		int producto = i * (i+1) * (i+2);
		if(producto == N){
			return true;
		}
		if(producto > N){
			return false;
		}
	}
}

int main(int argc, char** argv){
	int N;
	
	if(argc < 2){
		cerr << "Error, introduce el numero del que quieres encontrar el producto." << endl;
	}else{
		N = stoi(argv[1]);
	}
	
	if(esProductoDeTresConsecutivos(N)){
		cout << "El numero es producto de tres consecutivos." << endl;
	}else{
		cout << "El numero no es producto de tres consecutivos." << endl;
	}
	
	return 0;
}

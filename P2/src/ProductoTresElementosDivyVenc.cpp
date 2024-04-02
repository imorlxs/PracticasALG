#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

vector<int> encontrarTresConsecutivos(int N){
	int low = 1;
	int high = cbrt(N) + 1;

	while(low <= high){
		int mid = low + (high - low) / 2;
	
		int producto = mid * (mid+1) * (mid+2);

		if (producto == N) {
			return {
				mid, mid+1, mid + 2
			};
		}else if (producto < N){
			low = mid + 1;
		}else {
			high = mid - 1;
		}
	}
	
	return{};

}

int main(int argc, char** argv){
	if(argc < 2){
		cerr << "Error, introduzca un numero" << endl;
		return -1;
	}

	int N;
	vector<int> vec(3,0);
	
	N = stoi(argv[1]);
	vec = encontrarTresConsecutivos(N);

	if (!vec.empty()){
		cout << "El numero " << N << " es producto de:";
		for(int i=0; i<3; i++){
			cout << " " << vec[i];
		}
		cout << endl;
	}else{
		cout << "El numero no es producto de tres numeros consecutivos :(" << endl;
	}

	return 0;

}

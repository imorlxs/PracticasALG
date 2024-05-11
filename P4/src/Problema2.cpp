#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to calculate the total convenience of a seating arrangement
int calculateConvenience(const vector<vector<int>>& convenienceMatrix, const vector<int>& seatingArrangement) {
    int totalConvenience = 0;
    int n = seatingArrangement.size();
    for (int i = 0; i < n; i++) {
        int leftNeighbor = (i - 1 + n) % n;
        int rightNeighbor = (i + 1) % n;
        totalConvenience += convenienceMatrix[seatingArrangement[i]][seatingArrangement[leftNeighbor]];
        totalConvenience += convenienceMatrix[seatingArrangement[i]][seatingArrangement[rightNeighbor]];
    }
    return totalConvenience;
}

// Backtracking function to find the optimal seating arrangement
void backtrack(vector<vector<int>>& convenienceMatrix, vector<int>& seatingArrangement, int currentGuest, int maxConvenience, int& bestConvenience, vector<int>& bestSeatingArrangement) {
    int n = convenienceMatrix.size();
    if (currentGuest == n) {
        int totalConvenience = calculateConvenience(convenienceMatrix, seatingArrangement);
        if (totalConvenience > bestConvenience) {
            bestConvenience = totalConvenience;
            bestSeatingArrangement = seatingArrangement;
        }
    } else {
        for (int i = 0; i < n; i++) {
            if (find(seatingArrangement.begin(), seatingArrangement.end(), i) == seatingArrangement.end()) {
                seatingArrangement.push_back(i);
                backtrack(convenienceMatrix, seatingArrangement, currentGuest + 1, maxConvenience, bestConvenience, bestSeatingArrangement);
                seatingArrangement.pop_back();
            }
        }
    }
}

int main() {
    int n = 4;
    vector<vector<int>> convenienceMatrix = {
        {0, 10, 20, 30},
        {10, 0, 15, 25},
        {20, 15, 0, 30},
        {30, 25, 30, 0}
    };

    vector<int> seatingArrangement;
    int bestConvenience = 0;
    vector<int> bestSeatingArrangement;

    backtrack(convenienceMatrix, seatingArrangement, 0, 0, bestConvenience, bestSeatingArrangement);

    cout << "Maximum convenience: " << bestConvenience << endl;
    cout << "Optimal seating arrangement: ";
    for (int i = 0; i < bestSeatingArrangement.size(); i++) {
        cout << bestSeatingArrangement[i] + 1 << " ";
    }
    cout << endl;

    return 0;
}
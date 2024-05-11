#include <iostream>
#include <chrono>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
class Senku{
  private:
    int remaining;

    class Move {
      public:
        pair<int, int> from;
        pair<int, int> to;

        Move(pair<int, int> from_, pair<int,int> to_) : from(from_), to(to_){}

        pair<int,int> getPegToRemove() const {
          return make_pair(from.first + to.first) / 2, (from.second + to.second / 2);
        }
    };

  public:
    bool hasWon(){
      return this.remaining == 1 && tablero[3][3] == 1;
    }

  vector<Move> getPossibleMoves() {
    vector<Move> moves;

    for (int rowIdx = 0; rowIdx < board.size(); ++rowIdx){
      for (int cellIdx = 0; cellIdx < board[rowIdx].size(); ++cellIdx){
        if (board[rowIdx][cellIdx] != 1) continue;

        pair<int, int> from = make_pair(rowIdx, cellIdx);

        // Izquierda -> Derecha
        if (cellIdx <= 4 && board[rowIdx][cellIdx + 1] == 1
            && board[rowIdx][cellIdx + 2] == 0)
          moves.push_back(Move(from, make_pair(rowIdx, cellIdx + 2)));

        // Right => Left
        if (cellIdx >= 2 && board[rowIdx][cellIdx - 1] == 1 && board[rowIdx][cellIdx - 2] == 0)
            moves.push_back(Move(from, make_pair(rowIdx, cellIdx - 2)));

        // Up => Down
        if (rowIdx <= 4 && board[rowIdx + 1][cellIdx] == 1 && board[rowIdx + 2][cellIdx] == 0)
            moves.push_back(Move(from, make_pair(rowIdx + 2, cellIdx)));

        // Down => Up
        if (rowIdx >= 2 && board[rowIdx - 1][cellIdx] == 1 && board[rowIdx - 2][cellIdx] == 0)
                moves.push_back(Move(from, make_pair(rowIdx - 2, cellIdx)));
      }
    }
    return moves;
  }

  Senku move(Move move){
    auto newBoard = board;
    auto toRemove = move.getPegToRemove();
    newBoard[move.from.first][move.from.second] = 0;
    newBoard[toRemove.first][toRemove.second] = 0;
    newBoard[move.to.first][move.to.second] = 1;

    return Senku(newBoard, remainingPegs - 1);
  }

  Senku(const vector<vector<int>>& initialBoard, int pegsRemaining) : board(initialBoard), pegsRemaining(remainingPegs) {}
  Senku(){
        board = {{-1,-1,1,1,1,-1,-1},
                         {-1,-1,1,1,1,-1,-1},
                         {1,1,1,1,1,1,1},
                         {1,1,1,0,1,1,1},
                         {1,1,1,1,1,1,1},
                         {-1,-1,1,1,1,-1,-1},
                         {-1,-1,1,1,1,-1,-1}};
        this->pegsRemaining = 33;

  }

Pair<Move*, bool> dfs(Solitaire game) {
    if (game.hasWon()) return make_pair(nullptr, true);

    // Leer de la memoria
    auto hash = game.getBoardHash();
    if (memory.find(hash) != memory.end())
        return memory[hash];

    auto moves = game.getPossibleMoves();
    if (moves.empty()) return make_pair(nullptr, false);

    // Jugar cada movimiento y llamar recursivamente. Elegir la primera solución encontrada.
    for (auto move : moves) {
        auto newGame = game.move(move);
        auto hasWon = dfs(newGame).second;

        // Devolver movimiento que llevó a la victoria y almacenar en la memoria
        if (hasWon) {
            memory[hash] = make_pair(move, true);
            return memory[hash];
        }
    }

    // Caso en que no se encontró ninguna solución.
    return std::make_pair(&moves[0], false);
}


};

int main(){
  Senku game;
     auto startTime = std::chrono::steady_clock::now();
    int counter = 0;
    while (!game.hasWon()) {
        counter++;
        auto move = game.dfs(game);
        game = game.move(*(move.first));
    }
    auto endTime = std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    std::cout << "Done in " << duration.count() << " ms\n";

    return 0;
}

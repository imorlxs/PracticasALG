#include <iostream>
#include <chrono>
#include <vector>
#include <utility>
#include <algorithm>
#include <functional>

using namespace std;
class Move
{
public:
  pair<int, int> from;
  pair<int, int> to;

  Move(pair<int, int> from_, pair<int, int> to_) : from(from_), to(to_) {}
  Move()
  {
    from.first = -1;
    from.second = -1;
    to.first = -1;
    to.second = -1;
  }

  pair<int, int> getPegToRemove() const
  {
    return make_pair((from.first + to.first) / 2, (from.second + to.second) / 2);
  }
};
class Senku
{
public:
  vector<vector<int>> board;
  int remaining;

  bool hasWon()
  {
    return this->remaining == 1 && board[3][3] == 1;
  }

  vector<Move> getPossibleMoves()
  {
    vector<Move> moves;

    for (int rowIdx = 0; rowIdx < board.size(); ++rowIdx)
    {
      for (int cellIdx = 0; cellIdx < board[rowIdx].size(); ++cellIdx)
      {
        if (board[rowIdx][cellIdx] != 1)
          continue;

        pair<int, int> from = make_pair(rowIdx, cellIdx);

        // Izquierda a derecha
        if (cellIdx <= 4 && board[rowIdx][cellIdx + 1] == 1 && board[rowIdx][cellIdx + 2] == 0)
          moves.push_back(Move(from, make_pair(rowIdx, cellIdx + 2)));

        // Derecha a izquierda
        if (cellIdx >= 2 && board[rowIdx][cellIdx - 1] == 1 && board[rowIdx][cellIdx - 2] == 0)
          moves.push_back(Move(from, make_pair(rowIdx, cellIdx - 2)));

        // Arriba a abajo
        if (rowIdx <= 4 && board[rowIdx + 1][cellIdx] == 1 && board[rowIdx + 2][cellIdx] == 0)
          moves.push_back(Move(from, make_pair(rowIdx + 2, cellIdx)));

        // Abajo a arriba
        if (rowIdx >= 2 && board[rowIdx - 1][cellIdx] == 1 && board[rowIdx - 2][cellIdx] == 0)
          moves.push_back(Move(from, make_pair(rowIdx - 2, cellIdx)));
      }
    }
    return moves;
  }

  Senku move(Move move)
  {
    if (move.from.first != -1)
    {

      auto newBoard = board;
      auto toRemove = move.getPegToRemove();
      newBoard[move.from.first][move.from.second] = 0;
      newBoard[toRemove.first][toRemove.second] = 0;
      newBoard[move.to.first][move.to.second] = 1;
      return Senku(newBoard, remaining - 1);
    }
    else
      return *this;
  }

  Senku(const vector<vector<int>> &initialBoard, int pegsRemaining) : board(initialBoard), remaining(pegsRemaining) {}
  Senku()
  {
    board = {{-1, -1, 1, 1, 1, -1, -1},
             {-1, -1, 1, 1, 1, -1, -1},
             {1, 1, 1, 1, 1, 1, 1},
             {1, 1, 1, 0, 1, 1, 1},
             {1, 1, 1, 1, 1, 1, 1},
             {-1, -1, 1, 1, 1, -1, -1},
             {-1, -1, 1, 1, 1, -1, -1}};
    this->remaining = 32;
  }

  pair<Move, bool> findSolution(Senku game)
  {
    if (game.hasWon())
      return make_pair(Move(), true);

    auto moves = game.getPossibleMoves();
    if (moves.empty())
      return make_pair(Move(), false);

    // Jugar cada movimiento y llamar recursivamente. Elegir la primera solución encontrada.
    for (auto move : moves)
    {
      auto newGame = game.move(move);
      auto hasWon = findSolution(newGame).second;

      // Devolver movimiento que llevó a la victoria
      if (hasWon)
      {
        return make_pair(move, true);
      }
    }

    // Caso en que no se encontró ninguna solución.
    return std::make_pair(moves[0], false);
  }

  size_t getBoardHash() const
  {
    std::hash<std::string> hasher;
    std::string boardString;
    for (const auto &row : board)
    {
      for (int cell : row)
      {
        boardString += std::to_string(cell);
      }
    }
    return hasher(boardString);
  }

  void toString()
  {
    for (int i = 0; i < board.size(); i++)
    {
      for (int j = 0; j < board.size(); j++)
      {
        if (board[i][j] == 0)
          cout << "-"
               << " ";
        else if (board[i][j] == 1)
          cout << "O"
               << " ";
        else
          cout << " "
               << " ";
      }
      cout << endl;
    }
  }
};

int main()
{
  Senku game;
  auto startTime = std::chrono::steady_clock::now();
  int counter = 0;
  while (!game.hasWon())
  {
    counter++;
    auto move = game.findSolution(game);
    game = game.move((move.first));
    game.toString();
    cout << "Quedan: " << game.remaining << " pegs " << endl;
  }
  auto endTime = std::chrono::steady_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
  std::cout << "Resuelto en  " << duration.count() << " ms\n";

  return 0;
}

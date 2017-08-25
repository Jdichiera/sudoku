#pragma once
#include <iostream>
#include <set>
#include <vector>
#include <iterator> // inserter
#include <algorithm> // set_difference
#include <time.h> 
#include <random>


struct Coordinates {
	int row;
	int col;
};



class BoardGenerator {
public:

	BoardGenerator();
	int board[9][9];
	bool FillCells();
	void GenerateBoard();
	std::vector<Coordinates> GetEmptyCells();
	Coordinates FindEmptyCell();
	bool DuplicateInRow(int row, int value);
	bool DuplicateInColumn(int col, int value);
	bool DuplicateInBlock(int col, int row, int value);
	bool PlaceNumber(int col, int row, int value);
	std::set<int> FindPossibleValues(Coordinates emptyCell);
	void PrintBoard();
	bool ValidateBoard();
};
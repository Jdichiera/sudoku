#include "board-generator.h"

bool BoardGenerator::FillCells() {
	//std::cout << "\nFill cells";
	std::vector<Coordinates> emptyCellList = GetEmptyCells();
	while (!emptyCellList.empty()) {
		int random = rand();
		Coordinates tempCell = emptyCellList[0];
		emptyCellList.erase(emptyCellList.begin());
		std::set<int> possibleValues = FindPossibleValues(tempCell);
		std::vector<int> shuffledValues;
		for (auto number : possibleValues) {
			shuffledValues.push_back(number);
		}
		std::shuffle(std::begin(shuffledValues), std::end(shuffledValues), std::default_random_engine(random));
		for (auto value : shuffledValues) {
			board[tempCell.row][tempCell.col] = value;
			if (emptyCellList.empty()) {
				return true;
			}

			if (FillCells()) {
				return true;
			}
		}
		board[tempCell.row][tempCell.col] = 0;
		emptyCellList.push_back(tempCell);
		return false;
	}
}

std::vector<Coordinates> BoardGenerator::GetEmptyCells() {
	//std::cout << "\nGet empty cells";
	std::vector<Coordinates> emptyCells;
	Coordinates cell;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board[i][j] == 0) {
				cell.row = i;
				cell.col = j;
				emptyCells.push_back(cell);
			}
		}
	}

	return emptyCells;
}
std::set<int> BoardGenerator::FindPossibleValues(Coordinates emptyCell) {
	//std::cout << "\nFindPossibleValues";
	std::set<int> usedNumbers = {};
	std::set<int> allValues = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::set<int> possibleValues = {};
	std::vector<Coordinates> neighbors;
	Coordinates neighbor;
	// Add row values to set
	for (int i = 0; i < 9; i++) {
		neighbor.row = i;
		neighbor.col = emptyCell.col;
		neighbors.push_back(neighbor);
	}
	// Add col values to set
	for (int i = 0; i < 9; i++) {
		neighbor.row = emptyCell.row;
		neighbor.col = i;
		neighbors.push_back(neighbor);
	}
	// Add block values to set
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			neighbor.row = emptyCell.row - emptyCell.row % 3 + i;
			neighbor.col = emptyCell.col - emptyCell.col % 3 + j;
			neighbors.push_back(neighbor);
		}
	}
	for (auto cell : neighbors) {
		usedNumbers.insert(board[cell.row][cell.col]);
	}
	std::set_difference(allValues.begin(), allValues.end(),
		usedNumbers.begin(), usedNumbers.end(),
		std::inserter(possibleValues, possibleValues.begin()));
	return possibleValues;
}
bool BoardGenerator::PlaceNumber(int col, int row, int value) {
	//std::cout << "\nPlaceNumber";
	bool rowDuplicate = DuplicateInRow(row, value);
	bool colDuplicate = DuplicateInColumn(col, value);
	bool blockDuplicate = DuplicateInBlock(col, row, value);
	if (!rowDuplicate && !colDuplicate && !blockDuplicate) {
		return true;
	}
	return false;
}

bool BoardGenerator::DuplicateInBlock(int col, int row, int value) {
	//std::cout << "\nDuplicateInBlock";
	int colStart = col - col % 3;
	int rowStart = row - row % 3;
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (board[row + rowStart][col + colStart] == value) {
				return true;
			}
	return false;
}

bool BoardGenerator::DuplicateInRow(int row, int value) {
	//std::cout << "\nDuplicateInRow";
	for (int col = 0; col < 9; col++) {
		if (board[row][col] == value) {
			return true;
		}
	}
	return false;
}


bool BoardGenerator::DuplicateInColumn(int col, int value) {
	//std::cout << "\nDuplicateInColumn";
	for (int row = 0; row < 9; row++) {
		if (board[row][col] == value) {
			return true;
		}
	}
	return false;
}

void BoardGenerator::PrintBoard() {
	//std::cout << "\nPrintBoard";
	std::cout << "\n---------+---------+---------" << std::endl;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (j == 3 || j == 6) {
				std::cout << "|";
			}
			std::cout << " " << board[i][j] << " ";
		}
		if (i == 2 || i == 5) {
			std::cout << "\n---------+---------+--------";
		}
		std::cout << std::endl;
	}
	std::cout << "---------+---------+---------" << std::endl;
}

void BoardGenerator::GenerateBoard() {
	//std::cout << "\nGenerate Board";
	FillCells();
}

BoardGenerator::BoardGenerator() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			board[i][j] = 0;
		}
	}
}

bool BoardGenerator::ValidateBoard() {
	bool validBoard = false;

	return validBoard;
}





#pragma once

class Position{
private:
	int row;
	int col;

public:
	Position();

	Position(int row, int col);

	~Position();

	Position operator=(Position other);

	int getRow();

	int getCol();

	void setRow(int nRow);

	void setCol(int nCol);

    void set(int nrow, int ncol);

	bool operator==(const Position& other) const;
};


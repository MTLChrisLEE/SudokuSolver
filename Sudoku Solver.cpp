#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>


//FUNCTION DECLARATION//
void MainPage();
void PrintBaseSudoku(int array[9][9]);
int FillSudoku(int array[9][9], int x, int i, int j);
void PrintCurrentSudoku(int array[9][9]);
void EditSudoku(int array[9][9]);
void PrintFinalSudoku(int array[9][9]);
// void Solver();
bool IsZero(int array[9][9], int &i, int &j);
bool AlreadyInRow(int array[9][9], int i, int n);
bool AlreadyInBox(int array[9][9], int startrow, int startcol, int n);
bool AlreadyInColumn(int array[9][9], int j, int n);
bool SudokuSolver(int array[9][9]);
bool IsGood(int array[9][9], int i, int j, int n);
void PrintAnswer(int array[9][9]);

int main()
{
	int sudoku[9][9] = { { 0},
	{ 0 },
	{ 0 },
	{ 0 },
	{ 0 },
	{ 0 },
	{ 0 },
	{ 0 },
	{ 0 }
	};
	
	MainPage();
	PrintBaseSudoku(sudoku);
	FillSudoku(sudoku, 0, 0, 0);
	PrintCurrentSudoku(sudoku);
	EditSudoku(sudoku);
	PrintFinalSudoku(sudoku);

	printf("\n\n\n");


	if (SudokuSolver(sudoku) == true)
		PrintAnswer(sudoku);
	else
		printf("No solution exists");
	
	int x;
	std::cin >> x;
	

    return 0;
}


//MAIN PAGE//
void MainPage()
{
	printf("\n\n\n");
	std::cout << "\t*****  *   *  ***     ***   *   *  *   *" << std::endl;
	std::cout << "\t*      *   *  *  *   *   *  *  *   *   *" << std::endl;	
	std::cout << "\t*****  *   *  *   *  *   *  ***    *   *" << std::endl;
	std::cout << "\t    *  *   *  *  *   *   *  *  *   *   *" << std::endl;
	std::cout << "\t*****  *****  ***     ***   *   *  *****" << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
  
	std::cout << "\t\t\t*****   ***  *     *   * *****  *****" << std::endl;
	std::cout << "\t\t\t*      *   * *     *   * *      *   *" << std::endl;
	std::cout << "\t\t\t*****  *   * *     *   * *****  *****" << std::endl;
	std::cout << "\t\t\t    *  *   * *      * *  *      * *  " << std::endl;
	std::cout << "\t\t\t*****   ***  *****   *   *****  *   *" << std::endl;
	std::cout << "Created by SangHyuk(Chris) LEE" << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "\t\tPress Space bar to start!!" << std::endl;
	std::cout << "\t\tPress any other key to exit!!" << std::endl;

	int start;

	start=_getch();

	if (start == 32)
	{
		system("cls");
	}
	else
	{
		exit(1);
	}
}

//BASE SUDOKU//
void PrintBaseSudoku(int array[9][9])
{
	int i, j = 0;
		
	for (i = 0; i <= 8; i++)
	{
		for (j = 0; j <= 8; j++)
		{
		std::cout << array[i][j];
		std::cout << " ";
		}
		std::cout << std::endl;
	}

	printf("\n\n");
	std::cout << "This is the base sudoku" << std::endl;
	std::cout << "Input your Sudoku" << std::endl;
	printf("\n\n");

}

//FILL SUDOKU//
int FillSudoku(int array[9][9], int x, int i, int j)
{
	int inputting=13;

	while (inputting == 13)
	{
		std::cout << " Number:";
		std::cin >> x; std::cout << " ";
		std::cout << "Row position(starts with 1): ";
		std::cin >> i; std::cout<< " ";
		std::cout << "Column position(starts with 1): ";
		std::cin >> j; std::cout<< std::endl;
		array[i-1][j-1] = x;
		std::cout << "Do you want to put more numbers? If so, press Enter. If not, press any key" << std::endl;
		inputting = _getch();
		printf("\n");
	} 
	
	PrintCurrentSudoku(array);
	

	return x;
}

//PRINT CURRENT SUDOKU//
void PrintCurrentSudoku(int array[9][9])
{
	printf("\n\n\n");
	std::cout << "This is your sudoku\n\n" << std::endl;

	int i, j = 0;
	for (i = 0; i <= 8; i++)
	{
		for (j = 0; j <= 8; j++)
		{
			std::cout << array[i][j];
			std::cout << " ";
		}
		std::cout << std::endl;
	}

	
}

//EDIT SUDOKU//
void EditSudoku(int array[9][9])
{
	int answer;

	printf("\n\n");
	std::cout << "Is this your sudoku?" << std::endl;
	std::cout << "y/n ?";
	
	answer = _getch();

	printf("\n\n");
	
	if (answer == 110)
	{
		FillSudoku(array,0, 0, 0);
		EditSudoku(array);
	}
	else if (answer == 121)
	{
		system("cls");
	}

		

}

//PRINT FINAL SUDOKU//
void PrintFinalSudoku(int array[9][9])
{
	printf("\n\n\n");
	std::cout << "This is your final sudoku!! You cannot change it!!!" << std::endl;
	printf("\n\n");

	int i, j = 0;
	for (i = 0; i <= 8; i++)
	{
		for (j = 0; j <= 8; j++)
		{
			std::cout << array[i][j];
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}




bool SudokuSolver(int array[9][9])
{
	int i, j;


	// If there isn't any zero, it is solved. 
	if (!IsZero(array, i, j))
		return true;

	// An empty box, consider a number that to be put
	for (int num = 1; num <= 9; num++)
	{
		//If num can be writen in the empty box.
		if (IsGood(array, i, j, num))
		{
			// Put it.
			array[i][j] = num;

			// Recursion!!
			if (SudokuSolver(array))
				return true;

			// If it doesn't work, make it zero. Then, try the next number.
			array[i][j] = 0;
		}
	}
	return false; // this triggers backtracking
}

//IF A DIGIT IS ALREADY IN A ROW, THAT DIGIT CANNOT BE USED IN ANY OTHER BOX IN THE ROW.
bool IsZero(int array[9][9], int &i, int &j)
{
	for (i = 0; i <= 8; i++)
		for (j = 0; j <= 8; j++)
			if (array[i][j] == 0)
				return true;
	return false;
}


//IF A DIGIT IS ALREADY IN A ROW, THAT DIGIT CANNOT BE USED IN ANY OTHER BOX IN THE ROW.
bool AlreadyInRow(int array[9][9], int i, int n)
{
	for (int j = 0; j <=8; j++)
		if (array[i][j] == n)
			return true;
	return false;
}

//IF A DIGIT IS ALREADY IN A COLUMN, THAT DIGIT CANNOT BE USED IN ANY OTHER BOX IN THE COLUMN.
bool AlreadyInColumn(int array[9][9], int j, int n)
{
	for (int i = 0; i <=8; i++)
		if (array[i][j] == n)
			return true;
	return false;
}

//IF A DIGIT IS ALREADY IN 3X3 BOX, THAT DIGIT CANNOT BE USED IN ANY OTHER BOX IN THE BOX.
bool AlreadyInBox(int array[9][9], int BoxRow, int BoxCol, int n)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (array[i + BoxRow][j + BoxCol] == n)
				return true;
	return false;
}

//CHECK IF THE THE NUMBER CAN BE PUT.IN OTHER WORDS, FALSE FOR ALL THREE "ALREADY" FUNCTIONS
bool IsGood(int array[9][9], int i, int j, int n)
{
	/* Check if 'num' is not already placed in current row,
	current column and current 3x3 box */
	return !AlreadyInRow(array, i, n) &&
		!AlreadyInColumn(array, j, n) &&
		!AlreadyInBox(array, i - i % 3, j - j % 3, n);
}


void PrintAnswer(int array[9][9])
{
	for (int i = 0; i <=8; i++)
	{
		for (int j = 0; j <=8; j++)
			printf("%2d", array[i][j]);
		printf("\n");
	}
}

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "help.h"
#include <conio.h>
using namespace std;

// Inserts destroyer gem value where gems are in the shape of an elbow and eliminates surrounding gems in the elbow
void ElbowElimination(int Board[][8], int& score)
{
	//For elimination starting from left hand side
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++) 
		{
			if ((Board[i][j] == Board[i][j + 1] && Board[i][j + 1] == Board[i][j + 2]) && (Board[i][j] == Board[i + 1][j] && Board[i + 1][j] == Board[i + 2][j]))
			{
				Board[i][j] = -5;
				Board[i][j + 1] = -1;
				Board[i][j + 2] = -1;
				Board[i + 1][j] = -1;
				Board[i + 2][j] = -1;
				score = score + 500;

			}
		}
	}
	//For elimination starting from right hand side
	for (int i = 7; i > 1; i--)
	{
		for (int j = 0; j < 7; j++)
		{
			if ((Board[i][j] == Board[i][j + 1] && Board[i][j + 1] == Board[i][j + 2]) && (Board[i][j] == Board[i - 1][j] && Board[i - 1][j] == Board[i - 2][j]))
			{
				Board[i][j] = -5;
				Board[i][j + 1] = -1;
				Board[i][j + 2] = -1;
				Board[i - 1][j] = -1;
				Board[i - 2][j] = -1;
				score = score + 500;

			}
		}
	}
}
//Eliminates 3 equal gems from matrix
void EliminateGems(int Board[][8], int& score)
{
	//For horizontal elimination
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (Board[i][j] == Board[i][j + 1] && Board[i][j + 1] == Board[i][j + 2])
			{
				Board[i][j] = -1;
				Board[i][j + 1] = -1;
				Board[i][j + 2] = -1;
				score = score + 100;
			}
		}
	}
	// For vertical elimination
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 6; i++)
		{
			if (Board[i][j] == Board[i + 1][j] && Board[i + 1][j] == Board[i + 2][j])
			{
				Board[i][j] = -1;
				Board[i + 1][j] = -1;
				Board[i + 2][j] = -1;
				score = score + 100;
			}
		}
	}
}
//Moves Gems downwards on board when they are eliminated
void ShiftDown(int Board[][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (Board[i][j] == -1)
			{
				for (int k = j; k > 0; k--)
				{
					swap(Board[i][k], Board[i][k - 1]);
				}

			}
		}
	}
}
// Checks if a row or a column has four equal gems consecutively and inserts a special gem number in the row (i_player) and column (j_player) where the player swapped a gem.
void SpecialGemInsert(int Board[][8], int i_player, int j_player, int horizontal_check)
{
	if (horizontal_check == 1)
	{
		for (int j = 0; j < 5; j++)
		{
			if (Board[i_player][j] == Board[i_player][j + 1] && Board[i_player][j + 1] == Board[i_player][j + 2] && Board[i_player][j + 2] == Board[i_player][j + 3] && j <= j_player)
				Board[i_player][j_player] = -4;
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			if (Board[i][j_player] == Board[i + 1][j_player] && Board[i + 1][j_player] == Board[i + 2][j_player] && Board[i + 2][j_player] == Board[i + 3][j_player] && i <= i_player)
				Board[i_player][j_player] = -4;
		}
	}
}
// Checks if the user has swapped the gem into a position where it matches with other gems and returns a boolean value that tells if a swap is possible or not
bool SwapPossible(int Board[][8], int i_player, int j_player)
{
	bool possible = false;
	for (int j = 0; j < 6; j++)
	{
		if (Board[i_player][j] == Board[i_player][j + 1] && Board[i_player][j + 1] == Board[i_player][j + 2] && j <= j_player)
		{
			possible = true;
		}
	}
	for (int i = 0; i < 6; i++)
	{
		if (Board[i][j_player] == Board[i + 1][j_player] && Board[i + 1][j_player] == Board[i + 2][j_player] && i <= i_player)
		{
			possible = true;
		}
	}
	return possible;
}


// Enters random values at slots with -1 values
void UpdateBoard(int Board[][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (Board[i][j] == -1)
				Board[i][j] = rand() % 5 + 1;
		}
	}
}
// Converts a row number to a coordinate which can be used to display a gem graphically
int convert_rows(int i)
{
	int x = 50;
	for (int m = 0; m < i; m++)
	{
		x = x + 50;
	}
	return x;
}
// Converts a column number to a coordinate which can be used to display a gem graphically
int convert_columns(int j)
{
	int y = 50;
	for (int m = 0; m < j; m++)
	{
		y = y + 50;
	}
	return y;
}
// Function with fill color in rectangle
void myColorRectangle(int x1, int y1, int x2, int y2, int R, int G, int B, int fR, int fG, int fB)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(fR, fG, fB)); //Fill color can also be passed as parameter to the function!!!

	SelectObject(device_context, brush);

	Rectangle(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);
}
// Creates ellipse with fill color
void myColorEllipse(int x1, int y1, int x2, int y2, int R, int G, int B, int fR, int fG, int fB)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(fR, fG, fB));  //Fill color is black
	SelectObject(device_context, brush);
	Ellipse(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);


}
// Creates line with colors
void myColorLine(int x1, int y1, int x2, int y2, int color1, int color2, int color3) //use three 3 integers if you want colored lines.
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(color1, color2, color3)); //2 is the width of the pen
	SelectObject(device_context, pen);
	MoveToEx(device_context, x1, y1, NULL);
	LineTo(device_context, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
}

//Constructs destroyer gem
void DestroyerGem(int x, int y)
{
	myColorLine(x + 25, y + 10, x + 10, y + 40, 255, 0, 127);
	myColorLine(x + 25, y + 10, x + 40, y + 40, 255, 0, 127);
	myColorLine(x + 10, y + 40, x + 40, y + 40, 255, 0, 127);
}

// Constructs the triangle gem
void MakeTriangleGem(int x, int y)
{
	myColorLine(x + 25, y + 10, x + 10, y + 40, 51, 255, 255);
	myColorLine(x + 25, y + 10, x + 40, y + 40, 51, 255, 255);
	myColorLine(x + 10, y + 40, x + 40, y + 40, 51, 255, 255);
}
// Constructs the square gem
void MakeSquareGem(int x, int y)
{
	myColorRectangle(x + 10, y + 10, x + 40, y + 40, 255, 255, 255, 144, 238, 144);
}
// Constructs circle gem
void MakeCircleGem(int x, int y)
{
	myColorEllipse(x + 10, y + 10, x + 40, y + 40, 255, 255, 255, 102, 0, 204);
}
// Constructs diamond gem
void MakeDiamondGem(int x, int y)
{
	myLine(x + 10, y + 25, x + 25, y + 10, 255);
	myLine(x + 25, y + 10, x + 40, y + 25, 255);
	myLine(x + 10, y + 25, x + 25, y + 40, 255);
	myLine(x + 25, y + 40, x + 40, y + 25, 255);
}
// Constructs pentagon gem
void MakePentagonGem(int x, int y)
{
	myColorLine(x + 10, y + 25, x + 25, y + 10, 255, 255, 0);
	myColorLine(x + 25, y + 10, x + 40, y + 25, 255, 255, 0);
	myColorLine(x + 10, y + 25, x + 12, y + 40, 255, 255, 0);
	myColorLine(x + 40, y + 25, x + 37, y + 40, 255, 255, 0);
	myColorLine(x + 12, y + 40, x + 37, y + 40, 255, 255, 0);
}
void MakeFlameGem(int x, int y)
{
	myColorLine(x + 25, y + 10, x + 10, y + 40, 255, 255, 0);
	myColorLine(x + 25, y + 10, x + 40, y + 40, 255, 255, 0);
	myColorLine(x + 10, y + 40, x + 40, y + 40, 255, 255, 0);
}
// Displays cursor on board
void DisplayCursor(int x, int y, int color1, int color2, int color3)
{
	myColorLine(x, y, x + 50, y, color1, color2, color3);
	myColorLine(x, y + 50, x + 50, y + 50, color1, color2, color3);
	myColorLine(x, y, x, y + 50, color1, color2, color3);
	myColorLine(x + 50, y, x + 50, y + 50, color1, color2, color3);
}

// Displays graphical board on console
void DisplayBoard()
{
	myColorRectangle(50, 50, 450, 450, 255, 0, 0, 102, 102, 255);
	for (int i = 100; i < 450; i = i + 50)
	{
		myLine(50, i, 450, i, 255);
	}
	for (int j = 100; j < 450; j = j + 50)
	{
		myLine(j, 50, j, 450, 255);
	}
}
// Eliminates the row and column at which the destroyer gem is placed by putting -1 at the entire row and column
void ExplosionElimination(int Board[][8], int i, int j)
{
	for (int row = 0; row < 8; row++)
		Board[row][j] = -1;
	for (int col = 0; col < 8; col++)
		Board[i][col] = -1;
}
//Adds explosion
void Explosion(int x, int y)
{
	int selector = 1;
	int x_up = x, y_up = y, x_down = x, y_down = y, x_left = x, y_left = y;
	while (x < 400 || y_up > 50 || y_down < 400 || x_left > 50)
	{
		if (selector == 1)
		{
			if (x < 400)
				myColorLine(x + 25, y + 25, x + 50, y, 255, 255, 0); // for right hand side
			if (y_up > 50)
				myColorLine(x_up + 25, y_up + 25, x_up, y_up, 255, 255, 0); // for upwards
			if (y_down < 400)
				myColorLine(x_down + 25, y_down + 25, x_down, y_down + 50, 255, 255, 0); // for downwards
			if (x_left > 50)
				myColorLine(x_left + 25, y_left + 25, x_left, y_left + 50, 255, 255, 0); // for left hand side
			selector = 0;
		}
		else
		{
			if (x < 400)
				myColorLine(x + 50, y, x + 75, y + 25, 255, 255, 0); // for right hand side
			if (y_up > 50)
				myColorLine(x_up, y_up, x_up + 25, y_up - 25, 255, 255, 0); // for upwards
			if (y_down < 400)
				myColorLine(x_down, y_down + 50, x_down + 25, y_down + 75, 255, 255, 0); // for downwards
			if (x_left > 50)
				myColorLine(x_left, y_left + 50, x_left - 25, y_left + 25, 255, 255, 0); // for left hand side
			x = x + 50;
			y_up = y_up - 50;
			y_down = y_down + 50;
			x_left = x_left - 50;
			selector = 1;
		}
	}
}
//Adds gems to the board according to the numbers in the slots of the matrix
void AddGems(int Board[][8], int& explosion_check)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (Board[i][j] == 1)
				MakeTriangleGem(convert_rows(i), convert_columns(j)); // adds triangle gem where value is 1
			else if (Board[i][j] == 2)
				MakeSquareGem(convert_rows(i), convert_columns(j)); // adds square gem where value is 2
			else if (Board[i][j] == 3)
				MakeCircleGem(convert_rows(i), convert_columns(j)); // adds circle gem where value is 3
			else if (Board[i][j] == 4)
				MakeDiamondGem(convert_rows(i), convert_columns(j)); // adds diamond gem where value is 4
			else if (Board[i][j] == 5)
				MakePentagonGem(convert_rows(i), convert_columns(j)); // adds pentagon gem where value is 5
			else if (Board[i][j] == -4)
				MakeFlameGem(convert_rows(i), convert_columns(j)); // adds special gem where value is -4
			else if (Board[i][j] == -5)
			{
				DestroyerGem(convert_rows(i), convert_columns(j)); //Adds destroyer gem
			}
		}
	}
}
void Explosion2(int x, int y)
{
	if (x + 75 < 450)
		myWidthColorLine(x + 25, y + 25, x + 75, y + 25, 255, 0, 0, 5); // for right hand side
	if (y - 25 > 50)
		myWidthColorLine(x + 25, y + 25, x + 25, y - 25, 255, 0, 0, 5); // for upwards
	if (x - 25 > 50)
		myWidthColorLine(x + 25, y + 25, x - 25, y + 25, 255, 0, 0, 5); // for left hand side
	if (y + 75 < 450)
		myWidthColorLine(x + 25, y + 25, x + 25, y + 75, 255, 0, 0, 5); // for downwards
}
// checks if a row or column has a special gem of value -5. If flag is passed as one, it checks a column, otherwise a row. It also gives the positions of the flame gem and destroyer gem, which are passed by reference
bool HasSpecial(int Board[][8], int column, int row, bool flag, int& special_gem_flag, int& position_x, int& position_y, int& position2_x, int& position2_y)
{
	special_gem_flag = 0;
	bool found = false;
	if (flag == 1)
	{
		for (int i = column; i < column + 3 && found == false; i++)
		{
			if (Board[row][i] == -5)
			{
				found = true;
				special_gem_flag = 1; // gem type checking flag set to 1 if destroyer gem is found
				position2_x = row; // saving position of destroyer gem
				position2_y = i; // saving position of destroyer gem
			}
			else if (Board[row][i] == -4)
			{
				found = true;
				special_gem_flag = 2; // gem type checker flag set to 2 if flame gem is found
				position_x = row; // saving position of flame gem
				position_y = i; // saving position of flame gem
			}
		}
	}
	else
	{
		for (int j = row; j < row + 3 && found == false; j++)
		{
			if (Board[j][column] == -5)
			{
				found = true;
				special_gem_flag = 1;
				position2_x = j;
				position2_y = column;
			}
			else if (Board[j][column] == -4)
			{
				found = true;
				special_gem_flag = 2;
				position_x = j;
				position_y = column;
			}
		}
	}
	return found;
}
// Checks if a special gem has been with two triangle together and does an explosion if the condition is true
void SpecialGemElimination(int Board[][8], int& score)
{
	// for horizontal elimination
	int special_gem_flag, position_x, position_y, position2_x, position2_y;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (HasSpecial(Board, j, i, 1, special_gem_flag, position_x, position_y, position2_x, position2_y))
			{
				if (Board[i][j] == Board[i][j + 1] || Board[i][j] == Board[i][j + 2] || Board[i][j + 1] == Board[i][j + 2] && (Board[i][j] == 1 || Board[i][j + 1] == 1)) // checking if the special gem has been matched with two equal gems
				{
					if (special_gem_flag == 1) // checking gem type
					{
						Explosion(convert_rows(position2_x), convert_columns(position2_y));
						Sleep(700);
						for (int k = 0; k < 8; k++) // clearing out a row
						{
							Board[i][k] = -1;
						}
						for (int k = 0; k < 8; k++) // clearing out a column
						{
							Board[k][j] = -1;
						}
						score = score + 1000;
					}
					else if (special_gem_flag == 2) // checking gem type
					{
						Explosion2(convert_rows(position_x), convert_columns(position_y));
						Sleep(700);
						// clearing out gems inside explosion area
						Board[position_x][position_y] = -1;
						if (position_x < 7)
							Board[position_x + 1][position_y] = -1;
						else if (position_x > 0)
							Board[position_x - 1][position_y] = -1;
						else if (position_y < 7)
							Board[position_x][position_y + 1] = -1;
						else if (position_y > 0)
							Board[position_x][position_y - 1] = -1;
						score = score + 500;
					}
				}
			}
		}
	}
	// for vertical elimination
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 6; i++)
		{
			if (HasSpecial(Board, j, i, 0, special_gem_flag, position_x, position_y, position2_x, position2_y))
			{
				if (Board[i][j] == Board[i + 1][j] || Board[i][j] == Board[i + 2][j] || Board[i + 1][j] == Board[i + 2][j] && (Board[i][j] == 1 || Board[i + 1][j] == 1))
				{
					if (special_gem_flag == 1)
					{
						Explosion(convert_rows(position2_x), convert_columns(position2_y));
						Sleep(700);
						Board[i][j] = -1;
						for (int k = 0; k < 8; k++)
						{
							Board[i][k] = -1;
						}
						for (int k = 0; k < 8; k++)
						{
							Board[k][j] = -1;
						}
						score = score + 1000;
					}
					else if (special_gem_flag == 2)
					{
						Explosion2(convert_rows(position_x), convert_columns(position_y));
						Sleep(700);
						Board[position_x][position_y] = -1;
						if (position_x < 7)
							Board[position_x + 1][position_y] = -1;
						else if (position_x > 0)
							Board[position_x - 1][position_y] = -1;
						else if (position_y < 7)
							Board[position_x][position_y + 1] = -1;
						else if (position_y > 0)
							Board[position_x][position_y - 1] = -1;
						score = score + 500;
					}
				}
			}
		}
	}
}

//Adds a bar that shows time
void Timer(int x, int y)
{
	myColorRectangle(x, y, x + 240, y + 20, 255, 0, 0, 0, 255, 0);
}

int main()
{
	int Board[8][8], key, cursor_x = 50, cursor_y = 50, Board_update_check, player_x = 0, player_y = 0, selected = 0, selected_row, selected_column, score = 0, x = 700, total_time = 0, explosion_check = 0;
	time_t running_time, end;
	srand(time(0));
	for (int i = 0; i < 8; i++) // adds random gems to matrix
	{
		for (int j = 0; j < 8; j++)
		{
			Board[i][j] = rand() % 5 + 1;
		}
	}
	for (int i = 0, y = 0; i < 100; i++, y = y + 10) // to create background with random colors
	{
		for (int j = 0, x = 0; j < 100; j++, x = x + 10)
		{
			myColorRectangle(x, y, x + 10, y + 10, 255, 255, 255, rand() % 256, rand() % 256, rand() % 256);
		}
	}
	DisplayBoard(); // Displays grid
	DisplayCursor(cursor_x, cursor_y, 0, 255, 0); // Displays cursor
	AddGems(Board, explosion_check); // adds gem graphics
	Timer(460, 140); // adds time bar
	gotoxy(52, 4); // goes to position x, y
	cout << "Score: " << score; // prints score
	gotoxy(52, 5); // goes to position x, y
	cout << "Time remaining: "; 
	time(&running_time); // begins time calculation
	while (total_time < 120) // loop to run game until 2 minutes have passed
	{
		Board_update_check = 0; // flag to check if board needs to be updated and displayed in the second while loop
		if (isCursorKeyPressed(key) == 1) // checks if a cursor key is pressed
		{
			if (key == 1)
			{
				DisplayCursor(cursor_x, cursor_y, 0, 0, 0); // Displays the cursor at the position of the player without color for moving animation
				cursor_x = cursor_x - 50; // decrements cursor_x position as player is moving backwards
				player_x = player_x - 1; // decrements player_x position as player is moving backwards
 				if (player_x < 0) // resets player_x position if it is out of range of matrix
					player_x = 7;
				if (cursor_x < 50) // resets cursor_x position if it is out of range of graphical board
					cursor_x = 400;
				DisplayCursor(cursor_x, cursor_y, 0, 255, 0); // Displays new position of cursor
				if (selected == 1) // Checks if the player has previously selected a gem and runs the following code if condition if true
				{
					swap(Board[player_x][player_y], Board[selected_row][selected_column]); // swaps gems
					//AddGems(Board, explosion_check); // adds gems graphically
					//Sleep(100); //shows the user the gems have been swapped
					//if (SwapPossible(Board, player_x, player_y) == 0)
					//{
					//	swap(Board[player_x][player_y], Board[selected_row][selected_column]); // swaps the gems back if swap is not possible
					//}
					SpecialGemInsert(Board, player_x, player_y, 0); // adds special gem if four gems are equal
					SpecialGemInsert(Board, player_x, player_y, 1); // adds special gem if four gems are equal
					selected = 0; // selected variable is reset
				}
				Board_update_check = 1; // Board_update_check variable is set to 1 as the board needs to be updated after selection
			}
			else if (key == 2)
			{
				DisplayCursor(cursor_x, cursor_y, 0, 0, 0);
				cursor_y = cursor_y - 50; // decrements cursor_y as player is moving upwards
				player_y = player_y - 1; // decrements player_y as player is moving upwards
				if (player_y < 0) // resets player_y if it is out of range of matrix
					player_y = 7;
				if (cursor_y < 50) // resets cursor_y if it is out of range of grpahical board
					cursor_y = 400;
				DisplayCursor(cursor_x, cursor_y, 0, 255, 0);
				if (selected == 1)
				{
					swap(Board[player_x][player_y], Board[selected_row][selected_column]);
					//AddGems(Board, explosion_check); 
					//Sleep(100); 
					//if (SwapPossible(Board, player_x, player_y) == 0)
					//{
					//	swap(Board[player_x][player_y], Board[selected_row][selected_column]); 
					//}
					SpecialGemInsert(Board, player_x, player_y, 0);
					SpecialGemInsert(Board, player_x, player_y, 1); 
					selected = 0;
				}
				Board_update_check = 1;
			}
			else if (key == 3)
			{
				DisplayCursor(cursor_x, cursor_y, 0, 0, 0);
				cursor_x = cursor_x + 50; // increments cursor_x as player is moving rightwards
				player_x = player_x + 1; // increments player_x as player is moving rightwards
				if (player_x > 7) // resets player_x if it is out of range of matrix
					player_x = 0;
				if (cursor_x == 450) // resets cursor_x if it is out of range of graphical board
					cursor_x = 50;
				DisplayCursor(cursor_x, cursor_y, 0, 255, 0);
				if (selected == 1)
				{
					swap(Board[player_x][player_y], Board[selected_row][selected_column]);
					//AddGems(Board, explosion_check); 
					//Sleep(100); 
					//if (SwapPossible(Board, player_x, player_y) == 0)
					//{
					//	swap(Board[player_x][player_y], Board[selected_row][selected_column]); 
					//}
					SpecialGemInsert(Board, player_x, player_y, 0); 
					SpecialGemInsert(Board, player_x, player_y, 1);
					selected = 0;
				}
				Board_update_check = 1;
			}
			else if (key == 4)
			{
				DisplayCursor(cursor_x, cursor_y, 0, 0, 0);
				cursor_y = cursor_y + 50; // increments cursor_y as player is moving downwards
				player_y = player_y + 1; // increments player_y as player is moving downwards
				if (player_y > 7) // resets player_y if it is out of range of matrix
					player_y = 0;
				if (cursor_y == 450) // resets cursor_y if it is out of range of graphical board
					cursor_y = 50;
				DisplayCursor(cursor_x, cursor_y, 0, 255, 0);
				if (selected == 1)
				{
					swap(Board[player_x][player_y], Board[selected_row][selected_column]);
					//AddGems(Board, explosion_check); 
					//Sleep(100); 
					//if (SwapPossible(Board, player_x, player_y) == 0)
					//{
					//	swap(Board[player_x][player_y], Board[selected_row][selected_column]); 
					//}
					SpecialGemInsert(Board, player_x, player_y, 0); 
					SpecialGemInsert(Board, player_x, player_y, 1);
					selected = 0;
				}
				Board_update_check = 1;

			}
			else if (key == 5) // checks if player has pressed the enter button and runs the following code
			{
				DisplayCursor(cursor_x, cursor_y, 0, 0, 255);
				selected = 1; // sets selected to 1 as a gem is selected when enter is pressed
				selected_row = player_x; // saves row position of where player is currently at
				selected_column = player_y; // saves column position of where player is currently at
				Board_update_check = 1; // sets Board_update_check to 1 as board needs to be updated and displayed
			}
		}
		time(&end); // stops time calculation
		running_time = end - running_time; // calculates total time elapsed yet
		if (running_time == 1) // if the total time elapsed is equal to 1 second it runs the following code
		{
			total_time++; // the total game running time "total_time" is incremented to keep track of total seconds elapsed throughout the game
			running_time = 0; // running_time is reset to 0, so that a new second can be recorded next time
			x = x - 2; // x coordinate of empty black bar overlapping filled green bar is decremented so that it can give the effect of a decreasing time bar
			myRectangle(700, 140, x, 160, 255, 0, 0); // a black rectangle is created over the green time bar
		}
		while (Board_update_check) // runs the following code if the Board_update_check is true
		{
			ElbowElimination(Board, score); // first eliminates elbow shaped gems
			SpecialGemElimination(Board, score);
			EliminateGems(Board, score); // then eliminates simple gems in a row
			ShiftDown(Board); // then shifts the gems down into empty spaces and sends empty spaces to the top
			UpdateBoard(Board); // fills the empty spaces
			DisplayBoard(); // displays the grid
			AddGems(Board, explosion_check); // updates the graphical gems, filling the empty spaces
			if (selected == 1)
				DisplayCursor(cursor_x, cursor_y, 0, 0, 255); // if the player has selected a slot, it will display the cursor as blue
			else
				DisplayCursor(cursor_x, cursor_y, 0, 255, 0); // if the player has not selected a slot, it will display the cursor as green
			gotoxy(52, 4); // goes to position where score will be printed
			cout << "Score: " << score; // updates the score by printing it again
			Board_update_check = 0; // Board_update_check is set to 0 so that user can take a new turn
		}
	}
	system("cls"); // clears screen at the end of 2 minutes
	cout << "Game over" << endl;
	cout << "Your score was " << score << endl;
	_getch();
	return 0;
} 

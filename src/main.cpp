#include<iostream>
#include<string>
#include <sstream>
#include "Block.h"
#include "Command.h"
#include "variable.h"
#include "main.h"
#include <fstream>

using namespace std;

int rowSize, colSize;
Block board[20][20];
State state; //current game state
bool loaded; //if board is loaded


int main()
{
	//initialize
	state = State::Standby;
	loaded = false;
	string input, cmd, c = "command2.txt", o = "output2.txt";
	fstream inputFile, outputFile;
	inputFile.open(c);
	outputFile.open(o);

	//input till EOF
	while (getline(inputFile, input))
	{
		stringstream ss;
		ss << input;
		ss >> cmd;
		if (cmd == "Load")
		{
			if (state == State::Standby)
			{
				ss >> cmd;//boardfile, random count or random rate

				if (cmd == "BoardFile")
				{
					ss >> cmd;//filename
					loadBoardFile(cmd);
				}
				else if (cmd == "RandomCount")
				{
					int m, n, count;
					ss >> m >> n >> count;
					loadRandomCount(m, n, count);
				}
				else if (cmd == "RandomRate")
				{
					int m, n;
					double rate;
					ss >> m >> n >> rate;
					loadRandomRate(m, n, rate);
				}

				loaded = true;
				outputFile << "<" << input << "> : Success" << endl;
			}
			else
			{
				outputFile << "<" << input << "> : Failed" << endl;
			}
		}
		else if (cmd == "StartGame")
		{
			if (loaded && state == State::Standby)
			{
				state = State::Playing;
				outputFile << "<" << input << "> : Success" << endl;
			}
			else //if board is not loaded, we cant start game
			{
				outputFile << "<" << input << "> : Failed" << endl;
			}
		}
		else if (cmd == "Print")
		{
			ss >> cmd;
			outputFile << "<" << input << "> :" << endl;
			print(cmd, outputFile);
		}
		else if (cmd == "LeftClick")
		{
			int row, col;
			ss >> row >> col;
			if (state == State::Playing && isAbleLeftclick(row, col))
			{

				leftClick(row, col);
				outputFile << "<" << input << "> : Success" << endl;
				if (state == State::Gameover)
				{
					if (winOrNot)
					{
						outputFile << "You win the game" << endl;
					}
					else
					{
						outputFile << "You lose the game" << endl;
					}
				}
			}
			else
			{
				outputFile << "<" << input << "> : Failed" << endl;
			}
		}
		else if (cmd == "RightClick")
		{
			int row, col;
			ss >> row >> col;
			if (state == State::Playing && isAbleRightclick(row, col))
			{

				rightClick(row, col);
				outputFile << "<" << input << "> : Success" << endl;
			}
			else
			{
				outputFile << "<" << input << "> : Failed" << endl;
			}
		}
		else if (cmd == "Replay")
		{
			if (state == State::Gameover)
			{
				state = State::Standby;
				loaded = false;
				outputFile << "<" << input << "> : Success" << endl;
			}
			else
			{
				outputFile << "<" << input << "> : Failed" << endl;
			}
		}
		else if (cmd == "Quit")
		{
			if (state == State::Gameover)
			{
				outputFile << "<" << input << "> : Success" << endl;
				return 0;
			}
			else
			{
				outputFile << "<" << input << "> : Failed" << endl;
			}
		}
		else
		{
			outputFile << "Invalid Input!" << endl;
		}
		ss.str("");
		ss.clear();
	}
	inputFile.close();
	outputFile.close();
}

bool isInBoard(int r, int c)
{
	if (r >= 0 && r < rowSize && c >= 0 && c < colSize)return true;
	else return false;
}
bool isAbleRightclick(int r, int c)
{
	if (!isInBoard(r, c)) return false;
	if (board[r][c].getOpen()) return false;
	else return true;
}
bool isAbleLeftclick(int r, int c)
{
	if (!isInBoard(r, c)) return false;
	if (board[r][c].getOpen() || board[r][c].getFlag()) return false;
	else return true;
}
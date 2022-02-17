#include <iostream>
#include <vector>
#include <string>
#include <regex> //For input validation.
using namespace std;

class Board
{
	//We will represent the board as a 2 dimensional vector.
	//0 -> blank space
	//1 -> red piece
	//2 -> black piece

public:
	//Default Constructor
	Board()
	{
		for (int i = 0; i < 8; i++)
		{
			vector<int> board_row(8, 0);
			board_vector.push_back(board_row);
		}
		ResetBoard(); //Set Red/Black pieces on Board.
	}

	//Copy Constructor
	Board(const Board& old_board)
	{
		for (int i = 0; i < 8; i++)
		{
			vector<int> board_row(8, 0);
			board_vector.push_back(board_row);
		}

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				board_vector[i][j] = old_board.board_vector[i][j];
			}
		}
	}

	//Given a board (curren_board) and coordinates (r and c) set the board with given int value
	//Returns nullptr if failed to set and next state with set change if set successfull
	static Board* MakeBoardSetElement(const Board& current_board, int r, int c, int value)
	{
		if (r < 0 || r > 7)
			return nullptr;
		if (c < 0 || c > 7)
			return nullptr;
		if (value < 0 || value > 2)
			return nullptr;

		Board* new_board = new Board(current_board);
		new_board->board_vector[r][c] = value;

		return new_board;
	}

	//Resets the board to initial state with all checker pieces at
	// starting default positions.
	void ResetBoard()
	{
		//Note default value of a vector<int> is 0 as defined by C++ standard
		// for builtin types.
		for (int i = 7; i >= 0; i--)
		{
			for (int j = 0; j < 8; j++)
			{
				if (((i % 2) == (j % 2)) && i <= 2)
					board_vector[i][j] = 1;
				if (((i % 2) == (j % 2)) && i >= 5)
					board_vector[i][j] = 2;
			}
		}

	}

	//Given Board current_board coordinates x and y
	//Return the element value at the coordinate.
	//Returns -1 if out of bounds.
	static int GetBoardElement(const Board& current_board, int r, int c)
	{
		if (r < 0 || r > 7)
			return -1;
		if (c < 0 || c > 7)
			return -1;
		return current_board.board_vector[r][c];
	}

	//Prints out board to standard output
	void PrintBoard()
	{
		for (int i = 7; i >= 0; i--)
		{
			for (int j = 0; j < 8; j++)
			{
				cout << board_vector[i][j] << " ";
			}
			cout << endl;
		}
	}

	//TryMove given checker piece current coordinates and move-to coordinates
	//Returns the pointer to next board if move is successfull othersie it returns nullptr
	static Board* TryMove(Board* current_board, int old_r, int old_c, int new_r, int new_c)
	{
		int player_piece_value = GetBoardElement(*current_board, old_r, old_c);
		int move_to_value = GetBoardElement(*current_board, new_r, new_c);

		if (player_piece_value == -1 || move_to_value == -1) //Cannot select Item or move outside of board
			return nullptr;
		if (move_to_value == 1 || move_to_value == 2) //Cannot move piece on top of another piece
			return nullptr;
		//Cardinal Direction Movement checking

		Board* new_board = new Board(*current_board);
		new_board = MakeBoardSetElement(*new_board, old_r, old_c, 0);
		new_board = MakeBoardSetElement(*new_board, new_r, new_c, player_piece_value);

		return new_board;
	}

	//NextStates given current game board state (current_board)
	// returns a vector of possible legal next states
	static vector<Board> NextStates(Board& current_board)
	{
		vector<Board> s;
		return s;
	}

	~Board() {};
private:
	vector<vector<int>> board_vector;

};

int main()
{
	cout << "D; WELCOME TO MY CHECKERS GAME ;D" << endl;

	bool game_running = true;
	Board* current_playing_board = new Board();
	string move_input;
	int input_old_r;
	int input_old_c;
	int input_new_r;
	int input_new_c;

	while (game_running)
	{
		cout << "Make your move please: [old-r] [old-c] [new-r] [new-]" << endl;
		current_playing_board->PrintBoard();
		regex regex_string("(\\d) (\\d) (\\d) (\\d)");
		smatch regex_captures;
		getline(cin, move_input);



		if (regex_search(move_input, regex_captures, regex_string))
		{
			input_old_r = stoi(regex_captures[1]);
			input_old_c = stoi(regex_captures[2]);
			input_new_r = stoi(regex_captures[3]);
			input_new_c = stoi(regex_captures[4]);

			cout << endl;
			cout << input_old_r << endl;
			cout << input_old_c << endl;
			cout << input_new_r << endl;
			cout << input_new_c << endl;

			Board* new_board = Board::TryMove(current_playing_board, input_old_r, input_old_c, input_new_r, input_new_c);
			if (new_board != nullptr)
				current_playing_board = new_board;
			cout << endl << endl << endl;
		}
		else
		{
			cout << endl << endl << endl;
			cout << "Your move must follow convention [y1] [x1] [y2] [x2]" << endl;
		}
	}
	cout << "Done" << endl;
}
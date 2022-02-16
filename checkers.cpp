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
        Board()
        {
            for(int i=0; i<8; i++)
            {
                vector<int> board_row(8,0);
                board_vector.push_back(board_row);
            }
            ResetBoard(); //Set Red/Black pieces on Board.
        }

        //Given coordinates r and c set the board with given int value
        //Returns false if failed to set and true if set successfull
        bool SetBoardElement(int r, int c, int value)
        {
            if (r < 0 || r > 7)
                return false;
            if (c < 0 || c > 7)
                return false;
            if (value < 0 || value > 2)
                return false;
            
            board_vector[r][c] = value;
            return true;
            
        }

        //Resets the board to initial state with all checker pieces at
        // starting default positions.
        void ResetBoard()
        {
            //Note default value of a vector<int> is 0 as defined by C++ standard
            // for builtin types.
            for(int i = 7; i >= 0; i--)
            {
                for(int j = 0; j < 8; j++)
                {
                    if(((i % 2) == (j % 2)) && i <= 2)
                        SetBoardElement(i,j,1);
                    if(((i % 2) == (j % 2)) && i >= 5)
                        SetBoardElement(i,j,2);
                }
            }

        }

        //Given coordinates x and y
        //Return the element value at the coordinate.
        //Returns -1 if out of bounds.
        int GetBoardElement(int r, int c)
        {
            if (r < 0 || r > 7)
                return -1;
            if (c < 0 || c > 7)
                return -1;
            return board_vector[r][c];
        }

        //Prints out board to standard output
        void PrintBoard()
        {
            for(int i = 7; i >= 0; i--)
            {
                for(int j = 0; j < 8; j++)
                {
                    cout << board_vector[i][j] << " ";
                }
                cout << endl;
            }
        }

        bool MakeMove(int old_r, int old_c, int new_r, int new_c)
        {
            int player_piece_value = GetBoardElement(old_r, old_c);
            SetBoardElement(old_r, old_c, 0);
            SetBoardElement(new_r, new_c, player_piece_value);
            return true;
        }
        
        Board::~Board(){};
    private:
        vector<vector<int>> board_vector;

};

int main()
{
    cout << "D; WELCOME TO MY CHECKERS GAME ;D" << endl;

    bool game_running = true;
    Board my_board = Board();
    string move_input;
    int input_old_r;
    int input_old_c;
    int input_new_r;
    int input_new_c;

    while (game_running)
    {
        cout << "Make your move please: [old-r] [old-c] [new-r] [new-]" << endl;
        my_board.PrintBoard();
        regex regex_string("(\\d) (\\d) (\\d) (\\d)");
        smatch regex_captures;
        getline(cin, move_input);
        
        if(regex_search(move_input, regex_captures, regex_string))
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

            my_board.MakeMove(input_old_r, input_old_c, input_new_r, input_new_c);
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
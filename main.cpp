#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

/* Everything below this comment is starter code, and you are not
allowed to modify */

using namespace std;

// Function that displays the instructions to the user

void display_instructions() {
       cout << "Make a series of jumps until there is a single piece left" << endl
       << "anywhere on board. On each move you must jump an adjacent" << endl
       << "piece   into   an  empty  square,  jumping  horizontally," << endl
       << "vertically, or diagonally." << endl
       << endl
       << "Input of 'R' resets the board back to the beginning, and " << endl
       << "'X' exits the game." << endl;
}


char board[13]{};


char get_element(char position) {
  if ((position < 'A') || (position > 'M')) {
    cout << "Failed to get element at position " << position << endl
         << "Make sure the given position is an uppercase letter " << endl
         << "between A-M." << endl;
    exit(1);
  }
  return board[position - 'A'];
}

void set_element(char position, char value) {
  if ((position < 'A') || (position > 'M')) {
    cout << "Failed to set element at postion " << position << endl
         << "Make sure the given position is an uppercase letter " << endl
         << "between A-M." << endl;
    exit(1);
  }
  board[position - 'A'] = value;
}

// print out the board with the legend on the right

void display_board() {
  cout << endl;
  cout << setw(7) << "Board" << setw(12) << "Position" << endl;
  cout << setw(5) << board[0] << setw(11) << 'A' << endl
       << setw(3) << board[1] << ' ' << board[2] << ' ' << board[3] << setw(11)
       << "B C D" << endl
       << board[4] << ' ' << board[5] << ' ' << board[6] << ' ' << board[7]
       << ' ' << board[8] << ' ' << " E F G H I" << endl
       << setw(3) << board[9] << ' ' << board[10] << ' ' << board[11]
       << setw(11) << "J K L" << endl
       << setw(5) << board[12] << setw(11) << 'M' << endl;
  cout << endl;
}


void make_move();
void initialize_board();
bool game_over();

int main() {

  display_instructions();
  initialize_board();

  do {
    display_board();
    make_move();
  } while (!game_over() && !cin.eof());
  return 0;
}

bool checkRange(string input) {
  for (int i = 0; i < input.length(); i++) {
    if (input[i] > 'M') {
      return false;
    }
  }
  return true;
}

bool checkValid(string input) {

  string possibleMove[32] = {"ACG", "ABE", "ADI", "BGL", "BCD", "BFJ", "CGK",
                             "DGJ", "DCB", "DHL", "EFG", "EBA", "EJM", "FGH",
                             "GCA", "GFE", "GHI", "GKM", "HGF", "IHG", "IDA",
                             "ILM", "JGD", "JKL", "JFB", "KGC", "LGB", "LHD",
                             "LKJ", "MKG", "MJE", "MLI"};

  for (int i = 0; i < 32; i++) {
    if (input == possibleMove[i]) {
      return true;
    }
  }

  return false;
}

void make_move() {

  bool valid = false;
  int x = 5;

  while (valid == false) {
    x += 1;

    // Prompt + Read Input
    string input;
    char firstLet;
    cout << "Enter positions from, jump, and to (e.g. EFG): ";
    // had to change getline here need to fix some errors that will cause.
    cin >> input;
    firstLet = input[0];

    firstLet = toupper(firstLet);
    bool spaceCheck = false;

    // Uppercase the Input
    for (int i = 0; i < input.length(); i++) {
      input[i] = toupper(input[i]);
      if (input[i] == ' ') {
        spaceCheck = true;
      }
    }

    // Validity Checks
    if (input.length() != 3 && firstLet != 'X' && firstLet != 'R' ||
        spaceCheck) {
      cout << "*** Invalid sequence. Please retry." << endl;
      display_board();
      continue;
    } else if (input.length() != 1 && checkRange(input) == false) {
      cout << "*** Given move has positions not on the board! Please retry."
           << endl;
      display_board();
      continue;
    } else if (input.length() == 1 && firstLet == 'X') {
      cout << endl << "Exiting." << endl;
      game_over();
      exit(0);
    } else if (input.length() == 1 && firstLet == 'R') {
      cout << endl << "Restarting." << endl;
      initialize_board();
      display_board();
      continue;
    }

    // Move Checks
    char movingPiece = input[0];
    char jumpedPiece = input[1];
    char landingPiece = input[2];

    if (get_element(jumpedPiece) == '.') {
      cout << "*** Must jump a piece. Please retry." << endl;
      display_board();
      continue;
    } else if (get_element(movingPiece) == '.') {
      cout << "*** Source needs a piece. Please retry." << endl;
      display_board();
      continue;
    } else if (get_element(landingPiece) == '#') {
      cout << "*** Destination must be empty. Please retry." << endl;
      display_board();
      continue;
    } else {

      if (checkValid(input)) {

        set_element(movingPiece, '.');
        set_element(jumpedPiece, '.');
        set_element(landingPiece, '#');

        if (game_over() != true) {
          display_board();
        }

      } else {
        cout << "*** Move is invalid. Please retry." << endl;
        display_board();
      }

      if (game_over() == true) {
        cout << "Congrats you win!" << endl;
        valid = true;
      }

      continue;
    }
  }
}

bool game_over() {
  /* TODO: Write a function that returns true only if there is one
  one peg left, or if the user gives up by entering 'X' (or 'x')*/

  int pegCount = 0;
  char tempBoard[13] = {'A', 'B', 'C', 'D', 'E', 'F', 'G',
                        'H', 'I', 'J', 'K', 'L', 'M'};

  for (int i = 0; i < 13; i++) {
    if (get_element(tempBoard[i]) == '#') {
      pegCount += 1;
    }
  }
  if (pegCount == 1) {
    return true;
  } else {
    return false;
  }
}

void initialize_board() {

  char tempBoard[13] = {'A', 'B', 'C', 'D', 'E', 'F', 'G',
                        'H', 'I', 'J', 'K', 'L', 'M'};

  for (int i = 0; i < 13; i++) {
    if (tempBoard[i] != 'G') {
      set_element(tempBoard[i], '#');
    } else {
      set_element(tempBoard[i], '.');
    }
  }
}

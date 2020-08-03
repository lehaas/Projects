

/*
John Conway's GAME OF LIFE.

Rules: Every Cell is either dead (-) or alive (*). Starting from an initial grid of mixed 
cells, a cell dies in the next round either by lonlyness if less than 2 living cells are 
in its direct neighborhoud, or by overcrowding if more than 3 living cells are in its 
neighborhood. Further, a cell can be resurrected in the next round if it has precisely 3 
living neighbors.

Internal Encoding of Cells:
    - 0: dead and stays dead
    - 1: alive and stays alive
    - 2: dead and alive next round 
    - 3: alive and dead next round 
*/

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <random>
#include <unistd.h>

std::ostream& write_string(std::ostream& out, std::string const& s);

class GameState {
    public:
        GameState();
        int read_initial_state();
        void print_state();
        void run_game();

    private:
        int num_rows, num_columns;
        int **arena;

        int count_neighbors(int r, int c);
        void debug_print_state();
};

int main(int argc, char *argv[]) {
    GameState game;
    game.read_initial_state();
    game.run_game();
}



GameState::GameState() {
    return;
}

bool binomial_trial(const double p = 0.5) {
    static std::random_device dev;
    static auto gen = std::mt19937{dev()};
    static auto dist = std::uniform_real_distribution<double>(0,1);
    return (dist(gen) < p);
}

int GameState::read_initial_state() {
    std::string type;

    std::cout << "First input the number of rows: ";
    std::cin >> num_rows;
    std::cout << "Next input the number of columns: ";
    std::cin >> num_columns;
    
    arena = new int *[num_rows];
    for (int i = 0; i < num_rows; i++) 
        arena [i] = new int [num_columns];
    
    std::cout << "Tell me, do you wish to receive a random map (input \"r\") or user defined one (input \"u\"): ";
    std::cin >> type;


    if (type == "random") 
        for (int i = 0; i < num_rows; i++) 
            for (int j = 0; j < num_columns; j++) 
                arena[i][j] = binomial_trial(0.5) ? 1 : 0;
    else {
        std::cout << "Personal input is not implemented yet" << std::endl;
        exit(0);
    }

    return 1;

    /*
        print_state();

        std::cout << "Now you can enter the initial state (use 0 to mark an unpopulized field and 1 to mark a populized field)" << std::endl;
        int value;

        std::cout << "\e[4;6G";

        std::string str;
        while (true) {
            std::cin >> str;
            write_string(std::cout, str);

        }
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_columns; j++) {
                std::cin >> arena[i][j];
                std::cout << "\e[1A\e[F\e[0J" << ((arena[i][j] == 0) ? '-' : '*');
            }
        }
        return 1;
    */
}

void GameState::print_state() {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_columns; j++) {
            switch (arena[i][j])
            {
            case 0:
                std::cout << "-";
                break;
            case 1: 
                std::cout << "*";
            
            default:
                break;
            }
        }
        std::cout << std::endl;
    }
}


void GameState::debug_print_state() {
    std::cout << std::endl;
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_columns; j++) {
            std::cout << arena[i][j];
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}


void GameState::run_game() {

    std::cout << "The Game starts now" << std::endl;
    print_state();

    while (true) {
        sleep(1);

        int neighbors;
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_columns; j++) {
                neighbors = count_neighbors(i, j);
                if (arena[i][j] == 1) {
                    if (neighbors == 3 or neighbors == 2)
                        arena[i][j] = 1;
                    else 
                        arena[i][j] = 3;
                } else {
                    if (neighbors == 3)
                        arena[i][j] = 2;
                    else 
                        arena[i][j] = 0;
                }
            }
        }


        debug_print_state(); 

        for (int i = 0; i < num_rows; i++) 
            for (int j = 0; j < num_columns; j++) 
                arena[i][j] = arena[i][j] == 1 || arena[i][j] == 2;


        // std::cout << "\e[" << num_rows << "A\e[0J";
        std::cout << std::endl;

        print_state();
    }
}


int GameState::count_neighbors(int r, int c) {
    int counter = 0;
    for (int i = - 1; i < 2; i++) 
        if (r + i >= 0 & r + i < num_rows)
            for (int j = -1; j < 2; j++) 
                if (c + j >= 0 && c + j < num_columns && (i != 0 || j != 0) && arena[r + i][c + j] & 1)
                    counter ++;

    return counter;
}


/*
    UTILITY-FUNCTIONS
*/


std::ostream& write_string(std::ostream& out, std::string const& s)
{
   for ( auto ch : s )
   {
      switch (ch)
      {
         case '\'':
            out << "\\'";
            break;

         case '\"':
            out << "\\\"";
            break;

         case '\?':
            out << "\\?";
            break;

         case '\\':
            out << "\\\\";
            break;

         case '\a':
            out << "\\a";
            break;

         case '\b':
            out << "\\b";
            break;

         case '\e':
            out << "\\e";
            break;

         case '\f':
            out << "\\f";
            break;

         case '\n':
            out << "\\n";
            break;

         case '\r':
            out << "\\r";
            break;

         case '\t':
            out << "\\t";
            break;

         case '\v':
            out << "\\v";
            break;

         default:
            out << ch;
      }
   }

   return out;
}

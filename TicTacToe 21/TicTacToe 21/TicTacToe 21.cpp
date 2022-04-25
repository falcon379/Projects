// TicTacToe 21.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <string>
#include <utility>
#include <ctime>

using namespace std;

struct Coords
{
	int x;
	int y;
};

class Player;

class Game
{
public:
	Game()
	{
	}

	~Game()
	{
	  TwoD_array_delete();
	}

	void create_game();

	void play_game();

	void clear_grid();

private:

	void create_players();

	void generation_grid();

	void TwoD_array_delete();

	void TwoD_array_iniz(int size);

	void set_player_symbol(char s, const Coords& c);

	Player* check_winner();

	bool IsAvailable(const Coords & c);

	bool IsGameOver();

	void print_grid();

	int _grid_size = 0;

	int rows{};

	int cols{};

	char** _arr = nullptr;

    Player* _p1 = nullptr;

	Player* _p2 = nullptr;

	int _AvilableCells =0;
};

class Player
{
public:
	Player(char c, int grid_size) : _symbol(c), _win_sum(grid_size*c)
	{
	}

	int get_win_sum()const 
	{
		return _win_sum;
	}

	virtual Coords get_coord(int grid_size) = 0;
	char get_symbol() { return _symbol; }

private:

	int _win_sum = 0;

	char _symbol;
};

class Step_AI: public Player
{
public:
	Step_AI(char c, int grid_size) : Player(c, grid_size)
	{

	}
	virtual Coords get_coord(int grid_size) override;

private:

};

class Step_player :public Player
{
public:
	
	Step_player(char c, int grid_size) : Player(c, grid_size)
	{

	}
	virtual Coords get_coord(int grid_size) override;
	
};

void Game::TwoD_array_iniz(int size)
{

	_arr = new char* [size];

	for (size_t x = 0; x < size; x++)
	{
		_arr[x] = new char[size];
	}



	for (size_t x = 0; x < size; x++)
	{
		for (size_t y = 0; y < size; y++)
		{
			_arr[x][y] = ' ';
		}
	}
}

void Game::TwoD_array_delete()
{
	for (int x = 0; x < rows; x++)
	{
		delete[] _arr[x];
	}
	delete[] _arr;
}

void Game::set_player_symbol(char s, const Coords& c)
{
	_arr[c.y-1][c.x-1] = s;
	_AvilableCells--;
}

Player* Game::check_winner()
{

	size_t sum = 0;

	for (size_t i = 0; i < _grid_size; i++)
	{
		for (size_t j = 0; j < _grid_size; j++)
		{
			sum += _arr[i][j];
		}

		if (sum==_p1->get_win_sum())
		{
			return _p1;
		}

		if (sum== _p2->get_win_sum())
		{
			return _p2;
		}

		sum = 0;
	}

	for (size_t i = 0; i < _grid_size; i++)
	{
		for (size_t j = 0; j < _grid_size; j++)
		{
			sum += _arr[j][i];
		}

		if (sum == _p1->get_win_sum())
		{
			return _p1;
		}

		if (sum == _p2->get_win_sum())
		{
			return _p2;
		}

		sum = 0;
	}

	for (size_t i = 0; i < _grid_size; i++)
	{
		sum += _arr[i][i];
	}

	if (sum == _p1->get_win_sum())
	{
		return _p1;
	}

	if (sum == _p2->get_win_sum())
	{
		return _p2;
	}

	sum = 0;


	for (int i = _grid_size-1; i >= 0; i--)
	{
		sum += _arr[i][(_grid_size-1)-i];
	}

	if (sum == _p1->get_win_sum())
	{
		return _p1;
	}
	if (sum == _p2->get_win_sum())
	{
		return _p2;
	}

	return nullptr;
}

bool Game::IsAvailable(const Coords& c)
{
	return (_arr[c.y-1][c.x-1] == ' ') ? true : false;
}

bool Game::IsGameOver()
{
	return _AvilableCells == 0;
}

void Game::print_grid()
{
   for (size_t x = 0; x < _grid_size; x++)
   {
	cout << x + 1 << "|";

	for (size_t y = 0; y < _grid_size; y++)
    {
	cout << _arr[x][y] << "|";
	}
	cout << endl;
   }


}

void Game::create_players()
{
	int user_input;

	while (true)
	{
		cout << "Enter number of reaal playrs" << endl;

		cin >> user_input;

		if (user_input == 1)// Human and AI
		{
			char c1;
			cout << "Enter Big 'X' or Big 'O' " << endl;
			cin >> c1;
			_p1 = new Step_player(c1,_grid_size);
			_p2 = new Step_AI(c1 == 'X' ? 'O' : 'X',_grid_size);
			break;
		}

		if (user_input == 2)// Human and Human
		{
			char c1, c2;
			cout << "Player 1: Enter Big 'X' or Big 'O'" << endl;
			cin >> c1;
			cout << "Player 2: Enter the remaining character" << endl;
			cin >> c2;
			_p1 = new Step_player(c1, _grid_size);

			_p2 = new Step_player(c2, _grid_size);
			break;
		}

		cout << "entered value is not correct" << endl;
	}
}

void Game::generation_grid()
{
	while (true)
	{
		cout << " Select the size of the playing field : 3х3-3, 4х4-4, 6х6-6, 8х8-8" << endl;

		cin >> _grid_size;

		switch (_grid_size)
		{
		case 3:

			cout << endl;
			cout << " |1 2 3|\n";

			TwoD_array_iniz(_grid_size);
	
			return;


		case 4:
			cout << endl;
			cout << "| 1 2 3 4|\n";

			TwoD_array_iniz(_grid_size);
			
			return;


		case 6:
			cout << endl;
			cout << "| 1 2 3 4 5 6|\n";

			TwoD_array_iniz(_grid_size);
			
			return;


		case 8:
			cout << endl;
			cout << "| 1 2 3 4 5 6 7 8|\n";

			TwoD_array_iniz(_grid_size);
			
			return;


		default:

			cout << "You entered an invalid value" << endl;

			break;
		}
	}
}

void Game::create_game()
{
	generation_grid();
	create_players();
	clear_grid();
}

int Generate_random_number(int range)
{
	srand(time(NULL));

	 return rand() % range;

}

void Game::play_game()
{
	Coords coord;
	Player *winner;

	while (true)
	{
		while (true)
		{
			coord = _p1->get_coord(_grid_size);

			if (IsAvailable(coord))
			{
				set_player_symbol(_p1->get_symbol(), coord);
				cout << "step: " <<coord.x<<" "<<coord.y<< endl;
				break;
			}
		}

		print_grid();
		winner = check_winner();
		if (!winner)
		{
			if (IsGameOver())
			{
				cout << "dead heat"<<endl;
				return;
			}
		}
		else
		{
			cout << "winner: " << winner->get_symbol() << endl;
			break;
		}

		while (true)
		{

			coord = _p2->get_coord(_grid_size);

			if (IsAvailable(coord))
			{
				set_player_symbol(_p2->get_symbol(), coord);
				cout << "step: " << coord.x << " " << coord.y << endl;
				break;
			}
		}

		print_grid();
		winner=check_winner();
		if (!winner)
		{
			if (IsGameOver())
			{
				cout << "dead heat" << endl;
				return;
			}
		}
		else
		{
			cout << "winner: " << winner->get_symbol() << endl;
			break;
		}
	}
	
}

void Game::clear_grid()
{
	for (int x = 0; x < _grid_size; x++)
	{
		for (int y = 0; y < _grid_size; y++)
		{
			_arr[x][y] = ' ';
		}
	}

	_AvilableCells = _grid_size*_grid_size;
}

Coords Step_player::get_coord(int grid_size)
{

	Coords coord{ 0, 0 };

	while (true)
	{

		cout << "Enter coordinates Y " << endl;
		cin >> coord.y;
		cout << endl;
		cout << "Enter coordinates X " << endl;
		cin >> coord.x;

		if (!(coord.y<1 || coord.y >grid_size || coord.x<1 || coord.x >grid_size))
		{
			break;

		}
		cout << "Coordinates is invalid  " << endl;
	}

	return coord;
}

Coords Step_AI::get_coord(int grid_size)
{

	return{ Generate_random_number(grid_size) + 1,Generate_random_number(grid_size) + 1 };

}

int main()
{
	setlocale(LC_ALL, "ru");

	Game game;

	char repeat_game;
	bool isDone = false;

	while (!isDone)
	{
		game.create_game();
		game.play_game();
		cout << "do you want to play again? if yes any key, if not n/N  " << endl;
		cin >> repeat_game;
		if (repeat_game == 'n' || repeat_game == 'N')
		{
			isDone = true;
			game.clear_grid();
		}
	}

}
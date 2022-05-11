//Basic chess engine
//Author: Dr_42

//The engine takes a FEN string and a move string and tells if it is valid or not
//The engine stores an internal state of the board

#include <stdbool.h>
#include <stddef.h>

//Enum for the piece types
enum piece_type {
	p, n, b, r, q, k, P, N, B, R, Q, K, EMPTY
};

//Cell struct
struct cell {
	char piece;
	bool empty;
	char x;
	char y;
};

//Pieces struct
//Contains the piece names and their values
struct piece {
	char name;
	bool white;
	bool is_king;
	bool alive;
	struct cell *cell;
	struct attack_cells *attack_cells[64];
};

//Board struct
//Contains the board and the pieces
struct board {
	struct cell cells[8][8];
	struct piece pieces[32];
	bool white_turn;
	bool white_in_check;
	bool black_in_check;
	bool white_in_checkmate;
	bool black_in_checkmate;
	bool stalemate;
};

//FEN string parser
//Takes a FEN string and returns a board struct
struct board parse_fen(char *fen){
	struct board board;
	char *fen_string = fen;

	//Initialize the board
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			board.cells[i][j].piece = ' ';
			board.cells[i][j].empty = true;
			board.cells[i][j].x = i+'a';
			board.cells[i][j].y = j+'1';
		}
	}

	//Initialize the pieces
	for(int i = 0; i < 32; i++){
		board.pieces[i].name = ' ';
		board.pieces[i].white = false;
		board.pieces[i].is_king = false;
		board.pieces[i].alive = false;
		board.pieces[i].cell = NULL;
		for(int j = 0; j < 64; j++){
			board.pieces[i].attack_cells[j] = NULL;
		}
	}

	//Parse the FEN string
	return board;

}
int main() {
	return 0;
}

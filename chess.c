//Basic chess engine
//Author: Dr_42

//The engine takes a FEN string and a move string and tells if it is valid or not
//The engine stores an internal state of the board

#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>

//Enum for the piece types
enum piece_type {
	p, n, b, r, q, k, P, N, B, R, Q, K, EMPTY
};

//Cell struct
struct Cell {
	char piece;
	bool empty;
	char x;
	char y;
};

//Pieces struct
//Contains the piece names and their values
struct Piece {
	char name;
	bool white;
	bool is_king;
	bool alive;
	struct Cell *cell;
	struct attack_cells *attack_cells[64];
};

//Board struct
//Contains the board and the pieces
struct Board {
	struct Cell cells[8][8];
	struct Piece pieces[32];
	bool white_turn;
	bool white_in_check;
	bool black_in_check;
	bool white_in_checkmate;
	bool black_in_checkmate;
	bool stalemate;
};

//FEN string parser
//Takes a FEN string and returns a board struct

//Initialize the board
void init_board(struct Board *board){

	//Initialize the board
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			board->cells[i][j].piece = ' ';
			board->cells[i][j].empty = true;
			board->cells[i][j].x = i+'a';
			board->cells[i][j].y = j+'1';
		}
	}

	//Initialize the pieces
	for(int i = 0; i < 32; i++){
		board->pieces[i].name = ' ';
		board->pieces[i].white = false;
		board->pieces[i].is_king = false;
		board->pieces[i].alive = false;
		board->pieces[i].cell = NULL;
		for(int j = 0; j < 64; j++){
			board->pieces[i].attack_cells[j] = NULL;
		}
	}
}

void place_piece(struct Board *board, char piece, int x, int y, bool white, int piece_num){
	board->cells[x][y].piece = piece;
	board->cells[x][y].empty = false;

	board->pieces[piece_num].name = piece;
	board->pieces[piece_num].white = islower(piece);
	board->pieces[piece_num].is_king = (piece == 'k' || piece == 'K');
	board->pieces[piece_num].alive = true;
	board->pieces[piece_num].cell = &board->cells[x][y];
}


void parse_fen(struct Board *board,const char *fen){
	//Initialize the board
	init_board(board);

	//create a copy of the fen string
	char *fen_copy = malloc(strlen(fen)+1);
	strcpy(fen_copy, fen);

	//Split the FEN string into parts
	char *fen_chunks[10];
	int fen_chunks_count = 0;
	char *token = strtok(fen_copy, " ");
	while(token != NULL){
		fen_chunks[fen_chunks_count] = token;
		fen_chunks_count++;
		token = strtok(NULL, " ");
	}

	int xPos = 0;
	int yPos = 7;
	int piece_i = 0;
	//Place the pieces on the board
	for (int x = 0; x < strlen(fen_chunks[0]); x++)
	{
		if (isdigit(fen_chunks[0][x]))
		{
			xPos += fen_chunks[0][x] - '0';
		}
		else if (fen_chunks[0][x] == '/')
		{
			yPos -= 1;
			xPos = 0;
		}
		else{
			place_piece(board, fen_chunks[0][x], xPos, yPos, true, piece_i);
			piece_i++;
			xPos += 1;
		}
	}
}

wchar_t sym_from_char(char c){
	switch(c){
		case 'K':
		case 'k':
			return 0x265A;
		case 'Q':
		case 'q':
			return 0x265B;
		case 'R':
		case 'r':
			return 0x265C;
		case 'B':
		case 'b':
			return 0x265D;
		case 'N':
		case 'n':
			return 0x265E;
		case 'P':
		case 'p':
			return 0x265F;

/*
		case 'k':
			return 0x265A;
		case 'q':
			return 0x265B;
		case 'r':
			return 0x265C;
		case 'b':
			return 0x265D;
		case 'n':
			return 0x265E;
		case 'p':
			return 0x265F;
*/
		default:
			return 0x26A0;
	}
}

void print_board(struct Board *board){
	setlocale(LC_CTYPE, "");
	wprintf(L"\n");
	for(int i = 7; i >= 0; i--){
		wprintf(L"        ");
		for(int j = 0; j < 8; j++){
			if((i+j)%2==0)
				wprintf(L"\033[48;5;22m");
			else
				wprintf(L"\033[48;5;100m");

			if(!islower(board->cells[j][i].piece))
				wprintf(L"\033[38;5;151m");
			else
				wprintf(L"\033[38;5;16m");

			if(!board->cells[j][i].empty){
				wprintf(L"%lc", sym_from_char(board->cells[j][i].piece));
			}
			else{
				wprintf(L" ");
			}
			wprintf(L"\033[0m");
		}
		wprintf(L"%lc", 0x000A);
	}
}

int main() {
	//Initialize the board
	struct Board board;
	init_board(&board);
	//Declare the FEN string
	//const char *FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	const char *FEN = "r1bqkbnr/1ppp1ppp/p1n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 0 4";
	//Parse the FEN string
	parse_fen(&board, FEN);
	//Print the board
	print_board(&board);
}

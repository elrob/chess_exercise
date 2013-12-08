/* Filename: Rook.cpp 
 * Associated header file: Rook.h 
 *
 * MSc C++ Programming – Assessed Exercise No. 3 - Chess 
 *
 * Author: Robert Speller
 * Program last changed: 9th December 2012 
 */

#include <iostream>

using namespace std;

#include "Rook.h"

Rook::Rook( Colour_t c, ChessBoard *_board_ptr ) 
  : ChessPiece(c, ROOK, _board_ptr ){ }

bool Rook::valid_move( const string &from_sq, 
		       const string &to_sq ) {
  char from_file = from_sq[0];
  char from_rank = from_sq[1];
  char to_file = to_sq[0];
  char to_rank = to_sq[1];

  return ( ! to_sq_occupied_by_same_colour(to_sq) &&
	   ( from_file == to_file || from_rank == to_rank ) &&
	   nothing_en_route(from_sq, to_sq ) );
}

/* Filename: Bishop.cpp 
 * Associated header file: Bishop.h 
 *
 * MSc C++ Programming – Assessed Exercise No. 3 - Chess 
 *
 * Author: Robert Speller
 * Program last changed: 9th December 2012 
 */

#include <iostream>
#include <cstdlib>

using namespace std;

#include "Bishop.h"

Bishop::Bishop( Colour_t c, ChessBoard *_board_ptr ) 
  : ChessPiece(c, BISHOP, _board_ptr){ }

bool Bishop::valid_move( const string &from_sq, const string &to_sq )
{
  char from_file = from_sq[0];
  char from_rank = from_sq[1];
  char to_file = to_sq[0];
  char to_rank = to_sq[1];

  return ( ! to_sq_occupied_by_same_colour(to_sq) &&
	   abs(from_file - to_file) == abs(from_rank - to_rank ) &&
	   nothing_en_route(from_sq, to_sq ) );
}

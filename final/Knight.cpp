/* Filename: Knight.cpp 
 * Associated header file: Knight.h 
 *
 * MSc C++ Programming – Assessed Exercise No. 3 - Chess 
 *
 * Author: Robert Speller
 * Program last changed: 9th December 2012 
 */

#include <iostream>
#include <cstdlib>

using namespace std;

#include "Knight.h"

Knight::Knight( Colour_t c, ChessBoard *_board_ptr ) 
  : ChessPiece(c, KNIGHT, _board_ptr){ }


bool Knight::valid_move( const string &from_sq, const string &to_sq )
{
  char from_file = from_sq[0];
  char from_rank = from_sq[1];
  char to_file = to_sq[0];
  char to_rank = to_sq[1];
  int file_difference = abs(from_file - to_file);
  int rank_difference = abs(from_rank - to_rank);

  return ( ! to_sq_occupied_by_same_colour(to_sq) &&
	   file_difference < 3 && rank_difference < 3 &&
	   file_difference + rank_difference == 3 ); //L-shaped move
}

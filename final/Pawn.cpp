/* Filename: Pawn.cpp 
 * Associated header file: Pawn.h 
 *
 * MSc C++ Programming – Assessed Exercise No. 3 - Chess 
 *
 * Author: Robert Speller
 * Program last changed: 9th December 2012 
 */

#include <iostream>
#include <cstdlib>

using namespace std;

#include "Pawn.h"
#include "ChessBoard.h"

Pawn::Pawn( Colour_t c, ChessBoard *_board_ptr ) : ChessPiece(c, PAWN, _board_ptr ){ }

bool Pawn::valid_move( const string &from_sq, const string &to_sq ) {
  return ( ! to_sq_occupied_by_same_colour(to_sq) &&
	   ( valid_diagonal_pawn(from_sq, to_sq) ||
	     valid_forward_pawn(from_sq, to_sq) ) );
}
    

bool Pawn::valid_diagonal_pawn( const string &from_sq, 
				const string &to_sq ) const {
  char from_file = from_sq[0];
  char from_rank = from_sq[1];
  char to_file = to_sq[0];
  char to_rank = to_sq[1];
  return ( abs( from_file - to_file ) == 1 &&  
	   (( colour == WHITE && to_rank == from_rank + 1 ) || //moving forward 
	    ( colour == BLACK && to_rank == from_rank - 1 ) ) &&
	   ! board_ptr->is_empty_square( to_sq ) &&
	   board_ptr->get_piece_colour_at( to_sq ) != colour );
}


bool Pawn::valid_forward_pawn( const string &from_sq, 
			       const string &to_sq ) const {
  char from_file = from_sq[0];
  char from_rank = from_sq[1];
  char to_file = to_sq[0];
  char to_rank = to_sq[1];
  
  // pawn can't move forward to attack
  if ( from_file == to_file && board_ptr->is_empty_square( to_sq )) {
    if ( ( colour == WHITE && to_rank == from_rank + 1 ) ||
	 ( colour == BLACK && to_rank == from_rank - 1 ) )
      return true; //moving one space forward
    else if ( unmoved && ( (colour == WHITE && to_rank == from_rank + 2 ) || 
			   (colour == BLACK && to_rank == from_rank - 2 ) ) &&
	      nothing_en_route(from_sq, to_sq) )
      return true; //moving two spaces forward as first move
  }
  return false;
}
  
  
  

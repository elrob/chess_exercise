/* Filename: King.cpp 
 * Associated header file: King.h 
 *
 * MSc C++ Programming – Assessed Exercise No. 3 - Chess 
 *
 * Author: Robert Speller
 * Program last changed: 9th December 2012 
 */

#include <iostream>
#include <cstdlib>
#include <cassert>

using namespace std;

#include "King.h"
#include "ChessBoard.h"

King::King( Colour_t c, ChessBoard *_board_ptr ) 
  : ChessPiece(c, KING, _board_ptr){ }

bool King::valid_move( const string &from_sq, const string &to_sq ) {
  char from_file = from_sq[0];
  char from_rank = from_sq[1];
  char to_file = to_sq[0];
  char to_rank = to_sq[1];
  int file_difference = abs(from_file - to_file);
  int rank_difference = abs(from_rank - to_rank);

  return ( ! to_sq_occupied_by_same_colour(to_sq) &&
	   ((file_difference < 2 && rank_difference < 2 ) || 
	    valid_castling_move( from_file, from_rank, to_file, to_rank )));
}

bool King::valid_castling_move( char from_file, char from_rank, char to_file, char to_rank ) {
  if ( unmoved && from_rank == to_rank && abs(from_file - to_file) == 2 ) {
    char rook_file = ( from_file < to_file ? 'H' : 'A' ); //which corner is rook in
    string rook_sq = board_ptr->chars_to_string(rook_file,from_rank);
    string king_sq = board_ptr->chars_to_string(from_file,from_rank);
    if ( valid_castling_rook_at( rook_sq ) && 
	 nothing_en_route( king_sq, rook_sq ) && 
	 no_check_en_route( from_rank, from_file, to_file ) )
      return true;
  }
  return false;
}

bool King::valid_castling_rook_at( const string &rook_sq ) {
  return ( ! board_ptr->is_empty_square( rook_sq ) && 
	   board_ptr->get_piece_type_at( rook_sq ) == ROOK &&
	   board_ptr->piece_is_unmoved_at( rook_sq ) );
}

bool King::no_check_en_route( const char rank, const char from_file, 
			      const char to_file ) {
  assert( abs(from_file - to_file) == 2);

  char middle_file = (from_file+to_file)/2;

  string from_sq = board_ptr->chars_to_string(from_file,rank);
  string middle_sq = board_ptr->chars_to_string(middle_file,rank);
  string to_sq = board_ptr->chars_to_string(to_file,rank);
	       
  if ( board_ptr->is_in_check( colour ) || 
       board_ptr->in_check_after( from_sq, middle_sq ) ||
       board_ptr->in_check_after( from_sq, to_sq ) )
    return false;
  else
    return true;
}
  


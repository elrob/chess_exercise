/* Filename: ChessPiece.cpp 
 * Associated header file: ChessPiece.h 
 *
 * MSc C++ Programming – Assessed Exercise No. 3 - Chess 
 *
 * Author: Robert Speller
 * Program last changed: 9th December 2012 
 */

#include <iostream>
#include <cassert>
#include <cstdlib>

#include "ChessBoard.h"
#include "ChessPiece.h"

using namespace std;

ChessPiece::ChessPiece( Colour_t c, Piece_t pt, ChessBoard *_board_ptr ) 
  : colour(c), piece_type(pt), board_ptr(_board_ptr), unmoved(true) { }

ChessPiece::~ChessPiece(){
}

Colour_t ChessPiece::getColour() const {
  return colour;
}

Piece_t ChessPiece::get_piece_type() const {
  return piece_type;
}

bool ChessPiece::get_is_unmoved() const {
  return unmoved;
}

void ChessPiece::has_moved() {
  unmoved = false;
}

bool ChessPiece::to_sq_occupied_by_same_colour( const string &to_sq ) const {
  if ( ! board_ptr->is_empty_square( to_sq ) &&
       colour == board_ptr->get_piece_colour_at( to_sq ) )
    return true;
  else 
    return false;
}

bool ChessPiece::nothing_en_route( const string &from_sq, 
				   const string &to_sq ) const {
  char from_file = from_sq[0];
  char from_rank = from_sq[1];
  char to_file = to_sq[0];
  char to_rank = to_sq[1];
  
  if ( from_file == to_file && from_rank != to_rank ) //vertical move
    return nothing_en_vertical_route( from_file, from_rank, to_rank );

  else if ( from_rank == to_rank && from_file != to_file ) //horizontal
    return nothing_en_horizontal_route( from_rank, from_file, to_file );

  else if ( abs(from_file - to_file) == abs(from_rank - to_rank) ) //diagonal
    return nothing_en_diagonal_route( from_file, from_rank, 
				      to_file, to_rank );
  else {
    cout << "Not a vertical, horizontal or diagonal route!\n";
    assert(0);  // should never get here
    return true;  
  }
}

bool ChessPiece::nothing_en_vertical_route( const char from_file,
					    const char from_rank,
					    const char to_rank ) const {
  bool bottom_to_top;
  from_rank < to_rank ? bottom_to_top = true : bottom_to_top = false;

  char current_rank = from_rank; 
  bottom_to_top ? current_rank++ : current_rank--; //move towards to_rank
  
  while ( current_rank != to_rank ) {
    string str = board_ptr->chars_to_string(from_file,current_rank);
    if ( ! board_ptr->is_empty_square( str ) )
      return false;
    bottom_to_top ? current_rank++ : current_rank--; //move towards to_rank
  }
  return true;
}

bool ChessPiece::nothing_en_horizontal_route( const char from_rank,
					      const char from_file,
					      const char to_file ) const {
  bool left_to_right;
  from_file < to_file ? left_to_right = true : left_to_right = false;

  char current_file = from_file;
  left_to_right ? current_file++ : current_file--; //move towards to_file

  while ( current_file != to_file ) {
    string str = board_ptr->chars_to_string( current_file, from_rank);
    if ( ! board_ptr->is_empty_square( str ) )
      return false;
    left_to_right ? current_file++ : current_file--; //move towards to_file
  }
  return true;
}

bool ChessPiece::nothing_en_diagonal_route( const char from_file, 
					    const char from_rank, 
					    const char to_file, 
					    const char to_rank ) const {

  assert( from_file != to_file && from_rank != to_rank );
  bool left_to_right, bottom_to_top;
  from_file < to_file ? left_to_right = true : left_to_right = false;
  from_rank < to_rank ? bottom_to_top = true : bottom_to_top = false;

  char current_file = from_file;
  char current_rank = from_rank; 
  left_to_right ? current_file++ : current_file--; //move towards to_file
  bottom_to_top ? current_rank++ : current_rank--; //move towards to_rank
  
  while ( current_file != to_file && current_rank != to_rank ) {
    string str = board_ptr->chars_to_string(current_file,current_rank);
    if ( ! board_ptr->is_empty_square( str ) )
      return false;
    left_to_right ? current_file++ : current_file--; //move towards to_file
    bottom_to_top ? current_rank++ : current_rank--; //move towards to_rank
  }
  return true;
}
     

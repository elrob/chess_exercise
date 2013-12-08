/* Filename: Bishop.h 
 * Associated implementation file: Bishop.cpp 
 *
 * MSc C++ Programming – Assessed Exercise No. 3 - Chess 
 *
 * Author: Robert Speller
 * Program last changed: 9th December 2012 
 */

#ifndef Bishop_h
#define Bishop_h

#include "ChessPiece.h"
#include "Colour.h"

class Bishop : public ChessPiece {

 public:
  Bishop( Colour_t c, ChessBoard *_board_ptr );

  
  /* Returns true if these three conditions hold true:
   * -to_sq is not occupied by a piece of the same colour
   * -the move is a diagonal move
   * -there are no pieces in the intermediate squares 
   */
  bool valid_move( const string &from_sq, const string &to_sq );

};


#endif


  

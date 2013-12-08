/* Filename: Knight.h 
 * Associated implementation file: Knight.cpp 
 *
 * MSc C++ Programming – Assessed Exercise No. 3 - Chess 
 *
 * Author: Robert Speller
 * Program last changed: 9th December 2012 
 */

#ifndef Knight_h
#define Knight_h

#include "ChessPiece.h"
#include "Colour.h"

class Knight : public ChessPiece {

 public:
  Knight( Colour_t c, ChessBoard *_board_ptr );


  /* Returns true if these two conditions hold true:
   * -to_sq does not hold a piece of the same colour
   * -the move is a valid L-shaped move - 2 rank squares and 
   *  1 file square or 2 file squares and 1 rank square.
   */
  bool valid_move( const string &from_sq, const string &to_sq );

};


#endif


  

/* Filename: Rook.h 
 * Associated implementation file: Rook.cpp 
 *
 * MSc C++ Programming – Assessed Exercise No. 3 - Chess 
 *
 * Author: Robert Speller
 * Program last changed: 9th December 2012 
 */

#ifndef Rook_h
#define Rook_h

#include "ChessPiece.h"
#include "Colour.h"

class Rook : public ChessPiece {
 
 public:
  Rook( Colour_t c, ChessBoard *_board_ptr );


  /* Returns true if to_sq is not occupied by the same colour
   * and the move is along one file or one rank and there
   * are no pieces at intermediate squares along the route. 
   */
  bool valid_move( const string &from_sq, const string &to_sq );

};


#endif


  

/* Filename: Queen.h 
 * Associated implementation file: Queen.cpp 
 *
 * MSc C++ Programming – Assessed Exercise No. 3 - Chess 
 *
 * Author: Robert Speller
 * Program last changed: 9th December 2012 
 */

#ifndef Queen_h
#define Queen_h

#include "ChessPiece.h"
#include "Colour.h"

class Queen : public ChessPiece {


 public:
  Queen( Colour_t c, ChessBoard *_board_ptr );


  /* Returns true if these three conditions hold:
   * -to_sq is not occupied by a chess piece of the same colour
   * -the move is along one file, one rank or a diagonal
   * -there are no pieces in the intermediate squares
   */
  bool valid_move( const string &from_sq, const string &to_sq );
};


#endif

  

/* Filename: Pawn.h 
 * Associated implementation file: Pawn.cpp 
 *
 * MSc C++ Programming – Assessed Exercise No. 3 - Chess 
 *
 * Author: Robert Speller
 * Program last changed: 9th December 2012 
 */

#ifndef Pawn_h
#define Pawn_h

#include "ChessPiece.h"
#include "Colour.h"

class Pawn : public ChessPiece {

 public:
  Pawn( Colour_t c, ChessBoard *_board_ptr );

  
  /* First checks whether the to_sq is occupied by a chess piece
   * of the same colour. Then checks whether the move is a valid
   * diagonal or forward pawn move using the methods below. 
   */
  bool valid_move( const string &from_sq, const string &to_sq );


  /* Returns true if the move is a one square diagonal move in
   * the forward direction (dependant on colour) and that the
   * square it moves into contains a piece of the opposite colour.
   */
  bool valid_diagonal_pawn( const string &from_sq, 
			    const string &to_sq ) const;

  
  /* Returns true if the move is one square in the forward 
   * direction (dependant on colour) or is two squares forward,
   * the pawns first move and there is nothing in the intermediate
   * square.
   */
  bool valid_forward_pawn( const string &from_sq, 
			   const string &to_sq ) const;

};


#endif


  

/* Filename: King.h 
 * Associated implementation file: King.cpp 
 *
 * MSc C++ Programming – Assessed Exercise No. 3 - Chess 
 *
 * Author: Robert Speller
 * Program last changed: 9th December 2012 
 */

#ifndef King_h
#define King_h

#include "ChessPiece.h"
#include "Colour.h"

class King : public ChessPiece {

 public:
  King( Colour_t c, ChessBoard *_board_ptr );


  /* Returns true if the to_sq is not occupied by a chess piece of
   * the same colour and either of the following is true:
   * - the move is one square in distance
   * - the move is a valid castling move 
   */
  bool valid_move( const string &from_sq, const string &to_sq );


  /* First checks that the king has not moved and that the move is 
   * two squares along the same rank. Then checks that a rook is in 
   * the correct corner using the valid_castling_rook_at method
   * below. It then checks that there is nothing_en_route between
   * the king square and the rook square. Finally it ensures that the
   * king is not moving out of check, not passing a check position, 
   * and not moving into check using the no_check_en_route method 
   * below. 
   */
  bool valid_castling_move( char from_file, char from_rank, 
			    char to_file, char to_rank );

  
  /* Checks that the piece at rook_sq is a rook and that it hasn't
   * already moved. 
   */
  bool valid_castling_rook_at( const string &rook_sq );


  /* Returns false if the king is currently in check, if the square it
   * moves through is in check or if the square it is moving to is
   * in check.
  */
  bool no_check_en_route( const char rank, const char from_file, 
			  const char to_file );
  

};


#endif


  

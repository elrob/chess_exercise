/* Filename: ChessPiece.h 
 * Associated implementation file: ChessPiece.cpp 
 *
 * MSc C++ Programming – Assessed Exercise No. 3 - Chess 
 *
 * Author: Robert Speller
 * Program last changed: 9th December 2012 
 */

#ifndef ChessPiece_h
#define ChessPiece_h

#include <string>

#include "Colour.h"
#include "PieceType.h"

using namespace std;

class ChessBoard;

class ChessPiece {
 protected:
  const Colour_t colour;
  const Piece_t piece_type;
  ChessBoard *board_ptr;
  bool unmoved;

 public:
  ChessPiece( Colour_t c, Piece_t pt, ChessBoard *_board_ptr );

  virtual ~ChessPiece();

  /* Pure virtual function as each different ChessPiece has a different set
   * of rules to determine whether it can move from from_sq to to_sq. 
   */
  virtual bool valid_move( const string &from_sq, const string &to_sq ) = 0;
  
  
  /* Return the colour of the particular chess piece. 
   */
  Colour_t getColour() const;


  /* Return the piece type of the particular chess piece.
   */
  Piece_t get_piece_type() const;

  
  /* Return the state of the unmoved flag. Required by kings when determining
   * whether a castling move is possible using a particular rook. 
   */
  bool get_is_unmoved() const;

  
  /* Drop the unmoved flag. This is called after a piece has moved. 
   */
  void has_moved();


  /* Returns true if to_sq is occupied by a piece of the same colour
   * as the piece attempting a move there. 
   */
  bool to_sq_occupied_by_same_colour( const string &to_sq ) const;


  /* A method called by various pieces that attempt a move over intermediate
   * squares. This method determines whether a move is vertical, horizontal,
   * or diagonal and calls the respective methods below. If a piece is found
   * in an intermediate square this method returns false.
   */
  bool nothing_en_route( const string &from_sq, const string &to_sq ) const;

  
  /* Checks all squares on from_file between from_rank and to_rank
   * for the existence of a piece. If there is a piece it returns false. 
   */
  bool nothing_en_vertical_route( const char from_file, const char from_rank, 
				  const char to_rank ) const;

  
  /* Checks all squares on from_rank between from_file and to_file for the
   * existence of a piece. If a piece is found it returns false. 
   */
  bool nothing_en_horizontal_route( const char from_rank, 
				    const char from_file, 
				    const char to_file ) const;


  /* Checks all squares on the diagonal between from_file, from_rank 
   * and to_file, to_rank for the existence of a piece. If a piece is found
   * it returns false. 
   */
  bool nothing_en_diagonal_route( const char from_file, const char from_rank, 
				  const char to_file, const char to_rank ) const;


};


#endif

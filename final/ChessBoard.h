/* Filename: ChessBoard.h 
 * Associated implementation file: ChessBoard.cpp 
 *
 * MSc C++ Programming – Assessed Exercise No. 3 - Chess 
 *
 * Author: Robert Speller
 * Program last changed: 9th December 2012 
 */

# ifndef ChessBoard_h
# define ChessBoard_h

#include <string>
#include <map>

#include "ChessPiece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include "Colour.h"
#include "PieceType.h"

using namespace std;

/* the board consists of string elements "A1" through to "H8"
   and a corresponding pointer to a ChessPiece (or NULL) 
*/
typedef map< string, ChessPiece* > Board_t;
#define sq_string first   // sq_string = square string
#define cp_pointer second  // cp_pointer = ChessPiece pointer

class ChessBoard {
  public:

  ChessBoard();
  
  ~ChessBoard();


  /* User attempts a move from from_sq to to_sq 
   */
  void submitMove( const string &from_sq, const string &to_sq );


  /* User wants to start a new game so calls resetBoard( ) 
   */
  void resetBoard( );


  /* Check whether side_colour is now in check by checking 
   * whether any opposing piece can move to the square
   * currently occupied by the side_colour king. 
   */
  bool is_in_check( const Colour_t side_colour );


  /* Check whether side_colour is now in checkmate by checking
   * whether any of side_colour's pieces can make a move that 
   * takes side_colour out of check. 
   */
  bool is_in_checkmate( const Colour_t side_colour );


  /* Check whether the moving colour will be in check after a
   * theoretical move from from_sq to to_sq. The pieces are moved 
   * temporarily, check is tested and the pieces are replaced. 
   */
  bool in_check_after( const string &from_sq, const string &to_sq );


  /* true if square sq is mapped to a ChessPiece pointer to NULL 
   */
  bool is_empty_square( const string &sq ) const; 


  /* Dereference the ChessPiece pointer at square sq, call
   * its getColour() function and return its colour. 
   */
  Colour_t get_piece_colour_at( const string &sq ) const;


  /* Dereference the ChessPiece pointer at square sq, call
   * its get_piece_type() function and return its piece type.
   */
  Piece_t get_piece_type_at( const string &sq ) const;


  /* Return the piece type as a string. e.g. "King" 
   */
  string piece_type_string( const Piece_t type ) const;


  /* Find the king which has colour side_colour and return
   * its board location as a string. 
   */ 
  string get_king_square( const Colour_t side_colour );


  /* An extra check to ensure a user cannot attempt to move a piece 
   * to/from a square which doesn't exist on the board e.g "J9" 
   */
  bool on_board( const string &sq ) const;

  
  /* Ensure the from_sq and the to_sq are on the board and not equal. 
   */
  bool move_operands_valid( const string &from_sq, const string &to_sq ) const;


  /* Ensure from_sq contains a piece that it is of the correct colour 
   */
  bool piece_of_correct_colour( const string &from_sq ) const;

  
  /* Dereference the ChessPiece pointer at from_sq and call its valid_move 
   * function to check whether this particular piece and move to to_sq. 
   */
  bool piece_can_move( const string &from_sq, const string &to_sq ) const;


  /* Check whether the piece at from_sq can make a valid move by iterating
   * through each square on the board and checking whether it can make a 
   * valid move to that square. 
   */
  bool piece_can_move_somewhere( const string from_sq ) ;


  /* Used to check whether a king is making a castling move. The validity of
   * the move is carried out separately in the king's valid_move method. 
   */
  bool is_castling_move( const string &from_sq, const string &to_sq ) const;


  /* Dereference the ChessPiece pointer at square sq, call its
   * get_is_unmoved() method and return the result. This method is required
   * in the king's valid_move method, to determine whether a rook is unmoved
   * and a castling move is possible. 
   */
  bool piece_is_unmoved_at( const string &sq ) const;


  /* A simple function to concatenate chars c1 and c2 and return a string. 
   */
  string chars_to_string( const char c1, const char c2 ) const;


  /* See the current state of the board (in colour!) 
   */
  void printBoard( );


 private:

  /* Private variables */
  Board_t the_board;
  Colour_t turn_colour; // WHITE or BLACK
  bool end_of_game;
  

  /* Private methods */
  
  /* Create ChessPiece pointers of the correct type at the correct squares
   * on the_board. Set turn_colour to WHITE and end_of_game to false.
   */
  void initialiseBoard( );


  /* Carry out the move by moving the ChessPiece pointer at from_sq
   * to to_sq and deleting the ChessPiece pointer at to_sq if a piece
   * is already there. Output this information to the console output.
   * Dereference the moved ChessPiece pointer and drop its unmoved flag.
   */
  void move_piece( const string &from_sq, const string &to_sq );


  /* Calculate the location of the rook that must move in the castling
   * move and move the rook using the move_piece method above. 
   */
  void move_castling_rook( const string &king_from_sq, 
			   const string &king_to_sq );


  /* Test for check and then checkmate on the colour that hasn't
   * moved and print the status. Checkmate results in the board 
   * being printed and the end_of_game flag being raised. 
   */
  void post_move_checks( );


  /* Change turn_colour from WHITE to BLACK or vise versa after a move. 
   */
  void change_turn_colour( );
  

  /* Return true if the end_of_game flag is high and enable the user
   * to reset the board and start a new game. Otherwise return false.
   */
  bool check_end_of_game( );

  
  /* Iterate through the_board deleting the ChessPiece pointer at each
   * square ensuring that there are no memory leaks.
   */
  void delete_all_pieces( );

};

# endif

/* Filename: ChessBoard.cpp 
 * Associated header file: ChessBoard.h
 *
 * MSc C++ Programming – Assessed Exercise No. 3 - Chess 
 *
 * Author: Robert Speller
 * Program last changed: 9th December 2012
 */

#include <iostream>
#include <cstdlib>
#include <cassert>
#include "ChessBoard.h"

using namespace std;

/******************
 * public methods *
 *                *
 ******************/

ChessBoard::ChessBoard() {
  initialiseBoard();
  return;
}

ChessBoard::~ChessBoard() {
  delete_all_pieces();
  return;
}

void ChessBoard::submitMove( const string &from_sq, const string &to_sq ) {
  if ( !check_end_of_game() && 
       move_operands_valid( from_sq, to_sq ) && 
       piece_of_correct_colour( from_sq ) ) { //initial checks
    
    if ( piece_can_move( from_sq, to_sq ) && 
	 !in_check_after(from_sq, to_sq) ) { //move checks
      
      if ( is_castling_move( from_sq, to_sq ) ) {
	cout << "Castling move:\n";
	move_piece( from_sq, to_sq ); // move king
	move_castling_rook( from_sq, to_sq ); // move rook
      }
      else
	move_piece( from_sq, to_sq ); // move piece

      post_move_checks();
      change_turn_colour(); 
    }
    else //piece can't move
      cout << ( get_piece_colour_at(from_sq) == WHITE ? "White's " : "Black's " ) 
	   << piece_type_string(get_piece_type_at(from_sq)) << " cannot move to " 
	   << to_sq << "!\n";
  }
}

void ChessBoard::resetBoard( ) {
  delete_all_pieces( );
  initialiseBoard( );
return;
}

bool ChessBoard::is_in_check( const Colour_t side_colour ) {
  string king_sq = get_king_square( side_colour );
  Board_t::iterator it;
  for ( it = the_board.begin(); it != the_board.end(); it++ ) {
    string sq = it->sq_string;
    if ( !is_empty_square( sq ) && 
	 get_piece_colour_at( sq ) != side_colour && 
	 piece_can_move( sq, king_sq ) ) 
      return true;
  }
  return false;
}

bool ChessBoard::is_in_checkmate( const Colour_t side_colour ) {
  Board_t::iterator it;
  for ( it = the_board.begin(); it != the_board.end(); it++ ) {
    string from_sq = it->sq_string;
    if ( !is_empty_square( from_sq ) &&
	 get_piece_colour_at( from_sq ) == side_colour &&
	 piece_can_move_somewhere( from_sq ) )
      return false;
  }
  return true;
}

bool ChessBoard::in_check_after( const string &from_sq, 
				 const string &to_sq ) {
  Colour_t moving_colour = get_piece_colour_at(from_sq);
 
  ChessPiece *from_sq_ptr, *to_sq_ptr;
  from_sq_ptr = (the_board.find(from_sq))->cp_pointer;
  to_sq_ptr = (the_board.find(to_sq))->cp_pointer;
  
  the_board[to_sq] = from_sq_ptr; //temporarily move pieces
  the_board[from_sq] = NULL;
  
  bool in_check = is_in_check( moving_colour );
  
  the_board[from_sq] = from_sq_ptr; //replace pieces
  the_board[to_sq] = to_sq_ptr;
  
  return in_check;
}
  
bool ChessBoard::is_empty_square( const string &sq ) const {
  assert( on_board( sq ) );
  if ( (the_board.find( sq ))->cp_pointer == NULL )
    return true;
  else 
    return false;
}

Colour_t ChessBoard::get_piece_colour_at( const string &sq ) const {
  assert( on_board( sq ) && !is_empty_square( sq ) );
  return ((the_board.find( sq ))->cp_pointer)->getColour();
}

Piece_t ChessBoard::get_piece_type_at( const string &sq ) const {
  assert( on_board( sq ) && !is_empty_square( sq ) );
  return ((the_board.find( sq ))->cp_pointer)->get_piece_type();
}

string ChessBoard::piece_type_string( const Piece_t type ) const {
  switch(type) {
  case KING: return "King";
  case ROOK: return "Rook";
  case BISHOP: return "Bishop";
  case QUEEN: return "Queen";
  case KNIGHT: return "Knight";
  case PAWN: return "Pawn";
  default: return "Error!";}
}

string ChessBoard::get_king_square( const Colour_t side_colour ) {
  string king_sq = "un-init";
  Board_t::iterator it;
  it = the_board.begin();
  while ( it != the_board.end() && king_sq.compare( "un-init" ) == 0 ) {
    string current_sq = it->sq_string;
    if ( !is_empty_square( current_sq ) &&
	 get_piece_colour_at( current_sq ) == side_colour &&
	 get_piece_type_at( current_sq ) == KING )
      king_sq = current_sq;
    it++;
  }
  if ( king_sq.compare( "un-init" ) == 0 ) {
    cout << "Error: King not on board!" << endl;
    printBoard(); // the program should never get here
    assert(0);
  }
  return king_sq;
}

bool ChessBoard::on_board( const string &sq ) const {  
  if ( the_board.count( sq ) == 0 ) {
    cout << sq << " is not a square on the chess board!\n";
    return false;
  }
  else 
    return true;
}

bool ChessBoard::move_operands_valid( const string &from_sq, 
				      const string &to_sq ) const {
  if ( !on_board(from_sq) || !on_board(to_sq) || from_sq == to_sq )
    return false;
  else 
    return true;
}

bool ChessBoard::piece_of_correct_colour( const string &from_sq ) const {
  if ( is_empty_square( from_sq ) ) {
    cout << "There is no piece at position " << from_sq << "!\n";
    return false;
  }
  else if ( turn_colour != get_piece_colour_at( from_sq ) ) {
    cout << "It is not " 
    	 << ( turn_colour == WHITE ? "Black's " : "White's " )
    	 << "turn to move!\n";
    return false;
  }
  else 
    return true;
}

bool ChessBoard::piece_can_move( const string &from_sq, 
				 const string &to_sq ) const {
  if ( !move_operands_valid( from_sq, to_sq ) || is_empty_square( from_sq ) )
    return false;
  else //dereference the ChessPiece pointer and call its valid_move method
    return ((the_board.find(from_sq))->cp_pointer)->valid_move(from_sq,to_sq);
}

bool ChessBoard::piece_can_move_somewhere( const string from_sq ) {
  string to_sq;
  Board_t::iterator it;
  for ( it = the_board.begin(); it != the_board.end(); it++ ) {
    to_sq = it->sq_string;
    if ( piece_can_move( from_sq, to_sq ) && !in_check_after(from_sq,to_sq) )
      return true;
  }
  return false;
}

bool ChessBoard::is_castling_move( const string &from_sq, 
				   const string &to_sq ) const {
  int file_difference = abs(from_sq[0] - to_sq[0]);
  Piece_t piece_type = get_piece_type_at( from_sq );
  return file_difference == 2 && piece_type == KING;
}

bool ChessBoard::piece_is_unmoved_at( const string & sq ) const {
  assert( on_board( sq ) && !is_empty_square( sq ) );
  return ((the_board.find( sq ))->cp_pointer)->get_is_unmoved();
}

string ChessBoard::chars_to_string( const char c1, const char c2 ) const {
  string str;
  str = c1;
  str += c2;
  return str;
}

void ChessBoard::printBoard( ){ // prints in colour!
  cout << endl;
  if ( the_board.empty() )
    cout << "There are no pieces on the board so it can't be printed." << endl;
  else {
    bool square_colour_flag = 0;
    for ( char rank = '8'; rank >= '1'; rank-- ) {
      cout << ( rank == '5' ? "Rank " : "     " ) << rank << "| ";
      for ( char file = 'A'; file <= 'H'; file++ ) {
	if ( square_colour_flag )
	  cout << "\033[1;40m"; //board square colouring
	else
	  cout << "\033[1;47m"; 
	string str = chars_to_string(file,rank);
	if ( !is_empty_square(str) ) {
	  Colour_t colour = get_piece_colour_at( str );
	  if ( colour == BLACK )
	    cout << "\033[31m"; //piece colouring
	  else 
	    cout << "\033[34m";
	  cout << (colour == WHITE ? 'W' : 'B') ;
	  Piece_t type = get_piece_type_at( str );
	  if ( type != KNIGHT )
	    cout << piece_type_string(type)[0] << " ";
	  else
	    cout << "N ";
	}
	else
	  cout << "   "; //no ChessPiece at this square
	cout << "\033[0m"; //reset colour formatting
	square_colour_flag = !square_colour_flag;
      }
      cout << endl;
      square_colour_flag = !square_colour_flag;
    }
    cout << "        ________________________\n"
	 << "         A  B  C  D  E  F  G  H\n"
	 << "                 File\n" 
	 << endl;
  }  
  cout << endl << endl;
  return;
}
      

/*******************
 * private methods *
 *                 *
 *******************/

void ChessBoard::initialiseBoard( ){
  for ( char file = 'A'; file <= 'H'; file++ ) 
    for ( char rank = '1'; rank <= '8'; rank++ ) {
      string str = chars_to_string( file, rank );
      ChessPiece* ptr = NULL;
      Colour_t the_colour;
      rank <= '4' ? the_colour = WHITE : the_colour = BLACK;
      
      switch (rank) {
      case '1':
      case '8':
	{
	  switch ( file ){
	  case 'A':
	  case 'H':
	    ptr = new Rook(the_colour, this);
	    break;
	  case 'B':
	  case 'G':
	    ptr = new Knight(the_colour, this);
	    break;
	  case 'C':
	  case 'F':
	    ptr = new Bishop(the_colour, this);
	    break;
	  case 'D':
	    ptr = new Queen(the_colour, this);
	    break;
	  case 'E':
	    ptr = new King(the_colour, this);
	    break;
	  default:
	    cout << "Error: File not between A and H!\n";
	  }
	}
	break;

      case '2':
      case '7':
	ptr = new Pawn(the_colour, this);
	break;
      case '3':
      case '4':
      case '5':
      case '6':
	break;
      default:
	cout << "Error: Rank not between 1 and 8!\n";
      }
      the_board[str] = ptr;
    }

  turn_colour = WHITE;
  end_of_game = false;
  cout << "A new chess game is started!\n";

  return;
}

void ChessBoard::move_piece( const string &from_sq, const string &to_sq ) {
  Colour_t piece_colour = get_piece_colour_at(from_sq);
  Piece_t piece_type = get_piece_type_at(from_sq);

  cout << ( piece_colour == WHITE ? "White's " : "Black's " ) 
       << piece_type_string(piece_type)
       << " moves from " << from_sq << " to " << to_sq;

  ChessPiece *from_sq_ptr = (the_board.find(from_sq))->cp_pointer;

  if ( !is_empty_square( to_sq ) ) { //take the piece at to_sq
    cout <<  " taking " 
	 << ( get_piece_colour_at(to_sq) == WHITE ? "White's " : "Black's " ) 
	 << piece_type_string(get_piece_type_at(to_sq));
    ChessPiece *to_sq_ptr = (the_board.find(to_sq))->cp_pointer;
    delete to_sq_ptr;
  }

  the_board[to_sq] = from_sq_ptr; //change the ChessPiece pointers
  the_board[from_sq] = NULL;
  cout << endl;

  ((the_board.find(to_sq))->cp_pointer)->has_moved(); //drop the unmoved flag
}

void ChessBoard::move_castling_rook( const string &king_from_sq, 
				     const string &king_to_sq ) {
  char rook_rank = king_from_sq[1];
  char rook_file = ( king_from_sq[0] < king_to_sq[0] ? 'H' : 'A' );
  char rook_to_file = ( rook_file == 'A' ? 'D' : 'F' );
  string rook_from_sq = chars_to_string( rook_file, rook_rank );
  string rook_to_sq = chars_to_string( rook_to_file, rook_rank );
  move_piece( rook_from_sq, rook_to_sq );
}

void ChessBoard::post_move_checks() {
  Colour_t non_move_colour; //the side colour that didn't just move
  turn_colour == WHITE ? non_move_colour = BLACK : non_move_colour = WHITE;
  if ( is_in_check( non_move_colour ) ) {
    if ( is_in_checkmate( non_move_colour ) ) {
      cout << (non_move_colour == WHITE ? "White " : "Black ") 
	   << "is in checkmate\n";
      printBoard(); //print the board at the end of the game
      end_of_game = true;
    }
    else
      cout << (non_move_colour == WHITE ? "White " : "Black ") 
	   << "is in check\n";
  }
}

void ChessBoard::change_turn_colour() {
  if ( turn_colour == WHITE )
    turn_colour = BLACK;
  else // if ( turn_colour == BLACK )
    turn_colour = WHITE;
}

bool ChessBoard::check_end_of_game() {
  if ( end_of_game ) {
    cout << "The game has ended!\n"
     	 << "Would you like to resetBoard() and start a new game? "
     	 << "Type 'y' for yes: ";
    char answer;
    cin >> answer;
    cout << endl;
    if ( answer == 'y' || answer == 'Y' )
      resetBoard();
    return true;
  }
  else
    return false;
}
    
void ChessBoard::delete_all_pieces( ) {
  Board_t::iterator it;
  for ( it = the_board.begin(); it != the_board.end(); it++ )
    delete it->cp_pointer;
  the_board.clear();
  return;
}




#include <iostream>
#include "ChessBoard.h"

using namespace std;

int main() {

    cout << "===========================" << endl;
    cout << "Lasker vs. Thomas (1912)" << endl;
    cout << "===========================" << endl;
    cout << endl;

    ChessBoard cb;
    cout << endl;

    cb.submitMove("D2", "D4");
    cb.submitMove("E7", "E6");
    cout << endl;

    cb.submitMove("G1", "F3");
    cb.submitMove("F7", "F5");
    cout << endl;

    cb.submitMove("B1", "C3");
    cb.submitMove("G8", "F6");
    cout << endl;

    cb.submitMove("C1", "G5");
    cb.submitMove("F8", "E7");
    cout << endl;

    cb.submitMove("G5", "F6");
    cb.submitMove("E7", "F6");
    cout << endl;

    cb.submitMove("E2", "E4");
    cb.submitMove("F5", "E4");
    cout << endl;

    cb.submitMove("C3", "E4");
    cb.submitMove("B7", "B6");
    cout << endl;

    cb.submitMove("F3", "E5");
      // Black Castles
    cb.submitMove("E8", "G8");
    cout << endl;

    cb.submitMove("F1", "D3");
    cb.submitMove("C8", "B7");
    cout << endl;

    cb.submitMove("D1", "H5");
    cb.submitMove("D8", "E7");
    cout << endl;

    cb.submitMove("H5", "H7");
    cb.submitMove("G8", "H7");
    cout << endl;

    cb.submitMove("E4", "F6");
    cb.submitMove("H7", "H6");
    cout << endl;

    cb.submitMove("E5", "G4");
    cb.submitMove("H6", "G5");
    cout << endl;

    cb.submitMove("H2", "H4");
    cb.submitMove("G5", "F4");
    cout << endl;

    cb.submitMove("G2", "G3");
    cb.submitMove("F4", "F3");
    cout << endl;

    cb.submitMove("D3", "E2");
    cb.submitMove("F3", "G2");
    cout << endl;

    cb.submitMove("H1", "H2");
    cb.submitMove("G2", "G1");
    cout << endl;

    cb.submitMove("E1", "D2");
    cout << endl;

    return 0;
}

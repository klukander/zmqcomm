#ifndef CHESS_DEFS_H
#define CHESS_DEFS_H

//chess/queen's quadrille specific definitions

#include <string>
#include <array>

enum evttype { EZ, ET, EE, EC, EI, EG, EM, ENA }; // NR = Null/notrecognized
enum evtphase{ begin, end, PNA };
enum tasktype{ TQ, TM, TC, TV, TN, TNA };
enum pieces{ QQ0, KW0, KB0, BW1, BW2, BB1, BB2, TW1, TW2, TB1, TB2, HW1, HW2, HB1, HB2, CNA };
enum squares{ A1, A2, A3, A4, B1, B2, B3, B4, C1, C2, C3, C4, D1, D2, D3, D4, SNA };

//for lookups
const std::array<std::string, 16> piecenames = {"QQ0", "KW0", "KB0", "BW1", "BW2", "BB1", "BB2", "TW1", "TW2", "TB1", "TB2", "HW1", "HW2", "HB1", "HB2", "NA"};
const std::array<std::string, 17> squarenames = {"A1", "A2", "A3", "A4", "B1", "B2", "B3", "B4", "C1", "C2", "C3", "C4", "D1", "D2", "D3", "D4", "NA"};

struct evtmsg{
	evttype type; //Z, T, E, I, G, M
	evtphase phase;
	tasktype task;
	pieces target;
	//for tracking moves
	squares from;
	squares to;
};

evtmsg Parse(std::string msg);

#endif
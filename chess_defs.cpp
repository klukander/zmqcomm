
#include "chess_defs.h"
#include <iostream>
/*
enum evttype {	EZ, zero-time
				EE, event?
				EC, calibration
				EI, instruction
				EG, gazetracking
				EM, move
				ENR }; // NR = Null/notrecognized
enum evtphase{ e_begin, e_end };
enum tasktype  TQ, Queen's 
			   TM, Model Copy
			   TC, Classify B/W
			   TV, Visual search
			   TN, Number-order
enum pieces{ QQ0, KW0, KB0, BW1, BW2, BB1, BB2, TW1, TW2, TB1, TB2, HW1, HW2, HB1, HB2 };
enum squares{ A1, A2, A3, A4, B1, B2, B3, B4, C1, C2, C3, C4, D1, D2, D3, D4 };
*/

evtmsg Parse(std::string msg){
	evtmsg ret = { ENA, PNA, TNA, CNA, SNA, SNA }; //init with NA values
	//should check msg length!?	
	switch (msg[0]){
	case 'Z': //zerotime
		ret.type = EZ;
		if (msg[1] == 'T') ret.phase = e_begin;
		else ret.phase = e_end;
		break;
	case 'T': //task
		ret.type = ET;

		switch (msg[1]){
		case 'Q': ret.task = TQ; break;
		case 'M': ret.task = TM; break;
		case 'C': ret.task = TC; break;
		case 'V': ret.task = TV; break;
		case 'N': ret.task = TN; break;
		}

		if (msg[2] == 'B') ret.phase = e_begin;
		else ret.phase = e_end;
		break;
	case 'C': //calibration
		ret.type = EC;
		if (msg[1] == 'B') ret.phase = e_begin;
		else ret.phase = e_end;
		break;
	case 'E': //event
		ret.type = EE;
		break;
	case 'I': //instruction
		ret.type = EI;
		if (msg[1] == 'B') ret.phase = e_begin;
		else ret.phase = e_end;
		break;
	case 'G': //gaze tracking
		ret.type = EG;
		break;
	case 'M': //move
		ret.type = EM;

		if (msg.length() > 6){

			std::string piecename = msg.substr(1, 3);

			for (int i = 0; i < piecenames.size(); i++){
				if (piecename.compare(piecenames.at(i)) == 0){
					ret.target = (pieces)i;
				} //enums are replaced with an index starting from 0
			}

			std::string movefrom = msg.substr(4, 2);
			std::string moveto = msg.substr(6, 2);
			for (int i = 0; i < squarenames.size(); i++){
				if (movefrom.compare(squarenames.at(i)) == 0){
					ret.from = (squares)i;
				}
				if (moveto.compare(squarenames.at(i)) == 0){
					ret.to = (squares)i;
				}
			}

		}
		else{
			//do we need to do something here?
		}

		break;
	default:
		ret.type = ENA; //not recognized
	}
	return ret;
}

#include "chess_defs.h"

evtmsg Parse(std::string msg){
	evtmsg ret;
	//should check msg length!?
	switch (msg[0]){
	case 'Z': //zerotime
		ret.type = EZ;
		if (msg[1] == 'T') ret.phase = begin;
		else ret.phase = end;
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
		if (msg[2] == 'B') ret.phase = begin;
		else ret.phase = end;
		break;
	case 'E': //event
		ret.type = EE;
		break;
	case 'I': //instruction
		ret.type = EI;
		if (msg[1] == 'B') ret.phase = begin;
		else ret.phase = end;
		break;
	case 'G': //gaze tracking
		ret.type = EG;
		break;
	case 'M': //move
		ret.type = EM;
		break;
	default:
		ret.type = ENR; //not recognized
	}
	return ret;
}
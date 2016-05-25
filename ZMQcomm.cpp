// ZMQcomm.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <iostream>
#include <string>

#include "ZMQCommunicator.h"
#include "chess_defs.h"

// this is the callback function for handling zmq input in your program
void CallbackHandler(evtmsg evt){

	if (evt.type == EZ){
		//std::chrono::time_point<int, std::chrono::milliseconds> zerotime = std::chrono::steady_clock::now();
		//zerotime = std::chrono::steady_clock::now();
		std::cout << "zero time: " << std::endl;// << std::put_time(zerotime.time_since_epoch, "%F %T") << std::endl;
	}
	if (evt.type == ET && evt.task == TQ){
		if (evt.phase == begin) std::cout << "queen's begins!" << std::endl;
		else if (evt.phase == end) std::cout << "queen's ends!" << std::endl;
	}
	if (evt.type == EI){ std::cout << "instruction" << std::endl; }

	if (evt.type == EM){
		std::cout << piecenames.at(evt.target) << " moves from " << squarenames.at(evt.from) << " to " << squarenames.at(evt.to) << std::endl;
	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	ZMQCommunicator *zmqc = new ZMQCommunicator(PAIR, 1000);
	zmqc->setHandler(CallbackHandler);
	zmqc->Connect("127.0.0.1", "5555");
	//zmqc->Connect("192.168.2.183", "5555");

	zmqc->Run();

	std::cout << "running, press enter to stop" << std::endl;
	std::cin.ignore(); //waits for enter
	zmqc->Stop();

	return 0;
}


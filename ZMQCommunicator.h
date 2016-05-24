#pragma once

#include <iostream>
#include "zmq.hpp"
#include <string>
#include "zhelpers.hpp"
#include <thread>

#include <functional> //C++11 callbacks

#include "chess_defs.h"

enum connectiontype { REP, REQ, PAIR, SUB, PUB };

class ZMQCommunicator{
public:
	ZMQCommunicator(connectiontype conntype, int timeout);
	~ZMQCommunicator();
	bool Connect(std::string ip_address, std::string port);
	void Run();
	void Stop();

	void setHandler(std::function<void(evtmsg)> fun);

private:
	std::string address;
	connectiontype conntype;

	zmq::context_t *mContext;
	zmq::socket_t *mSocket;

	std::thread *mThread;
	void ZMQCommunicator::ProcessLoop();

	std::function<void(evtmsg)> evtCallback;

	bool running = false;

};

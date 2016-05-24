#include "ZMQCommunicator.h"

void ZMQCommunicator::setHandler(std::function<void(evtmsg)> fun){
	this->evtCallback = fun;
}

ZMQCommunicator::ZMQCommunicator(connectiontype conntype, int timeout){

	this->conntype = conntype;

	mContext = new zmq::context_t();

	this->evtCallback = nullptr;

	switch (conntype){
	case REP:
		mSocket = new zmq::socket_t(*(mContext), ZMQ_REP);
		break;
	case REQ:
		mSocket = new zmq::socket_t(*(mContext), ZMQ_REQ);
		break;
	case PAIR:
		mSocket = new zmq::socket_t(*(mContext), ZMQ_PAIR);
		break;
	case SUB:
		mSocket = new zmq::socket_t(*(mContext), ZMQ_SUB);
		break;
	case PUB:
		mSocket = new zmq::socket_t(*(mContext), ZMQ_PUB);
		break;
		//there's no default, it'll be one of the connectiontypes
	}

	//set the default timeout to timeout ms
	zmq_setsockopt((*mSocket), ZMQ_RCVTIMEO, &timeout, sizeof(timeout)); // in milliseconds
}

ZMQCommunicator::~ZMQCommunicator(){

	if (this->running) this->Stop();

	mSocket->close();
	mContext->close();

	delete mSocket;
	//delete mContext; //for some unknowable reason, this crashes. Doesn't really matter as this is the end.
}

bool ZMQCommunicator::Connect(std::string ip_address, std::string port){

	//std::cout << "Starting up zmq testing server..." << std::endl;

	switch (conntype){
	case REP:
		mSocket->bind("tcp://" + ip_address + ":" + port);
		break;
	case REQ:
		mSocket->connect("tcp://" + ip_address + ":" + port);
		break;
	case PAIR:
		mSocket->connect("tcp://" + ip_address + ":" + port);
		break;
	case SUB:
		mSocket->connect("tcp://" + ip_address + ":" + port);
		break;
	case PUB:
		mSocket->bind("tcp://" + ip_address + ":" + port);
		break;
	}

	return true;
}

void ZMQCommunicator::ProcessLoop(){
	auto zerotime = std::chrono::steady_clock::now();

	while (running) {
		try{
			zmq::message_t request;

			// Wait for next request from client, this is a blocking operation (run in it's own thread)
			// zmq_setsockopt((*mSocket), ZMQ_RCVTIMEO, &timeout, sizeof(timeout)); // allows to set a timeout in milliseconds to avoid infinite wait (done in constructor)

			//mSocket->recv(&request);
			std::string msg = s_recv((*mSocket)); 

			// Parse could also be made to be a callback?
			evtmsg evt = Parse(msg);

			//call the callback
			evtCallback(evt);

		}
		catch (const zmq::error_t& ex)
		{
			// recv() throws ETERM when the zmq context is destroyed,
			//  as when AsyncZmqListener::Stop() is called
			if (ex.num() != ETERM)
				throw;
		}
	}

	std::cout << "ZMQC stopped" << std::endl;
}

void ZMQCommunicator::Run(){

	this->running = true;
	mThread = new std::thread(&ZMQCommunicator::ProcessLoop, this);

}

void ZMQCommunicator::Stop(){
	running = false;
	mThread->join();
}

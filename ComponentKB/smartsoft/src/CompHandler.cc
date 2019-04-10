//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain
// The SmartSoft Toolchain has been developed by:
//  
// Service Robotics Research Center
// University of Applied Sciences Ulm
// Prittwitzstr. 10
// 89075 Ulm (Germany)
//
// Information about the SmartSoft MDSD Toolchain is available at:
// www.servicerobotik-ulm.de
//
// This file is generated once. Modify this file to your needs. 
// If you want the toolchain to re-generate this file, please 
// delete it before running the code generator.
//--------------------------------------------------------------------------
#include "CompHandler.hh"
#include "ComponentKB.hh"
#include "CompTask.hh"
#include "KbEventServerEventTestHandler.hh"

#include <iostream>

#if defined (__GNUC__) && defined(__unix__)

#elif defined (WIN32) || defined (WIN64)
#include <locale.h>
#endif

#include <ace/Init_ACE.h>

// include communication objects

//CompTask can not be a managed task!
CompTask COMP_TASK;

////////////////////////////////////////////////
// Lisp-C-Interface


#if defined (__GNUC__) && defined(__unix__)
extern "C" char* getquery()
#elif defined (WIN32) || defined (WIN64)
extern "C" __declspec(dllexport) char* getquery()
#endif
{
	//the buffer will be freed on the lisp side
	char* result = NULL;

	//10 bytes extra for () the spaces and the null termination
	unsigned int char_size = 10;

	std::cout<<"[MAIN-L] Wait for kBQueryHandler->getQuery..."<<std::endl;
	CommBasicObjects::CommKBRequest request;
	long id;
	if(COMP->kbQueryHandler->getQuery(request, id) != 0){
		char_size += 100;
		result = (char *)malloc(char_size * sizeof(char));
		sprintf(result, "(%d %s)" , 0, "(ON_COMPONENT_SHUTDOWN)");
	} else {
		std::cout<<"Got Query! ID: "<<id<<"req: "<<request<<std::endl;
		char_size += request.getRequest().size();
		result = (char *)malloc(char_size * sizeof(char));
		sprintf(result, "(%ld %s)", id, request.getRequest().c_str());
	}
	return result;
}

#if defined (__GNUC__) && defined(__unix__)
extern "C" void answerquery(char* inString, long id)
#elif defined (WIN32) || defined (WIN64)
extern "C" __declspec(dllexport) void answerquery(char* inString, long id)
#endif
{

	CommBasicObjects::CommKBResponse answer;
	answer.setResponse(inString);
	COMP->kbQueryHandler->answerQuery(answer, id);
}

#if defined (__GNUC__) && defined(__unix__)
extern "C" void memorychanged()
#elif defined (WIN32) || defined (WIN64)
extern "C" __declspec(dllexport) void memorychanged()
#endif
{
	//do not hand over the full memory as state (empty com obj.)
	//the handler will ask the KB for changes
	CommBasicObjects::CommVoid dummy;
//	std::cout<<__FUNCTION__<<"-->PUT"<<std::endl;
	COMP->kbEventServer->put(dummy);
//	std::cout<<__FUNCTION__<<" PUT-->DONE."<<std::endl;
}

#if defined (__GNUC__) && defined(__unix__)
extern "C" char* getcheckparamevent()
#elif defined (WIN32) || defined (WIN64)
extern "C" __declspec(dllexport) char* getcheckparamevent()
#endif
{
	//the buffer will be freed on the lisp side
	char* result = NULL;

	//10 bytes extra for () the spaces and the null termination
	unsigned int char_size = 10;

	std::cout<<"Wait for CheckParamForEvent!"<<std::endl;
	CommBasicObjects::CommKBEventParam param;
	if(dynamic_cast<KbEventServerEventTestHandler*>(COMP->kbEventServerEventTestHandler)->getCheckEventParam(param) != 0){
		std::cout<<__FUNCTION__<<":"<<__LINE__<<std::endl;
		char_size +=100;
		result = (char *)malloc(char_size * sizeof(char));
		sprintf(result,"(ON_COMPONENT_SHUTDOWN nil nil)");
	} else {
		if(param.getFormatingClause().empty()== true){
			char_size += param.getQuery().size();
			char_size += param.getLatestState().size();
			result = (char *)malloc(char_size * sizeof(char));
			sprintf(result,"(%s nil %s)", param.getQuery().c_str(), param.getLatestState().c_str());

		} else {
			char_size += param.getQuery().size();
			char_size += param.getFormatingClause().size();
			char_size += param.getLatestState().size();
			result = (char *)malloc(char_size * sizeof(char));
			sprintf(result,"(%s %s %s)", param.getQuery().c_str(), param.getFormatingClause().c_str(), param.getLatestState().c_str());
		}
	}
	return result;
}

#if defined (__GNUC__) && defined(__unix__)
extern "C" void answercheckeventparam(char* inString, bool fireEvent, char* formatedAnswer)
#elif defined (WIN32) || defined (WIN64)
extern "C" __declspec(dllexport) void answercheckeventparam(char* inString, bool fireEvent, char* formatedAnswer)
#endif
{

//	std::cout<<__FUNCTION__<<":"<<__LINE__<<std::endl;
//	std::cout<<"inString: "<<inString<<std::endl;
//	std::cout<<"formatedAnswer: "<<formatedAnswer<<std::endl;
	CommBasicObjects::CommKBEventResult answer;
	answer.setResult(inString);
	answer.setFormatedResult(formatedAnswer);
	dynamic_cast<KbEventServerEventTestHandler*>(COMP->kbEventServerEventTestHandler)->answerCheckEventParam(answer,fireEvent);
}


#if defined (__GNUC__) && defined(__unix__)
extern "C" int registerslavedentry(char* key, char* values )
#elif defined (WIN32) || defined (WIN64)
extern "C" __declspec(dllexport) int registerslavedentry(char* key, char* values )
#endif
{
	std::stringstream ss;
	ss<<"(kb-query-all :key '"<<key<<" :value '"<<values<<")";
	CommBasicObjects::CommKBEventParam eventParam;
	eventParam.setQuery(ss.str());
//	locationsEventsParam.setFormatingClause(),
	SmartACE::EventId eventID;
	Smart::StatusCode status = COMP->kbChainedEntriesEventClient->activate(Smart::continuous, eventParam, eventID);
	std::cout<<"Event Activate result: "<<Smart::StatusCodeConversion(status)<<" EventID: "<<eventID<<std::endl;
	return eventID;
}

void CompHandler::onStartup() 
{
	// TO NOT USE THIS METHOD --> WILL NEVER BE CALLED!
}

void CompHandler::onShutdown() 
{
	// TO NOT USE THIS METHOD --> WILL NEVER BE CALLED!
	
}

#if defined (__GNUC__) && defined(__unix__)
extern "C" int initialize(char* param)
#elif defined (WIN32) || defined (WIN64)
extern "C" __declspec(dllexport) int initialize(char* param)
#endif
{
//	CHS::StatusCode status;

	// force to use point as decimal seperator (required because of SBCL)
	setlocale(LC_NUMERIC, "C");

	std::cout << "initialize  param: " << param << "\n";


	std::istringstream iss(param);
	std::string s;
	std::vector< std::string > list;
	while ( getline( iss, s, ' ' ) ) {
		list.push_back(s);
	}

	//char *argv[list.size()];
	char** argv = new char*[list.size()];
	for(unsigned int i=0;i<list.size();i++){
		//argv[i] = list[i].c_str();
		argv[i] = const_cast<char*> (list[i].c_str());
	}

	//TODO Not yet clear why this is needed in windows VS14
	std::cout << "ACE init..." << std::endl;
	ACE::init();
	std::cout << "DONE ACE init" << std::endl;

//	argv[0] = (char*)"dummy";
//	argv[1] = paramFile;
	COMP->init(list.size(), argv);

	// start the component task!
	COMP_TASK.open();

	//set component state to ALIVE!
	COMP->setStartupFinished();

	if(COMP->getGlobalState().getSettings().getConnectChainedEntries() == true)
	{
		Smart::StatusCode status;

		std::cout << "connecting to: " << COMP->connections.kbChainedEntriesEventClient.serverName
				<< "; " << COMP->connections.kbChainedEntriesEventClient.serviceName << std::endl;
		status = COMP->kbChainedEntriesEventClient->connect(
				COMP->connections.kbChainedEntriesEventClient.serverName,
				COMP->connections.kbChainedEntriesEventClient.serviceName);
		while (status != Smart::SMART_OK)
		{
			usleep(500000);
			status = COMP->kbChainedEntriesEventClient->connect(
					COMP->connections.kbChainedEntriesEventClient.serverName,
					COMP->connections.kbChainedEntriesEventClient.serviceName);
		}
		std::cout << "connected.\n";
	}

	delete [] argv;
	return 0;
}

#if defined (__GNUC__) && defined(__unix__)
extern "C" void waitoncomptasktocomplete()
#elif defined (WIN32) || defined (WIN64)
extern "C" __declspec(dllexport) void waitoncomptasktocomplete()
#endif
{
	ACE_Thread_Manager::instance()->wait_task(&COMP_TASK);
}


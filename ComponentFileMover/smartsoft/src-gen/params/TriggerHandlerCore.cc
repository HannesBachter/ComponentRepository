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
// Please do not modify this file. It will be re-generated
// running the code generator.
//--------------------------------------------------------------------------

#include "TriggerHandlerCore.hh"

int TriggerHandlerCore::on_execute()
{
	// blocking wait until some active trigger request(s) come in
	sema.acquire();
	
	{
		SmartACE::SmartGuard g(mutex);
		
		// get the top trigger from the queue
		current_trigger_enumerator = trigger_queue.front();
		trigger_queue.pop();
		
		// retrieve the corresponding trigger attributes from the trigger specific queue
		switch(current_trigger_enumerator) {
		case TriggerEnumerators::COMMBASICOBJECTS_FILEOPERATIONSPARAM_COPYFILE:
			current_CommBasicObjects_FileOperationsParam_COPYFILE = CommBasicObjects_FileOperationsParam_COPYFILE_queue.front();
			CommBasicObjects_FileOperationsParam_COPYFILE_queue.pop();
			break;
		}
	} // mutex release

	// now call the corresponding trigger handler
	// (releasing the mutex before, allows to store newly incoming trigger commands on the queue in parallel)
	switch(current_trigger_enumerator) {
	case TriggerEnumerators::COMMBASICOBJECTS_FILEOPERATIONSPARAM_COPYFILE:
		this->handleCommBasicObjects_FileOperationsParam_COPYFILE(current_CommBasicObjects_FileOperationsParam_COPYFILE.sourceFile, current_CommBasicObjects_FileOperationsParam_COPYFILE.destinationFile);
		break;
	}
	return 0;
}

//
// trigger internal handler methods
//

	// handle COPYFILE
	void TriggerHandlerCore::handleCommBasicObjects_FileOperationsParam_COPYFILECore(const std::string &sourceFile, const std::string &destinationFile)
	{
		SmartACE::SmartGuard g(mutex);

		// store the current set of trigger-attributes in a queue
		CommBasicObjects_FileOperationsParam_COPYFILEAttributes attr;
		attr.destinationFile = destinationFile;
		attr.sourceFile = sourceFile;
		CommBasicObjects_FileOperationsParam_COPYFILE_queue.push(attr);
		
		// store the current trigger call in the shared trigger-queue
		trigger_queue.push(TriggerEnumerators::COMMBASICOBJECTS_FILEOPERATIONSPARAM_COPYFILE);
		
		// signal the task, in case it is waiting
		sema.release();
	}

//
// extended trigger internal handler methods
//
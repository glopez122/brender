/*
 * @author: Gustavo Lopez 10-21-17
 * 
 * @version: 2.2.0
 */

#include "ObjExportManager.h"
#include "ObjExportable.h"


using namespace std;

bool ObjExportManager::instanceFlag = false;
ObjExportManager* ObjExportManager::manager = NULL;
ObjExportManager* ObjExportManager::getInstance()
{
	if (!instanceFlag)
	{
		manager = new ObjExportManager();
		instanceFlag = true;
		return manager;
	}
	else
	{
		return manager;
	}
}

int ObjExportManager::getFrame()
{
	return frame;
}

void ObjExportManager::exportObjs()
{
	int objNum = 1;
	for (auto objExportable : objExportables) {
		ofstream outfile;

		char filename[50];
		const char* checkname = objExportable->getObjName().c_str();
		//if object has not been given name
		if (strcmp(checkname, "") == 0) {
			sprintf(filename, "%s/%06d_Object%d.obj", EXPORT_DIR, frame, objNum);
		}
		//if object has been given specific name
		else {
			std::string objname_str = objExportable->getObjName();
			char* objname_char = new char[objname_str.length() + 1];
			strcpy(objname_char, objname_str.c_str());
			sprintf(filename, "%s/%06d_%s.obj", EXPORT_DIR, frame, objname_char);
		}
		//open file
		outfile.open(filename);
		//frame string
		char framestring[50];
		sprintf(framestring, "# frame %06d \n", frame);
		outfile << framestring;
		//obj name
		//if object has not been given name
		if (strcmp(checkname, "") == 0) {
			outfile << "# name Object " + to_string(objNum) + " \n";
		}
		//if object has been given specific name
		else {
			outfile << "# name " + objExportable->getObjName() + " \n";
		}
		objExportable->exportObj(outfile);
		outfile.close();
		objNum++;
	}
	//Only time frame should be changed/modified
	frame++;
}

void ObjExportManager::exportObjs(double time)
{
	int objNum = 1;
	for (auto objExportable : objExportables) {
		ofstream outfile;

		char filename[100];

		const char* checkname = objExportable->getObjName().c_str();
		//if object has not been given name
		if (strcmp(checkname, "") == 0) {
			sprintf(filename, "%s/%06d_Object%d.obj", EXPORT_DIR, frame, objNum);
		}
		//if object has been given specific name
		else {
			std::string objname_str = objExportable->getObjName();
			char* objname_char = new char[objname_str.length() + 1];
			strcpy(objname_char, objname_str.c_str());
			sprintf(filename, "%s/%06d_%s.obj", EXPORT_DIR, frame, objname_char);
			}
		//open file
		outfile.open(filename);
		//frame string
		char framestring[50];
		sprintf(framestring, "# frame %06d \n", frame);
		outfile << framestring;
		//frame time
		char timeval[50];
		sprintf(timeval, "# time %f \n", time);
		outfile << timeval;
		//obj name
		//if object has not been given name
		if (strcmp(checkname, "") == 0) {
			outfile << "# name Object" + to_string(objNum) + " \n";
		}
		//if object has been given specific name
		else {
			outfile << "# name " + objExportable->getObjName() + " \n";
		}
		objExportable->exportObj(outfile);
		outfile.close();
		objNum++;
	}
	//Only time frame should be changed/modified
	frame++;
}

void ObjExportManager::add(shared_ptr<ObjExportable> exportable)
{
	objExportables.push_back(exportable);
}

void ObjExportManager::setExportDir(std::string export_dir) 
{	
	char* export_char = new char[export_dir.length() + 1];
	strcpy(export_char, export_dir.c_str());
	EXPORT_DIR = export_char;
}



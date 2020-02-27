// Module:	PeopleClass.h
// Author:	Miguel Antonio Logarta
// Date:	February 26, 2020
// Purpose: Adds methods to <string>
//			Header file for PeopleClass.h

#pragma once
class PeopleClass :
	public string
{
public:
	string TCHARToString(TCHAR*);											// Convert TCHAR to string
	TCHAR* StringToTCHAR(string);											// Convert string to TCHAR

private:
	string strReturn;														// Return value
	TCHAR szReturn[TCHAR_SIZE];												// Return value
};


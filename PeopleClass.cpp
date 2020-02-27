// Module:	PeopleClass.h
// Author:	Miguel Antonio Logarta
// Date:	February 26, 2020
// Purpose: Implementation file for PeopleClass
//			Adds methods to <string>

#include "framework.h"
#include "CIS023_S2020_Lab11b Miguel Antonio Logarta.h"

string PeopleClass::TCHARToString(TCHAR* szIn)
{
	strReturn = "";											// Empty the return value, just in case

	if (lstrlen(szIn) != 0)									// If empty, do nothing
	{
		wstring temp(szIn);									// Convert TCHAR to wstring
		string str(temp.begin(), temp.end());				// Convert wstring to string
		strReturn = str;									// Copy temp string to return
	}

	return strReturn;										// Return the converted (or empty) string
}

TCHAR* PeopleClass::StringToTCHAR(string strIn)
{
	size_t pReturnValue;									// Return value for mbstowcs_s()

	mbstowcs_s(												// Convert chars to TCHAR
		&pReturnValue,										// Return value
		szReturn,											// Destination TCHAR
		TCHAR_SIZE,											// Size of TCHAR
		strIn.c_str(),										// Source string
		TCHAR_SIZE);										// Max chars to convert


	return szReturn;										// Return the TCHAR
}

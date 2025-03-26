// Lab1_PD_PA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383
#define TOTALBYTES    8192
#define BYTEINCREMENT 4096
using namespace std;             

void QueryKey(HKEY hKey)
{
    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName = 0;                   // size of name string 
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
    DWORD    cchClassName = MAX_PATH;  // size of class string 
    DWORD    cSubKeys = 0;               // number of subkeys 
    DWORD    cbMaxSubKey = 0;              // longest subkey size 
    DWORD    cchMaxClass = 0;              // longest class string 
    DWORD    cValues = 0;              // number of values for key 
    DWORD    cchMaxValue = 0;          // longest value name 
    DWORD    cbMaxValueData = 0;       // longest value data 
    DWORD    cbSecurityDescriptor = 0; // size of security descriptor 
    FILETIME ftLastWriteTime;      // last write time 

    DWORD i = 0, j = 0, retCode = 0;

    TCHAR  achValue[MAX_VALUE_NAME] = { '\0' };
    DWORD cchValue = MAX_VALUE_NAME;

    // Get the class name and the value count. 
    retCode = ::RegQueryInfoKey(
        hKey,                    // key handle 
        achClass,                // buffer for class name 
        &cchClassName,           // size of class string 
        NULL,                    // reserved 
        &cSubKeys,               // number of subkeys 
        &cbMaxSubKey,            // longest subkey size 
        &cchMaxClass,            // longest class string 
        &cValues,                // number of values for this key 
        &cchMaxValue,            // longest value name 
        &cbMaxValueData,         // longest value data 
        &cbSecurityDescriptor,   // security descriptor 
        &ftLastWriteTime);       // last write time 


    printf("Query info error status code : %d\n", retCode);
    // Enumerate the subkeys, until RegEnumKeyEx fails.

    if (cSubKeys)
    {
        printf("\nNumber of subkeys: %d\n", cSubKeys);
        for (i = 0; i < cSubKeys; i++)
        {
            cbName = MAX_KEY_LENGTH;
            retCode = ::RegEnumKeyEx(hKey, i,
                achKey,
                &cbName,
                NULL,
                NULL,
                NULL,
                  &ftLastWriteTime);
            if (retCode == ERROR_SUCCESS)
            {
                _tprintf(TEXT("(%d) %s\n"), i + 1, achKey);
            }
        }
    }

    // Enumerate the key values. 

    if (cValues)
    {
        printf("\nNumber of values: %d\n", cValues);
        for (i = 0; i < cValues; i++)
        {
            cchValue = MAX_VALUE_NAME;
            achValue[0] = '\0';
            retCode = ::RegEnumValue(hKey, i,
                achValue,
                &cchValue,
                NULL,
                NULL,
                NULL,
                NULL);
            if (retCode == ERROR_SUCCESS)
            {
                _tprintf(TEXT("(%d) %s\n"), i + 1, achValue);
            }
        }
    }
}

int main()
{
    DWORD BufferSize = TOTALBYTES;
    DWORD cbData;
    DWORD dwRet;

    PPERF_DATA_BLOCK PerfData = (PPERF_DATA_BLOCK)malloc(BufferSize);
    cbData = BufferSize;
    HKEY hTestKey = 0;

    cout << "Hello World!| Start of programm\n";
    if (RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Control Panel\\Desktop\\Colors"), 0, KEY_READ, &hTestKey) == ERROR_SUCCESS)
    {
        QueryKey(hTestKey);
    }

    
    dwRet = RegQueryValueEx(hTestKey,
        TEXT("InfoText"),
        NULL,
        NULL,
        (LPBYTE)PerfData,
        &cbData);

    while (dwRet == ERROR_MORE_DATA)
    {
        // Get a buffer that is big enough.

        BufferSize += BYTEINCREMENT;
        PerfData = (PPERF_DATA_BLOCK)realloc(PerfData, BufferSize);
        cbData = BufferSize;

        printf(".");
        dwRet = RegQueryValueEx(HKEY_PERFORMANCE_DATA,
            TEXT("InfoText"),
            NULL,
            NULL,
            (LPBYTE)PerfData,
            &cbData);
    }
    
    if(PerfData != NULL)
    {
        printf("\n value of key: ");
        
        for (i=0; i<cbData;i++)     
        {
            printf("%x", PerfData[i]);
        }
        
        printf("\n");
    }

    if (RegCloseKey(hTestKey) == ERROR_SUCCESS)
    {
        printf("Successfully closed reg!\n");
    }
    else {
        printf("Error when closing reg: %d\n", RegCloseKey(hTestKey));
    }
    
    system("pause");
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
// LAB2_Memory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
using namespace std;

#define PAGELIMIT 80            // Number of pages to ask for
#define ISIZE 2000


LPTSTR lpNxtPage;               // Address of the next page to ask for
DWORD dwPages = 0;              // Count of pages gotten so far
DWORD dwPageSize;               // Page size on this computer

INT PageFaultExceptionFilter(DWORD dwCode)
{
    LPVOID lpvResult;

    // If the exception is not a page fault, exit.

    if (dwCode != EXCEPTION_ACCESS_VIOLATION)
    {
        _tprintf(TEXT("Exception code = %d.\n"), dwCode);
        return EXCEPTION_EXECUTE_HANDLER;
    }

    _tprintf(TEXT("Exception is a page fault.\n"));

    // If the reserved pages are used up, exit.

    if (dwPages >= PAGELIMIT)
    {
        _tprintf(TEXT("Exception: out of pages.\n"));
        return EXCEPTION_EXECUTE_HANDLER;
    }

    // Otherwise, commit another page.

    lpvResult = VirtualAlloc(
        (LPVOID)lpNxtPage, // Next page to commit
        dwPageSize,         // Page size, in bytes
        MEM_COMMIT,         // Allocate a committed page
        PAGE_READWRITE);    // Read/write access
    if (lpvResult == NULL)
    {
        _tprintf(TEXT("VirtualAlloc failed.\n"));
        return EXCEPTION_EXECUTE_HANDLER;
    }
    else
    {
        _tprintf(TEXT("Allocating another page.\n"));
    }

    // Increment the page count, and advance lpNxtPage to the next page.

    dwPages++;
    lpNxtPage = (LPTSTR)((PCHAR)lpNxtPage + dwPageSize);

    // Continue execution where the page fault occurred.

    return EXCEPTION_CONTINUE_EXECUTION;
}

VOID ErrorExit(LPTSTR lpMsg)
{
    _tprintf(TEXT("Error! %s with error code of %ld.\n"),
        lpMsg, GetLastError());
    exit(0);
}

VOID _tmain(VOID)
{
    LPVOID lpvBase;               // Base address of the test memory
    LPTSTR lpPtr;                 // Generic character pointer
    BOOL bSuccess;                // Flag
    DWORD i;                      // Generic counter
    SYSTEM_INFO sSysInfo;         // Useful information about the system

    GetSystemInfo(&sSysInfo);     // Initialize the structure.
    _tprintf(TEXT("This computer has page size %d.\n"), sSysInfo.dwPageSize);
    dwPageSize = sSysInfo.dwPageSize;

    int nrPages;
    nrPages = ceil(ISIZE / dwPageSize)+1;
    _tprintf(TEXT("\n # Size in pages = %d\n"), nrPages);

    // Reserve pages in the virtual address space of the process.

    lpvBase = VirtualAlloc(
        NULL,                 // System selects address
        (nrPages+1) * dwPageSize, // Size of allocation
        MEM_COMMIT,          // Allocate reserved pages
        PAGE_READWRITE);       // Protection = no access

    if (lpvBase == NULL)
        ErrorExit(LPTSTR(TEXT("VirtualAlloc reserve failed.")));

    _tprintf(TEXT("\n # Start address = 0x%x\n"), lpvBase);
    lpPtr = lpNxtPage = (LPTSTR)lpvBase;

    // Use structured exception handling when accessing the pages.
    // If a page fault occurs, the exception filter is executed to
    // commit another page from the reserved block of pages.
    for (i = 0; i < nrPages * dwPageSize; i++)
    {
        __try
        {
            // Write to memory.

            lpPtr[i] = '0';
        }

        // If there's a page fault, commit another page and try again.

        __except (PageFaultExceptionFilter(GetExceptionCode()))
        {

            // This code is executed only if the filter function
            // is unsuccessful in committing the next page.

            _tprintf(TEXT("Finish memory search, Exiting process.\n"));
            break;
            //ExitProcess(GetLastError());

        }

    }

    // Release the block of pages when you are finished using them.
    _tprintf(TEXT("\n # Stop address = 0x%x\n"), lpPtr);
    _tprintf(TEXT("\n # Total size allocated = 0x%x | %d bytes | %d bits\n"), i, i ,i*8);
    _tprintf(TEXT("\n # Total size used      =  0x%x | %d bytes | %d bits\n"), ISIZE, ISIZE, ISIZE*8);

    bSuccess = VirtualFree(
        lpvBase,       // Base address of block
        0,             // Bytes of committed pages
        MEM_RELEASE);  // Decommit the pages

    _tprintf(TEXT("\nRelease %s.\n"), bSuccess ? TEXT("succeeded") : TEXT("failed"));
    system("pause");
}
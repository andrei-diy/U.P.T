#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <winioctl.h>
using namespace std;
int main()
{
	HANDLE HandleFile;
	BOOL Result;
	DISK_GEOMETRY pdg = { 0 };
	ULONGLONG DiskSize = 0;
	LPDWORD JUNK;

	HandleFile = CreateFileA(
		LPCSTR(TEXT("E")),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);

	if (HandleFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(TEXT("\n Invalid Handle \n"));
	}

	Result = DeviceIoControl(
		HandleFile,
		//IOCTL_DISK_GET_DRIVE_LAYOUT_EX, //
		IOCTL_DISK_GET_DRIVE_GEOMETRY,
		NULL, 0,
		pdg, 
		sizeof(pdg),
		JUNK,
		(LPOVERLAPPED)NULL);

	CloseHandle(HandleFile);
	
	if (Result)
	{
		DISK_GEOMETRY pdg2 = pdg;
		_tprintf(TEXT("Cylinders       = %I64d\n"), pdg2.Cylinders);
		_tprintf(TEXT("Tracks/cylinder = %ld\n"), (ULONG)pdg2.TracksPerCylinder);
		_tprintf(TEXT("Sectors/track   = %ld\n"), (ULONG)pdg2.SectorsPerTrack);
		_tprintf(TEXT("Bytes/sector    = %ld\n"), (ULONG)pdg2.BytesPerSector);
		DiskSize = pdg2.Cylinders.QuadPart * (ULONG)pdg2.TracksPerCylinder * (ULONG)pdg2.SectorsPerTrack * (ULONG)pdg2.BytesPerSector;
		_tprintf(TEXT("Disk size       = %I64d (Bytes) = %I64d (Gb)\n"), DiskSize, DiskSize / (1024 * 1024 * 1024));

	}
	else
	{
		_tprintf(TEXT("\n Could not reag geometry drive data \n"));
	}

	return 0;

}
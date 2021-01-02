/*
 *	Upanix - An x86 based Operating System
 *  Copyright (C) 2011 'Prajwala Prabhakar' 'srinivasa_prajwal@yahoo.co.in'
 *                                                                          
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *                                                                          
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *                                                                          
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/
 */

#pragma once

#if defined __cplusplus
extern "C" {
#endif

# include <stdlib.h>
# include <stdbool.h>
# include <fs.h>
# include <mosstd.h>
# include <drive.h>

#define NO_OF_SYSCALL_PARAMS 10

#define DO_SYS_CALL(SYS_CALL_ID) \
__asm__ __volatile__("pushl %0" : : "i"(SYS_CALL_ID)) ; \
__asm__ __volatile__("lcall $0x78, $0x00") ; 

/*********************************** SYS CALL NUMBERS *******************************/

typedef enum
{
	SYS_CALL_DISPLAY_START = 0,
		SYS_CALL_DISPLAY_MESSAGE,
		SYS_CALL_DISPLAY_CHARACTER,
		SYS_CALL_DISPLAY_CLR_SCR,
		SYS_CALL_DISPLAY_MOV_CURSOR,
		SYS_CALL_DISPLAY_CLR_LINE,
		SYS_CALL_DISPLAY_ADDRESS,
		SYS_CALL_DISPLAY_SET_CURSOR,
		SYS_CALL_DISPLAY_GET_CURSOR,
		SYS_CALL_DISPLAY_RAW_CHAR,
    SYS_CALL_DISPLAY_SIZE,
	SYS_CALL_DISPLAY_END,
	
	SYS_CALL_FILE_START = 200,
		SYS_CALL_CHANGE_DIR,
		SYS_CALL_PWD,
		SYS_CALL_CWD,
		SYS_CALL_MKDIR,
		SYS_CALL_RMDIR,
		SYS_CALL_GET_DIR_LIST,
		SYS_CALL_FILE_OPEN,
		SYS_CALL_FILE_CREATE,
		SYS_CALL_FILE_CLOSE,
		SYS_CALL_FILE_READ,
		SYS_CALL_FILE_WRITE,
		SYS_CALL_FILE_SEEK,
		SYS_CALL_FILE_TELL,
		SYS_CALL_FILE_MODE,
		SYS_CALL_FILE_STAT,
		SYS_CALL_FILE_STAT_FD,
		SYS_CALL_FILE_ACCESS,
		SYS_CALL_FILE_DUP2,
		SYS_CALL_FILE_RESET_STD,
	SYS_CALL_FILE_END,

	SYS_CALL_MEM_START = 400,
		SYS_CALL_ALLOC,
		SYS_CALL_FREE,
		SYS_CALL_GET_ALLOC_SIZE,
	SYS_CALL_MEM_END,

	SYS_CALL_PROC_START = 600,
		SYS_CALL_DLL_RELOCATE,
		SYS_CALL_PROCESS_EXEC,
		SYS_CALL_THREAD_EXEC,
		SYS_CALL_PROCESS_WAIT_PID,
		SYS_CALL_PROCESS_EXIT,
		SYS_CALL_PROCESS_SLEEP,
		SYS_CALL_PROCESS_PID,
		SYS_CALL_PROCESS_GET_ENV,
		SYS_CALL_PROCESS_SET_ENV,
		SYS_CALL_PROCESS_GET_PS_LIST,
		SYS_CALL_PROCESS_FREE_PS_LIST,
		SYS_CALL_DISABLE_TASK_SWITCH,
		SYS_CALL_ENABLE_TASK_SWITCH,
		SYS_CALL_PROCESS_CHILD_ALIVE,
	SYS_CALL_PROC_END,

	SYS_CALL_KB_START = 800,
		SYS_CALL_KB_READ,
	SYS_CALL_KB_END,

	SYS_CALL_DRIVE_START = 900,
		SYS_CALL_CHANGE_DRIVE,
		SYS_CALL_SHOW_DRIVES,
		SYS_CALL_MOUNT_DRIVE,
		SYS_CALL_UNMOUNT_DRIVE,
		SYS_CALL_FORMAT_DRIVE,
		SYS_CALL_CURRENT_DRIVE_STAT,
	SYS_CALL_DRIVE_END,

	SYS_CALL_UTIL_START = 1200,
		SYS_CALL_UTIL_DTIME,
		SYS_CALL_UTIL_REBOOT,
		SYS_CALL_UTIL_TOD,
	SYS_CALL_UTIL_END,

} SYS_CALL_NUMBERS ;

/************************************************************************************/

void SysDisplay_Message(const char* szMessage, unsigned uiAttr);
void SysDisplay_Character(const char ch, unsigned uiAttr);
void SysDisplay_ClearScreen();
void SysDisplay_MoveCursor(int n);
void SysDisplay_ClearLine(int pos);
void SysDisplay_Address(const char* szMessage, unsigned uiNumber);
void SysDisplay_SetCursor(__volatile__ int iCurPos, __volatile__ bool bUpdateCursorOnScreen);
int SysDisplay_GetCursor();
void SysDisplay_RawCharacter(__volatile__ const char ch, __volatile__ unsigned uiAttr, __volatile__ bool bUpdateCursorOnScreen);

int SysDrive_ChangeDrive(const char* szDriveName);
int SysDrive_ShowDrives(DriveStat** pDriveList, int* iListSize);
int SysDrive_Mount(const char* szDriveName);
int SysDrive_UnMount(const char* szDriveName);
int SysDrive_Format(const char* szDriveName);
int SysDrive_GetCurrentDriveStat(DriveStat* pDriveStat);

int SysFS_ChangeDirectory(const char* szDirPath);
void SysFS_PWD(char** uiReturnDirPathAddress);
int SysFS_CreateDirectory(const char* szDirPath, unsigned short usAttribute);
int SysFS_DeleteDirectory(const char* szDirPath);
int SysFS_GetDirContent(const char* szDirPath, FS_Node** pDirList, int* iListSize);
int SysFS_CreateFile(const char* szDirPath, unsigned short usAttribute);
int SysFS_FileOpen(const char* szFileName, byte bMode);
int SysFS_FileClose(int fd);
int SysFS_FileRead(int fd, char* buf, int len);
int SysFS_FileWrite(int fd, const char* buf, int len);
int SysFS_FileSeek(int fd, int offSet, int seekType);
int SysFS_FileTell(int fd);
int SysFS_FileOpenMode(int fd);
int SysFS_FileStat(const char* szFileName, struct stat* pFileStat);
int SysFS_FileStatFD(int iFD, struct stat* pFileStat);

void SysKB_GetWait(int* ch);

int SysMemory_Alloc(void** addr, unsigned uiSizeInBytes);
int SysMemory_Free(void* uiAddress);
int SysMemory_GetAllocSize(void* uiAddress, int* size);
int SysProcess_Exec(const char* szFileName, int iNoOfArgs, char *const szArgList[]);
int SysProcess_ThreadExec(uint32_t threadCaller, uint32_t entryAddress, void* arg);
void SysProcess_WaitPID(int iProcessID);
void SysProcess_Exit(int iExitStatus);
void SysProcess_Sleep(unsigned milisec);
int SysProcess_GetPID();
const char* SysProcess_GetEnv(const char* szVar);
int SysProcess_SetEnv(const char* szVar, const char* szVal);
int SysProcess_GetProcList(PS** pProcList, unsigned* uiListSize);
void SysProcess_FreeProcListMem(PS* pProcList, unsigned uiListSize);
void SysProcess_DisableTaskSwitch();
void SysProcess_EnableTaskSwitch();

void SysUtil_GetDateTime(RTCTime* pRTCTime);
void SysUtil_Reboot();

int SysUtil_GetTimeOfDay(struct timeval* pTV);

#if defined __cplusplus
}
#endif

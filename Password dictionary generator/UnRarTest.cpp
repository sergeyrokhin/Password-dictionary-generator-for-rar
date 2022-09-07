#define STRICT
#include <windows.h>
#include <stdio.h>
#include <ctype.h>
#include <locale.h>
#include "unrar.h"
#include "Сombinatorics.h"

extern bool password_found;
enum { EXTRACT, TEST, PRINT, LIST };

void ExtractArchive(char* ArcName);
void ListArchive(char* ArcName);
void ShowComment(wchar_t* CmtBuf);
void OutHelp(void);

enum ERR_TYPE { ERR_OPEN, ERR_READ, ERR_PROCESS };
void OutError(int Error, char* ArcName, int ErrType);

void ShowArcInfo(unsigned int Flags, char* ArcName);
void PrintTime(const char* Label, unsigned int Low, unsigned int High);
void OutProcessFileError(int Error);
int CALLBACK CallbackProc(UINT msg, LPARAM UserData, LPARAM P1, LPARAM P2);

PasswordCounter* PC;

void OutHelp(void)
{
	printf("\nUNRDLL.   This is a simple example of UNRAR.DLL usage\n");
	printf("\nSyntax:\n");
	printf("\nUNRDLL <Archive>  password1 password2 ...\n");
}


void ExtractArchive(char* ArcName, KeyWords* words, WordMap* map)
{
	int Mode = TEST;
	HANDLE hArcData;
	int RHCode, PFCode;
	wchar_t CmtBuf[16384];
	struct RARHeaderData HeaderData;
	struct RAROpenArchiveDataEx OpenArchiveData;

	memset(&HeaderData, 0, sizeof(HeaderData));
	memset(&OpenArchiveData, 0, sizeof(OpenArchiveData));

	OpenArchiveData.ArcName = ArcName;
	OpenArchiveData.CmtBufW = CmtBuf;
	OpenArchiveData.CmtBufSize = sizeof(CmtBuf) / sizeof(CmtBuf[0]);
	OpenArchiveData.OpenMode = RAR_OM_EXTRACT;
	OpenArchiveData.Callback = CallbackProc;
	OpenArchiveData.UserData = Mode;
	//    hArcData = RAROpenArchiveEx(&OpenArchiveData);


	//    ShowArcInfo(OpenArchiveData.Flags, ArcName);

		//if (OpenArchiveData.CmtState == 1)
		//    ShowComment(CmtBuf);

	for (size_t set = 0; set < 2; set++)
	{
		WordOrder order(words->number);
		PC = new PasswordCounter(words, set, map, &order);
		printf("\n");

		while (PC->NextPassword()) {
			hArcData = RAROpenArchiveEx(&OpenArchiveData);
			if (OpenArchiveData.OpenResult != 0)
			{
				OutError(OpenArchiveData.OpenResult, ArcName, ERR_OPEN);
				return;
			}
			RHCode = RARReadHeader(hArcData, &HeaderData);
			printf("\rtest: %s Number of test: %u", PC->password, PC->count);
			RARSetPassword(hArcData, PC->password);
			PFCode = RARProcessFile(hArcData, (Mode == EXTRACT) ? RAR_EXTRACT : RAR_TEST, NULL, NULL);
			if (PFCode == 0) {
				printf("\n======= !!!! ===== password: %s\nNumber of test: %u\n", PC->password, PC->count);
				password_found = true;
				set = 2; //прервать перебор сетов
				break;
			}
			RARCloseArchive(hArcData);
			/// ////////////////////
		}
		if (PFCode == 0) {
			printf(" OK");
		}
		else
		{
			//printf("\n");
			//		printf("\nPassword not found\nNumber of test: %u\n", PC->count);
	//		OutError(PFCode, ArcName, ERR_PROCESS);
		}
	}
}

void OutError(int Error, char* ArcName, int ErrType)
{
	switch (Error)
	{
	case ERAR_NO_MEMORY:
		printf("\nNot enough memory");
		break;
	case ERAR_BAD_DATA:
		printf("\n%s: archive header or data are damaged", ArcName);
		break;
	case ERAR_BAD_ARCHIVE:
		printf("\n%s is not RAR archive", ArcName);
		break;
	case ERAR_UNKNOWN_FORMAT:
		printf("Unknown archive format");
		break;
	case ERAR_EOPEN:
		if (ErrType == ERR_PROCESS) // Returned by RARProcessFile.
			printf("Volume open error");
		else
			printf("\nCannot open file: %s", ArcName);
		OutHelp();
		break;
	case ERAR_ECREATE:
		printf("File create error");
		break;
	case ERAR_ECLOSE:
		printf("File close error");
		break;
	case ERAR_EREAD:
		printf("Read error");
		break;
	case ERAR_EWRITE:
		printf("Write error");
		break;
	case ERAR_SMALL_BUF:
		printf("Buffer for archive comment is too small, comment truncated");
		break;
	case ERAR_UNKNOWN:
		printf("Unknown error");
		break;
	case ERAR_MISSING_PASSWORD:
		printf("Password for encrypted file or header is not specified");
		break;
	case ERAR_EREFERENCE:
		printf("Cannot open file source for reference record");
		break;
	case ERAR_BAD_PASSWORD:
		printf("Wrong password is specified");
		break;
	}
}


void ShowArcInfo(unsigned int Flags, char* ArcName)
{
	printf("\nArchive %s\n", ArcName);
	printf("\nVolume:\t\t%s", (Flags & 1) ? "yes" : "no");
	printf("\nComment:\t%s", (Flags & 2) ? "yes" : "no");
	printf("\nLocked:\t\t%s", (Flags & 4) ? "yes" : "no");
	printf("\nSolid:\t\t%s", (Flags & 8) ? "yes" : "no");
	printf("\nNew naming:\t%s", (Flags & 16) ? "yes" : "no");
	printf("\nRecovery:\t%s", (Flags & 64) ? "yes" : "no");
	printf("\nEncr.headers:\t%s", (Flags & 128) ? "yes" : "no");
	printf("\nFirst volume:\t%s", (Flags & 256) ? "yes" : "no or older than 3.0");
	printf("\n---------------------------\n");
}


void PrintTime(const char* Label, unsigned int Low, unsigned int High)
{
	if (Low != 0 || High != 0)
	{
		FILETIME ft;
		ft.dwLowDateTime = Low;
		ft.dwHighDateTime = High;
		SYSTEMTIME ust, st;
		FileTimeToSystemTime(&ft, &ust);
		SystemTimeToTzSpecificLocalTime(NULL, &ust, &st);
		printf("\n%s:  %u-%02u-%02u %02u:%02u:%02u,%03u", Label, st.wYear, st.wMonth,
			st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	}
}


int CALLBACK CallbackProc(UINT msg, LPARAM UserData, LPARAM P1, LPARAM P2)
{

	switch (msg)
	{
	case UCM_CHANGEVOLUMEW:
		if (P2 == RAR_VOL_ASK)
		{
			printf("\n\nVolume %S is required\nPossible options:\n", (wchar_t*)P1);
			printf("\nEnter - try again");
			printf("\n'R'   - specify a new volume name");
			printf("\n'Q'   - quit");
			printf("\nEnter your choice: ");
			switch (toupper(getchar()))
			{
			case 'Q':
				return(-1);
			case 'R':
			{
				wchar_t* eol;
				printf("\nEnter new name: ");
				fflush(stdin);

				// fgetws may fail to read non-English characters from stdin
				// in some compilers. In this case use something more
				// appropriate for Unicode input.
				fgetws((wchar_t*)P1, MAX_PATH, stdin);

				eol = wcspbrk((wchar_t*)P1, L"\r\n");
				if (eol != NULL)
					*eol = 0;
			}
			return(1);
			default:
				return(1);
			}
		}
		if (P2 == RAR_VOL_NOTIFY)
			printf("\n  ... volume %S\n", (wchar_t*)P1);
		return(1);
	case UCM_PROCESSDATA:
		if (UserData == PRINT)
		{
			fflush(stdout);
			fwrite((char*)P1, 1, P2, stdout);
			fflush(stdout);
		}
		return(1);
	case UCM_NEEDPASSWORDW:
	{
		wchar_t* eol;
		//       printf("\nPassword required: ");

			   // fgetws may fail to read non-English characters from stdin
			   // in some compilers. In this case use something more appropriate
			   // for Unicode input.
	   //        fgetws((wchar_t*)P1, (int)P2, stdin);
		wcsncpy_s(
			(wchar_t*)P1,
			PC->LenghtPassord(),
			PC->wpassword,
			_TRUNCATE
		);
		eol = wcspbrk((wchar_t*)P1, L"\r\n"); //удаляем управляющие символы, ставим конец строки
		if (eol != NULL)
			*eol = 0;
	}
	return(1);
	}
	return(0);
}

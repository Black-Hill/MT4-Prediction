// Prediction.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Prediction.h"

#include <Winhttp.h>

#pragma comment(lib, "winhttp.lib")

//52.87.65.246/getPrediction/EUR_USD/H1/computed
#define HOST				L"52.87.65.246"

wchar_t resultBuffer[4096];

// This is an example of an exported function.
PREDICTION_API int __stdcall GetPrediction(const wchar_t* username, const wchar_t* password, const wchar_t* pair, const wchar_t* timeframe)
{
    wchar_t token[256];
	wchar_t url[256];
    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    LPSTR pszOutBuffer;
    BOOL  bResults = FALSE;

    wsprintf(token, _T("token: %s:%s\r\n"), username, password);
	wsprintf(url, _T("/getPrediction/%s/%s/computed"), pair, timeframe);

    HINTERNET  hSession = NULL,
        hConnect = NULL,
        hRequest = NULL;

    hSession = WinHttpOpen(NULL,
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS, 0);

    if (hSession)
        hConnect = WinHttpConnect(hSession, HOST,
        80, 0);

    if (hConnect)
		hRequest = WinHttpOpenRequest(hConnect, L"GET", url,
        NULL, WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        0);

    if (hRequest)
        bResults = WinHttpSendRequest(hRequest,
        token,
        0, WINHTTP_NO_REQUEST_DATA, 0,
        0, 0);

    if (bResults)
        bResults = WinHttpReceiveResponse(hRequest, NULL);
    if (bResults)
    {
        do
        {
            dwSize = 0;
            if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) break;

            if (!dwSize) break;
            pszOutBuffer = new char[dwSize + 1];
            if (!pszOutBuffer) break;

            ZeroMemory(pszOutBuffer, dwSize + 1);
            if (WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded))
            {
                //lstrcpy(resultBuffer, pszOutBuffer);
                MultiByteToWideChar(CP_UTF8, 0, pszOutBuffer, dwSize + 1, resultBuffer, dwSize + 1);
            }
            delete[] pszOutBuffer;
            if (!dwDownloaded)
                break;
        } while (dwSize > 0);
    }
    else
    {
        wsprintf(resultBuffer, _T("Network error code %d (%08X)"), GetLastError(), GetLastError());
    }

    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);

    //MessageBox(NULL, resultBuffer, L"Info", MB_ICONINFORMATION);
    return _ttoi(resultBuffer);
}



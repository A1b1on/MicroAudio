#include "Audio.h"
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <functiondiscoverykeys_devpkey.h>
#include <iostream>
#include <string>
#include <atlbase.h> // ��� ������������� CComPtr

std::string ConvertLPWSTRToString(LPWSTR lpwstr)
{
    // ������ ������, ����������� ��� �������� ������������� ������
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, lpwstr, -1, NULL, 0, NULL, NULL);

    // ������� ������ ������� �������
    std::string strTo(size_needed, 0);

    // ������������ ������� ������ � �������������
    WideCharToMultiByte(CP_UTF8, 0, lpwstr, -1, &strTo[0], size_needed, NULL, NULL);

    return strTo;
}

int Audio::InputList()
{
    // ������������� COM
    CoInitialize(NULL);

    // �������� ������� ����������
    CComPtr<IMMDeviceEnumerator> pEnumerator;
    HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pEnumerator));
    if (FAILED(hr))
    {
        std::cout << "Failed to create IMMDeviceEnumerator instance." << std::endl;
        CoUninitialize();
        return -1;
    }

    // ��������� ��������� ��������������
    CComPtr<IMMDeviceCollection> pCollection;
    hr = pEnumerator->EnumAudioEndpoints(eCapture, DEVICE_STATE_ACTIVE, &pCollection);
    if (FAILED(hr))
    {
        std::cout << "Failed to enumerate audio endpoints." << std::endl;
        CoUninitialize();
        return -1;
    }

    // ��������� ���������� ���������
    UINT count;
    hr = pCollection->GetCount(&count);
    if (FAILED(hr))
    {
        std::cout << "Failed to get device count." << std::endl;
        CoUninitialize();
        return -1;
    }

    // ����� ������ ���������
    for (UINT i = 0; i < count; ++i)
    {
        CComPtr<IMMDevice> pDevice;
        hr = pCollection->Item(i, &pDevice);
        if (FAILED(hr))
        {
            std::cout << "Failed to get device at index " << i << std::endl;
            continue;
        }

        // ��������� ������� ����������
        CComPtr<IPropertyStore> pProps;
        hr = pDevice->OpenPropertyStore(STGM_READ, &pProps);
        if (FAILED(hr))
        {
            std::cout << "Failed to open property store for device at index " << i << std::endl;
            continue;
        }

        // ��������� ����� ����������
        PROPVARIANT varName;
        PropVariantInit(&varName);
        hr = pProps->GetValue(PKEY_Device_FriendlyName, &varName);
        if (FAILED(hr))
        {
            std::cout << "Failed to get device name at index " << i << std::endl;
        }
        else
        {
            std::string str = ConvertLPWSTRToString(varName.pwszVal);
            std::wcout << L"Device " << i << L": " << varName.pwszVal << std::endl;
        }
        PropVariantClear(&varName);
    }

    // ������� COM
    CoUninitialize();
}
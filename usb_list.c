#include <windows.h>
#include <setupapi.h>
#include <stdio.h>
#include <string.h>

#pragma comment(lib, "setupapi.lib")

int main() {

    HDEVINFO deviceInfoSet;
    SP_DEVINFO_DATA deviceInfoData;
    DWORD i = 0;
    int count = 0;

    deviceInfoSet = SetupDiGetClassDevs(
        NULL,
        "USB",
        NULL,
        DIGCF_ALLCLASSES | DIGCF_PRESENT
    );

    if (deviceInfoSet == INVALID_HANDLE_VALUE) {
        printf("Failed to get USB device list.\n");
        return 1;
    }

    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    printf("Listing all USB devices...\n\n");

    while (SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData)) {

        WCHAR deviceNameW[1024] = {0};
        WCHAR hardwareIdW[1024] = {0};

        char deviceName[1024] = {0};
        char hardwareId[1024] = {0};

        DWORD dataType, size;

        int isUsbDevice = 0;

        if (SetupDiGetDeviceRegistryPropertyW(
                deviceInfoSet,
                &deviceInfoData,
                SPDRP_HARDWAREID,
                &dataType,
                (PBYTE)hardwareIdW,
                sizeof(hardwareIdW),
                &size))
        {
            WideCharToMultiByte(
                CP_UTF8,
                0,
                hardwareIdW,
                -1,
                hardwareId,
                sizeof(hardwareId),
                NULL,
                NULL
            );

            if (strstr(hardwareId, "USB") != NULL)
                isUsbDevice = 1;
        }

        if (isUsbDevice) {

            count++;

            if (SetupDiGetDeviceRegistryPropertyW(
                    deviceInfoSet,
                    &deviceInfoData,
                    SPDRP_DEVICEDESC,
                    &dataType,
                    (PBYTE)deviceNameW,
                    sizeof(deviceNameW),
                    &size))
            {
                WideCharToMultiByte(
                    CP_UTF8,
                    0,
                    deviceNameW,
                    -1,
                    deviceName,
                    sizeof(deviceName),
                    NULL,
                    NULL
                );
            }
            else
            {
                strcpy(deviceName, "Unknown USB Device");
            }

            printf("Device %d\n", count);
            printf("  Name: %s\n", deviceName);
            printf("  Hardware ID: %s\n\n", hardwareId);
        }

        i++;
    }

    SetupDiDestroyDeviceInfoList(deviceInfoSet);

    printf("Total USB devices found: %d\n", count);

    return 0;
}
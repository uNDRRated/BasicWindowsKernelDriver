#include <ntddk.h> //contains windows kernel defs
#include <wdf.h> //contains definitions for drivers based on the windows driver framework

//declarations for two callbacks
DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD KmdfHelloWorldEvtDeviceAdd;

//DriverEntry

NTSTATUS DriverEntry(
	_In_ PDRIVER_OBJECT DriverObject,
	_In_ PUNICODE_STRING RegistryPath
) {
	//NTSTATUS var to record success or failure
	NTSTATUS status = STATUS_SUCCESS;

	//Allocate the driver config object
	WDF_DRIVER_CONFIG config;

	//Print HelloWorld for DriverEntry
	KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "KernelDriver: DriverEntry\n"));

	//Init the driver config object to register
	//the entry point for the EvtDeviceAdd callback, KmdfHelloWorldEvtDeviceAdd
	WDF_DRIVER_CONFIG_INIT(&config, KmdfHelloWorldEvtDeviceAdd);

	//Create the driver object;

	status = WdfDriverCreate(DriverObject, RegistryPath, WDF_NO_OBJECT_ATTRIBUTES, &config, WDF_NO_HANDLE);

	return status;
}

//DriverEntry is the entry point for all drivers, like Main is for many user mode apps. DriverEntry is to init driver-wide structs and resources. In this example, 
//DriverEntry is being printed, configured the driver object to register your EvtDeviceAdd callbacks entry point, then crated the driver object and returned.


NTSTATUS KmdfHelloWorldEvtDeviceAdd(
	_In_ WDFDRIVER Driver,
	_Inout_ PWDFDEVICE_INIT DeviceInit
) {
	//Not using driver object, so we need to mark it as unreferenced
	UNREFERENCED_PARAMETER(Driver);

	NTSTATUS status;

	//Allocate the device object
	WDFDEVICE hDevice;

	//Print text
	KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "KernelDriver: KmdfHelloWorldEvtDeviceAdd"));

	//Create the device object
	status = WdfDeviceCreate(&DeviceInit, WDF_NO_OBJECT_ATTRIBUTES, &hDevice);

	return status;
}

//EvtDeviceAdd is invoked by the system when it detects that your device has arrived. Its job is to
//initialzise structures and resources for that device. In this example, "KernelDriver: KmdfHelloWorldEvtDeviceAdd" is being printed out for EvtDeviceAdd,
//created the device object and returned it.
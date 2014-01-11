#include <stdio.h>
#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <mmsystem.h>

void set_vol_vista(double new_Volume)//для изменения громкости начиная с Vista и позднее
{
	HRESULT hr;
	//инициализация
	CoInitialize(NULL);
	IMMDeviceEnumerator *deviceEnumerator = NULL;
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
	IMMDevice *defaultDevice = NULL;

	hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	deviceEnumerator->Release();
	deviceEnumerator = NULL;

	IAudioEndpointVolume *endpointVolume = NULL;
	hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
	defaultDevice->Release();
	defaultDevice = NULL;
	hr = endpointVolume->SetMasterVolumeLevel((float)new_Volume, NULL);
	endpointVolume->Release();

	CoUninitialize();
	return;
}

void SetVolume_XP(unsigned int SetVolume)
{
	
    WAVEOUTCAPSA Woc;
    DWORD Volume ;
	HWAVEOUT tmp; 
    if(waveOutGetDevCapsA(WAVE_MAPPER, &Woc, sizeof(Woc)) ==MMSYSERR_NOERROR)
       if(Woc.dwSupport && WAVECAPS_VOLUME == WAVECAPS_VOLUME)
           waveOutSetVolume(0, SetVolume);//был вместо 0 WAVe_MAPPER, надо разобраться что это(инфы почти нет)
	return;
}

void main()
{
	double cur_volume, new_volume;
	int cur_version;
	//текущий уровень шума

	//проверка версий OC
	if(cur_version = 2)
		set_vol_vista(new_volume);
	else
		SetVolume_XP((int)new_volume);

	
		

}
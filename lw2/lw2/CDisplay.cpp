#include "CDisplay.h"

CDisplay::CDisplay(IObservable<SWeatherInfo> &data1, IObservable<SWeatherInfoPro> &data2, int priority)
	:m_data1(&data1),
	m_data2(&data2)
{
	m_data1->RegisterObserver(*this, priority);
	m_data2->RegisterObserver(*this, priority);
}

void CDisplay::Update (SWeatherInfo const& data, string str)
{
	cout << str + " Current Temp " << data.temperature << endl;
	cout << str + " Current Hum " << data.humidity << endl;
	cout << str + " Current Pressure " << data.pressure << endl;
	cout << "----------------" << endl;
}

void CDisplay::Update(SWeatherInfoPro const& data, string str)
{
	cout << str + " Current Temp " << data.temperature << endl;
	cout << str + " Current Hum " << data.humidity << endl;
	cout << str + " Current Pressure " << data.pressure << endl;
	cout << str + " Current Dir " << data.dir << endl;
	cout << str + " Current Speed " << data.speed << endl;
	cout << "----------------" << endl;
}

void CDisplay::RemoveObservers()
{
	m_data1->RemoveObserver(*this);
	m_data2->RemoveObserver(*this);
}
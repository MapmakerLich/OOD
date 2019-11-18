#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observable.h"
#include "WeatherDataPro.h"



class CDisplay : public IObserver<SWeatherInfo>, public IObserver<SWeatherInfoPro>
{
public:
	CDisplay(IObservable<SWeatherInfo> &data1, IObservable<SWeatherInfoPro> &data2, int priority);
private:
	void Update(SWeatherInfo const& data, string str) override;
	void Update(SWeatherInfoPro const& data, string str) override;

	IObservable<SWeatherInfo>* m_data1;
	IObservable<SWeatherInfoPro>* m_data2;

	void RemoveObservers();
};

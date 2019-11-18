#pragma once
#include <set>
#include <functional>
#include "Observable.h"

using namespace std;

/*
��������� ��������� IObserver. ��� ������ ������������� �����,
�������� �������� ����������� �� ���������������� IObservable
���������� ������� �������� ��� ���������,
������������� ����������� � ����� Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data, string str) = 0;
	virtual ~IObserver() = default;
};

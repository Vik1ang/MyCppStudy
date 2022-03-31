#pragma once

#define MYFOLLY_API __declspec(dllexport)

class MYFOLLY_API IInterface
{
public:
	static IInterface* CreateInterface();

	virtual void Init() = 0;
	virtual void Destroy() = 0;
	virtual char* GetName() = 0;
};



#include "pch.h"

#include <cstdio>

#include "Interface.h"

class FHello :public IInterface
{
public:
	FHello();
	virtual void Init() override;
	virtual void Destroy() override;
	virtual char* GetName() override;

private:
	char  Name[1024];
};

FHello::FHello()
{
	memset(Name, 0, 1024);
	strcpy(Name, "Hello");
}

void FHello::Init()
{
	printf("FHello::Init()");
}

void FHello::Destroy()
{
	printf("FHello::Init()");
}

char* FHello::GetName()
{
	printf("FHello::Init()");
	return Name;
}

IInterface* IInterface::CreateInterface()
{
	return new FHello();
}

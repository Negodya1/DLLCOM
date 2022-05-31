#ifndef IMANAGER2_H
#define IMANAGER2_H
#include "OBJBASE.h"
#include "IMusician2.h"
#include "IMusician.h"
HRESULT_ CreateInstance(CLSID_, IID_, void**);

class ServerNew : public IHAccordion, public IHarmony {
private:
	IAccordion* iAccordion;

	std::string note;
	std::string accord;
	std::string harmony;
    long m_cRef;
public:
    ServerNew(std::string, std::string, std::string);
	ServerNew();
    ~ServerNew();
    virtual int GetSound();
    virtual int GetAccord();
	virtual int NextAccord();
	virtual int GetHarmony();
    virtual int NextHarmony();
    HRESULT_ QueryInterface2(IID_, void**);
    ULONG_ _AddRef();
    ULONG_ _Release();
};
#endif

class NewServerFactory : public _IClassFactory2 {
private:
    long m_cRef;
public:
    NewServerFactory();
    ~NewServerFactory();
    HRESULT_ CreateInstance2(IID_, void**);
    HRESULT_ QueryInterface2(IID_, void**);
    ULONG_ _AddRef();
    ULONG_ _Release();
};

class NewMyServerFactory : public NewServerFactory {
public:
	HRESULT_ CreateInstance3(IID_, void**, std::string, std::string, std::string);
};
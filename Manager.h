#ifndef IMANAGER_H
#define IMANAGER_H
#include "OBJBASE.h"
#include "IMusician.h"
HRESULT_ CreateInstance(CLSID_, IID_, void**);

class Server2 : public IPlayer {
private:
	std::string note;
	std::string accord;
    long m_cRef;
public:
    Server2(std::string, std::string);
	Server2();
    ~Server2();
    virtual int PlaySound();
	virtual int PlayAccord();
	virtual int NextAccord();
    HRESULT_ QueryInterface(IID_, void**);
    ULONG_ _AddRef();
    ULONG_ _Release();
};

class Server : public IAccordion, public IPlayer {
private:
	std::string note;
	std::string accord;
    long m_cRef;
public:
    Server(std::string, std::string);
	Server();
    ~Server();
    virtual int GetSound();
    virtual int GetAccord();
	virtual int NextAccord();
	virtual int PlaySound();
    virtual int PlayAccord();
    HRESULT_ QueryInterface(IID_, void**);
    ULONG_ _AddRef();
    ULONG_ _Release();
};
#endif

class Server2Factory : public _IClassFactory {
private:
    long m_cRef;
public:
    Server2Factory();
    ~Server2Factory();
    HRESULT_ CreateInstance(IID_, void**);
    HRESULT_ QueryInterface(IID_, void**);
    ULONG_ _AddRef();
    ULONG_ _Release();
};

class MyServer2Factory : public Server2Factory {
public:
	HRESULT_ CreateInstance2(IID_, void**, std::string, std::string);
};

class ServerFactory : public _IClassFactory {
private:
    long m_cRef;
public:
    ServerFactory();
    ~ServerFactory();
    HRESULT_ CreateInstance(IID_, void**);
    HRESULT_ QueryInterface(IID_, void**);
    ULONG_ _AddRef();
    ULONG_ _Release();
};

class MyServerFactory : public ServerFactory {
public:
	HRESULT_ CreateInstance2(IID_, void**, std::string, std::string);
};
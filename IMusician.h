#ifndef IUNKNOWN_H
#define IUNKNOWN_H
#include "OBJBASE.h"
class IMusician {
public:
    virtual HRESULT_ QueryInterface(IID_, void**) = 0;
    virtual ULONG_ _AddRef() = 0;
    virtual ULONG_ _Release() = 0;
};

class IAccordion : public IMusician {
public:
    virtual int GetSound() = 0;
	virtual int GetAccord() = 0;
	virtual int NextAccord() = 0;
};

class IPlayer : public IMusician {
public:
    virtual int PlaySound() = 0;
	virtual int PlayAccord() = 0;
	virtual int NextAccord() = 0;
};

class _IClassFactory : public IMusician {
public:
    virtual HRESULT_ CreateInstance(IID_, void**) = 0;
};
#endif
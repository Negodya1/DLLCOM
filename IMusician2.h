#ifndef IUNKNOWN2_H
#define IUNKNOWN2_H
#include "OBJBASE.h"
class IMusician2 {
public:
    virtual HRESULT_ QueryInterface2(IID_, void**) = 0;
    virtual ULONG_ _AddRef() = 0;
    virtual ULONG_ _Release() = 0;
};

class IHAccordion : public IMusician2 {
public:
    virtual int GetSound() = 0;
	virtual int GetAccord() = 0;
	virtual int NextAccord() = 0;
};

class IHarmony : public IMusician2 {
public:
    virtual int GetHarmony() = 0;
	virtual int NextHarmony() = 0;
	virtual int NextAccord() = 0;
};

class _IClassFactory2 : public IMusician2 {
public:
    virtual HRESULT_ CreateInstance2(IID_, void**) = 0;
};
#endif
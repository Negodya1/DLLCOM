#include <windows.h>
#include <fstream>
#include <iostream>
#include "Manager2.h"
#include "Manager.h"
#include "OBJBASE.h"

TCHAR path[MAX_PATH];
long global_m_cRef;

typedef HRESULT_ (*FunctionType) (CLSID_, IID_, void**);

HRESULT_ CreateInstance2(CLSID_ CLSID, IID_ IID, void** ppv) {
    IMusician2* pIUnknown = NULL;
    switch (CLSID) {
		case CLSID_SERVERNEW:
			pIUnknown = (IHAccordion*) new ServerNew;
			std::cout << "Global.CreateInstance: ServerNew connected." << std::endl;
			break;
		default:
			std::cout << "Global.CreateInstance: connection error." << std::endl;
			return S_FAIL;
			break;
    }
    pIUnknown->_AddRef();
    return pIUnknown->QueryInterface2(IID, ppv);
}

ServerNew::ServerNew(std::string _note, std::string _accord, std::string _harmony) {
	FunctionType f;
	HINSTANCE h;

    h=LoadLibrary("out/Manager.dll");
	if (!h) {
           std::cout << "No dll!!!" << std::endl;
    }
	
	f = (FunctionType) GetProcAddress(h,"GetClassObject");
    if (!f) {
          std::cout << "No dll function" << std::endl;
    }
	
    _IClassFactory* pF = NULL;
    HRESULT_ result = f(CLSID_SERVER, IID_ICLASSFACTORY, (void**)&pF);
	
    if (result == S__OK) {
        IAccordion* pX = NULL;
        result = pF->CreateInstance(IID_IACCORDION, (void**)&pX);
		
        if (result == S__OK) {
            iAccordion = pX;
        }
    }
    else std::cout << "Warning3" << std::endl;
	
	pF->_Release();
	
	note = _note;
	accord = _accord;
	harmony = _harmony;
    m_cRef = 0;
};
ServerNew::ServerNew() {
	FunctionType f;
	HINSTANCE h;

    h=LoadLibrary("out/Manager.dll");
	if (!h) {
           std::cout << "No dll!!!" << std::endl;
    }
	
	f = (FunctionType) GetProcAddress(h,"GetClassObject");
    if (!f) {
          std::cout << "No dll function" << std::endl;
    }
	
    _IClassFactory* pF = NULL;
    HRESULT_ result = f(CLSID_SERVER, IID_ICLASSFACTORY, (void**)&pF);
	
    if (result == S__OK) {
        IAccordion* pX = NULL;
        result = pF->CreateInstance(IID_IACCORDION, (void**)&pX);
		
        if (result == S__OK) {
            iAccordion = pX;
        }
    }
    else std::cout << "Warning3" << std::endl;
	
	pF->_Release();
	
	note = "A";
	accord = "m";
	harmony = "default";
    m_cRef = 0;
};

ServerNew::~ServerNew() {
    std::cout << "Server.Destructor: Liquidated." << std::endl;
};

int ServerNew::GetSound() {
    return iAccordion->GetSound();
}

int ServerNew::GetAccord() {
    return iAccordion->GetAccord();
}

int ServerNew::NextAccord() {
    return iAccordion->NextAccord();
}

int ServerNew::GetHarmony() {
    return 21;
}

int ServerNew::NextHarmony() {
    return 22;
}

HRESULT_ ServerNew::QueryInterface2(IID_ IID, void** ppv) {
    switch (IID) {
    case IID_IMUSICIAN:
        *ppv = (IMusician2*)(IHAccordion*)ppv;
        std::cout << "Server.QueryInterface: IUnknown connected." << std::endl;
        break;
    case IID_IACCORDION:
        *ppv = (IHAccordion*)this;
        std::cout << "Server.QueryInterface: IX connected." << std::endl;
        break;
    case IID_IHARMONY:
        *ppv = (IHarmony*)this;
        std::cout << "Server.QueryInterface: IY connected." << std::endl;
        break;
    default:
        *ppv = NULL;
        std::cout << "Server.QueryInterface: Invalid interface" << std::endl;
        return S_FAIL;
    }
    reinterpret_cast<IMusician2*>(*ppv)->_AddRef();
    return S__OK;
}

ULONG_ ServerNew::_AddRef() { 
    std::cout << "Server.AddRef = " << m_cRef + 1 << std::endl;
    return ++m_cRef; 
} 
 
ULONG_ ServerNew::_Release() { 
    std::cout << "Server.Release = " << m_cRef - 1 << std::endl;
    if(--m_cRef == 0) {
        delete this;
        return 0;
    }
    return m_cRef;
}

NewServerFactory::NewServerFactory() {
    m_cRef = 0;
};
NewServerFactory::~NewServerFactory() {
    std::cout << "ServerFactory.Destructor: Liquidated." << std::endl;
};

HRESULT_ NewServerFactory::CreateInstance2(IID_ IID, void** ppv) {
    ServerNew* server = new ServerNew;
    std::cout << "Server.CreateInstance: Server connected." << std::endl;
    return server->QueryInterface2(IID, ppv);
};

HRESULT_ NewServerFactory::QueryInterface2(IID_ IID, void** ppv) {
    switch (IID) {
    case IID_ICLASSFACTORY:
        std::cout << "ServerFactory.QueryInterface: IClassFactory connected." << std::endl;
        *ppv = (_IClassFactory2*)this;
        break;
    default:
        std::cout << "ServerFactory.QueryInterface: Invalid interface" << std::endl;
        *ppv = NULL;
        return S_FAIL;
    }
    reinterpret_cast<IMusician2*>(*ppv)->_AddRef();
    return S__OK;
};

ULONG_ NewServerFactory::_AddRef() { 
    std::cout << "ServerFactory.AddRef = " << m_cRef + 1 << std::endl;
    return ++m_cRef; 
} 
 
ULONG_ NewServerFactory::_Release() { 
    std::cout << "ServerFactory.Release = " << m_cRef - 1 << std::endl;
    if(--m_cRef == 0) {
        delete this;
        return 0;
    }
    return m_cRef;
}

HRESULT_ NewMyServerFactory::CreateInstance3(IID_ IID, void** ppv, std::string note, std::string accord = "m", std::string harmony = "default") {
    ServerNew* server = new ServerNew;
    std::cout << "Server.CreateInstance: Server connected." << std::endl;
    server->_AddRef();
    return server->QueryInterface2(IID, ppv);
};

extern "C" HRESULT_ __declspec(dllexport) DLLGetClassObject(CLSID_ CLSID, IID_ IID, void** ppv) {
    IMusician2* pIUnknown = NULL;
    switch (CLSID) {
		case CLSID_SERVERNEW:
			pIUnknown = (_IClassFactory2*) new NewServerFactory;
			std::cout << "GetClassObject: ServerFactory connected." << std::endl;
			break;
		default:
			std::cout << "GetClassObject: connection error." << std::endl;
			return S_FAIL;
			break;
    }
    pIUnknown->_AddRef();
    return pIUnknown->QueryInterface2(IID, ppv);
}

extern "C"  HRESULT_ __declspec(dllexport) DllRegisterServer(void) {
    std::string str_cls_id = std::to_string(CLSID_SERVERNEW);
    std::string temp;
    std::ifstream f1("C:/Users/maksim/Desktop/COMDLL2/reg.txt");
    if (!f1) return S_FAIL;
	
    while (f1 >> temp) {
        if (temp == str_cls_id) {
            f1.close();
            return S__OK;
        }
    }
    f1.close();
	
    std::ofstream f2("C:/Users/maksim/Desktop/COMDLL2/reg.txt", std::ios::app);
    f2 << CLSID_SERVER << " " << path << std::endl;
    f2.close();
    return S__OK;
}

extern "C"  HRESULT_ __declspec(dllexport) DllUnregisterServer() {
    std::string temp;
    std::string str_cls_id = std::to_string(CLSID_SERVERNEW);
	
    std::ifstream f1("C:/Users/maksim/Desktop/COMDLL2/reg.txt");
    if (!f1) return S_FAIL;
	
    std::ofstream f2("C:/Users/maksim/Desktop/COMDLL2/regTemp.txt");
    if (!f2) return S_FAIL;
	
    while (std::getline(f1, temp)) {
        if (temp == str_cls_id + " " + path) continue;
        else f2 << temp << std::endl;
    }
    f1.close();
    f2.close();
	
    std::ofstream f3("C:/Users/maksim/Desktop/COMDLL2/reg.txt");
    if (!f3) return S_FAIL;
	
    std::ifstream f4("C:/Users/maksim/Desktop/COMDLL2/regTemp.txt");
    if (!f4) return S_FAIL;
    while (std::getline(f4, temp)) f3 << temp << std::endl;
    f3.close();
    f4.close();
}

extern "C" HRESULT_ __declspec(dllexport) _DllCanUnloadNow() {
    if(global_m_cRef == 0) return S__OK;
    else return S_FAIL;
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
			GetModuleFileName(hinstDLL, path, MAX_PATH);
			global_m_cRef = 0;
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
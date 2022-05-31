#include <windows.h>
#include <fstream>
#include <iostream>
#include "Manager.h"
#include "OBJBASE.h"

TCHAR path[MAX_PATH];
long global_m_cRef;

HRESULT_ CreateInstance(CLSID_ CLSID, IID_ IID, void** ppv) {
    IMusician* pIUnknown = NULL;
    switch (CLSID) {
		case CLSID_SERVER:
			pIUnknown = (IAccordion*) new Server;
			std::cout << "Global.CreateInstance: Server connected." << std::endl;
			break;
		case CLSID_SERVER2:
			pIUnknown = (IPlayer*) new Server2;
			std::cout << "Global.CreateInstance: Server2 connected." << std::endl;
			break;
		default:
			std::cout << "Global.CreateInstance: connection error." << std::endl;
			return S_FAIL;
			break;
    }
    pIUnknown->_AddRef();
    return pIUnknown->QueryInterface(IID, ppv);
}

Server::Server(std::string _note, std::string _accord) {
	note = _note;
	accord = _accord;
    m_cRef = 0;
};
Server::Server() {
	note = "A";
	accord = "m";
    m_cRef = 0;
};

Server::~Server() {
    std::cout << "Server.Destructor: Liquidated." << std::endl;
};

int Server::GetSound() {
    return 11;
}

int Server::GetAccord() {
    return 12;
}

int Server::NextAccord() {
    return 13;
}

int Server::PlaySound() {
    return 21;
}

int Server::PlayAccord() {
    return 22;
}

HRESULT_ Server::QueryInterface(IID_ IID, void** ppv) {
    switch (IID) {
    case IID_IMUSICIAN:
        *ppv = (IMusician*)(IAccordion*)ppv;
        std::cout << "Server.QueryInterface: IUnknown connected." << std::endl;
        break;
    case IID_IACCORDION:
        *ppv = (IAccordion*)this;
        std::cout << "Server.QueryInterface: IX connected." << std::endl;
        break;
    case IID_IPLAYER:
        *ppv = (IPlayer*)this;
        std::cout << "Server.QueryInterface: IY connected." << std::endl;
        break;
    default:
        *ppv = NULL;
        std::cout << "Server.QueryInterface: Invalid interface" << std::endl;
        return S_FAIL;
    }
    reinterpret_cast<IMusician*>(*ppv)->_AddRef();
    return S__OK;
}

ULONG_ Server::_AddRef() { 
    std::cout << "Server.AddRef = " << m_cRef + 1 << std::endl;
    return ++m_cRef; 
} 
 
ULONG_ Server::_Release() { 
    std::cout << "Server.Release = " << m_cRef - 1 << std::endl;
    if(--m_cRef == 0) {
        delete this;
        return 0;
    }
    return m_cRef;
}

ServerFactory::ServerFactory() {
    m_cRef = 0;
};
ServerFactory::~ServerFactory() {
    std::cout << "ServerFactory.Destructor: Liquidated." << std::endl;
};

HRESULT_ ServerFactory::CreateInstance(IID_ IID, void** ppv) {
    Server* server = new Server;
    std::cout << "Server.CreateInstance: Server connected." << std::endl;
    return server->QueryInterface(IID, ppv);
};

HRESULT_ ServerFactory::QueryInterface(IID_ IID, void** ppv) {
    switch (IID) {
    case IID_ICLASSFACTORY:
        std::cout << "ServerFactory.QueryInterface: IClassFactory connected." << std::endl;
        *ppv = (IClassFactory*)this;
        break;
    default:
        std::cout << "ServerFactory.QueryInterface: Invalid interface" << std::endl;
        *ppv = NULL;
        return S_FAIL;
    }
    reinterpret_cast<IMusician*>(*ppv)->_AddRef();
    return S__OK;
};

ULONG_ ServerFactory::_AddRef() { 
    std::cout << "ServerFactory.AddRef = " << m_cRef + 1 << std::endl;
    return ++m_cRef; 
} 
 
ULONG_ ServerFactory::_Release() { 
    std::cout << "ServerFactory.Release = " << m_cRef - 1 << std::endl;
    if(--m_cRef == 0) {
        delete this;
        return 0;
    }
    return m_cRef;
}

HRESULT_ MyServerFactory::CreateInstance2(IID_ IID, void** ppv, std::string note, std::string accord = "m") {
    Server* server = new Server;
    std::cout << "Server.CreateInstance: Server connected." << std::endl;
    server->_AddRef();
    return server->QueryInterface(IID, ppv);
};

Server2::Server2(std::string _note, std::string _accord) {
	note = _note;
	accord = _accord;
    m_cRef = 0;
};
Server2::Server2() {
	note = "A";
	accord = "m";
    m_cRef = 0;
};
Server2::~Server2() {
    std::cout << "Server2.Destructor: Liquidated." << std::endl;
};

int Server2::PlaySound() {
    return 21;
}

int Server2::PlayAccord() {
    return 22;
}

int Server2::NextAccord() {
    return 13;
}

HRESULT_ Server2::QueryInterface(IID_ IID, void** ppv) {
    switch (IID) {
    case IID_IMUSICIAN:
        *ppv = (IMusician*)(IPlayer*)ppv;
        std::cout << "Server2.QueryInterface: IUnknown connected." << std::endl;
        break;
    case IID_IPLAYER:
        *ppv = (IPlayer*)this;
        std::cout << "Server2.QueryInterface: IY connected." << std::endl;
        break;
    default:
        *ppv = NULL;
        std::cout << "Server2.QueryInterface: Invalid interface" << std::endl;
        return S_FAIL;
    }
    return S__OK;
}

ULONG_ Server2::_AddRef() {
    std::cout << "Server2.AddRef = " << m_cRef + 1 << std::endl;
    return ++m_cRef; 
} 
 
ULONG_ Server2::_Release() { 
    std::cout << "Server2.Release = " << m_cRef - 1 << std::endl;
    if(--m_cRef == 0)
    {
        delete this;
        return 0;
    }
    return m_cRef;
}


Server2Factory::Server2Factory() {
    m_cRef = 0;
};
Server2Factory::~Server2Factory() {
    std::cout << "Server2Factory.Destructor: Liquidated." << std::endl;
};

HRESULT_ Server2Factory::CreateInstance(IID_ IID, void** ppv) {
    Server2* server2 = new Server2;
    std::cout << "Server2.CreateInstance: Server2 connected." << std::endl;
    return server2->QueryInterface(IID, ppv);
};

HRESULT_ Server2Factory::QueryInterface(IID_ IID, void** ppv) {
    switch (IID) {
		case IID_ICLASSFACTORY:
			std::cout << "Server2Factory.QueryInterface: IClassFactory connected." << std::endl;
			*ppv = (IClassFactory*)this;
			break;
		default:
			std::cout << "Server2Factory.QueryInterface: Invalid interface" << std::endl;
			*ppv = NULL;
			return S_FAIL;
    }
    return S__OK;
}

ULONG_ Server2Factory::_AddRef() { 
    std::cout << "Server2Factory.AddRef = " << m_cRef + 1 << std::endl;
    return ++m_cRef; 
} 
 
ULONG_ Server2Factory::_Release() { 
    std::cout << "Server2Factory.Release = " << m_cRef - 1 << std::endl;
    if(--m_cRef == 0) {
        delete this;
        return 0;
    }
    return m_cRef;
}

HRESULT_ MyServer2Factory::CreateInstance2(IID_ IID, void** ppv, std::string note, std::string accord = "m") {
    Server2* server2 = new Server2;
    std::cout << "Server2.CreateInstance: Server2 connected." << std::endl;
    return server2->QueryInterface(IID, ppv);
};

extern "C" HRESULT_ __declspec(dllexport) DLLGetClassObject(CLSID_ CLSID, IID_ IID, void** ppv) {
    IMusician* pIUnknown = NULL;
    switch (CLSID) {
		case CLSID_SERVER:
			pIUnknown = (_IClassFactory*) new ServerFactory;
			std::cout << "GetClassObject: ServerFactory connected." << std::endl;
			break;
		case CLSID_SERVER2:
			pIUnknown = (_IClassFactory*) new Server2Factory;
			std::cout << "GetClassObject: Server2Factory connected." << std::endl;
			break;
		default:
			std::cout << "GetClassObject: connection error." << std::endl;
			return S_FAIL;
			break;
    }
    pIUnknown->_AddRef();
    return pIUnknown->QueryInterface(IID, ppv);
}

extern "C"  HRESULT_ __declspec(dllexport) DllRegisterServer(void) {
    std::string str_cls_id = std::to_string(CLSID_SERVER);
    std::string temp;
    std::ifstream f1("C:/Users/maksim/Desktop/COMDLL/reg.txt");
    if (!f1) return S_FAIL;
	
    while (f1 >> temp) {
        if (temp == str_cls_id) {
            f1.close();
            return S__OK;
        }
    }
    f1.close();
	
    std::ofstream f2("C:/Users/maksim/Desktop/COMDLL/reg.txt", std::ios::app);
    f2 << CLSID_SERVER << " " << path << std::endl;
    f2.close();
    return S__OK;
}

extern "C"  HRESULT_ __declspec(dllexport) DllUnregisterServer() {
    std::string temp;
    std::string str_cls_id = std::to_string(CLSID_SERVER);
	
    std::ifstream f1("C:/Users/maksim/Desktop/COMDLL/reg.txt");
    if (!f1) return S_FAIL;
	
    std::ofstream f2("C:/Users/maksim/Desktop/COMDLL/regTemp.txt");
    if (!f2) return S_FAIL;
	
    while (std::getline(f1, temp)) {
        if (temp == str_cls_id + " " + path) continue;
        else f2 << temp << std::endl;
    }
    f1.close();
    f2.close();
	
    std::ofstream f3("C:/Users/maksim/Desktop/COMDLL/reg.txt");
    if (!f3) return S_FAIL;
	
    std::ifstream f4("C:/Users/maksim/Desktop/COMDLL/regTemp.txt");
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
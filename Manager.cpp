#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "Manager.h"
#include "OBJBASE.h"

typedef HRESULT_ (*FunctionType) (CLSID_, IID_, void**);
typedef HRESULT_ (*FunctionType2) ();

HINSTANCE hinstLib;
std::vector<HINSTANCE> libs;

extern "C" HRESULT_ __declspec(dllexport) GetClassObject(CLSID_ CLSID, IID_ IID, void** ppv) {
	FunctionType f;
    HINSTANCE h;

	std::string temp;
    std::string str_cls_id = std::to_string(CLSID);
    char path[MAX_PATH] = {};
    std::ifstream file("C:/Users/maksim/Desktop/COMDLL2/reg.txt");
    while(file >> temp) {
        if (temp == str_cls_id) {
            file >> path;
            break;
        }
    }
    file.close();
	std::cout << path << std::endl;
    h=LoadLibrary(path);
	if (!h) {
           std::cout << "Manager: No dll!" << std::endl;
           return 0;
    }
	
	f = (FunctionType) GetProcAddress(h,"DLLGetClassObject");
    if (!f) {
          std::cout << "No dll function" << std::endl;
          return 0;
    }
	
    return f(CLSID, IID, ppv);
}

extern "C" HRESULT_ __declspec(dllexport) _FreeLibrary() {
    FunctionType2 _DllCanUnloadNow;
    HRESULT_ result;
    for (int i = 0; i < libs.size(); i++) {
        _DllCanUnloadNow = (FunctionType2) GetProcAddress(libs[i], "_DllCanUnloadNow");
        if (_DllCanUnloadNow) {
            result = _DllCanUnloadNow();
            if (result == S__OK) {
                FreeLibrary(libs[i]);
                libs.erase(libs.begin() + i);
                libs.resize(libs.size() - 1);
            }
        }
    }
    return result;
}
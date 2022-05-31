#include <windows.h>
#include <iostream>
#include "Manager2.h"
#include "OBJBASE.h"

typedef HRESULT_ (*FunctionType) (CLSID_, IID_, void**);

int main() {
	FunctionType f;
    HINSTANCE h;

    h=LoadLibrary("out/Manager2.dll");
	if (!h) {
           std::cout << "No dll!!!" << std::endl;
           return 0;
    }
	
	f = (FunctionType) GetProcAddress(h,"GetClassObject");
    if (!f) {
          std::cout << "No dll function" << std::endl;
          return 0;
    }
	
    _IClassFactory2* pF = NULL;
    HRESULT_ result = f(CLSID_SERVERNEW, IID_ICLASSFACTORY, (void**)&pF);
	
    if (result == S__OK) {
        IHAccordion* pX = NULL;
        result = pF->CreateInstance2(IID_IACCORDION, (void**)&pX);
		
        if (result == S__OK) {
            std::cout << "Func result: " << pX->GetSound() << std::endl;
        }
        else std::cout << "Warning1" << std::endl;
        
		IHarmony* pY = NULL;
		result = pX->QueryInterface2(IID_IHARMONY, (void**)&pY);
		
        if (result == S__OK) {
            std::cout << "Func result: " << pY->GetHarmony() << std::endl;
            pX->_Release();
        }
        else std::cout << "Warning2" << std::endl;
        pX->_Release();
    }
    else std::cout << "Warning3" << std::endl;
	
	pF->_Release();
	
    return 0;
}
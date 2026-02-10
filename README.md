# dxc-in-c
C bindings for [DirectX Shader Compiler][] (DXC).

The bindings target DXC version **1.8.2505.32**. Microsoft guarantees that COM interfaces use stable IIDs and CLSIDs across versions, meaning that the bindings remain compatible with newer DXC versions. Newer versions may
introduce additional interfaces and types that may not be exposed by these bindings.

## Requirements
This repository only contains the `dxc_c.h` header file. You must provide the DXC binaries yourself. See official [DXC releases][].
## Usage
```c
#include <Windows.h>
#include <initguid.h> // NOTE: Required for IIDs and CLSIDs
#include "dxc_c.h"

int main(void) {
    IDxcUtils*     dxc_utils;
    IDxcCompiler3* dxc_compiler;

    HMODULE dxc_dll = LoadLibrary(L"dxcompiler.dll");
    DxcCreateInstanceProc DxcCreateInstance = (DxcCreateInstanceProc)GetProcAddress(dxc_dll, "DxcCreateInstance");
    DxcCreateInstance(&CLSID_DxcUtils, &IID_IDxcUtils, &dxc_utils);
    DxcCreateInstance(&CLSID_DxcCompiler, &IID_IDxcCompiler3, &dxc_compiler);

    ...

    IDxcResult* result;
    HRESULT hr = IDxcCompiler3_Compile(..., &IID_IDxcResult, &result);

    if (FAILED(hr)) {
        IDxcBlobUtf8* errors;
        IDxcResult_GetOutput(result, DXC_OUT_ERRORS, &IID_IDxcBlobUtf8, &errors, NULL);
        OutputDebugStringA(IDxcBlobUtf8_GetStringPointer(errors));
    }

    IDxcResult_Release(result);
    IDxcCompiler3_Release(dxc_compiler);
    IDxcUtils_Release(dxc_utils);

    return 0;
}
```

[DirectX Shader Compiler]: https://github.com/microsoft/DirectXShaderCompiler
[DXC releases]: https://github.com/microsoft/DirectXShaderCompiler/releases

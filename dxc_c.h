///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// dxc_c.h                                                                   //
// C bindings for the DirectX Shader Compiler (DXC)                          //
//                                                                           //
// Copyright (c) 2026 Jack Henrikson                                         //
//                                                                           //
// This file is licensed under the MIT License.                              //
// See the LICENSE file for details.                                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#ifndef __DXC_API_C__
#define __DXC_API_C__

#ifdef _WIN32
    #ifndef DXC_API_IMPORT
        #define DXC_API_IMPORT __declspec(dllimport)
    #endif
#else
    #ifndef DXC_API_IMPORT
        #define DXC_API_IMPORT __attribute__((visibility("default")))
    #endif
#endif

#ifndef CROSS_PLATFORM_UUIDOF
    #ifdef _WIN32
        #define CROSS_PLATFORM_UUIDOF(interface, spec) struct __declspec(uuid(spec)) interface;
    #else
        #define CROSS_PLATFORM_UUIDOF(interface, spec)
    #endif
#endif

#define COM_CALL(obj, idx, fn_type, ...) ((fn_type)(obj)->v->tbl[idx])(__VA_ARGS__)

#define DXC_CP_UTF8  65001
#define DXC_CP_UTF16 1200
#define DXC_CP_UTF32 12000
#define DXC_CP_ACP   0
#ifdef _WIN32
    #define DXC_CP_WIDE DXC_CP_UTF16
#else
    #define DXC_CP_WIDE DXC_CP_UTF32
#endif

#define DXC_HASHFLAG_INCLUDES_SOURCE 1

#define DXC_FOURCC(ch0, ch1, ch2, ch3) \
    ((UINT32)(UINT8)(ch0) | (UINT32)(UINT8)(ch1) << 8 | \
     (UINT32)(UINT8)(ch2) << 16 | (UINT32)(UINT8)(ch3) << 24)
#define DXC_PART_PDB                      DXC_FOURCC('I', 'L', 'D', 'B')
#define DXC_PART_PDB_NAME                 DXC_FOURCC('I', 'L', 'D', 'N')
#define DXC_PART_PRIVATE_DATA             DXC_FOURCC('P', 'R', 'I', 'V')
#define DXC_PART_ROOT_SIGNATURE           DXC_FOURCC('R', 'T', 'S', '0')
#define DXC_PART_DXIL                     DXC_FOURCC('D', 'X', 'I', 'L')
#define DXC_PART_REFLECTION_DATA          DXC_FOURCC('S', 'T', 'A', 'T')
#define DXC_PART_SHADER_HASH              DXC_FOURCC('H', 'A', 'S', 'H')
#define DXC_PART_INPUT_SIGNATURE          DXC_FOURCC('I', 'S', 'G', '1')
#define DXC_PART_OUTPUT_SIGNATURE         DXC_FOURCC('O', 'S', 'G', '1')
#define DXC_PART_PATCH_CONSTANT_SIGNATURE DXC_FOURCC('P', 'S', 'G', '1')

#define DXC_ARG_DEBUG                          L"-Zi"
#define DXC_ARG_SKIP_VALIDATION                L"-Vd"
#define DXC_ARG_SKIP_OPTIMIZATIONS             L"-Od"
#define DXC_ARG_PACK_MATRIX_ROW_MAJOR          L"-Zpr"
#define DXC_ARG_PACK_MATRIX_COLUMN_MAJOR       L"-Zpc"
#define DXC_ARG_AVOID_FLOW_CONTROL             L"-Gfa"
#define DXC_ARG_PREFER_FLOW_CONTROL            L"-Gfp"
#define DXC_ARG_ENABLE_STRICTNESS              L"-Ges"
#define DXC_ARG_ENABLE_BACKWARDS_COMPATIBILITY L"-Gec"
#define DXC_ARG_IEEE_STRICTNESS                L"-Gis"
#define DXC_ARG_OPTIMIZATION_LEVEL0            L"-O0"
#define DXC_ARG_OPTIMIZATION_LEVEL1            L"-O1"
#define DXC_ARG_OPTIMIZATION_LEVEL2            L"-O2"
#define DXC_ARG_OPTIMIZATION_LEVEL3            L"-O3"
#define DXC_ARG_WARNINGS_ARE_ERRORS            L"-WX"
#define DXC_ARG_RESOURCES_MAY_ALIAS            L"-res_may_alias"
#define DXC_ARG_ALL_RESOURCES_BOUND            L"-all_resources_bound"
#define DXC_ARG_DEBUG_NAME_FOR_SOURCE          L"-Zss"
#define DXC_ARG_DEBUG_NAME_FOR_BINARY          L"-Zsb"

#define DxcValidatorFlags_Default           0
#define DxcValidatorFlags_InPlaceEdit       1
#define DxcValidatorFlags_RootSignatureOnly 2
#define DxcValidatorFlags_ModuleOnly        4
#define DxcValidatorFlags_ValidMask         0x7
#define DxcVersionInfoFlags_None     0
#define DxcVersionInfoFlags_Debug    1
#define DxcVersionInfoFlags_Internal 2

#define DXC_EXTRA_OUTPUT_NAME_STDOUT L"*stdout*"
#define DXC_EXTRA_OUTPUT_NAME_STDERR L"*stderr*"

// --- Enums ------------------------------------------------------------------
typedef enum DXC_OUT_KIND {
    DXC_OUT_NONE           = 0,
    DXC_OUT_OBJECT         = 1,
    DXC_OUT_ERRORS         = 2,
    DXC_OUT_PDB            = 3,
    DXC_OUT_SHADER_HASH    = 4,
    DXC_OUT_DISASSEMBLY    = 5,
    DXC_OUT_HLSL           = 6,
    DXC_OUT_TEXT           = 7,
    DXC_OUT_REFLECTION     = 8,
    DXC_OUT_ROOT_SIGNATURE = 9,
    DXC_OUT_EXTRA_OUTPUTS  = 10,
    DXC_OUT_REMARKS        = 11,
    DXC_OUT_TIME_REPORT    = 12,
    DXC_OUT_TIME_TRACE     = 13,
    DXC_OUT_LAST           = DXC_OUT_TIME_TRACE,
    DXC_OUT_NUM_ENUMS,
    DXC_OUT_FORCE_DWORD    = 0xFFFFFFFF
} DXC_OUT_KIND;

// --- Structs ----------------------------------------------------------------
typedef struct DxcShaderHash { UINT32 Flags; BYTE HashDigest[16]; } DxcShaderHash;
typedef struct DxcBuffer { LPCVOID Ptr; SIZE_T Size; UINT Encoding; } DxcBuffer;
typedef DxcBuffer DxcText;
typedef struct DxcDefine { LPCWSTR Name; LPCWSTR Value; } DxcDefine;
typedef struct DxcArgPair { const WCHAR *pName; const WCHAR *pValue; } DxcArgPair;

// --- Interfaces -------------------------------------------------------------
typedef struct IDxcBlob                { struct { void *tbl[]; } *v; } IDxcBlob;
typedef struct IDxcBlobEncoding        { struct { void *tbl[]; } *v; } IDxcBlobEncoding;
typedef struct IDxcBlobWide            { struct { void *tbl[]; } *v; } IDxcBlobWide;
typedef struct IDxcBlobUtf8            { struct { void *tbl[]; } *v; } IDxcBlobUtf8;
typedef struct IDxcIncludeHandler      { struct { void *tbl[]; } *v; } IDxcIncludeHandler;
typedef struct IDxcCompilerArgs        { struct { void *tbl[]; } *v; } IDxcCompilerArgs;
typedef struct IDxcLibrary             { struct { void *tbl[]; } *v; } IDxcLibrary;
typedef struct IDxcOperationResult     { struct { void *tbl[]; } *v; } IDxcOperationResult;
typedef struct IDxcCompiler            { struct { void *tbl[]; } *v; } IDxcCompiler;
typedef struct IDxcCompiler2           { struct { void *tbl[]; } *v; } IDxcCompiler2;
typedef struct IDxcCompiler3           { struct { void *tbl[]; } *v; } IDxcCompiler3;
typedef struct IDxcLinker              { struct { void *tbl[]; } *v; } IDxcLinker;
typedef struct IDxcUtils               { struct { void *tbl[]; } *v; } IDxcUtils;
typedef struct IDxcResult              { struct { void *tbl[]; } *v; } IDxcResult;
typedef struct IDxcExtraOutputs        { struct { void *tbl[]; } *v; } IDxcExtraOutputs;
typedef struct IDxcValidator           { struct { void *tbl[]; } *v; } IDxcValidator;
typedef struct IDxcValidator2          { struct { void *tbl[]; } *v; } IDxcValidator2;
typedef struct IDxcContainerBuilder    { struct { void *tbl[]; } *v; } IDxcContainerBuilder;
typedef struct IDxcAssembler           { struct { void *tbl[]; } *v; } IDxcAssembler;
typedef struct IDxcContainerReflection { struct { void *tbl[]; } *v; } IDxcContainerReflection;
typedef struct IDxcOptimizerPass       { struct { void *tbl[]; } *v; } IDxcOptimizerPass;
typedef struct IDxcOptimizer           { struct { void *tbl[]; } *v; } IDxcOptimizer;
typedef struct IDxcVersionInfo         { struct { void *tbl[]; } *v; } IDxcVersionInfo;
typedef struct IDxcVersionInfo2        { struct { void *tbl[]; } *v; } IDxcVersionInfo2;
typedef struct IDxcVersionInfo3        { struct { void *tbl[]; } *v; } IDxcVersionInfo3;
typedef struct IDxcPdbUtils            { struct { void *tbl[]; } *v; } IDxcPdbUtils;
typedef struct IDxcPdbUtils2           { struct { void *tbl[]; } *v; } IDxcPdbUtils2;
#ifdef _WIN32
typedef IDxcBlobWide IDxcBlobUtf16;
#endif

// --- Typedefs ---------------------------------------------------------------
typedef HRESULT(__stdcall *DxcCreateInstanceProc)(REFCLSID rclsid, REFIID riid, LPVOID *ppv);
typedef HRESULT(__stdcall *DxcCreateInstance2Proc)(IMalloc *pMalloc, REFCLSID rclsid, REFIID riid, LPVOID *ppv);

// --- Methods ----------------------------------------------------------------
static inline HRESULT IDxcBlob_QueryInterface(IDxcBlob *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcBlob*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcBlob_AddRef(IDxcBlob *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcBlob*), self); }
static inline ULONG   IDxcBlob_Release(IDxcBlob *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcBlob*), self); }
static inline LPVOID  IDxcBlob_GetBufferPointer(IDxcBlob *self) { return COM_CALL(self, 3, LPVOID(__stdcall*)(IDxcBlob*), self); }
static inline SIZE_T  IDxcBlob_GetBufferSize(IDxcBlob *self) { return COM_CALL(self, 4, SIZE_T(__stdcall*)(IDxcBlob*), self); }

static inline HRESULT IDxcBlobEncoding_QueryInterface(IDxcBlobEncoding *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcBlobEncoding*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcBlobEncoding_AddRef(IDxcBlobEncoding *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcBlobEncoding*), self); }
static inline ULONG   IDxcBlobEncoding_Release(IDxcBlobEncoding *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcBlobEncoding*), self); }
static inline LPVOID  IDxcBlobEncoding_GetBufferPointer(IDxcBlobEncoding *self) { return COM_CALL(self, 3, LPVOID(__stdcall*)(IDxcBlobEncoding*), self); }
static inline SIZE_T  IDxcBlobEncoding_GetBufferSize(IDxcBlobEncoding *self) { return COM_CALL(self, 4, SIZE_T(__stdcall*)(IDxcBlobEncoding*), self); }
static inline HRESULT IDxcBlobEncoding_GetEncoding(IDxcBlobEncoding *self, BOOL *pKnown, UINT32 *pCodePage) { return COM_CALL(self, 5, HRESULT(__stdcall*)(IDxcBlobEncoding*, BOOL*, UINT32*), self, pKnown, pCodePage); }

static inline HRESULT IDxcBlobWide_QueryInterface(IDxcBlobWide *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcBlobWide*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcBlobWide_AddRef(IDxcBlobWide *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcBlobWide*), self); }
static inline ULONG   IDxcBlobWide_Release(IDxcBlobWide *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcBlobWide*), self); }
static inline LPVOID  IDxcBlobWide_GetBufferPointer(IDxcBlobWide *self) { return COM_CALL(self, 3, LPVOID(__stdcall*)(IDxcBlobWide*), self); }
static inline SIZE_T  IDxcBlobWide_GetBufferSize(IDxcBlobWide *self) { return COM_CALL(self, 4, SIZE_T(__stdcall*)(IDxcBlobWide*), self); }
static inline HRESULT IDxcBlobWide_GetEncoding(IDxcBlobWide *self, BOOL *pKnown, UINT32 *pCodePage) { return COM_CALL(self, 5, HRESULT(__stdcall*)(IDxcBlobWide*, BOOL*, UINT32*), self, pKnown, pCodePage); }
static inline LPCWSTR IDxcBlobWide_GetStringPointer(IDxcBlobWide *self) { return COM_CALL(self, 6, LPCWSTR(__stdcall*)(IDxcBlobWide*), self); }
static inline SIZE_T  IDxcBlobWide_GetStringLength(IDxcBlobWide *self) { return COM_CALL(self, 7, SIZE_T(__stdcall*)(IDxcBlobWide*), self); }

static inline HRESULT IDxcBlobUtf8_QueryInterface(IDxcBlobUtf8 *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcBlobUtf8*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcBlobUtf8_AddRef(IDxcBlobUtf8 *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcBlobUtf8*), self); }
static inline ULONG   IDxcBlobUtf8_Release(IDxcBlobUtf8 *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcBlobUtf8*), self); }
static inline LPVOID  IDxcBlobUtf8_GetBufferPointer(IDxcBlobUtf8 *self) { return COM_CALL(self, 3, LPVOID(__stdcall*)(IDxcBlobUtf8*), self); }
static inline SIZE_T  IDxcBlobUtf8_GetBufferSize(IDxcBlobUtf8 *self) { return COM_CALL(self, 4, SIZE_T(__stdcall*)(IDxcBlobUtf8*), self); }
static inline HRESULT IDxcBlobUtf8_GetEncoding(IDxcBlobUtf8 *self, BOOL *pKnown, UINT32 *pCodePage) { return COM_CALL(self, 5, HRESULT(__stdcall*)(IDxcBlobUtf8*, BOOL*, UINT32*), self, pKnown, pCodePage); }
static inline LPCSTR  IDxcBlobUtf8_GetStringPointer(IDxcBlobUtf8 *self) { return COM_CALL(self, 6, LPCSTR(__stdcall*)(IDxcBlobUtf8*), self); }
static inline SIZE_T  IDxcBlobUtf8_GetStringLength(IDxcBlobUtf8 *self) { return COM_CALL(self, 7, SIZE_T(__stdcall*)(IDxcBlobUtf8*), self); }

static inline HRESULT IDxcIncludeHandler_QueryInterface(IDxcIncludeHandler *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcIncludeHandler*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcIncludeHandler_AddRef(IDxcIncludeHandler *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcIncludeHandler*), self); }
static inline ULONG   IDxcIncludeHandler_Release(IDxcIncludeHandler *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcIncludeHandler*), self); }
static inline HRESULT IDxcIncludeHandler_LoadSource(IDxcIncludeHandler *self, LPCWSTR pFilename, IDxcBlob **ppIncludeSource) { return COM_CALL(self, 3, HRESULT(__stdcall*)(IDxcIncludeHandler*, LPCWSTR, IDxcBlob**), self, pFilename, ppIncludeSource); }

static inline HRESULT  IDxcCompilerArgs_QueryInterface(IDxcCompilerArgs *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcCompilerArgs*, REFIID, void**), self, riid, ppv); }
static inline ULONG    IDxcCompilerArgs_AddRef(IDxcCompilerArgs *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcCompilerArgs*), self); }
static inline ULONG    IDxcCompilerArgs_Release(IDxcCompilerArgs *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcCompilerArgs*), self); }
static inline LPCWSTR *IDxcCompilerArgs_GetArguments(IDxcCompilerArgs *self) { return COM_CALL(self, 3, LPCWSTR*(__stdcall*)(IDxcCompilerArgs*), self); }
static inline UINT32   IDxcCompilerArgs_GetCount(IDxcCompilerArgs *self) { return COM_CALL(self, 4, UINT32(__stdcall*)(IDxcCompilerArgs*), self); }
static inline HRESULT  IDxcCompilerArgs_AddArguments(IDxcCompilerArgs *self, LPCWSTR *pArguments, UINT32 argCount) { return COM_CALL(self, 5, HRESULT(__stdcall*)(IDxcCompilerArgs*, LPCWSTR*, UINT32), self, pArguments, argCount); }
static inline HRESULT  IDxcCompilerArgs_AddArgumentsUTF8(IDxcCompilerArgs *self, LPCSTR *pArguments, UINT32 argCount) { return COM_CALL(self, 6, HRESULT(__stdcall*)(IDxcCompilerArgs*, LPCSTR*, UINT32), self, pArguments, argCount); }
static inline HRESULT  IDxcCompilerArgs_AddDefines(IDxcCompilerArgs *self, const DxcDefine *pDefines, UINT32 defineCount) { return COM_CALL(self, 7, HRESULT(__stdcall*)(IDxcCompilerArgs*, const DxcDefine*, UINT32), self, pDefines, defineCount); }

static inline HRESULT IDxcLibrary_QueryInterface(IDxcLibrary *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcLibrary*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcLibrary_AddRef(IDxcLibrary *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcLibrary*), self); }
static inline ULONG   IDxcLibrary_Release(IDxcLibrary *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcLibrary*), self); }
static inline HRESULT IDxcLibrary_SetMalloc(IDxcLibrary *self, IMalloc *pMalloc) { return COM_CALL(self, 3, HRESULT(__stdcall*)(IDxcLibrary*, IMalloc*), self, pMalloc); }
static inline HRESULT IDxcLibrary_CreateBlobFromBlob(IDxcLibrary *self, IDxcBlob *pBlob, UINT32 offset, UINT32 length, IDxcBlob **ppResult) { return COM_CALL(self, 4, HRESULT(__stdcall*)(IDxcLibrary*, IDxcBlob*, UINT32, UINT32, IDxcBlob**), self, pBlob, offset, length, ppResult); }
static inline HRESULT IDxcLibrary_CreateBlobFromFile(IDxcLibrary *self, LPCWSTR pFileName, UINT32 *codePage, IDxcBlobEncoding **pBlobEncoding) { return COM_CALL(self, 5, HRESULT(__stdcall*)(IDxcLibrary*, LPCWSTR, UINT32*, IDxcBlobEncoding**), self, pFileName, codePage, pBlobEncoding); }
static inline HRESULT IDxcLibrary_CreateBlobWithEncodingFromPinned(IDxcLibrary *self, LPCVOID pText, UINT32 size, UINT32 codePage, IDxcBlobEncoding **pBlobEncoding) { return COM_CALL(self, 6, HRESULT(__stdcall*)(IDxcLibrary*, LPCVOID, UINT32, UINT32, IDxcBlobEncoding**), self, pText, size, codePage, pBlobEncoding); }
static inline HRESULT IDxcLibrary_CreateBlobWithEncodingOnHeapCopy(IDxcLibrary *self, LPCVOID pText, UINT32 size, UINT32 codePage, IDxcBlobEncoding **pBlobEncoding) { return COM_CALL(self, 7, HRESULT(__stdcall*)(IDxcLibrary*, LPCVOID, UINT32, UINT32, IDxcBlobEncoding**), self, pText, size, codePage, pBlobEncoding); }
static inline HRESULT IDxcLibrary_CreateBlobWithEncodingOnMalloc(IDxcLibrary *self, LPCVOID pText, IMalloc *pIMalloc, UINT32 size, UINT32 codePage, IDxcBlobEncoding **pBlobEncoding) { return COM_CALL(self, 8, HRESULT(__stdcall*)(IDxcLibrary*, LPCVOID, IMalloc*, UINT32, UINT32, IDxcBlobEncoding**), self, pText, pIMalloc, size, codePage, pBlobEncoding); }
static inline HRESULT IDxcLibrary_CreateIncludeHandler(IDxcLibrary *self, IDxcIncludeHandler **ppResult) { return COM_CALL(self, 9, HRESULT(__stdcall*)(IDxcLibrary*, IDxcIncludeHandler**), self, ppResult); }
static inline HRESULT IDxcLibrary_CreateStreamFromBlobReadOnly(IDxcLibrary *self, IDxcBlob *pBlob, IStream **ppStream) { return COM_CALL(self, 10, HRESULT(__stdcall*)(IDxcLibrary*, IDxcBlob*, IStream**), self, pBlob, ppStream); }
static inline HRESULT IDxcLibrary_GetBlobAsUtf8(IDxcLibrary *self, IDxcBlob *pBlob, IDxcBlobEncoding **pBlobEncoding) { return COM_CALL(self, 11, HRESULT(__stdcall*)(IDxcLibrary*, IDxcBlob*, IDxcBlobEncoding**), self, pBlob, pBlobEncoding); }
static inline HRESULT IDxcLibrary_GetBlobAsWide(IDxcLibrary *self, IDxcBlob *pBlob, IDxcBlobEncoding **pBlobEncoding) { return COM_CALL(self, 12, HRESULT(__stdcall*)(IDxcLibrary*, IDxcBlob*, IDxcBlobEncoding**), self, pBlob, pBlobEncoding); }

static inline HRESULT IDxcOperationResult_QueryInterface(IDxcOperationResult *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcOperationResult*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcOperationResult_AddRef(IDxcOperationResult *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcOperationResult*), self); }
static inline ULONG   IDxcOperationResult_Release(IDxcOperationResult *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcOperationResult*), self); }
static inline HRESULT IDxcOperationResult_GetStatus(IDxcOperationResult *self, HRESULT *pStatus) { return COM_CALL(self, 3, HRESULT(__stdcall*)(IDxcOperationResult*, HRESULT*), self, pStatus); }
static inline HRESULT IDxcOperationResult_GetResult(IDxcOperationResult *self, IDxcBlob **ppResult) { return COM_CALL(self, 4, HRESULT(__stdcall*)(IDxcOperationResult*, IDxcBlob**), self, ppResult); }
static inline HRESULT IDxcOperationResult_GetErrorBuffer(IDxcOperationResult *self, IDxcBlobEncoding **ppErrors) { return COM_CALL(self, 5, HRESULT(__stdcall*)(IDxcOperationResult*, IDxcBlobEncoding**), self, ppErrors); }

static inline HRESULT IDxcCompiler_QueryInterface(IDxcCompiler *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcCompiler*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcCompiler_AddRef(IDxcCompiler *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcCompiler*), self); }
static inline ULONG   IDxcCompiler_Release(IDxcCompiler *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcCompiler*), self); }
static inline HRESULT IDxcCompiler_Compile(IDxcCompiler *self, IDxcBlob *pSource, LPCWSTR pSourceName, LPCWSTR pEntryPoint, LPCWSTR pTargetProfile, LPCWSTR *pArguments, UINT32 argCount, const DxcDefine *pDefines, UINT32 defineCount, IDxcIncludeHandler *pIncludeHandler, IDxcOperationResult **ppResult) { return COM_CALL(self, 3, HRESULT(__stdcall*)(IDxcCompiler*, IDxcBlob*, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR*, UINT32, const DxcDefine*, UINT32, IDxcIncludeHandler*, IDxcOperationResult**), self, pSource, pSourceName, pEntryPoint, pTargetProfile, pArguments, argCount, pDefines, defineCount, pIncludeHandler, ppResult); }
static inline HRESULT IDxcCompiler_Preprocess(IDxcCompiler *self, IDxcBlob *pSource, LPCWSTR pSourceName, LPCWSTR *pArguments, UINT32 argCount, const DxcDefine *pDefines, UINT32 defineCount, IDxcIncludeHandler *pIncludeHandler, IDxcOperationResult **ppResult) { return COM_CALL(self, 4, HRESULT(__stdcall*)(IDxcCompiler*, IDxcBlob*, LPCWSTR, LPCWSTR*, UINT32, const DxcDefine*, UINT32, IDxcIncludeHandler*, IDxcOperationResult**), self, pSource, pSourceName, pArguments, argCount, pDefines, defineCount, pIncludeHandler, ppResult); }
static inline HRESULT IDxcCompiler_Disassemble(IDxcCompiler *self, IDxcBlob *pSource, IDxcBlobEncoding **ppDisassembly) { return COM_CALL(self, 5, HRESULT(__stdcall*)(IDxcCompiler*, IDxcBlob*, IDxcBlobEncoding**), self, pSource, ppDisassembly); }

static inline HRESULT IDxcCompiler2_QueryInterface(IDxcCompiler2 *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcCompiler2*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcCompiler2_AddRef(IDxcCompiler2 *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcCompiler2*), self); }
static inline ULONG   IDxcCompiler2_Release(IDxcCompiler2 *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcCompiler2*), self); }
static inline HRESULT IDxcCompiler2_CompileWithDebug(IDxcCompiler2 *self, IDxcBlob *pSource, LPCWSTR pSourceName, LPCWSTR pEntryPoint, LPCWSTR pTargetProfile, LPCWSTR *pArguments, UINT32 argCount, const DxcDefine *pDefines, UINT32 defineCount, IDxcIncludeHandler *pIncludeHandler, IDxcOperationResult **ppResult, LPWSTR *ppDebugBlobName, IDxcBlob **ppDebugBlob) { return COM_CALL(self, 6, HRESULT(__stdcall*)(IDxcCompiler2*, IDxcBlob*, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR*, UINT32, const DxcDefine*, UINT32, IDxcIncludeHandler*, IDxcOperationResult**, LPWSTR*, IDxcBlob**), self, pSource, pSourceName, pEntryPoint, pTargetProfile, pArguments, argCount, pDefines, defineCount, pIncludeHandler, ppResult, ppDebugBlobName, ppDebugBlob); }

static inline HRESULT IDxcLinker_QueryInterface(IDxcLinker *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcLinker*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcLinker_AddRef(IDxcLinker *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcLinker*), self); }
static inline ULONG   IDxcLinker_Release(IDxcLinker *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcLinker*), self); }
static inline HRESULT IDxcLinker_RegisterLibrary(IDxcLinker *self, LPCWSTR pLibName, IDxcBlob *pLib) { return COM_CALL(self, 3, HRESULT(__stdcall*)(IDxcLinker*, LPCWSTR, IDxcBlob*), self, pLibName, pLib); }
static inline HRESULT IDxcLinker_Link(IDxcLinker *self, LPCWSTR pEntryName, LPCWSTR pTargetProfile, const LPCWSTR *pLibNames, UINT32 libCount, const LPCWSTR *pArguments, UINT32 argCount, IDxcOperationResult **ppResult) { return COM_CALL(self, 4, HRESULT(__stdcall*)(IDxcLinker*, LPCWSTR, LPCWSTR, const LPCWSTR*, UINT32, const LPCWSTR*, UINT32, IDxcOperationResult**), self, pEntryName, pTargetProfile, pLibNames, libCount, pArguments, argCount, ppResult); }

static inline HRESULT IDxcUtils_QueryInterface(IDxcUtils *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcUtils*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcUtils_AddRef(IDxcUtils *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcUtils*), self); }
static inline ULONG   IDxcUtils_Release(IDxcUtils *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcUtils*), self); }
static inline HRESULT IDxcUtils_CreateBlobFromBlob(IDxcUtils *self, IDxcBlob *pBlob, UINT32 offset, UINT32 length, IDxcBlob **ppResult) { return COM_CALL(self, 3, HRESULT(__stdcall*)(IDxcUtils*, IDxcBlob*, UINT32, UINT32, IDxcBlob**), self, pBlob, offset, length, ppResult); }
static inline HRESULT IDxcUtils_CreateBlobFromPinned(IDxcUtils *self, LPCVOID pData, UINT32 size, UINT32 codePage, IDxcBlobEncoding **ppBlobEncoding) { return COM_CALL(self, 4, HRESULT(__stdcall*)(IDxcUtils*, LPCVOID, UINT32, UINT32, IDxcBlobEncoding**), self, pData, size, codePage, ppBlobEncoding); }
static inline HRESULT IDxcUtils_MoveToBlob(IDxcUtils *self, LPCVOID pData, IMalloc *pIMalloc, UINT32 size, UINT32 codePage, IDxcBlobEncoding **ppBlobEncoding) { return COM_CALL(self, 5, HRESULT(__stdcall*)(IDxcUtils*, LPCVOID, IMalloc*, UINT32, UINT32, IDxcBlobEncoding**), self, pData, pIMalloc, size, codePage, ppBlobEncoding); }
static inline HRESULT IDxcUtils_CreateBlob(IDxcUtils *self, LPCVOID pData, UINT32 size, UINT32 codePage, IDxcBlobEncoding **ppBlobEncoding) { return COM_CALL(self, 6, HRESULT(__stdcall*)(IDxcUtils*, LPCVOID, UINT32, UINT32, IDxcBlobEncoding**), self, pData, size, codePage, ppBlobEncoding); }
static inline HRESULT IDxcUtils_LoadFile(IDxcUtils *self, LPCWSTR pFileName, UINT32 *pCodePage, IDxcBlobEncoding **ppBlobEncoding) { return COM_CALL(self, 7, HRESULT(__stdcall*)(IDxcUtils*, LPCWSTR, UINT32*, IDxcBlobEncoding**), self, pFileName, pCodePage, ppBlobEncoding); }
static inline HRESULT IDxcUtils_CreateReadOnlyStreamFromBlob(IDxcUtils *self, IDxcBlob *pBlob, IStream **ppStream) { return COM_CALL(self, 8, HRESULT(__stdcall*)(IDxcUtils*, IDxcBlob*, IStream**), self, pBlob, ppStream); }
static inline HRESULT IDxcUtils_CreateDefaultIncludeHandler(IDxcUtils *self, IDxcIncludeHandler **ppResult) { return COM_CALL(self, 9, HRESULT(__stdcall*)(IDxcUtils*, IDxcIncludeHandler**), self, ppResult); }
static inline HRESULT IDxcUtils_GetBlobAsUtf8(IDxcUtils *self, IDxcBlob *pBlob, IDxcBlobUtf8 **ppBlobEncoding) { return COM_CALL(self, 10, HRESULT(__stdcall*)(IDxcUtils*, IDxcBlob*, IDxcBlobUtf8**), self, pBlob, ppBlobEncoding); }
static inline HRESULT IDxcUtils_GetBlobAsWide(IDxcUtils *self, IDxcBlob *pBlob, IDxcBlobWide **ppBlobEncoding) { return COM_CALL(self, 11, HRESULT(__stdcall*)(IDxcUtils*, IDxcBlob*, IDxcBlobWide**), self, pBlob, ppBlobEncoding); }
static inline HRESULT IDxcUtils_GetDxilContainerPart(IDxcUtils *self, const DxcBuffer *pShader, UINT32 DxcPart, void **ppPartData, UINT32 *pPartSizeInBytes) { return COM_CALL(self, 12, HRESULT(__stdcall*)(IDxcUtils*, const DxcBuffer*, UINT32, void**, UINT32*), self, pShader, DxcPart, ppPartData, pPartSizeInBytes); }
static inline HRESULT IDxcUtils_CreateReflection(IDxcUtils *self, const DxcBuffer *pData, REFIID iid, void **ppvReflection) { return COM_CALL(self, 13, HRESULT(__stdcall*)(IDxcUtils*, const DxcBuffer*, REFIID, void**), self, pData, iid, ppvReflection); }
static inline HRESULT IDxcUtils_BuildArguments(IDxcUtils *self, LPCWSTR pSourceName, LPCWSTR pEntryPoint, LPCWSTR pTargetProfile, LPCWSTR *pArguments, UINT32 argCount, const DxcDefine *pDefines, UINT32 defineCount, IDxcCompilerArgs **ppArgs) { return COM_CALL(self, 14, HRESULT(__stdcall*)(IDxcUtils*, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR*, UINT32, const DxcDefine*, UINT32, IDxcCompilerArgs**), self, pSourceName, pEntryPoint, pTargetProfile, pArguments, argCount, pDefines, defineCount, ppArgs); }
static inline HRESULT IDxcUtils_GetPDBContents(IDxcUtils *self, IDxcBlob *pPDBBlob, IDxcBlob **ppHash, IDxcBlob **ppContainer) { return COM_CALL(self, 15, HRESULT(__stdcall*)(IDxcUtils*, IDxcBlob*, IDxcBlob**, IDxcBlob**), self, pPDBBlob, ppHash, ppContainer); }

static inline HRESULT      IDxcResult_QueryInterface(IDxcResult *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcResult*, REFIID, void**), self, riid, ppv); }
static inline ULONG        IDxcResult_AddRef(IDxcResult *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcResult*), self); }
static inline ULONG        IDxcResult_Release(IDxcResult *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcResult*), self); }
static inline HRESULT      IDxcResult_GetStatus(IDxcResult *self, HRESULT *pStatus) { return COM_CALL(self, 3, HRESULT(__stdcall*)(IDxcResult*, HRESULT*), self, pStatus); }
static inline HRESULT      IDxcResult_GetResult(IDxcResult *self, IDxcBlob **ppResult) { return COM_CALL(self, 4, HRESULT(__stdcall*)(IDxcResult*, IDxcBlob**), self, ppResult); }
static inline HRESULT      IDxcResult_GetErrorBuffer(IDxcResult *self, IDxcBlobEncoding **ppErrors) { return COM_CALL(self, 5, HRESULT(__stdcall*)(IDxcResult*, IDxcBlobEncoding**), self, ppErrors); }
static inline BOOL         IDxcResult_HasOutput(IDxcResult *self, DXC_OUT_KIND dxcOutKind) { return COM_CALL(self, 6, BOOL(__stdcall*)(IDxcResult*, DXC_OUT_KIND), self, dxcOutKind); }
static inline HRESULT      IDxcResult_GetOutput(IDxcResult *self, DXC_OUT_KIND dxcOutKind, REFIID iid, void **ppvObject, IDxcBlobWide **ppOutputName) { return COM_CALL(self, 7, HRESULT(__stdcall*)(IDxcResult*, DXC_OUT_KIND, REFIID, void**, IDxcBlobWide**), self, dxcOutKind, iid, ppvObject, ppOutputName); }
static inline UINT32       IDxcResult_GetNumOutputs(IDxcResult *self) { return COM_CALL(self, 8, UINT32(__stdcall*)(IDxcResult*), self); }
static inline DXC_OUT_KIND IDxcResult_GetOutputByIndex(IDxcResult *self, UINT32 Index) { return COM_CALL(self, 9, DXC_OUT_KIND(__stdcall*)(IDxcResult*, UINT32), self, Index); }
static inline DXC_OUT_KIND IDxcResult_PrimaryOutput(IDxcResult *self) { return COM_CALL(self, 10, DXC_OUT_KIND(__stdcall*)(IDxcResult*), self); }

static inline HRESULT IDxcExtraOutputs_QueryInterface(IDxcExtraOutputs *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcExtraOutputs*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcExtraOutputs_AddRef(IDxcExtraOutputs *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcExtraOutputs*), self); }
static inline ULONG   IDxcExtraOutputs_Release(IDxcExtraOutputs *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcExtraOutputs*), self); }
static inline UINT32  IDxcExtraOutputs_GetOutputCount(IDxcExtraOutputs *self) { return COM_CALL(self, 3, UINT32(__stdcall*)(IDxcExtraOutputs*), self); }
static inline HRESULT IDxcExtraOutputs_GetOutput(IDxcExtraOutputs *self, UINT32 uIndex, REFIID iid, void **ppvObject, IDxcBlobWide **ppOutputType, IDxcBlobWide **ppOutputName) { return COM_CALL(self, 4, HRESULT(__stdcall*)(IDxcExtraOutputs*, UINT32, REFIID, void**, IDxcBlobWide**, IDxcBlobWide**), self, uIndex, iid, ppvObject, ppOutputType, ppOutputName); }

static inline HRESULT IDxcCompiler3_QueryInterface(IDxcCompiler3 *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcCompiler3*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcCompiler3_AddRef(IDxcCompiler3 *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcCompiler3*), self); }
static inline ULONG   IDxcCompiler3_Release(IDxcCompiler3 *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcCompiler3*), self); }
static inline HRESULT IDxcCompiler3_Compile(IDxcCompiler3 *self, const DxcBuffer *pSource, LPCWSTR *pArguments, UINT32 argCount, IDxcIncludeHandler *pIncludeHandler, REFIID riid, void **ppResult) { return COM_CALL(self, 3, HRESULT(__stdcall*)(IDxcCompiler3*, const DxcBuffer*, LPCWSTR*, UINT32, IDxcIncludeHandler*, REFIID, void**), self, pSource, pArguments, argCount, pIncludeHandler, riid, ppResult); }
static inline HRESULT IDxcCompiler3_Disassemble(IDxcCompiler3 *self, const DxcBuffer *pObject, REFIID riid, void **ppResult) { return COM_CALL(self, 4, HRESULT(__stdcall*)(IDxcCompiler3*, const DxcBuffer*, REFIID, void**), self, pObject, riid, ppResult); }

static inline HRESULT IDxcValidator_QueryInterface(IDxcValidator *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcValidator*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcValidator_AddRef(IDxcValidator *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcValidator*), self); }
static inline ULONG   IDxcValidator_Release(IDxcValidator *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcValidator*), self); }
static inline HRESULT IDxcValidator_Validate(IDxcValidator *self, IDxcBlob *pShader, UINT32 Flags, IDxcOperationResult **ppResult) { return COM_CALL(self, 3, HRESULT(__stdcall*)(IDxcValidator*, IDxcBlob*, UINT32, IDxcOperationResult**), self, pShader, Flags, ppResult); }

static inline HRESULT IDxcValidator2_QueryInterface(IDxcValidator2 *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcValidator2*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcValidator2_AddRef(IDxcValidator2 *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcValidator2*), self); }
static inline ULONG   IDxcValidator2_Release(IDxcValidator2 *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcValidator2*), self); }
static inline HRESULT IDxcValidator2_Validate(IDxcValidator2 *self, IDxcBlob *pShader, UINT32 Flags, IDxcOperationResult **ppResult) { return COM_CALL(self, 3, HRESULT(__stdcall*)(IDxcValidator2*, IDxcBlob*, UINT32, IDxcOperationResult**), self, pShader, Flags, ppResult); }
static inline HRESULT IDxcValidator2_ValidateWithDebug(IDxcValidator2 *self, IDxcBlob *pShader, UINT32 Flags, DxcBuffer *pOptDebugBitcode, IDxcOperationResult **ppResult) { return COM_CALL(self, 4, HRESULT(__stdcall*)(IDxcValidator2*, IDxcBlob*, UINT32, DxcBuffer*, IDxcOperationResult**), self, pShader, Flags, pOptDebugBitcode, ppResult); }

static inline HRESULT IDxcContainerBuilder_QueryInterface(IDxcContainerBuilder *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcContainerBuilder*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcContainerBuilder_AddRef(IDxcContainerBuilder *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcContainerBuilder*), self); }
static inline ULONG   IDxcContainerBuilder_Release(IDxcContainerBuilder *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcContainerBuilder*), self); }
static inline HRESULT IDxcContainerBuilder_Load(IDxcContainerBuilder *self, IDxcBlob *pDxilContainerHeader) { return COM_CALL(self, 3, HRESULT(__stdcall*)(IDxcContainerBuilder*, IDxcBlob*), self, pDxilContainerHeader); }
static inline HRESULT IDxcContainerBuilder_AddPart(IDxcContainerBuilder *self, UINT32 fourCC, IDxcBlob *pSource) { return COM_CALL(self, 4, HRESULT(__stdcall*)(IDxcContainerBuilder*, UINT32, IDxcBlob*), self, fourCC, pSource); }
static inline HRESULT IDxcContainerBuilder_RemovePart(IDxcContainerBuilder *self, UINT32 fourCC) { return COM_CALL(self, 5, HRESULT(__stdcall*)(IDxcContainerBuilder*, UINT32), self, fourCC); }
static inline HRESULT IDxcContainerBuilder_SerializeContainer(IDxcContainerBuilder *self, IDxcOperationResult **ppResult) { return COM_CALL(self, 6, HRESULT(__stdcall*)(IDxcContainerBuilder*, IDxcOperationResult**), self, ppResult); }

static inline HRESULT IDxcAssembler_QueryInterface(IDxcAssembler *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcAssembler*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcAssembler_AddRef(IDxcAssembler *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcAssembler*), self); }
static inline ULONG   IDxcAssembler_Release(IDxcAssembler *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcAssembler*), self); }
static inline HRESULT IDxcAssembler_AssembleToContainer(IDxcAssembler *self, IDxcBlob *pShader, IDxcOperationResult **ppResult) { return COM_CALL(self, 3, HRESULT(__stdcall*)(IDxcAssembler*, IDxcBlob*, IDxcOperationResult**), self, pShader, ppResult); }

static inline HRESULT IDxcContainerReflection_QueryInterface(IDxcContainerReflection *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcContainerReflection*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcContainerReflection_AddRef(IDxcContainerReflection *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcContainerReflection*), self); }
static inline ULONG   IDxcContainerReflection_Release(IDxcContainerReflection *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcContainerReflection*), self); }
static inline HRESULT IDxcContainerReflection_Load(IDxcContainerReflection *self, IDxcBlob *pContainer) { return COM_CALL(self, 3, HRESULT(__stdcall*)(IDxcContainerReflection*, IDxcBlob*), self, pContainer); }
static inline HRESULT IDxcContainerReflection_GetPartCount(IDxcContainerReflection *self, UINT32 *pResult) { return COM_CALL(self, 4, HRESULT(__stdcall*)(IDxcContainerReflection*, UINT32*), self, pResult); }
static inline HRESULT IDxcContainerReflection_GetPartKind(IDxcContainerReflection *self, UINT32 idx, UINT32 *pResult) { return COM_CALL(self, 5, HRESULT(__stdcall*)(IDxcContainerReflection*, UINT32, UINT32*), self, idx, pResult); }
static inline HRESULT IDxcContainerReflection_GetPartContent(IDxcContainerReflection *self, UINT32 idx, IDxcBlob **ppResult) { return COM_CALL(self, 6, HRESULT(__stdcall*)(IDxcContainerReflection*, UINT32, IDxcBlob**), self, idx, ppResult); }
static inline HRESULT IDxcContainerReflection_FindFirstPartKind(IDxcContainerReflection *self, UINT32 kind, UINT32 *pResult) { return COM_CALL(self, 7, HRESULT(__stdcall*)(IDxcContainerReflection*, UINT32, UINT32*), self, kind, pResult); }
static inline HRESULT IDxcContainerReflection_GetPartReflection(IDxcContainerReflection *self, UINT32 idx, REFIID iid, void **ppvObject) { return COM_CALL(self, 8, HRESULT(__stdcall*)(IDxcContainerReflection*, UINT32, REFIID, void**), self, idx, iid, ppvObject); }

static inline HRESULT IDxcOptimizerPass_QueryInterface(IDxcOptimizerPass *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcOptimizerPass*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcOptimizerPass_AddRef(IDxcOptimizerPass *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcOptimizerPass*), self); }
static inline ULONG   IDxcOptimizerPass_Release(IDxcOptimizerPass *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcOptimizerPass*), self); }
static inline HRESULT IDxcOptimizerPass_GetOptionName(IDxcOptimizerPass *self, LPWSTR *ppResult) { return COM_CALL(self, 3, HRESULT(__stdcall*)(IDxcOptimizerPass*, LPWSTR*), self, ppResult); }
static inline HRESULT IDxcOptimizerPass_GetDescription(IDxcOptimizerPass *self, LPWSTR *ppResult) { return COM_CALL(self, 4, HRESULT(__stdcall*)(IDxcOptimizerPass*, LPWSTR*), self, ppResult); }
static inline HRESULT IDxcOptimizerPass_GetOptionArgCount(IDxcOptimizerPass *self, UINT32 *pCount) { return COM_CALL(self, 5, HRESULT(__stdcall*)(IDxcOptimizerPass*, UINT32*), self, pCount); }
static inline HRESULT IDxcOptimizerPass_GetOptionArgName(IDxcOptimizerPass *self, UINT32 argIndex, LPWSTR *ppResult) { return COM_CALL(self, 6, HRESULT(__stdcall*)(IDxcOptimizerPass*, UINT32, LPWSTR*), self, argIndex, ppResult); }
static inline HRESULT IDxcOptimizerPass_GetOptionArgDescription(IDxcOptimizerPass *self, UINT32 argIndex, LPWSTR *ppResult) { return COM_CALL(self, 7, HRESULT(__stdcall*)(IDxcOptimizerPass*, UINT32, LPWSTR*), self, argIndex, ppResult); }

static inline HRESULT IDxcOptimizer_QueryInterface(IDxcOptimizer *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcOptimizer*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcOptimizer_AddRef(IDxcOptimizer *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcOptimizer*), self); }
static inline ULONG   IDxcOptimizer_Release(IDxcOptimizer *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcOptimizer*), self); }
static inline HRESULT IDxcOptimizer_GetAvailablePassCount(IDxcOptimizer *self, UINT32 *pCount) { return COM_CALL(self, 3, HRESULT(__stdcall*)(IDxcOptimizer*, UINT32*), self, pCount); }
static inline HRESULT IDxcOptimizer_GetAvailablePass(IDxcOptimizer *self, UINT32 index, IDxcOptimizerPass **ppResult) { return COM_CALL(self, 4, HRESULT(__stdcall*)(IDxcOptimizer*, UINT32, IDxcOptimizerPass**), self, index, ppResult); }
static inline HRESULT IDxcOptimizer_RunOptimizer(IDxcOptimizer *self, IDxcBlob *pBlob, LPCWSTR *ppOptions, UINT32 optionCount, IDxcBlob **pOutputModule, IDxcBlobEncoding **ppOutputText) { return COM_CALL(self, 5, HRESULT(__stdcall*)(IDxcOptimizer*, IDxcBlob*, LPCWSTR*, UINT32, IDxcBlob**, IDxcBlobEncoding**), self, pBlob, ppOptions, optionCount, pOutputModule, ppOutputText); }

static inline HRESULT IDxcVersionInfo_QueryInterface(IDxcVersionInfo *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcVersionInfo*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcVersionInfo_AddRef(IDxcVersionInfo *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcVersionInfo*), self); }
static inline ULONG   IDxcVersionInfo_Release(IDxcVersionInfo *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcVersionInfo*), self); }
static inline HRESULT IDxcVersionInfo_GetVersion(IDxcVersionInfo *self, UINT32 *pMajor, UINT32 *pMinor) { return COM_CALL(self, 3, HRESULT(__stdcall*)(IDxcVersionInfo*, UINT32*, UINT32*), self, pMajor, pMinor); }
static inline HRESULT IDxcVersionInfo_GetFlags(IDxcVersionInfo *self, UINT32 *pFlags) { return COM_CALL(self, 4, HRESULT(__stdcall*)(IDxcVersionInfo*, UINT32*), self, pFlags); }

static inline HRESULT IDxcVersionInfo2_QueryInterface(IDxcVersionInfo2 *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcVersionInfo2*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcVersionInfo2_AddRef(IDxcVersionInfo2 *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcVersionInfo2*), self); }
static inline ULONG   IDxcVersionInfo2_Release(IDxcVersionInfo2 *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcVersionInfo2*), self); }
static inline HRESULT IDxcVersionInfo2_GetVersion(IDxcVersionInfo2 *self, UINT32 *pMajor, UINT32 *pMinor) { return COM_CALL(self, 3, HRESULT(__stdcall*)(IDxcVersionInfo2*, UINT32*, UINT32*), self, pMajor, pMinor); }
static inline HRESULT IDxcVersionInfo2_GetFlags(IDxcVersionInfo2 *self, UINT32 *pFlags) { return COM_CALL(self, 4, HRESULT(__stdcall*)(IDxcVersionInfo2*, UINT32*), self, pFlags); }
static inline HRESULT IDxcVersionInfo2_GetCommitInfo(IDxcVersionInfo2 *self, UINT32 *pCommitCount, char **pCommitHash) { return COM_CALL(self, 5, HRESULT(__stdcall*)(IDxcVersionInfo2*, UINT32*, char**), self, pCommitCount, pCommitHash); }

static inline HRESULT IDxcVersionInfo3_QueryInterface(IDxcVersionInfo3 *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcVersionInfo3*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcVersionInfo3_AddRef(IDxcVersionInfo3 *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcVersionInfo3*), self); }
static inline ULONG   IDxcVersionInfo3_Release(IDxcVersionInfo3 *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcVersionInfo3*), self); }
static inline HRESULT IDxcVersionInfo3_GetCustomVersionString(IDxcVersionInfo3 *self, char **pVersionString) { return COM_CALL(self, 3, HRESULT(__stdcall*)(IDxcVersionInfo3*, char**), self, pVersionString); }

static inline HRESULT IDxcPdbUtils_QueryInterface(IDxcPdbUtils *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcPdbUtils*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcPdbUtils_AddRef(IDxcPdbUtils *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcPdbUtils*), self); }
static inline ULONG   IDxcPdbUtils_Release(IDxcPdbUtils *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcPdbUtils*), self); }
static inline HRESULT IDxcPdbUtils_Load(IDxcPdbUtils *self, IDxcBlob *pPdbOrDxil) { return COM_CALL(self, 3, HRESULT(__stdcall*)(IDxcPdbUtils*, IDxcBlob*), self, pPdbOrDxil); }
static inline HRESULT IDxcPdbUtils_GetSourceCount(IDxcPdbUtils *self, UINT32 *pCount) { return COM_CALL(self, 4, HRESULT(__stdcall*)(IDxcPdbUtils*, UINT32*), self, pCount); }
static inline HRESULT IDxcPdbUtils_GetSource(IDxcPdbUtils *self, UINT32 uIndex, IDxcBlobEncoding **ppResult) { return COM_CALL(self, 5, HRESULT(__stdcall*)(IDxcPdbUtils*, UINT32, IDxcBlobEncoding**), self, uIndex, ppResult); }
static inline HRESULT IDxcPdbUtils_GetSourceName(IDxcPdbUtils *self, UINT32 uIndex, BSTR *pResult) { return COM_CALL(self, 6, HRESULT(__stdcall*)(IDxcPdbUtils*, UINT32, BSTR*), self, uIndex, pResult); }
static inline HRESULT IDxcPdbUtils_GetFlagCount(IDxcPdbUtils *self, UINT32 *pCount) { return COM_CALL(self, 7, HRESULT(__stdcall*)(IDxcPdbUtils*, UINT32*), self, pCount); }
static inline HRESULT IDxcPdbUtils_GetFlag(IDxcPdbUtils *self, UINT32 uIndex, BSTR *pResult) { return COM_CALL(self, 8, HRESULT(__stdcall*)(IDxcPdbUtils*, UINT32, BSTR*), self, uIndex, pResult); }
static inline HRESULT IDxcPdbUtils_GetArgCount(IDxcPdbUtils *self, UINT32 *pCount) { return COM_CALL(self, 9, HRESULT(__stdcall*)(IDxcPdbUtils*, UINT32*), self, pCount); }
static inline HRESULT IDxcPdbUtils_GetArg(IDxcPdbUtils *self, UINT32 uIndex, BSTR *pResult) { return COM_CALL(self, 10, HRESULT(__stdcall*)(IDxcPdbUtils*, UINT32, BSTR*), self, uIndex, pResult); }
static inline HRESULT IDxcPdbUtils_GetArgPairCount(IDxcPdbUtils *self, UINT32 *pCount) { return COM_CALL(self, 11, HRESULT(__stdcall*)(IDxcPdbUtils*, UINT32*), self, pCount); }
static inline HRESULT IDxcPdbUtils_GetArgPair(IDxcPdbUtils *self, UINT32 uIndex, BSTR *pName, BSTR *pValue) { return COM_CALL(self, 12, HRESULT(__stdcall*)(IDxcPdbUtils*, UINT32, BSTR*, BSTR*), self, uIndex, pName, pValue); }
static inline HRESULT IDxcPdbUtils_GetDefineCount(IDxcPdbUtils *self, UINT32 *pCount) { return COM_CALL(self, 13, HRESULT(__stdcall*)(IDxcPdbUtils*, UINT32*), self, pCount); }
static inline HRESULT IDxcPdbUtils_GetDefine(IDxcPdbUtils *self, UINT32 uIndex, BSTR *pResult) { return COM_CALL(self, 14, HRESULT(__stdcall*)(IDxcPdbUtils*, UINT32, BSTR*), self, uIndex, pResult); }
static inline HRESULT IDxcPdbUtils_GetTargetProfile(IDxcPdbUtils *self, BSTR *pResult) { return COM_CALL(self, 15, HRESULT(__stdcall*)(IDxcPdbUtils*, BSTR*), self, pResult); }
static inline HRESULT IDxcPdbUtils_GetEntryPoint(IDxcPdbUtils *self, BSTR *pResult) { return COM_CALL(self, 16, HRESULT(__stdcall*)(IDxcPdbUtils*, BSTR*), self, pResult); }
static inline HRESULT IDxcPdbUtils_GetMainFileName(IDxcPdbUtils *self, BSTR *pResult) { return COM_CALL(self, 17, HRESULT(__stdcall*)(IDxcPdbUtils*, BSTR*), self, pResult); }
static inline HRESULT IDxcPdbUtils_GetHash(IDxcPdbUtils *self, IDxcBlob **ppResult) { return COM_CALL(self, 18, HRESULT(__stdcall*)(IDxcPdbUtils*, IDxcBlob**), self, ppResult); }
static inline HRESULT IDxcPdbUtils_GetName(IDxcPdbUtils *self, BSTR *pResult) { return COM_CALL(self, 19, HRESULT(__stdcall*)(IDxcPdbUtils*, BSTR*), self, pResult); }
static inline BOOL    IDxcPdbUtils_IsFullPDB(IDxcPdbUtils *self) { return COM_CALL(self, 20, BOOL(__stdcall*)(IDxcPdbUtils*), self); }
static inline HRESULT IDxcPdbUtils_GetFullPDB(IDxcPdbUtils *self, IDxcBlob **ppFullPDB) { return COM_CALL(self, 21, HRESULT(__stdcall*)(IDxcPdbUtils*, IDxcBlob**), self, ppFullPDB); }
static inline HRESULT IDxcPdbUtils_GetVersionInfo(IDxcPdbUtils *self, IDxcVersionInfo **ppVersionInfo) { return COM_CALL(self, 22, HRESULT(__stdcall*)(IDxcPdbUtils*, IDxcVersionInfo**), self, ppVersionInfo); }
static inline HRESULT IDxcPdbUtils_SetCompiler(IDxcPdbUtils *self, IDxcCompiler3 *pCompiler) { return COM_CALL(self, 23, HRESULT(__stdcall*)(IDxcPdbUtils*, IDxcCompiler3*), self, pCompiler); }
static inline HRESULT IDxcPdbUtils_CompileForFullPDB(IDxcPdbUtils *self, IDxcResult **ppResult) { return COM_CALL(self, 24, HRESULT(__stdcall*)(IDxcPdbUtils*, IDxcResult**), self, ppResult); }
static inline HRESULT IDxcPdbUtils_OverrideArgs(IDxcPdbUtils *self, DxcArgPair *pArgPairs, UINT32 uNumArgPairs) { return COM_CALL(self, 25, HRESULT(__stdcall*)(IDxcPdbUtils*, DxcArgPair*, UINT32), self, pArgPairs, uNumArgPairs); }
static inline HRESULT IDxcPdbUtils_OverrideRootSignature(IDxcPdbUtils *self, const WCHAR *pRootSignature) { return COM_CALL(self, 26, HRESULT(__stdcall*)(IDxcPdbUtils*, const WCHAR*), self, pRootSignature); }

static inline HRESULT IDxcPdbUtils2_QueryInterface(IDxcPdbUtils2 *self, REFIID riid, void **ppv) { return COM_CALL(self, 0, HRESULT(__stdcall*)(IDxcPdbUtils2*, REFIID, void**), self, riid, ppv); }
static inline ULONG   IDxcPdbUtils2_AddRef(IDxcPdbUtils2 *self) { return COM_CALL(self, 1, ULONG(__stdcall*)(IDxcPdbUtils2*), self); }
static inline ULONG   IDxcPdbUtils2_Release(IDxcPdbUtils2 *self) { return COM_CALL(self, 2, ULONG(__stdcall*)(IDxcPdbUtils2*), self); }
static inline HRESULT IDxcPdbUtils2_Load(IDxcPdbUtils2 *self, IDxcBlob *pPdbOrDxil) { return COM_CALL(self, 3, HRESULT(__stdcall*)(IDxcPdbUtils2*, IDxcBlob*), self, pPdbOrDxil); }
static inline HRESULT IDxcPdbUtils2_GetSourceCount(IDxcPdbUtils2 *self, UINT32 *pCount) { return COM_CALL(self, 4, HRESULT(__stdcall*)(IDxcPdbUtils2*, UINT32*), self, pCount); }
static inline HRESULT IDxcPdbUtils2_GetSource(IDxcPdbUtils2 *self, UINT32 uIndex, IDxcBlobEncoding **ppResult) { return COM_CALL(self, 5, HRESULT(__stdcall*)(IDxcPdbUtils2*, UINT32, IDxcBlobEncoding**), self, uIndex, ppResult); }
static inline HRESULT IDxcPdbUtils2_GetSourceName(IDxcPdbUtils2 *self, UINT32 uIndex, IDxcBlobWide **ppResult) { return COM_CALL(self, 6, HRESULT(__stdcall*)(IDxcPdbUtils2*, UINT32, IDxcBlobWide**), self, uIndex, ppResult); }
static inline HRESULT IDxcPdbUtils2_GetLibraryPDBCount(IDxcPdbUtils2 *self, UINT32 *pCount) { return COM_CALL(self, 7, HRESULT(__stdcall*)(IDxcPdbUtils2*, UINT32*), self, pCount); }
static inline HRESULT IDxcPdbUtils2_GetLibraryPDB(IDxcPdbUtils2 *self, UINT32 uIndex, IDxcPdbUtils2 **ppOutPdbUtils, IDxcBlobWide **ppLibraryName) { return COM_CALL(self, 8, HRESULT(__stdcall*)(IDxcPdbUtils2*, UINT32, IDxcPdbUtils2**, IDxcBlobWide**), self, uIndex, ppOutPdbUtils, ppLibraryName); }
static inline HRESULT IDxcPdbUtils2_GetFlagCount(IDxcPdbUtils2 *self, UINT32 *pCount) { return COM_CALL(self, 9, HRESULT(__stdcall*)(IDxcPdbUtils2*, UINT32*), self, pCount); }
static inline HRESULT IDxcPdbUtils2_GetFlag(IDxcPdbUtils2 *self, UINT32 uIndex, IDxcBlobWide **ppResult) { return COM_CALL(self, 10, HRESULT(__stdcall*)(IDxcPdbUtils2*, UINT32, IDxcBlobWide**), self, uIndex, ppResult); }
static inline HRESULT IDxcPdbUtils2_GetArgCount(IDxcPdbUtils2 *self, UINT32 *pCount) { return COM_CALL(self, 11, HRESULT(__stdcall*)(IDxcPdbUtils2*, UINT32*), self, pCount); }
static inline HRESULT IDxcPdbUtils2_GetArg(IDxcPdbUtils2 *self, UINT32 uIndex, IDxcBlobWide **ppResult) { return COM_CALL(self, 12, HRESULT(__stdcall*)(IDxcPdbUtils2*, UINT32, IDxcBlobWide**), self, uIndex, ppResult); }
static inline HRESULT IDxcPdbUtils2_GetArgPairCount(IDxcPdbUtils2 *self, UINT32 *pCount) { return COM_CALL(self, 13, HRESULT(__stdcall*)(IDxcPdbUtils2*, UINT32*), self, pCount); }
static inline HRESULT IDxcPdbUtils2_GetArgPair(IDxcPdbUtils2 *self, UINT32 uIndex, IDxcBlobWide **ppName, IDxcBlobWide **ppValue) { return COM_CALL(self, 14, HRESULT(__stdcall*)(IDxcPdbUtils2*, UINT32, IDxcBlobWide**, IDxcBlobWide**), self, uIndex, ppName, ppValue); }
static inline HRESULT IDxcPdbUtils2_GetDefineCount(IDxcPdbUtils2 *self, UINT32 *pCount) { return COM_CALL(self, 15, HRESULT(__stdcall*)(IDxcPdbUtils2*, UINT32*), self, pCount); }
static inline HRESULT IDxcPdbUtils2_GetDefine(IDxcPdbUtils2 *self, UINT32 uIndex, IDxcBlobWide **ppResult) { return COM_CALL(self, 16, HRESULT(__stdcall*)(IDxcPdbUtils2*, UINT32, IDxcBlobWide**), self, uIndex, ppResult); }
static inline HRESULT IDxcPdbUtils2_GetTargetProfile(IDxcPdbUtils2 *self, IDxcBlobWide **ppResult) { return COM_CALL(self, 17, HRESULT(__stdcall*)(IDxcPdbUtils2*, IDxcBlobWide**), self, ppResult); }
static inline HRESULT IDxcPdbUtils2_GetEntryPoint(IDxcPdbUtils2 *self, IDxcBlobWide **ppResult) { return COM_CALL(self, 18, HRESULT(__stdcall*)(IDxcPdbUtils2*, IDxcBlobWide**), self, ppResult); }
static inline HRESULT IDxcPdbUtils2_GetMainFileName(IDxcPdbUtils2 *self, IDxcBlobWide **ppResult) { return COM_CALL(self, 19, HRESULT(__stdcall*)(IDxcPdbUtils2*, IDxcBlobWide**), self, ppResult); }
static inline HRESULT IDxcPdbUtils2_GetHash(IDxcPdbUtils2 *self, IDxcBlob **ppResult) { return COM_CALL(self, 20, HRESULT(__stdcall*)(IDxcPdbUtils2*, IDxcBlob**), self, ppResult); }
static inline HRESULT IDxcPdbUtils2_GetName(IDxcPdbUtils2 *self, IDxcBlobWide **ppResult) { return COM_CALL(self, 21, HRESULT(__stdcall*)(IDxcPdbUtils2*, IDxcBlobWide**), self, ppResult); }
static inline HRESULT IDxcPdbUtils2_GetVersionInfo(IDxcPdbUtils2 *self, IDxcVersionInfo **ppVersionInfo) { return COM_CALL(self, 22, HRESULT(__stdcall*)(IDxcPdbUtils2*, IDxcVersionInfo**), self, ppVersionInfo); }
static inline HRESULT IDxcPdbUtils2_GetCustomToolchainID(IDxcPdbUtils2 *self, UINT32 *pID) { return COM_CALL(self, 23, HRESULT(__stdcall*)(IDxcPdbUtils2*, UINT32*), self, pID); }
static inline HRESULT IDxcPdbUtils2_GetCustomToolchainData(IDxcPdbUtils2 *self, IDxcBlob **ppBlob) { return COM_CALL(self, 24, HRESULT(__stdcall*)(IDxcPdbUtils2*, IDxcBlob**), self, ppBlob); }
static inline HRESULT IDxcPdbUtils2_GetWholeDxil(IDxcPdbUtils2 *self, IDxcBlob **ppResult) { return COM_CALL(self, 25, HRESULT(__stdcall*)(IDxcPdbUtils2*, IDxcBlob**), self, ppResult); }
static inline BOOL    IDxcPdbUtils2_IsFullPDB(IDxcPdbUtils2 *self) { return COM_CALL(self, 26, BOOL(__stdcall*)(IDxcPdbUtils2*), self); }
static inline BOOL    IDxcPdbUtils2_IsPDBRef(IDxcPdbUtils2 *self) { return COM_CALL(self, 27, BOOL(__stdcall*)(IDxcPdbUtils2*), self); }

// --- Interface IDs ----------------------------------------------------------
DEFINE_GUID(IID_IDxcBlob,                 0x8ba5fb08, 0x5195, 0x40e2, 0xac, 0x58, 0x0d, 0x98, 0x9c, 0x3a, 0x01, 0x02);
DEFINE_GUID(IID_IDxcBlobEncoding,         0x7241d424, 0x2646, 0x4191, 0x97, 0xc0, 0x98, 0xe9, 0x6e, 0x42, 0xfc, 0x68);
DEFINE_GUID(IID_IDxcBlobWide,             0xa3f84eab, 0x0faa, 0x497e, 0xa3, 0x9c, 0xee, 0x6e, 0xd6, 0x0b, 0x2d, 0x84);
DEFINE_GUID(IID_IDxcBlobUtf8,             0x3da636c9, 0xba71, 0x4024, 0xa3, 0x01, 0x30, 0xcb, 0xf1, 0x25, 0x30, 0x5b);
DEFINE_GUID(IID_IDxcIncludeHandler,       0x7f61fc7d, 0x950d, 0x467f, 0xb3, 0xe3, 0x3c, 0x02, 0xfb, 0x49, 0x18, 0x7c);
DEFINE_GUID(IID_IDxcCompilerArgs,         0x73effe2a, 0x70dc, 0x45f8, 0x96, 0x90, 0xef, 0xf6, 0x4c, 0x02, 0x42, 0x9d);
DEFINE_GUID(IID_IDxcLibrary,              0xe5204dc7, 0xd18c, 0x4c3c, 0xbd, 0xfb, 0x85, 0x16, 0x73, 0x98, 0x0f, 0xe7);
DEFINE_GUID(IID_IDxcOperationResult,      0xcedb484a, 0xd4e9, 0x445a, 0xb9, 0x91, 0xca, 0x21, 0xca, 0x15, 0x7d, 0xc2);
DEFINE_GUID(IID_IDxcCompiler,             0x8c210bf3, 0x011f, 0x4422, 0x8d, 0x70, 0x6f, 0x9a, 0xcb, 0x8d, 0xb6, 0x17);
DEFINE_GUID(IID_IDxcCompiler2,            0xa005a9d9, 0xb8bb, 0x4594, 0xb5, 0xc9, 0x0e, 0x63, 0x3b, 0xec, 0x4d, 0x37);
DEFINE_GUID(IID_IDxcCompiler3,            0x228b4687, 0x5a6a, 0x4730, 0x90, 0x0c, 0x97, 0x02, 0xb2, 0x20, 0x3f, 0x54);
DEFINE_GUID(IID_IDxcLinker,               0xf1b5be2a, 0x62dd, 0x4327, 0xa1, 0xc2, 0x42, 0xac, 0x1e, 0x1e, 0x78, 0xe6);
DEFINE_GUID(IID_IDxcUtils,                0x4605c4cb, 0x2019, 0x492a, 0xad, 0xa4, 0x65, 0xf2, 0x0b, 0xb7, 0xd6, 0x7f);
DEFINE_GUID(IID_IDxcResult,               0x58346cda, 0xdde7, 0x4497, 0x94, 0x61, 0x6f, 0x87, 0xaf, 0x5e, 0x06, 0x59);
DEFINE_GUID(IID_IDxcExtraOutputs,         0x319b37a2, 0xa5c2, 0x494a, 0xa5, 0xde, 0x48, 0x01, 0xb2, 0xfa, 0xf9, 0x89);
DEFINE_GUID(IID_IDxcValidator,            0xa6e82bd2, 0x1fd7, 0x4826, 0x98, 0x11, 0x28, 0x57, 0xe7, 0x97, 0xf4, 0x9a);
DEFINE_GUID(IID_IDxcValidator2,           0x458e1fd1, 0xb1b2, 0x4750, 0xa6, 0xe1, 0x9c, 0x10, 0xf0, 0x3b, 0xed, 0x92);
DEFINE_GUID(IID_IDxcContainerBuilder,     0x334b1f50, 0x2292, 0x4b35, 0x99, 0xa1, 0x25, 0x58, 0x8d, 0x8c, 0x17, 0xfe);
DEFINE_GUID(IID_IDxcAssembler,            0x091f7a26, 0x1c1f, 0x4948, 0x90, 0x4b, 0xe6, 0xe3, 0xa8, 0xa7, 0x71, 0xd5);
DEFINE_GUID(IID_IDxcContainerReflection,  0xd2c21b26, 0x8350, 0x4bdc, 0x97, 0x6a, 0x33, 0x1c, 0xe6, 0xf4, 0xc5, 0x4c);
DEFINE_GUID(IID_IDxcOptimizerPass,        0xae2cd79f, 0xcc22, 0x453f, 0x9b, 0x6b, 0xb1, 0x24, 0xe7, 0xa5, 0x20, 0x4c);
DEFINE_GUID(IID_IDxcOptimizer,            0x25740e2e, 0x9cba, 0x401b, 0x91, 0x19, 0x4f, 0xb4, 0x2f, 0x39, 0xf2, 0x70);
DEFINE_GUID(IID_IDxcVersionInfo,          0xb04f5b50, 0x2059, 0x4f12, 0xa8, 0xff, 0xa1, 0xe0, 0xcd, 0xe1, 0xcc, 0x7e);
DEFINE_GUID(IID_IDxcVersionInfo2,         0xfb6904c4, 0x42f0, 0x4b62, 0x9c, 0x46, 0x98, 0x3a, 0xf7, 0xda, 0x7c, 0x83);
DEFINE_GUID(IID_IDxcVersionInfo3,         0x5e13e843, 0x9d25, 0x473c, 0x9a, 0xd2, 0x03, 0xb2, 0xd0, 0xb4, 0x4b, 0x1e);
DEFINE_GUID(IID_IDxcPdbUtils,             0xe6c9647e, 0x9d6a, 0x4c3b, 0xb9, 0x4c, 0x52, 0x4b, 0x5a, 0x6c, 0x34, 0x3d);
DEFINE_GUID(IID_IDxcPdbUtils2,            0x4315d938, 0xf369, 0x4f93, 0x95, 0xa2, 0x25, 0x20, 0x17, 0xcc, 0x38, 0x07);

// --- Class IDs --------------------------------------------------------------
DEFINE_GUID(CLSID_DxcCompiler,            0x73e22d93, 0xe6ce, 0x47f3, 0xb5, 0xbf, 0xf0, 0x66, 0x4f, 0x39, 0xc1, 0xb0);
DEFINE_GUID(CLSID_DxcLinker,              0xef6a8087, 0xb0ea, 0x4d56, 0x9e, 0x45, 0xd0, 0x7e, 0x1a, 0x8b, 0x78, 0x06);
DEFINE_GUID(CLSID_DxcDiaDataSource,       0xcd1f6b73, 0x2ab0, 0x484d, 0x8e, 0xdc, 0xeb, 0xe7, 0xa4, 0x3c, 0xa0, 0x9f);
DEFINE_GUID(CLSID_DxcCompilerArgs,        0x3e56ae82, 0x224d, 0x470f, 0xa1, 0xa1, 0xfe, 0x30, 0x16, 0xee, 0x9f, 0x9d);
DEFINE_GUID(CLSID_DxcLibrary,             0x6245d6af, 0x66e0, 0x48fd, 0x80, 0xb4, 0x4d, 0x27, 0x17, 0x96, 0x74, 0x8c);
DEFINE_GUID(CLSID_DxcValidator,           0x8ca3e215, 0xf728, 0x4cf3, 0x8c, 0xdd, 0x88, 0xaf, 0x91, 0x75, 0x87, 0xa1);
DEFINE_GUID(CLSID_DxcAssembler,           0xd728db68, 0xf903, 0x4f80, 0x94, 0xcd, 0xdc, 0xcf, 0x76, 0xec, 0x71, 0x51);
DEFINE_GUID(CLSID_DxcContainerReflection, 0xb9f54489, 0x55b8, 0x400c, 0xba, 0x3a, 0x16, 0x75, 0xe4, 0x72, 0x8b, 0x91);
DEFINE_GUID(CLSID_DxcOptimizer,           0xae2cd79f, 0xcc22, 0x453f, 0x9b, 0x6b, 0xb1, 0x24, 0xe7, 0xa5, 0x20, 0x4c);
DEFINE_GUID(CLSID_DxcContainerBuilder,    0x94134294, 0x411f, 0x4574, 0xb4, 0xd0, 0x87, 0x41, 0xe2, 0x52, 0x40, 0xd2);
DEFINE_GUID(CLSID_DxcPdbUtils,            0x54621dfb, 0xf2ce, 0x457e, 0xae, 0x8c, 0xec, 0x35, 0x5f, 0xae, 0xec, 0x7c);
#define CLSID_DxcUtils CLSID_DxcLibrary

#endif /* __DXC_API_C__ */
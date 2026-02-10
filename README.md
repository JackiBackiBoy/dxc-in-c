# dxc-in-c
C bindings for [DirectX Shader Compiler][] (DXC).

The bindings target DXC version **1.8.2505.32**. Microsoft guarantees that COM interfaces use stable IIDs and CLSIDs across versions, meaning that the bindings remain compatible with newer DXC versions. Newer versions may
introduce additional interfaces that may not be exposed by these bindings.

[DirectX Shader Compiler]: https://github.com/microsoft/DirectXShaderCompiler

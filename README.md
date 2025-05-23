<p align="center">
  <img src="https://raw.githubusercontent.com/AcademySoftwareFoundation/MaterialX/main/documents/Images/MaterialXLogo.png" height="170" />
</p>

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://github.com/AcademySoftwareFoundation/MaterialX/blob/main/LICENSE)
[![Version](https://img.shields.io/github/v/release/AcademySoftwareFoundation/MaterialX)](https://github.com/AcademySoftwareFoundation/MaterialX/releases/latest)
[![Build Status](https://github.com/AcademySoftwareFoundation/MaterialX/workflows/main/badge.svg)](https://github.com/AcademySoftwareFoundation/MaterialX/actions)
[![CII Best Practices](https://bestpractices.coreinfrastructure.org/projects/6025/badge)](https://bestpractices.coreinfrastructure.org/projects/6025)

## Introduction

MaterialX is an open standard for representing rich material and look-development content in computer graphics, enabling its platform-independent description and exchange across applications and renderers.  Launched at [Industrial Light & Magic](https://www.ilm.com/) in 2012, MaterialX has been a key technology in their feature films and real-time experiences since _Star Wars: The Force Awakens_ and _Millennium Falcon: Smugglers Run_.  The project was released as open source in 2017, with companies including Sony Pictures Imageworks, Pixar, Autodesk, Adobe, and SideFX contributing to its ongoing development.  In 2021, MaterialX became the seventh hosted project of the [Academy Software Foundation](https://www.aswf.io/).

## Quick Start for Developers

- Download the latest version of the [CMake](https://cmake.org/) build system.
- Point CMake to the root of the MaterialX library and generate C++ projects for your platform and compiler.
- Select the `MATERIALX_BUILD_PYTHON` option to build Python bindings.
- Select the `MATERIALX_BUILD_VIEWER` option to build the [MaterialX Viewer](https://github.com/AcademySoftwareFoundation/MaterialX/blob/main/documents/DeveloperGuide/Viewer.md).
- Select the `MATERIALX_BUILD_GRAPH_EDITOR` option to build the [MaterialX Graph Editor](https://github.com/AcademySoftwareFoundation/MaterialX/blob/main/documents/DeveloperGuide/GraphEditor.md). 

## Supported Platforms

The MaterialX codebase requires a compiler with support for C++17, and can be built with any of the following:

- Microsoft Visual Studio 2017 or newer
- GCC 8 or newer
- Clang 5 or newer

The Python bindings for MaterialX are based on [PyBind11](https://github.com/pybind/pybind11), and support Python versions 3.9 and greater.

## MaterialX Viewer

The [MaterialX Viewer](documents/DeveloperGuide/Viewer.md) leverages shader generation to build GLSL shaders from MaterialX graphs, rendering the results using the NanoGUI framework.

**Figure 1:** Procedural and uniform materials in the MaterialX viewer
<p float="left">
  <img title="Standard Surface Marble material"
       src="https://raw.githubusercontent.com/AcademySoftwareFoundation/MaterialX/main/documents/Images/MaterialXView_Marble.png"
       width="24%" />
  <img title="Standard Surface Copper material"
       src="https://raw.githubusercontent.com/AcademySoftwareFoundation/MaterialX/main/documents/Images/MaterialXView_Copper.png"
       width="24%" />
  <img title="Standard Surface Plastic material"
       src="https://raw.githubusercontent.com/AcademySoftwareFoundation/MaterialX/main/documents/Images/MaterialXView_Plastic.png"
       width="24%" />
  <img title="Standard Surface Carpaint material"
       src="https://raw.githubusercontent.com/AcademySoftwareFoundation/MaterialX/main/documents/Images/MaterialXView_Carpaint.png"
       width="24%" />
</p>

**Figure 2:** Textured, color-space-managed materials in the MaterialX viewer
<p float="left">
  <img title="Standard Surface Tiled Brass material"
       src="https://raw.githubusercontent.com/AcademySoftwareFoundation/MaterialX/main/documents/Images/MaterialXView_TiledBrass.png"
       width="49%" />
  <img title="Standard Surface Tiled Wood material"
       src="https://raw.githubusercontent.com/AcademySoftwareFoundation/MaterialX/main/documents/Images/MaterialXView_TiledWood.png"
       width="49%" />
</p>

## Open Chess Set

The Open Chess Set is an open reference asset, consisting of a [MaterialX file](resources/Materials/Examples/StandardSurface/standard_surface_chess_set.mtlx) in the Standard Surface shading model and a [geometry file](resources/Geometry) in the glTF format.  It was authored by Moeen Sayed and Mujtaba Sayed, and was contributed to the MaterialX project by Side Effects.

**Figure 3:** The Open Chess Set, rendered in Arnold for Maya
![The Open Chess Set rendered in Arnold for Maya](https://raw.githubusercontent.com/AcademySoftwareFoundation/MaterialX/main/documents/Images/OpenChessSet_Arnold_01.png)

**Figure 4:** The Open Chess Set, rendered in Karma XPU for Houdini
![The Open Chess Set rendered in Karma XPU for Houdini](https://raw.githubusercontent.com/AcademySoftwareFoundation/MaterialX/main/documents/Images/OpenChessSet_Karma_01.png)

## Pre-Built Binaries

The following packages contain pre-built binaries for the latest release, including the MaterialX viewer, Python libraries, and example assets:

- [Microsoft Windows (Visual Studio 2022, Python 3.13)](https://github.com/AcademySoftwareFoundation/MaterialX/releases/latest/download/MaterialX_Windows_VS2022_x64_Python313.zip)
- [MacOS (Xcode 16, Python 3.13)](https://github.com/AcademySoftwareFoundation/MaterialX/releases/latest/download/MaterialX_MacOS_Xcode_16_Python313.zip)
- [Linux (GCC 14, Python 3.13)](https://github.com/AcademySoftwareFoundation/MaterialX/releases/latest/download/MaterialX_Linux_GCC_14_Python313.zip)

## Additional Resources

- The [Developer Guide](http://www.materialx.org/docs/api/index.html) contains a developer-oriented overview of MaterialX with Build and API documentation.
- The [Python Scripts](python/Scripts) folder contains standalone examples of MaterialX Python code.
- The [JavaScript](javascript) folder contains details on building JavaScript bindings for MaterialX.
- Presentations at [ASWF Open Source Days](https://materialx.org/assets/ASWF_OSD2024_MaterialX_Final.pdf) and the [SIGGRAPH Physically Based Shading Course](https://blog.selfshadow.com/publications/s2020-shading-course/#materialx) provide details on the roadmap for MaterialX development.

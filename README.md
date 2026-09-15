# VoidEngine

A game engine made specifically for desktop platforms.

## Build instructions

Dependencies:
- git
- premake5
- cmake

Building:
1. Run in your project: 
```bash
git submodule add https://github.com/WhoTFTookShadowFlare/VoidEngine VoidEngine --recurse-submodules
```

2. In your premake5.lua add the following:
```lua
-- At the start of your file
local VoidEngine = include("VoidEngine")

-- In your workspace
VoidEngine.addVoidEngine()

-- In your project
VoidEngine.useVoidEngine()
```

3. Run premake5 normally

## Usage
TODO: Make the example repo

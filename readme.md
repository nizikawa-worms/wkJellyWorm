# wkJellyWorm
_A dead ProjectX clone for Worms Armageddon 3.8.1_

This module hooks into most gameplay classes and exposes their functionality and internal structure to LUA scripts. It enables player to alter gameplay physics, object behaviour and add custom weapons.

### Features:
- Hooked all CTask and CGameTask classes - both member variables and virtual table methods
- Basic LUA scripting
- Support for adding more weapons to the game
- An experimental OpenGL renderer (unfinished)
- Basic support for online play

## Usage:
Host a LAN lobby and type: /enable test 
This will enable a test package with custom airstrike weapons. Type /help for more commands.

## Building:
Use cmake Release or RelWithDebInfo build types with MSVC compiler. Debug build types will not work due to custom calling conventions in some hooked functions.

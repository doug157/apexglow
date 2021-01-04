#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <vector>
#include <cstdint>
#include <string>
#include <detours.h>
#include <mutex>
#include "apex.h"

#define ENTITY_LIST 0x18c7af8
#define ENTITY_TYPE 0x560
#define CLIENT_STATE 0x127c0e0
#define SIGNON_STATE 0x127c178
#define LEVEL_NAME 0x127c290
#define GLOW 0x3C0
#define GLOW_DURATION 0x310
#define GLOW_RANGE 0x33C
#define HIGHLIGHT_CONTEXT 0x350
#define COLOR 0x1D0

#define BRIGHTNESS 0.1f
#define SRGB RGB(195, 0, 220)

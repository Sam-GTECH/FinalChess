#pragma once

#ifdef SFML_STATIC
#include <SFML/Graphics.hpp>
#endif

#include <iostream>
#include <vector>
#include <string>
#ifdef SFML_STATIC
#include <fstream>
#include <windowsx.h>

#define SCALE 4

#define OFFSET 7*SCALE
#endif
#include <windows.h>

#define CONSOLE GetStdHandle(STD_OUTPUT_HANDLE)

#include "resource.h"

using namespace std;

#include "utils.h"

#include "piece.h"
#include "piece_king.h"
#include "piece_knight.h"
#include "piece_pawn.h"
#ifndef _LITE
#include "piece_bishop.h"
#include "piece_queen.h"
#include "piece_rook.h"
#endif

#if defined(LOG)
#include "logger.h"
#endif

#include "board.h"

#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DEBUG_NEW
#endif

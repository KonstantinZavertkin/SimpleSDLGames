#ifndef _COMMON_TYPES_H_
#define _COMMON_TYPES_H_

//! First - Line index
//! Second - Column index
using TCoords = std::pair<int, int>;

constexpr TCoords vectorUp = { -1, 0 };
constexpr TCoords vectorDown = { 1, 0 };
constexpr TCoords vectorLeft = { 0, -1 };
constexpr TCoords vectorRight = { 0, 1 };

#endif

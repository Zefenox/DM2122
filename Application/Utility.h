#pragma once
#include "Mtx44.h"
#include "Source/Vertex.h"

Position operator*(const Mtx44& lhs, const Position& rhs);
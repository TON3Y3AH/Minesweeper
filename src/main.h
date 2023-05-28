#pragma once
#include "Block.h"

bool isInBoard(int r, int c);
bool isAbleRightclick(int r, int c);//if can be flaged. if has been opened, we cant flag it
bool isAbleLeftclick(int r, int c);//if can be opened. if has been opened and flaged, we cant open it

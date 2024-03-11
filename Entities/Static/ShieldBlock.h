#pragma once

#include "BoundBlock.h"
#include <memory>

class ShieldBlock : public BoundBlock {

public:
    ShieldBlock(int x, int y, shared_ptr<Handler> handler) : BoundBlock(x, y, handler) {}
    ~ShieldBlock(){};
};
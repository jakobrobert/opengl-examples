#pragma once

#include "core/Renderer.hpp"

class EmptyRenderer : public Renderer
{
public:
    virtual void onInit() override;
    virtual void onDestroy() override {}
    virtual void onDraw() override;
};

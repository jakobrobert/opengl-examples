#pragma once

#include <core/Renderer.hpp>

class EmptyRenderer : public Renderer
{
public:
    virtual bool onInit() override;
    virtual void onDestroy() override {}
    virtual void onResize(int width, int height) override {}
    virtual void onUpdate(float time) override {}
    virtual void onDraw() override;
};

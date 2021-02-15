#pragma once

#include <core/Renderer.hpp>

class EmptyRenderer : public Renderer
{
public:
    virtual bool onInit() override;
    virtual void onDestroy() override {}
    virtual void onResize(int width, int height) override;
    virtual void onUpdate(const class Window& window, float frameTime) override {}
    virtual void onDraw() override;
};

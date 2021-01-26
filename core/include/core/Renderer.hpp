#pragma once

class Renderer
{
public:
    virtual bool onInit() = 0;
    virtual void onDestroy() = 0;
    virtual void onResize(int width, int height) = 0;
    virtual void onUpdate(float time) = 0;
    virtual void onDraw() = 0;
};

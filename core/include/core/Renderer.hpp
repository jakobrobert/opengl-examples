#pragma once

class Renderer
{
public:
    virtual bool onInit() = 0;
    virtual void onDestroy() = 0;
    virtual void onDraw() = 0;
};

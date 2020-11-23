#pragma once

// TODO: bool to check for success
class Renderer {
public:
    virtual void onInit() = 0;
    virtual void onDestroy() = 0;
    virtual void onDraw() = 0;
};

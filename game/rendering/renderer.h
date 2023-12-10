#pragma once

typedef struct renderer {
    // TODO: add rendering config like windows sizes, effects, post-processing
    // draw calls, etc.
    (void*)drawTexture();
} renderer;

extern renderer rend;

void renderer_init();

void renderer_free();
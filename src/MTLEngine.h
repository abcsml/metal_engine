#pragma once

// #import <MetalKit/MetalKit.h>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

class MTLEngine {
public:
    static void init(MTL::Device* device);

    static MTL::Device* getDevice();
    static MTL::Library* getLibrary();
    static MTL::CommandQueue* getCommandQueue();
    // static CA::MetalDrawable* getCurrentDrawable();

private:
    // static void initDefaultLibrary();
    // static void initCommandQueue();

    static MTL::Device* metalDevice_;
    // static MTKView* metalView;
    static MTL::Library* metalDefaultLibrary_;
    static MTL::CommandQueue* metalCommandQueue_;

private:
    MTLEngine() = delete;
};


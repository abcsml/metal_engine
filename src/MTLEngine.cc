#include "MTLEngine.h"
#include <iostream>

MTL::Device* MTLEngine::metalDevice = nullptr;
// MTKView* MTLEngine::metalView = nullptr;
MTL::Library* MTLEngine::metalDefaultLibrary = nullptr;
MTL::CommandQueue* MTLEngine::metalCommandQueue = nullptr;

void MTLEngine::init(MTL::Device* device) {
    std::cout << "MTLEngine init\n";
    metalDevice = device;
    // metalView = metalView;
    assert(metalDevice);
    // assert(metalView);

    metalDefaultLibrary = metalDevice->newDefaultLibrary();
    if(!metalDefaultLibrary){
        std::cerr << "Failed to load default library.";
        std::exit(-1);
    }

    metalCommandQueue = metalDevice->newCommandQueue();
}

MTL::Device* MTLEngine::getDevice() {
    return metalDevice;
}

MTL::Library* MTLEngine::getLibrary() {
    return metalDefaultLibrary;
}

MTL::CommandQueue* MTLEngine::getCommandQueue() {
    return metalCommandQueue;
}

// CA::MetalDrawable* MTLEngine::getCurrentDrawable() {
//     return (__bridge CA::MetalDrawable*) [metalView currentDrawable];
// }

// CA::MetalDrawable* MTLEngine::getNextDrawable() {
//     return (__bridge CA::MetalDrawable*) [metalView nextDrawable];
// }

// void MTLEngine::initDefaultLibrary() {
//     MTLEngine::metalDefaultLibrary = MTLEngine::metalDevice->newDefaultLibrary();
//     if(!MTLEngine::metalDefaultLibrary){
//         std::cerr << "Failed to load default library.";
//         std::exit(-1);
//     }
// }

// void MTLEngine::initCommandQueue() {
//     MTLEngine::metalCommandQueue = MTLEngine::metalDevice->newCommandQueue();
// }

#include "MTLEngine.h"
#include "spdlog/spdlog.h"

MTL::Device* MTLEngine::metalDevice_ = nullptr;
// MTKView* MTLEngine::metalView = nullptr;
MTL::Library* MTLEngine::metalDefaultLibrary_ = nullptr;
MTL::CommandQueue* MTLEngine::metalCommandQueue_ = nullptr;

void MTLEngine::init(MTL::Device* device) {
    spdlog::info("MTLEngine init");
    metalDevice_ = device;
    // metalView = metalView;
    assert(metalDevice_);
    // assert(metalView);

    metalDefaultLibrary_ = metalDevice_->newDefaultLibrary();
    if(!metalDefaultLibrary_){
        spdlog::error("Failed to load default library.");
        std::exit(-1);
    }

    metalCommandQueue_ = metalDevice_->newCommandQueue();
}

MTL::Device* MTLEngine::getDevice() {
    return metalDevice_;
}

MTL::Library* MTLEngine::getLibrary() {
    return metalDefaultLibrary_;
}

MTL::CommandQueue* MTLEngine::getCommandQueue() {
    return metalCommandQueue_;
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

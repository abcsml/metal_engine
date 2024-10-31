#import <AppKit/AppKit.h>
#import "AppDelegate.h"

#import "common.h"
#import "system.h"

#import "Shape.h"

class MySystem: public System {
public:
    void update(CA::MetalDrawable* drawable) {
        PositionUnit* pos = em_->getUnit<PositionUnit>(0);
        pos->data_.x += 0.001;
    };
};

class MyWorld: public World {
public:
    void setup() override {
        spdlog::info("World setup");

        Entity entity = em_.createEntity();
        em_.addUnit(entity, new PositionUnit({0, 0}));

        RenderUnit* ru = Shape::genTriangle();
        ru->useTransform_ = true;
        ru->transformBuffer_ = MTLEngine::getDevice()->newBuffer(
            sizeof(simd::float2),
            MTL::ResourceStorageModeShared
        );
        em_.addUnit(entity, ru);

        // Entity* entity2 = new Entity;
        // entity2->test = new TestUnit();

        addSystem(new RenderSystem);
        addSystem(new MySystem);
    };
};

int main() {
    spdlog::set_level(spdlog::level::trace);

    @autoreleasepool {
        // 初始化App和MTLEngine(在App内部)
        [NSApplication sharedApplication];
        AppDelegate* appDelegate = [AppDelegate alloc];

        // App创建world
        World* world = new MyWorld();
        [appDelegate create:world];

        [NSApp setDelegate:appDelegate];
        [NSApp run];

        delete world;
    }
    return 0;
}

#import <AppKit/AppKit.h>
#import "AppDelegate.h"

#import "common.h"

class MyWorld: public World {
public:
    void draw() override {
    // MyWorld() {
        RenderUnit::VertexData triangle;
        triangle.vertices.push_back(simd::make<simd::float3>(-0.5, -0.5, 0));
        triangle.vertices.push_back(simd::make<simd::float3>(-0.5,  0.5, 0));
        triangle.vertices.push_back(simd::make<simd::float3>( 0.0,  0.0, 0));
        triangle.primitiveType = MTL::PrimitiveTypeTriangle;

        Entity* entity = new Entity;
        entity->test = new TestUnit();
        // entity->render = new RenderUnit(triangle);

        add(entity);

        // Entity* entity2 = new Entity;
        // entity2->test = new TestUnit();

        addSystem(new RenderSystem(getEntities()));
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

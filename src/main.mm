#import <AppKit/AppKit.h>
#import "AppDelegate.h"

#import "common.h"
#import "system.h"

#import "Shape.h"

class MySystem: public System {
private:
    float lasttime = 0;
public:
    bool filter(Entity entity) const override {
        return em_->hasUnit<TransFormUnit>(entity);
    };

    void task(Entity entity) override {
        TransFormUnit* pos = em_->getUnit<TransFormUnit>(entity);
        PhysicUnit* phy = em_->getUnit<PhysicUnit>(entity);
        if (pos->data_.columns[1].z < -0.5) {
            phy->v_.y = -phy->v_.y;
        }
        // float now = em_->getUnit<ClockUnit>(0)->runTime_.count();
        // if (now - lasttime > 1000) {
        //     spdlog::debug("fps: {}", 1/em_->getUnit<ClockUnit>(0)->getDeltaTime());
        //     lasttime = now;
        //     Entity entity = em_->createEntity();
        //     em_->addUnit(entity, new PositionUnit({1, 1}));

        //     RenderUnit* ru = Shape::genTriangle();
        //     ru->useTransform_ = true;
        //     ru->transformBuffer_ = MTLEngine::getDevice()->newBuffer(
        //         sizeof(simd::float2),
        //         MTL::ResourceStorageModeShared
        //     );
        //     em_->addUnit(entity, ru);
        //     em_->addUnit(entity, new PhysicUnit(1, {-0.5, 0}));
        // }

    };
};

class MyWorld: public World {
public:
    void setup() override {
        spdlog::info("World setup");

        // 创建0号entity，存储一些系统资源；
        Entity entity = em_.createEntity();
        em_.addUnit(entity, new ClockUnit);


        entity = em_.createEntity();
        ShapeUnit* shape = new ShapeUnit(Rectangle);
        RenderUnit* ren = new RenderUnit(shape);
        em_.addUnit(entity, shape);
        em_.addUnit(entity, ren);

        TransFormUnit* pos = new TransFormUnit(TransFormUnit({0,0}));
        ren->addTransform(pos);
        em_.addUnit(entity, pos);

        // em_.addUnit(entity, new PhysicUnit);


        // entity = em_.createEntity();
        // em_.addUnit(entity, Shape::genTriangle());

        // Entity* entity2 = new Entity;
        // entity2->test = new TestUnit();
        addSystem(new ClockSystem);

        addSystem(new RenderSystem);
        // addSystem(new RenderUnitUpdateSystem);
        // addSystem(new MySystem);
        // addSystem(new PhysicSystem);
    };
};

int main() {
    spdlog::set_level(spdlog::level::trace);

    // 初始化App和MTLEngine(在App内部)
    [NSApplication sharedApplication];
    AppDelegate* appDelegate = [AppDelegate alloc];

    // App创建world
    World* world = new MyWorld();
    [appDelegate create:world];

    [NSApp setDelegate:appDelegate];
    [NSApp run];

    delete world;

    return 0;
}

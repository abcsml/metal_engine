#import <Cocoa/Cocoa.h>
#import <MetalKit/MetalKit.h>

#import "MTLEngine.h"
#import "World.h"

@interface AppDelegate : NSObject <NSApplicationDelegate, MTKViewDelegate, NSWindowDelegate>
    @property (nonatomic, strong) NSWindow* window;
    @property (nonatomic, strong) id<MTLDevice> device;
    @property (nonatomic, assign) World* viewer;

    // - (instancetype)init:(id<MTLDevice>)device;

    - (void)create:(World *)viewer;
@end
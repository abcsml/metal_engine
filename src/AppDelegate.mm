#import "AppDelegate.h"
// #import <simd/simd.h>

@implementation AppDelegate

// - (instancetype)init:(id<MTLDevice>)device {
//     self = [super init];
//     if (self) {
//         _device = device;
//         // _viewer = viewer;
//     }
//     return self;
// }

- (void)create:(World *)viewer {
    _viewer = viewer;
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // 创建菜单栏
    NSMenu *mainMenu = [[NSMenu alloc] init];
    NSMenuItem *appMenuItem = [[NSMenuItem alloc] init];
    [mainMenu addItem:appMenuItem];
    
    NSMenu *appMenu = [[NSMenu alloc] init];
    NSMenuItem *quitMenuItem = [[NSMenuItem alloc] initWithTitle:@"Quit" action:@selector(terminate:) keyEquivalent:@"q"];
    [appMenu addItem:quitMenuItem];
    [appMenuItem setSubmenu:appMenu];
    
    [NSApp setMainMenu:mainMenu];

    // 创建窗口
    NSRect frame = NSMakeRect(0, 0, 600, 600);
    NSUInteger style = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskMiniaturizable;

    _window = [[NSWindow alloc] initWithContentRect:frame
        styleMask: style
        backing:NSBackingStoreBuffered
        defer:NO];

    _device = MTLCreateSystemDefaultDevice();

    MTKView* view = [[MTKView alloc] initWithFrame:frame
        device:_device];
    [view setDelegate:self];

    [_window setDelegate:self];

    [_window center];
    [_window setContentView:view];
    [_window makeKeyAndOrderFront:NSApp];

    // init engine
    MTLEngine::init((__bridge MTL::Device*) _device, (__bridge CA::MetalLayer*) view.layer);
    // MTLEngine::init((__bridge MTL::Device*) _device);
    // init world
    _viewer->setup();
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

- (BOOL)applicationSupportsSecureRestorableState:(NSApplication *)app {
    return YES;
}

- (void)dealloc {
    // delete _viewer; // Clean up C++ object
    // [super dealloc];
}


- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication {
    (void)theApplication;
    return YES;
}

- (void)mtkView:(MTKView*)view drawableSizeWillChange:(CGSize)size {
    // Window is not resizable
    (void)view;
    (void)size;
}

- (void)drawInMTKView:(MTKView*)view {
    // _viewer->update((__bridge CA::MetalDrawable*) [view currentDrawable]);
    _viewer->update();
}

// window delegate
- (void)windowDidMove:(NSNotification *)notification {
    NSWindow *movedWindow = notification.object;
    NSRect frame = movedWindow.frame;
    // NSLog(@"Window moved to new position: x = %.2f, y = %.2f", frame.origin.x, frame.origin.y);
}

@end
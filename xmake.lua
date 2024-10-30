add_rules("mode.debug", "mode.release")

set_project("MyApp")
set_version("1.0.0")
set_languages("gnuxx17")

add_requires("spdlog")

target("MyApp")
    add_rules("xcode.application")
    set_kind("binary")

    add_includedirs("lib/metal-cpp")

    add_includedirs("src")
    add_files("src/*.mm", "src/*.cc")

    add_files("src/*.metal")
    add_files("src/Info.plist")
    -- add_resources("*.xcassets")

    add_cxflags("-fobjc-arc")  -- Enable ARC (Automatic Reference Counting)

    add_frameworks("Cocoa", "AppKit", "Metal", "MetalKit", "QuartzCore")
    add_packages("spdlog")

    set_targetdir("build")

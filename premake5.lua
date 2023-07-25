workspace "ExExplorer"
    architecture "x64"    
    
    OutputDir = "%{cfg.buildcfg}-%{cfg.architecture}"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    flags
    {
        "MultiProcessorCompile"
    }

    group "Dependencies"
        include "vendor"
    group ""    
    
    include "ExExplorer"


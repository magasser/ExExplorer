project "ExExplorer"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"
    architecture "x64"

    IncludeDir = {}
    IncludeDir["spdlog"] = "../vendor/spdlog/include"
    IncludeDir["glfw"] = "../vendor/glfw/include"
    IncludeDir["imgui"] = "../vendor/imgui"

    targetdir ("bin/" .. OutputDir)
    objdir ("bin-int/" .. OutputDir)    

    pchheader "eepch.h"
    pchsource "src/eepch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp",
    }

    includedirs
    {
        "src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.imgui}",
    }

    links
    {
        "ImGui",
        "GLFW",
		"opengl32.lib"
    }

	filter "configurations:Debug"
        defines "EE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
        defines "EE_RELEASE"
		runtime "Release"
		optimize "speed"

    filter "configurations:Dist"
        defines "EE_DIST"
		runtime "Release"
		optimize "speed"
        symbols "off"

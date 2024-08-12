workspace "MinecraftClone"
    architecture "x64"
    
    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "MinecraftClone"
    location "MinecraftClone"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "%{prj.name}")

    files
    {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h",
        "%{prj.name}/libraries/glad/src/glad.c",
        "%{prj.name}/libraries/stb/stb/stb_image.cpp",
    }

    includedirs
    {
        "%{prj.name}/libraries/glm",
        "%{prj.name}/libraries/glad/include",
        "%{prj.name}/libraries/GLFW/include",
        "%{prj.name}/libraries/glm",
        "%{prj.name}/libraries/stb",
        "%{prj.name}/libraries/entt",
        "%{prj.name}/libraries/fastNoiseLite/include"
    }

    libdirs
    {
        "%{prj.name}/libraries/GLFW/lib",
    }

    links
    {
        "glfw3",
        "opengl32",
    }

    filter "configurations:Debug"
        defines "CP_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "CP_RELEASE"
        optimize "On"

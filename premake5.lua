workspace "lxwindows"
	architecture "x86_64"
	configurations { "Debug", "Release"}

-- shared build
project "lxwindows"
	kind "SharedLib"
	language "C"
	cdialect "c99"
	targetdir "bin"
	includedirs { "include" }
	files { "src/**.c", "include/**.h" }
	
	filter "system:linux"
		links { "X11", "GL", "GLX", "EGL" }
		linkoptions { "-Wl,-rpath,$$ORIGIN" }

	filter "system:windows"
		libdirs { "bin" }
		links { "opengl32", "glu32", "user32", "gdi32", "libEGL" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

include 'examples/basic_window/basic_window.lua'

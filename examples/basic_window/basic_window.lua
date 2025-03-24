project "basic-window"
	kind "ConsoleApp"
	language "C"
	cdialect "c99"
	targetdir "../../bin"
	includedirs { "../../include" }
	files { "basic_window.c" }

	filter "system:linux"
		links { "GL", "lxwindows" }
	filter "system:windows"
		links { "opengl32", "lxwindows" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

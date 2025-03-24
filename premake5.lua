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
   
   links { "X11", "GL", "GLX"}
   linkoptions { "-Wl,-rpath,$$ORIGIN" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

-- static build
project "lxwindows-s"
   kind "StaticLib"
   language "C"
   cdialect "c99"
   targetdir "bin"
   includedirs { "include" }
   files { "src/**.c", "include/**.h" }
   
   links { "X11", "GL", "GLX" }
   
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

include 'examples/x11/x11.lua'

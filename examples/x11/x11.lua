project "x11-example"
   kind "ConsoleApp"
   language "C"
   cdialect "c99"
   targetdir "../../bin"
   includedirs { "../../include" }
   files { "x11.c" }

   links { "GL", "GLEW", "lxwindows" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

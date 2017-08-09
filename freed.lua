workspace "FreeD"
	location "../gen"
	language "C++"
	flags { "C++11"}
	architecture "x86_64"
	
	targetdir ("../build/%{prj.name}/%{cfg.longname}")
	objdir ("../artifacts/%{prj.name}/%{cfg.longname}")
	
	configurations { "Debug", "Release" }
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		targetsuffix "_d"
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
	
	
function use_catch()
	includedirs "../external/catch"
	defines "CATCH_CPP11_OR_GREATER"
end

project "core"
   kind "StaticLib"
   
   includedirs { "core/public" }
   files { "core/**.h", "core/**.cpp" }
   removefiles { "core/tests/**" }
  
	  
function use_core()
	includedirs "core/public"
	links "core"
end


project "console_app"
	kind "ConsoleApp"
	files { "console_app/**.h", "console_app/**.cpp" }
	
	use_core()
	

project "unit_tests"
	kind "ConsoleApp"
	files "*/tests/*.cpp"
	use_catch()
	use_core()
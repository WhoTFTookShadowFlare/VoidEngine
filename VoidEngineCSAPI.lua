project "VoidEngineCSAPI"
	kind "SharedLib"
	language "C#"
	clr "Off"
	csversion "8"
	targetdir(tostring(_MAIN_SCRIPT_DIR) .. "/bin/%{cfg.buildcfg}")

	targetname "VoidEngine"

	files { "cs/**.cs" }


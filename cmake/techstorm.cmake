
function(TS_Add_Packages)
	message(STATUS "Adding Techstorm Packages...")

	CPMAddPackage(
        NAME raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
    ) 

    CPMAddPackage(
        NAME ImGui
	    GIT_REPOSITORY https://github.com/ocornut/imgui.git
	    GIT_TAG v1.91.2
    )

    CPMADDPACKAGE(
        NAME eventpp
        GIT_REPOSITORY https://github.com/wqking/eventpp.git
        GIT_TAG v0.1.3
    )
endfunction()

function(TS_Add_Subdirectory dir) 
    message(STATUS "Adding Subdirectory: ${dir}")

endfunction()
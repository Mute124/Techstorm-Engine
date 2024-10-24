#include "../project/project.h"
#ifdef _DEBUG
	#include <crtdbg.h>
#endif 

void initProject(Project& project, int argc, char* argv[]) {
	project.preInit();
	project.init(argc, argv);
	project.postInit();
}


int main(int argc, char* argv[]) {
#ifdef _DEBUG
	// Enable leak detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Project project = Project();

	initProject(project, argc, argv);

	int projectResult = project.run(argc, argv);
	return projectResult;
}
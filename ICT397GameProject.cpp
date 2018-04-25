#include "Engine.h"

int main(int argc, char* argv[])
{
	Engine ENG;

	if (ENG.Initalise("./Resources/Scripts/startup.lua")){
		ENG.Run();
	}
	else {
		if (DEBUGMODE) std::cerr << "Issue initalising engine. Closing now." << std::endl;
	}

	return 0;
}


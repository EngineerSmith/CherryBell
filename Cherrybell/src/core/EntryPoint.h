#pragma once
#include "core/Core.h"

#ifdef CB_PLATFORM_WINDOWS

extern CherryBell::Application* CherryBell::CreateApplication();

int main(int argc, char* argv) {
	CherryBell::Log::Init();

	CB_PROFILE_BEGIN_SESSION("Startup", "CherryBellProfile_Startup.json");
	auto app = CherryBell::CreateApplication();
	CB_PROFILE_END_SESSION();

	CB_PROFILE_BEGIN_SESSION("Runtime", "CherryBellProfile_Runtime.json");
	app->Run();
	CB_PROFILE_END_SESSION();

	CB_PROFILE_BEGIN_SESSION("Shutdown", "CherryBellProfile_Shutdown.json");
	delete app;
	CB_PROFILE_END_SESSION();
}

#endif

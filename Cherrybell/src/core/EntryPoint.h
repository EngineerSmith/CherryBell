#pragma once
#include "core/Core.h"

#ifdef CB_PLATFORM_WINDOWS

extern CherryBell::Application* CherryBell::CreateApplication();

int main(int argc, char* argv) {
	CherryBell::Log::Init();
	CB_CORE_INFO("Welcome to CherryBell!");

	auto app = CherryBell::CreateApplication();

	CB_CORE_INFO("Running application");
	app->Run();
	delete app;
}

#endif

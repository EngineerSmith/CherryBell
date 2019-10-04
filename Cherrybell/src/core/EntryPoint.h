#pragma once

#ifdef CB_PLATFORM_WINDOWS

extern CherryBell::Application* CherryBell::CreateApplication();

int main(int argc, char* argv) {
	CherryBell::Log::Init();
	CB_CORE_INFO("Welcome to CherryBell!");

	CB_CORE_INFO("Creating application");
	auto app = CherryBell::CreateApplication();

	CB_CORE_INFO("Starting application");
	app->Run();
	delete app;
}

#endif
#pragma once

#ifdef CB_PLATFORM_WINDOWS

extern CherryBell::Application* CherryBell::CreateApplication();

int main(int argc, char* argv) {
	auto app = CherryBell::CreateApplication();
	app->Run();
	delete app;
}

#endif
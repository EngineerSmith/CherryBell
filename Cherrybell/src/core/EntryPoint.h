#pragma once

#ifdef CB_PLATFORM_WINDOWS

extern CherryBell::Application* CherryBell::CreateApplication();

int main(int argc, char* argv) {
	CherryBell::Log::Init();
	CB_CORE_INFO("Initialized logging.");
	int a = 5;
	CB_ERROR("UH OH: {0}", a);

	auto app = CherryBell::CreateApplication();
	app->Run();
	delete app;
}

#endif
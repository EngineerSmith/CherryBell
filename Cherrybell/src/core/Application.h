#pragma once
#include "Core.h"

namespace CherryBell {
	class CB_API Application
	{
	public:
		Application() = default;
		virtual ~Application() = default;

		void Run();
	};

	//To be define in client application - EntryPoint.h
	Application* CreateApplication();
}

#pragma once
#include "Core.h"

namespace CherryBell {
	class CB_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be define in client
	Application* CreateApplication();
}

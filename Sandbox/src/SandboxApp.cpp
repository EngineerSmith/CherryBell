
#include <CherryBell.h>

class Sandbox : public CherryBell::Application {
public:
	Sandbox() {};
	virtual ~Sandbox() {};
};

CherryBell::Application* CherryBell::CreateApplication() {
	return new Sandbox();
}

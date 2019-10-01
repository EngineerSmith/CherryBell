#include <CherryBell.h>

class Sandbox : public CherryBell::Application {
public:
	Sandbox() = default;
	virtual ~Sandbox() = default;
};

CherryBell::Application* CherryBell::CreateApplication() {
	return new Sandbox();
}

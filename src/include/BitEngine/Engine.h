#pragma once

namespace be {

class Engine {
public:
	Engine() = default;
	virtual ~Engine() = default;

	void run();
protected:
	virtual void onInitialize() = 0;
	virtual void onShutdown() = 0;
private:
	void init();
	void loop();
	void close();
};

}

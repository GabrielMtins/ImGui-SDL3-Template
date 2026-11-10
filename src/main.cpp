#include <iostream>

#include <memory>

#include "App.hpp"

void run_app(void) {
	auto app = App::create("Title");

	if(app == nullptr) exit(1);

	app->run();
}

int main(void) {
	if(!SDL_Init(SDL_INIT_VIDEO)) {
		return -1;
	}

	run_app();

	SDL_Quit();

	return 0;
}

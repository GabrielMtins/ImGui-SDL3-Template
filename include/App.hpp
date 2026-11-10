#ifndef APP_HPP
#define APP_HPP

#include <imgui.h>
#include <SDL3/SDL.h>
#include <memory>

class App {
	public:
		static std::unique_ptr<App> create(const char *title);
		~App(void);

		void run(void);

	private:
		SDL_Window *window = NULL;
		SDL_Renderer *renderer = NULL;
		bool quit = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		void processEvents(void);
		void loop(void);
		virtual void step(void);
};

#endif

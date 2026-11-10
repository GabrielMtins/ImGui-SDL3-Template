#include "App.hpp"

#include <cstdlib>

#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

std::unique_ptr<App> App::create(const char *title) {
	auto app = std::make_unique<App>();

	float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());

	app->window = SDL_CreateWindow(
			title, main_scale * 1280.0f, main_scale * 720.0f,
			SDL_WINDOW_RESIZABLE
			);

	if(app->window == NULL) {
		return nullptr;
	}

	app->renderer = SDL_CreateRenderer(
			app->window,
			NULL
			);

	if(app->renderer == NULL) {
		return nullptr;
	}

	SDL_SetRenderVSync(app->renderer, 1);
	SDL_SetWindowPosition(app->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGuiStyle& style = ImGui::GetStyle();
	ImGui::StyleColorsDark();
	style.FrameRounding = 3.0f;
	style.GrabRounding = 3.0f;
    style.FontSizeBase = 16.0f;

	style.ScaleAllSizes(main_scale);
	style.FontScaleDpi = main_scale;

	ImGui_ImplSDL3_InitForSDLRenderer(app->window, app->renderer);
	ImGui_ImplSDLRenderer3_Init(app->renderer);

	return app;
}

App::~App(void) {
	if(window != NULL) {
		SDL_DestroyWindow(window);
	}

	if(renderer != NULL) {
		SDL_DestroyRenderer(renderer);
	}
}

void App::run(void) {
	while(!quit) {
		loop();
	}
}

void App::processEvents(void) {
	SDL_Event event;

	while(SDL_PollEvent(&event)) {
		ImGui_ImplSDL3_ProcessEvent(&event);
		if(event.type == SDL_EVENT_QUIT) quit = true;

	}
}

void App::loop(void) {
	processEvents();

	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	step();

	ImGui::Render();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	SDL_SetRenderScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
	SDL_SetRenderDrawColorFloat(renderer, clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	SDL_RenderClear(renderer);
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
	SDL_RenderPresent(renderer);
}

/* Insert your code here. */
void App::step(void) {
	ImGui::ShowDemoWindow();
}

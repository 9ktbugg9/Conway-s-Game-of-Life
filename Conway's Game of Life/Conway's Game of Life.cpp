#include "stdafx.h"
#include "Screen.h"
#include "Grid.h"

#include <iostream>

#define WIDTH 1000
#define HEIGHT WIDTH
#define NAME "Conway's Game of Life"
#define FPS 6000

int main(int args, char* argc[]) {
	Screen screen(NAME, WIDTH, HEIGHT);
	SDL_Event event;

	Grid life(WIDTH, HEIGHT);

	Uint32 startingTick, fpsTick = SDL_GetTicks();
	bool running = true, pause = false, clicked = false;
	int pauseTimer = 0, mouseTimer = 0, updateTimer = 0;
	while (running) {
		startingTick = SDL_GetTicks();

		if (SDL_PollEvent(&event) != NULL) {
			if (event.type == SDL_QUIT)
				running = false;
			if (event.type == SDL_KEYDOWN)
				if (event.key.keysym.sym == SDLK_ESCAPE)
					running = false;
			if (event.key.keysym.sym == SDLK_p && pauseTimer == 0) {
				if (pause) {
					pause = false;
					SDL_SetWindowTitle(screen.gWindow, "Conway's Game of Life");
				}
				else if (!pause) {
					pause = true;
					SDL_SetWindowTitle(screen.gWindow, "Conway's Game of Life   *PAUSED*");
				}
				pauseTimer = 10;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
				clicked = true;
			if (event.type == SDL_MOUSEBUTTONUP)
				clicked = false;
		}

		if (clicked && mouseTimer == 0) {
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			life.update(mouseX, mouseY);
			mouseTimer = 5;
		}

		SDL_SetRenderDrawColor(screen.gRenderer, 0, 0, 0, 255);
		SDL_RenderClear(screen.gRenderer);

		SDL_SetRenderDrawColor(screen.gRenderer, 255, 255, 255, 255);
		if (++updateTimer > 10 && !pause) {
			life.update();
			updateTimer = 0;
		}
		life.render(screen.gRenderer);
		SDL_RenderPresent(screen.gRenderer);


		if ((1000 / FPS) > SDL_GetTicks() - startingTick) {
			SDL_Delay(1000 / FPS - (SDL_GetTicks() - startingTick));
		}

		if (pauseTimer > 0)
			pauseTimer--;

		if (mouseTimer > 0)
			mouseTimer--;
	}
	return 0;
}


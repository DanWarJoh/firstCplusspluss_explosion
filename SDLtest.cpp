#include <iostream>
#include <SDL.h>
#include <iomanip>
#include <math.h>
#include "Screen.h"
#include "Swarm.h"
#include <stdlib.h>
#include <time.h>

#undef main;

using namespace std;
using namespace screenns;

int main() {
	srand(time(NULL));
	Screen screen;
	if (screen.init() == false) {
		cout << "Error initialising SDL" << endl;
	}

	Swarm swarm;

	while(true) {

		int elapsed = SDL_GetTicks();

		//screen.clear();
		swarm.update(elapsed);

		unsigned char red = (unsigned char)((1 + cos(elapsed*0.001)) * 128);
		unsigned char green = (unsigned char)((1 + sin(elapsed*0.002)) * 128);
		unsigned char blue = (unsigned char)((1 + cos(elapsed*0.003)) * 128);



		const Particle * const pParticles = swarm.getParticles();
		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			Particle particle = pParticles[i];
			int x = (particle.m_x + 1)*screen.SCREEN_WIDTH / 2;
			int y = (particle.m_y*screen.SCREEN_WIDTH / 2)+(screen.SCREEN_HIGHT/2);

			screen.setPixel(x, y, red, green, blue);
		}
		//draw particles
		
		/*
		int elapsed = SDL_GetTicks();
		
		unsigned char red = (unsigned char)((1 + cos(elapsed*0.001)) * 128);
		unsigned char green = (unsigned char)((1 + sin(elapsed*0.002)) * 128);
		unsigned char blue = (unsigned char)((1 + cos(elapsed*0.003)) * 128);


		for(int y = 0; y < screen.SCREEN_HIGHT; y++) {
			for(int x = 0; x < screen.SCREEN_WIDTH; x++) {
				screen.setPixel(x, y, red, green, blue);
			}
		}
		*/

		screen.boxBlur();
		//Draw screen
		screen.update();

		//update particles
		//draw particles
		//check for messages/events
		if(screen.processEvents() == false) {
			break;
		}
	}

	screen.close();


	return 0;
}



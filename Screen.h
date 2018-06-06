#pragma once

#include <SDL.h>

namespace screenns {
	class Screen
	{
	public:
		const int SCREEN_WIDTH = 800;
		const int SCREEN_HIGHT = 600;
	private:
		SDL_Window *m_window; //m_ instance variables
		SDL_Renderer *m_renderer;
		SDL_Texture *m_texture;
		Uint32 *m_buffer1;
		Uint32 *m_buffer2;
	public:
		Screen();
		bool init();
		void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
		void update();
		bool processEvents();
		void close();
		void clear();
		void boxBlur();
		
		~Screen();
	};

} //end screenns

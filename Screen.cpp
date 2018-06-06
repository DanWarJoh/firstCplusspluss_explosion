#include "Screen.h"
#include <iomanip>
namespace screenns {

	Screen::Screen() :
		m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), m_buffer2(NULL)
	{
	}


	Screen::~Screen()
	{
	}

	bool Screen::init() {
		m_window = SDL_CreateWindow("Particle Fire Explosion",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HIGHT,
			SDL_WINDOW_SHOWN);

		if (m_window == NULL) {

			SDL_Quit();
			return false;
		}

		//SDL_Renderer *renderer //already defined!!! refining overwrites just use predefined variabel name
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
		m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HIGHT);

		if (m_renderer == NULL) {
			//cout << "Could not create renderer!" << endl;
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}
		if (m_texture == NULL) {
			//cout << "Could not create texture!" << endl;
			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}

		m_buffer1 = new Uint32[SCREEN_WIDTH*SCREEN_HIGHT];

		//memset(buffer, 255, SCREEN_WIDTH*SCREEN_HIGHT * sizeof(Uint32));//Allocate memory - here full RBGA per pixel 255- result = white
		//memset(buffer, 0xFF, SCREEN_WIDTH*SCREEN_HIGHT * sizeof(Uint32));//Allocate memory - here full RBGA per pixel (0xFF = 255)- result = white
		//memset(buffer, 0, SCREEN_WIDTH*SCREEN_HIGHT * sizeof(Uint32));//Allocate memory - here empty RBGA per pixel 0- result = black
		//setting pixel colour:
		//buffer[30000] = 0xFFFFFFFF;//Hexadecimal colour one FF pair per pixel

		/*for (int i = 0; i < SCREEN_WIDTH*SCREEN_HIGHT; i++) {
			m_buffer[i] = 0x0080FFFF;
		}*/

		//memset(buffer, 0, SCREEN_WIDTH*SCREEN_HIGHT * sizeof(Uint32));
		return true;

	}

	void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

		if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HIGHT) {
			return;
		}

		Uint32 color = 0;

		//bit shift int = 32 bits shifts 8 bits to left
		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;
		color <<= 8;
		color += 0xFF; //Alpha

		m_buffer1[(y*SCREEN_WIDTH) + x] = color;
	}

	void Screen::update() {
		SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(m_renderer);
		SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
		SDL_RenderPresent(m_renderer);
	}

	void Screen::boxBlur() {
		//swap the buffers so buffer info in 2 and drawing to 1
		Uint32 *temp = m_buffer1;
		m_buffer1 = m_buffer2;
		m_buffer2 = temp;

		for (int y = 0; y < SCREEN_HIGHT; y++) {
			for (int x = 0; x > SCREEN_WIDTH; x++) {
				int redTotal = 0;
				int greenTotal = 0;
				int blueTotal = 0;

				for (int row = -1; row <= 1; row++) {
					for(int col = -1; col <= 1; col++) {
						int currentX = x + col;
						int currentY = y + row;
						
						if (currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HIGHT) {
							Uint32 color = m_buffer2[currentY*SCREEN_WIDTH + currentX];

							Uint8 red = color >> 24;
							Uint8 green = color >> 16;
							Uint8 blue = color >> 8;
							
							redTotal += red;
							greenTotal += green;
							blueTotal += blue;



						}
					}
				}
				Uint8 red = redTotal / 9;
				Uint8 green = greenTotal / 9;
				Uint8 blue = blueTotal / 9;

				setPixel(x, y, red, green, blue);
			}
		}
	}

	/* Screen::clear() {
		memset(m_buffer1, 0, SCREEN_WIDTH*SCREEN_HIGHT * sizeof(Uint32));

	}*/

	bool Screen::processEvents() {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { //om X / lukker vinduet
				return false;
			}
		}
		return true;
}
	void Screen::close() {
		delete[] m_buffer1;
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyTexture(m_texture);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
}

}
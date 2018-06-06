#include "Particle.h"
#include <stdlib.h>
#include <iomanip>
#include "SDL.h"

using namespace std;
namespace screenns {

	Particle::Particle() : m_x(0),m_y(0)
	{

		/*m_x = ((2.0*rand()) / RAND_MAX)-1; //random number for -1 to +1
		m_y = ((2.0*rand()) / RAND_MAX) - 1;*/
		//m_xspeed = 0.0001*((2.0*rand()) / RAND_MAX - 1);
		//m_yspeed = 0.0001*((2.0*rand()) / RAND_MAX - 1);

		m_direction = (2.0*M_PI*rand()) / RAND_MAX;
		m_speed = (0.0005*rand()) / RAND_MAX;
	}


	void Particle::update(int interval) {
		
		double xspeed = m_speed * cos(m_direction);
		double yspeed = m_speed * sin(m_direction);

		m_x += xspeed * interval;
		m_y += yspeed * interval;

		/*m_x += m_xspeed;
		m_y += m_yspeed;

		if (m_x < -1.0 || m_x >= 1.0) {
			m_xspeed = -m_xspeed;
		}

		if (m_y < -1.0 || m_y >= 1.0) {
			m_yspeed = -m_yspeed;
		}*/
	}

	Particle::~Particle()
	{
	}

}
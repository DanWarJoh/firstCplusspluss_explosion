#pragma once
#include "Particle.h"

namespace screenns {
class Swarm
{
public:
	const static int NPARTICLES = 2000;
private:
	Particle * m_pParticles;
	int lastTime;
public:
	Swarm();
	~Swarm();
	void update(int elapsed);
	const Particle * const getParticles() { return m_pParticles; };
};

} //end screenns nameapace
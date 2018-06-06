#pragma once

namespace screenns {
	struct Particle //stract is a class where members are public as default private in class
	{
		double m_x;
		double m_y;
		 //double m_xspeed;
		 //double m_yspeed;
		double m_speed;
		double m_direction;

	public:
		Particle();
		~Particle();
		void update(int interval);
	};
}// end namespace screenns

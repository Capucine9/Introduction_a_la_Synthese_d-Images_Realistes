#include "PointLight.hpp"
#include "light_sample.hpp"

namespace RT_ISICG
{
	LightSample PointLight::sample( const Vec3f & p_point ) const 
	{
		Vec3f direction = _position - p_point;
		float distance	= glm::length( direction );
		float facteur = 1.f / ( distance * distance );
		Vec3f radiance = _color * _power * facteur;
		
		direction = glm::normalize( direction );
		
		return LightSample( direction, distance, radiance, 1.f );
	}

} // namespace RT_ISICG

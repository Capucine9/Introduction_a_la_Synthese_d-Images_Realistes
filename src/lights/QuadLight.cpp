#include "QuadLight.hpp"
#include "light_sample.hpp"
#include "utils/random.hpp"

namespace RT_ISICG
{
	LightSample QuadLight::sample( const Vec3f & p_point ) const
	{
		// Génération d'une position aléatoire sur le quad
		float u_alea		= randomFloat() * _u.x;
		float v_alea		= randomFloat() * _v.z;
		Vec3f position_alea = Vec3f( _position + u_alea + v_alea );

		Vec3f direction = position_alea - p_point;

		// Calcul distance et PDF
		float distance = glm::length( direction );

		direction = glm::normalize( direction );

		float inv_area	  = 1.f / _area;
		float cos		  = glm::dot( _n, direction );
		float facteur_geo = ( distance * distance ) / cos;
		float pdf		  = inv_area * facteur_geo;

		Vec3f radiance = _color * _power / pdf;

		return LightSample( direction, distance, radiance, pdf );
	}

} // namespace RT_ISICG


#include "PlaneGeometry.hpp"

namespace RT_ISICG
{
	bool PlaneGeometry::intersect(const Ray & p_ray, float& p_t) const {
		float a = _normale.x;
		float b = _normale.y;
		float c = _normale.z;

		float d = _point.x * (-_normale.x) + _point.y * (-_normale.y) + _point.z * (-_normale.z);
		float denominateur = glm::dot( _normale, p_ray.getDirection() );

		if ( fabsf( denominateur ) < 1e-6f ) { return false; } // denominateur == 0

		p_t = ( -glm::dot( _normale, p_ray.getOrigin() ) - d ) / denominateur;


		return true;
	}
}


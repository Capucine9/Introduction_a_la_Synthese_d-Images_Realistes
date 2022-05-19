#include "PlaneGeometry.hpp"

namespace RT_ISICG
{
	bool PlaneGeometry::intersect(const Ray & p_ray, float & p_t) const {
		float const_d = _point.x * (-_normale.x) + _point.y * (-_normale.y) + _point.z * (-_normale.z);
		float denominateur = glm::dot( _normale, p_ray.getDirection() );

		if ( fabs( denominateur ) < 1e-6f ) { return false; } // denominateur == 0

		p_t = ( -glm::dot( _normale, p_ray.getOrigin() ) - const_d ) / denominateur;

		return true;
	}
}


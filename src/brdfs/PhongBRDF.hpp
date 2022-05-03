#ifndef __RT_ISICG_BRDF_PHONG__
#define __RT_ISICG_BRDF_PHONG__

#include "ray.hpp"
#include "hit_record.hpp"
#include "lights/light_sample.hpp"
#include "defines.hpp"

namespace RT_ISICG
{
	class PhongBRDF
	{
	  public:
		PhongBRDF( const Vec3f & p_ks, const float p_s ) : _ks( p_ks ), _s(p_s) {};

		inline Vec3f evaluate( Ray p_ray, HitRecord p_hitRecord, LightSample p_lightSample) const
		{ 
			float cos = glm::dot( glm::reflect( p_lightSample._direction, p_hitRecord._normal ), p_ray.getDirection() );
			return _ks * glm::pow (glm::max(0.f, cos) ,_s );
		}

		inline const Vec3f & getKs() const { return _ks; }

	  private:
		Vec3f _ks = WHITE;
		float _s = 0.3f;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_PHONG__

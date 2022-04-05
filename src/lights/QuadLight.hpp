#ifndef __RT_ISICG_QUAD_LIGHT__
#define __RT_ISICG_QUAD_LIGHT__

#include "base_light.hpp"

namespace RT_ISICG
{
	class QuadLight : public BaseLight
	{
	  public:
		QuadLight( const Vec3f p_position,
				   const Vec3f _u,
				   const Vec3f _v,
				   const Vec3f p_color,
				   const float p_power = 1.f )
			: BaseLight( p_color, p_power ), _position( p_position ), _u( _u ), _v( _v )
		{
			_area = glm::length(_u) * glm::length(_v);
			_n	  = glm::cross( _u, _v );
			_n	  = glm::normalize( _n );
		}

		virtual LightSample sample( const Vec3f & p_point ) const override;

	  protected:
		Vec3f _position = VEC3F_ZERO;
		Vec3f _u = VEC3F_ZERO;
		Vec3f _v = VEC3F_ZERO;
		Vec3f _n = VEC3F_ZERO;
		float _area	= 0.f;

	};

} // namespace RT_ISICG

#endif // __RT_ISICG_POINT_LIGHT__



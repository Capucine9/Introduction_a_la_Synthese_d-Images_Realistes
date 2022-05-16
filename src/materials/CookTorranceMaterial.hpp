#ifndef __RT_ISICG_COOKTORRANCE_MATERIAL__
#define __RT_ISICG_COOKTORRANCE_MATERIAL__

#include "defines.hpp"
#include "base_material.hpp"
#include "brdfs/CookTorranceBRDF.hpp"
#include "brdfs/lambert_brdf.hpp"

namespace RT_ISICG
{
	class CookTorranceMaterial : public BaseMaterial
	{
	  public:
		CookTorranceMaterial( const std::string & p_name,
						 const Vec3f &		 p_diffuse,
						 const Vec3f &		 p_speculaire,
						 const float		 p_metalness , 
						 const Vec3f		 Fo, 
						 const float		 rugosite)
			: BaseMaterial( p_name ), _brdfL( p_diffuse ), _metalness(p_metalness), _brdfCT( p_speculaire, Fo, rugosite )
		{
		}

		virtual ~CookTorranceMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			return ( 1 - _metalness ) * _brdfL.evaluate()
				   + _metalness * _brdfCT.evaluate( -p_ray.getDirection(), p_lightSample._direction, p_hitRecord._normal );
		}

		inline const Vec3f & getFlatColor() const override { return _brdfL.getKd() + _brdfCT.getKd(); }

	  protected:
		LambertBRDF _brdfL;
		CookTorranceBRDF _brdfCT;
		float _metalness = 0.5f;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_COOKTORRANCE_MATERIAL__
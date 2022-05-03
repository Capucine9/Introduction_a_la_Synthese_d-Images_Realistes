#ifndef __RT_ISICG_PLASTIC_MATERIAL__
#define __RT_ISICG_PLASTIC_MATERIAL__

#include "base_material.hpp"
#include "brdfs/lambert_brdf.hpp"
#include "brdfs/PhongBRDF.hpp"

namespace RT_ISICG
{
	class PlasticMaterial : public BaseMaterial
	{
	  public:
		PlasticMaterial( const std::string & p_name, const Vec3f & p_diffuse, const Vec3f & p_speculaire, const float _s )
			: BaseMaterial( p_name ), _brdfL( p_diffuse ), _brdfP( p_speculaire, _s )
		{
		}

		virtual ~PlasticMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			return _brdfL.evaluate() + _brdfP.evaluate(p_ray, p_hitRecord, p_lightSample);
		}

		inline const Vec3f & getFlatColor() const override { return _brdfL.getKd() + _brdfP.getKs(); }

	  protected:
		LambertBRDF _brdfL;
		PhongBRDF	_brdfP;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_PLASTIC_MATERIAL__
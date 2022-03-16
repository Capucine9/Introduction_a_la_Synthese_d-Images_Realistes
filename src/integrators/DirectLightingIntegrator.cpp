#include "DirectLightingIntegrator.hpp"
#include "defines.hpp"
#include "base_integrator.hpp"

namespace RT_ISICG
{
	Vec3f DirectLightingIntegrator::_directLighting( const Scene &   p_scene,
													 const Vec3f &   p_direction,
													 const Vec3f	 p_radiance,
													 const HitRecord hitRecord ) const 
	{
		float costheta = glm::dot( hitRecord._normal, -p_direction );

		Vec3f mtl = hitRecord._object->getMaterial()->getFlatColor() * p_radiance * std::max(costheta, 0.f);

		return mtl;

	}

	Vec3f DirectLightingIntegrator::Li( const Scene & p_scene,
								  const Ray &	p_ray,
								  const float	p_tMin,
								  const float	p_tMax ) const

	{
		HitRecord hitRecord;
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{ 
			Vec3f somme_directLighting = Vec3f( 0.f, 0.f, 0.f );
			for (BaseLight* light : p_scene.getLights()) {
				LightSample ls = light->sample( hitRecord._point );
				Vec3f color = _directLighting( p_scene, ls._direction, ls._radiance, hitRecord );
				somme_directLighting += color;
			}
			return somme_directLighting;
		}
		else
		{
			return _backgroundColor;
		}
	}
	

} // namespace RT_ISICG
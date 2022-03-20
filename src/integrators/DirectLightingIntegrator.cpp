#include "DirectLightingIntegrator.hpp"
#include "defines.hpp"
#include "base_integrator.hpp"

namespace RT_ISICG
{
	Vec3f DirectLightingIntegrator::_directLighting( const Scene &   p_scene,
													 HitRecord	 &  hitRecord ) const 
	{
		Vec3f somme_directLighting = Vec3f( 0.f, 0.f, 0.f );
		for ( BaseLight * light : p_scene.getLights() )
		{
			LightSample ls = light->sample( hitRecord._point );
			float costheta = glm::dot( hitRecord._normal, ls._direction );
			Vec3f mtl = hitRecord._object->getMaterial()->getFlatColor() /* * ls._radiance*/ * glm::max( costheta, 0.f );
			somme_directLighting += mtl;
		}
		return somme_directLighting;

	}


	Vec3f DirectLightingIntegrator::Li( const Scene & p_scene,
								  const Ray &	p_ray,
								  const float	p_tMin,
								  const float	p_tMax ) const
	{
		HitRecord hitRecord;
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			return _directLighting( p_scene, hitRecord );
		}
		else
		{
			return _backgroundColor;
		}
	}
	

} // namespace RT_ISICG
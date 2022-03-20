#include "DirectLightingIntegrator.hpp"
#include "defines.hpp"
#include "base_integrator.hpp"

namespace RT_ISICG
{
	Vec3f DirectLightingIntegrator::_directLighting( const Scene &   p_scene,
													 HitRecord &   hitRecord,
													 const float   p_tMin,
													 const float   p_tMax ) const 
	{
		Vec3f somme_directLighting = Vec3f( 0.f, 0.f, 0.f );
		for ( BaseLight * light : p_scene.getLights() )
		{
			HitRecord	tmphitRecord;
			LightSample ls = light->sample( hitRecord._point );
			Ray			rayon_ombre = Ray( hitRecord._point, ls._direction );
			// TP2_Exo 4_3 :
			//rayon_ombre.offset( hitRecord._normal );
			float costheta = glm::dot( hitRecord._normal, ls._direction );
			if ( !p_scene.intersect( rayon_ombre, p_tMin, p_tMax, tmphitRecord ) ) //TP2_Exo 4_1 :
			{
				Vec3f mtl
					= hitRecord._object->getMaterial()->getFlatColor() /* * ls._radiance*/ * glm::max( costheta, 0.f );
				somme_directLighting += mtl;
			}
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
			return _directLighting( p_scene, hitRecord, p_tMin, p_tMax );
		}
		else
		{
			return _backgroundColor;
		}
	}
	

} // namespace RT_ISICG
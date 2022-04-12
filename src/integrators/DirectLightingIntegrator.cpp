#include "DirectLightingIntegrator.hpp"
#include "defines.hpp"
#include "base_integrator.hpp"

namespace RT_ISICG
{
	 Vec3f DirectLightingIntegrator::_directLighting( const Scene & p_scene,
													 HitRecord &   hitRecord,
													 const float   p_tMin,
													 const float   p_tMax ) const 
	{
		Vec3f somme_directLighting = Vec3f( 0.f, 0.f, 0.f );

		// TP3_Exo 3_2 :
		for ( BaseLight * light : p_scene.getLights() )
		{
			Vec3f somme_quadLighting = Vec3f( 0.f, 0.f, 0.f );
			for ( int i = 1; i <= _nbLightSamples; i++ )
			{
				HitRecord	tmphitRecord;
				LightSample ls			= light->sample( hitRecord._point );
				Ray			rayon_ombre = Ray( hitRecord._point, ls._direction );
				// TP2_Exo 4_3 :
				rayon_ombre.offset( hitRecord._normal );
				// TP2_Exo 4_1 :
				// if ( !p_scene.intersect( rayon_ombre, p_tMin, p_tMax, tmphitRecord ) )

				// TP2_Exo 5_2 :
				float tMax = ls._distance;
				if ( !p_scene.intersectAny( rayon_ombre, SHADOW_EPSILON, tMax ) )
				{
					float costheta = glm::dot( hitRecord._normal, ls._direction );
					Vec3f mtl
						= hitRecord._object->getMaterial()->getFlatColor() * ls._radiance * glm::max( costheta, 0.f );
					//somme_directLighting += mtl;
					// TP3_Exo 3_2 :
					somme_quadLighting += mtl;
				}
				// TP3_Exo 3_2 :
				if ( light -> getSurface() != true ) { break; }
			}
			// TP3_Exo 3_2 :
			if ( light->getSurface() == true ) { 
				somme_quadLighting /= _nbLightSamples; 
			}
			somme_directLighting += somme_quadLighting;
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
	/*
	Vec3f DirectLightingIntegrator::Li( const Scene & p_scene,
										const Ray &	  p_ray,
										const float	  p_tMin,
										const float	  p_tMax ) const
	{
		HitRecord hitRecord;
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			// float costheta = glm::max( glm::dot( -p_ray.getDirection(), hitRecord._normal ), 0.0f );

			Vec3f Li( 0.f );
			for ( BaseLight * light : p_scene.getLights() )
			{
				if ( light->getSurface() )
				{
					Vec3f tmp_ombre( 0.f );

					for ( int nb = 0; nb < _nbLightSamples; nb++ )
					{
						LightSample ls	  = light->sample( hitRecord._point );
						Ray			ombre = Ray( hitRecord._point, ls._direction );
						ombre.offset( hitRecord._normal );
						if ( !p_scene.intersectAny( ombre, p_tMin, ls._distance ) )
						{
							tmp_ombre += _directLighting( ls, hitRecord, p_ray );
						}
					}
					tmp_ombre /= _nbLightSamples;
					Li += tmp_ombre;
				}

				else
				{
					LightSample ls	  = light->sample( hitRecord._point );
					Ray			ombre = Ray( hitRecord._point, ls._direction );
					ombre.offset( hitRecord._normal );
					if ( !p_scene.intersectAny( ombre, p_tMin, ls._distance ) )
					{
						Li += _directLighting( ls, hitRecord, p_ray );
					}
				}
			}

			return Li;
		}

		else
		{
			return _backgroundColor;
		}
	}*/

} // namespace RT_ISICG
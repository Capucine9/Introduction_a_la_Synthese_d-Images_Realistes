#include "WhittedIntegrator.hpp"
#include "base_integrator.hpp"
#include "defines.hpp"

namespace RT_ISICG
{
	Vec3f WhittedIntegrator::_directLighting( const Scene & p_scene,
											  const Ray &	p_ray,
											  const float	p_tMin,
											  const float	p_tMax,
											  int			_nblimite,
											  bool			interieurObj ) const
	{
		HitRecord hitRecord;

		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			// TP5_Exo 2 :
			if ( hitRecord._object->getMaterial()->isMirror() )
			{
				if ( _nblimite != _nbBounces )
				{
					_nblimite += 1;
					Ray rayon_reflect
						= Ray( hitRecord._point, glm::reflect( p_ray.getDirection(), hitRecord._normal ) );
					rayon_reflect.offset( hitRecord._normal );
					return _directLighting( p_scene, rayon_reflect, p_tMin, p_tMax, _nblimite, false );
				}
				else { return BLACK; }
			}
			else
			{
				// TP5_Exo 3 :
				if ( hitRecord._object->getMaterial()->isTransparent() )
				{
					if ( _nblimite == _nbBounces ) { return BLACK; }
					else
					{
						_nblimite += 1;
						float RefractIn	 = 0.f;
						float RefractOut = 0.f;

						if ( interieurObj )
						{
							RefractIn  = hitRecord._object->getMaterial()->getIOR();
							RefractOut = 1.f;
						}
						else
						{
							RefractIn  = 1.f;
							RefractOut = hitRecord._object->getMaterial()->getIOR();
						}

						Ray rayon_reflect
							= Ray( hitRecord._point,
								   glm::normalize( glm::reflect( p_ray.getDirection(), hitRecord._normal ) ) );
						rayon_reflect.offset( hitRecord._normal );
						Ray rayon_refract
							= Ray( hitRecord._point,
								   glm::normalize( glm::refract(
									   p_ray.getDirection(), hitRecord._normal, RefractIn / RefractOut ) ) );
						rayon_refract.offset( -hitRecord._normal );


						float theta_i = glm::dot( hitRecord._normal, -p_ray.getDirection() );
						float theta_t = glm::dot( -hitRecord._normal, rayon_refract.getDirection() );

						float rs = ( RefractIn * theta_i - RefractOut * theta_t )
								   / ( RefractIn * theta_i + RefractOut * theta_t );
						float rp = ( RefractIn * theta_t - RefractOut * theta_i )
								   / ( RefractIn * theta_t + RefractOut * theta_i );

						float kr = ( rs * rs + rp * rp ) * 0.5f;

						if ( kr < 1 )
						{
							return ( 1 - kr ) * _directLighting(p_scene, rayon_refract, p_tMin, p_tMax, _nblimite, !interieurObj )
								   + kr* _directLighting(p_scene, rayon_reflect, p_tMin, p_tMax, _nblimite, interieurObj );
						}

						else
						{
							return kr
								   * _directLighting( p_scene, rayon_reflect, p_tMin, p_tMax, _nblimite, interieurObj );
						}



					}
				}
				else
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
							if ( !p_scene.intersectAny( rayon_ombre, p_tMin, tMax ) )
							{
								float costheta = glm::dot( hitRecord._normal, ls._direction );
								// TP4_Exo 1_2 : (modifier le getFlatColor() par shade())
								Vec3f mtl = hitRecord._object->getMaterial()->shade( p_ray, hitRecord, ls )
											* ls._radiance * glm::max( costheta, 0.f );
								// somme_directLighting += mtl;
								// TP3_Exo 3_2 :
								somme_quadLighting += mtl;
							}
							// TP3_Exo 3_2 :
							if ( light->getSurface() != true ) { break; }
						}
						// TP3_Exo 3_2 :
						if ( light->getSurface() == true ) { somme_quadLighting /= _nbLightSamples; }
						somme_directLighting += somme_quadLighting;
					}
					return somme_directLighting;
				}
			}
		}
		else
		{
			return _backgroundColor;
		}
	}

	Vec3f WhittedIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax ) const
	{
		int _nblimite = 0;
		bool interieurObj  = false;
		return _directLighting( p_scene, p_ray, p_tMin, p_tMax, _nblimite, interieurObj );
	}

} // namespace RT_ISICG


#include "sphere_geometry.hpp"

namespace RT_ISICG
{
	bool SphereGeometry::intersect( const Ray & p_ray, float & p_t1, float & p_t2 ) const
	{
		// TP1_Exo 3_1:
		
		// equation sphère : r**2= (x-a)**2 + (y-b)**2 + (z-c)**2;
		// trouver les paramètres de l'équation
		float a = dot( p_ray.getDirection(), p_ray.getDirection() );

		float b = 2 * dot( p_ray.getDirection(), ( p_ray.getOrigin() - _center ) );

		float c = dot( ( p_ray.getOrigin() - _center ), ( p_ray.getOrigin() - _center ) ) - _radius * _radius;

		// calcul du discriminant
		float delta = b * b - 4 * a * c;

		if ( delta < 0 )
		{
			p_t2 = -1; // distance d'intersection
			p_t1 = -1;
			return false;
		}
		else
		{
			if ( delta == 0 )
			{
				p_t1 = -b / ( 2 * a );
				p_t2 = -1;
			}
			else
			{
				p_t1 = ( -b - sqrt( delta ) ) / ( 2 * a );
				p_t2 = ( -b + sqrt( delta ) ) / ( 2 * a );
			}
			return true;
		}
	}

} // namespace RT_ISICG

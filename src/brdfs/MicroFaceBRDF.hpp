#ifndef __RT_ISICG_BRDF_MICROFACE__
#define __RT_ISICG_BRDF_MICROFACE__

#include "defines.hpp"

namespace RT_ISICG
{
	class MicroFaceBRDF
	{
	  public:
		MicroFaceBRDF( const Vec3f & p_kd ) : _kd( p_kd ) {};

		inline Vec3f evaluate() const { 
			//float alpha = ;

			return _kd * INV_PIf; 
		}

		inline const Vec3f & getKd() const { return _kd; }

	  private:
		Vec3f _kd = WHITE;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_MICROFACE__

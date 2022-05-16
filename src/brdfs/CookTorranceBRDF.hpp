#ifndef __RT_ISICG_BRDF_COOKTORRANCE__
#define __RT_ISICG_BRDF_COOKTORRANCE__

#include "defines.hpp"
#include "brdfs/lambert_brdf.hpp"

namespace RT_ISICG
{
	class CookTorranceBRDF
	{
	  public:
		CookTorranceBRDF( const Vec3f & p_kd, const Vec3f p_Fo, const float p_rugosite )
			: _kd( p_kd ), Fo( p_Fo ), rugosite( p_rugosite) {};

		inline Vec3f evaluate(const Vec3f _wo, const Vec3f _wi, const Vec3f _n) const { 
			float alpha = rugosite * rugosite;
			float alpha_carre = alpha * alpha;
			Vec3f h = glm::normalize( _wo + _wi );
			float D = alpha_carre / ( PIf * glm::pow(( glm::dot(_n, h) * glm::dot(_n, h) * (alpha_carre - 1.f) + 1.f), 2));

			float k = glm::pow( ( rugosite + 1 ), 2 ) / 8;
			float G1o = glm::dot( _n, _wo ) / ( glm::dot( _n, _wo ) * ( 1 - k ) + k );
			float G1i = glm::dot( _n, _wi ) / ( glm::dot( _n, _wi ) * ( 1 - k ) + k );
			float G = G1o * G1i;

			Vec3f F = Fo + ( Vec3f( 1 ) - Fo ) * glm::pow( ( 1 - ( glm::dot( h, _wo ) ) ), 5.f );

			return ( D * F * G ) / ( 4 * glm::dot( _wo, _n ) * glm::dot( _wi, _n ) );
		}

		inline const Vec3f & getKd() const { return _kd; }

	  private:
		Vec3f _kd = WHITE;
		Vec3f Fo = Vec3f(0.f, 0.f, 0.f);
		float rugosite	 = 0.0f;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_COOKTORRANCE__

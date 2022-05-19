#ifndef __RT_ISICG_WHITTED_INTEGRATOR__
#define __RT_ISICG_WHITTED_INTEGRATOR__

#include "base_integrator.hpp"
#include "defines.hpp"

namespace RT_ISICG
{
	class WhittedIntegrator : public BaseIntegrator
	{
	  public:
		WhittedIntegrator() : BaseIntegrator() {}
		virtual ~WhittedIntegrator() = default;

		Vec3f Li( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;

		const IntegratorType getType() const override { return IntegratorType::WHITTED; }

	  private:
		Vec3f _directLighting( const Scene & p_scene,
							   const Ray &	 p_ray,
							   const float	 p_tMin,
							   const float	 p_tMax,
							   int _nblimite) const;

	  protected:
		int _nbLightSamples = 32;
		int _nbBounces		= 5;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_WHITTED_INTEGRATOR__

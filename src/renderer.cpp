#include "renderer.hpp"
#include "integrators/ray_cast_integrator.hpp"
#include "integrators/DirectLightingIntegrator.hpp"
#include "utils/console_progress_bar.hpp"
#include "utils/random.hpp"

namespace RT_ISICG
{
	Renderer::Renderer() { _integrator = new RayCastIntegrator(); }

	void Renderer::setIntegrator( const IntegratorType p_integratorType )
	{
		if ( _integrator != nullptr ) { delete _integrator; }

		switch ( p_integratorType )
		{
		case IntegratorType::RAY_CAST:
		{
			_integrator = new RayCastIntegrator();
			break;
		}
		case IntegratorType::DIRECT_LIGHT:
		{
			_integrator = new DirectLightingIntegrator();
			break;
		}
		default:
		{
			_integrator = new RayCastIntegrator();
			break;
		}
		}
	}

	void Renderer::setBackgroundColor( const Vec3f & p_color )
	{
		if ( _integrator == nullptr ) { std::cout << "[Renderer::setBackgroundColor] Integrator is null" << std::endl; }
		else
		{
			_integrator->setBackgroundColor( p_color );
		}
	}

	float Renderer::renderImage( const Scene & p_scene, const BaseCamera * p_camera, Texture & p_texture )
	{
		const int width	 = p_texture.getWidth();
		const int height = p_texture.getHeight();

		Chrono			   chrono;
		ConsoleProgressBar progressBar;

		progressBar.start( height, 50 );
		chrono.start();

		// TP1_Exo 1 :
		/* for ( int j = 0; j < height; j++ )
		{
			for ( int i = 0; i < width; i++ )
			{
				p_texture.setPixel( i, j, Vec3f( float( i ) / ( width - 1 ), float( j ) / ( height - 1 ), 0 ) );

			}
			progressBar.next();
		}*/

		// TP1_Exo 2_3 :
		/* for ( int j = 0; j < height; j++ )
		{
			for ( int i = 0; i < width; i++ )
			{
				Ray ray = p_camera->generateRay( float( i + 0.5 ) / ( width - 1 ), float( j + 0.5 ) / ( height - 1 ) );
				//p_texture.setPixel( i, j, ( ray.getDirection() + 1.f ) * 0.5f );
				
				//TP1_Exo 3_1 :
				p_texture.setPixel( i, j, _integrator->Li( p_scene, ray, 0.0f, 10.0f ) );
			}
			progressBar.next();
		}*/

		
		// TP1_Exo 5
		for ( int j = 0; j < height; j++ )
		{
			for ( int i = 0; i < width; i++ )
			{
				Vec3f moy_color = Vec3f(0, 0, 0);

				for ( int k = 0; k < ( _nbPixelSamples ); k++ )
				{
					float random_i = static_cast<float>( rand() ) / static_cast<float>( RAND_MAX );
					float random_j = static_cast<float>( rand() ) / static_cast<float>( RAND_MAX );

					Ray ray
						= p_camera->generateRay( float( i + random_i ) / ( width - 1 ),
												 float( j + random_j ) / ( height - 1 ) );

					moy_color += _integrator->Li( p_scene, ray, 0.0f, 1000.0f );
				}
				
				moy_color = moy_color * (1.f / _nbPixelSamples);
				p_texture.setPixel( i, j, moy_color );

				// TP2_Exo 3_3 :
				//p_texture.setPixel( i, j, glm::clamp( moy_color, Vec3f( 0.f, 0.f, 0.f ), Vec3f( 1.f, 1.f, 1.f ) ) );
			}
			progressBar.next();

		}

		chrono.stop();
		progressBar.stop();

		return chrono.elapsedTime();
	}
} // namespace RT_ISICG

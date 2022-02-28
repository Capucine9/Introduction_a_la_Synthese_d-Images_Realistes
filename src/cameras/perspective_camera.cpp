#include "perspective_camera.hpp"
#include <glm/gtx/string_cast.hpp>

namespace RT_ISICG
{
	PerspectiveCamera::PerspectiveCamera( const float p_aspectRatio ) : _aspectRatio( p_aspectRatio )
	{
		_updateViewport();
	}

	PerspectiveCamera::PerspectiveCamera( const Vec3f & p_position,
										  const Vec3f & p_lookAt,
										  const Vec3f & p_up,
										  const float	p_fovy,
										  const float	p_aspectRatio )
		: BaseCamera( p_position ), _fovy( p_fovy ), _aspectRatio( p_aspectRatio )
	{
		// TP1_Exo 4_1 :
		/// TODO ! _u ? _v ? _w ?

		_w = glm::normalize( p_position - p_lookAt );
		_u = glm::cross( p_up, _w );
		_v = glm::cross( _w, _u );

		Vec3f direction = p_lookAt - p_position;

		_updateViewport();
	}

	void PerspectiveCamera::_updateViewport()
	{
		/// TODO ! _viewportTopLeftCorner ?	_viewportU ? _viewportV ?
		
		// TP1_Exo2
		float dist = glm::tan( glm::radians( _fovy ) / 2 ) * _focalDistance;
		// vecteur vertical
		Vec3f _viewportV2 = _v * dist;
		// vecteur horizontal
		Vec3f _viewportU2 = _u * dist * _aspectRatio;

		// coordonnée du coin en haut à gauche
		_viewportTopLeftCorner = _position + _w * -_focalDistance + -_viewportU2 + _viewportV2;

		//vecteurs représentant la largeur et la longueur totale du viewport
		_viewportU = _viewportU2 * 2.f;
		_viewportV = _viewportV2 * 2.f;
	}

} // namespace RT_ISICG

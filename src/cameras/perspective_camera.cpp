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
		/// TODO ! _u ? _v ? _w ?

		_updateViewport();
	}

	void PerspectiveCamera::_updateViewport()
	{
		/// TODO ! _viewportTopLeftCorner ?	_viewportU ? _viewportV ?
		
		// TP1_Exo2
		float amount_v = glm::tan( glm::radians( _fovy ) / 2 ) * _focalDistance;
		// vecteur associé à la distance précédente
		Vec3f tmp_viewportV = _v * amount_v;
		// vecteur partant du centre du viewport et allant jusqu'au bord droit du viewport
		Vec3f tmp_viewportU = _u * amount_v * _aspectRatio;

		// coordonnée du coin haut-gauche du viewport
		// à partir du centre de la cam, déplacement en w pour obtenir le centre du viewport, puis déplacement en u et v
		// pour obtenir le coin
		_viewportTopLeftCorner = _position + _w * -_focalDistance + -tmp_viewportU + tmp_viewportV;

		// multiplier par deux pour que les vecteurs représente la largeur et la longueur du viewport
		_viewportU = tmp_viewportU * 2.f;
		_viewportV = tmp_viewportV * 2.f;
	}

} // namespace RT_ISICG

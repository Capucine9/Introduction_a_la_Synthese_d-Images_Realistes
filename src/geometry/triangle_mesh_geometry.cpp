#include "triangle_mesh_geometry.hpp"
#include "objects/triangle_mesh.hpp"

namespace RT_ISICG
{
	TriangleMeshGeometry::TriangleMeshGeometry( const unsigned int p_v0,
												const unsigned int p_v1,
												const unsigned int p_v2,
												MeshTriangle *	   p_refMesh )
		: _v0( p_v0 ), _v1( p_v1 ), _v2( p_v2 ), _refMesh( p_refMesh )
	{
		_faceNormal = glm::normalize( glm::cross( _refMesh->_vertices[ p_v1 ] - _refMesh->_vertices[ p_v0 ],
												  _refMesh->_vertices[ p_v2 ] - _refMesh->_vertices[ p_v0 ] ) );
	}

	bool TriangleMeshGeometry::intersect( const Ray & p_ray, float & p_t ) const
	{
		const Vec3f & o	 = p_ray.getOrigin();
		const Vec3f & d	 = p_ray.getDirection();
		const Vec3f & v0 = _refMesh->_vertices[ _v0 ];
		const Vec3f & v1 = _refMesh->_vertices[ _v1 ];
		const Vec3f & v2 = _refMesh->_vertices[ _v2 ];

		//TP6_Ex 1:
		const float eps = 1e-6f;
		Vec3f		edge1, edge2, h, s, q;
		float		a, f;

		edge1 = v1 - v0;
		edge2 = v2 - v0;

		h = glm::cross( d, edge2 );
		a = glm::dot( edge1, h );

		// a != 0 car (denominateur)
		if ( a > -eps && a < eps ) { return false; }

		f = 1.0 / a;
		s = o - v0;
		float u = f * glm::dot( s, h );
		if ( u < 0.0 || u > 1.0 ) { return false; }
		q = glm::cross( s, edge1 );
		float v = f * glm::dot( d, q );
		if ( v < 0.0 || u + v > 1.0 ) { return false; }

		float t = f * glm::dot( edge2, q );
		if ( t > eps )
		{
			Vec3f intersect = o + d * t;
			p_t				= glm::distance( intersect, o );
			return true;
		}
		else { return false; }

		return false;
	}

} // namespace RT_ISICG

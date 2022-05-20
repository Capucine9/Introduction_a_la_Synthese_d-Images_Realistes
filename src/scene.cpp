#include "scene.hpp"
#include "materials/color_material.hpp"
#include "materials/lambert_material.hpp"
#include "materials/Plasticmaterial.hpp"
#include "materials/CookTorranceMaterial.hpp"
#include "materials/MirrorMaterial.hpp"
#include "materials/TransparentMaterial.hpp"
#include "objects/sphere.hpp"
#include "objects/Plane.hpp"
#include "lights/PointLight.hpp"
#include "lights/QuadLight.hpp"
#include "objects/triangle_mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#define DATA_PATH "object/"

namespace RT_ISICG
{
	Scene::Scene() { _addMaterial( new ColorMaterial( "default", WHITE ) ); }

	Scene::~Scene()
	{
		for ( const ObjectMapPair & object : _objectMap )
		{
			delete object.second;
		}
		for ( const MaterialMapPair & material : _materialMap )
		{
			delete material.second;
		}
		for ( const BaseLight * light : _lightList )
		{
			delete light;
		}
	}

	void Scene::init()
	{
		// Add materials.
		_addMaterial( new ColorMaterial( "Red", RED ) );
		_addMaterial( new ColorMaterial( "Blue", BLUE ) );
		// TP4
		_addMaterial( new ColorMaterial( "Grey", GREY ) );

		////////////////////////////////////////////////
		// SPHERE

		// Add objects.
		//_addObject( new Sphere( "Sphere1", Vec3f( 0.f, 0.f, 3.f ), 1.f ) );

		// Add materials
		// TP4_Ex 1_2 :
		_addMaterial( new LambertMaterial( "LambertSphere", GREY ) );
		// TP4_Ex 3 :
		_addMaterial( new PlasticMaterial( "PhongSphere", GREY * 0.7f, GREY * 0.3f, 64.f) );
		// TP4_Ex 4 :
		_addMaterial( new CookTorranceMaterial( "TorranceSphere", YELLOW, YELLOW, 1.f, Vec3f( 1.f, 0.85f, 0.57f ), 0.3f ) );
		
		// Link objects and materials.
		//_attachMaterialToObject( "Blue", "Sphere1" );
		// TP4 :
		//_attachMaterialToObject( "Grey", "Sphere1" );
		// TP4_Ex 1_2 :
		//_attachMaterialToObject( "LambertSphere", "Sphere1" );
		// TP4_Ex 3 :
		//_attachMaterialToObject( "PhongSphere", "Sphere1" );
		// TP4_Ex 4 :
		//_attachMaterialToObject( "TorranceSphere", "Sphere1" );

		////////////////////////////////////////////////
		// PLAN

		// TP2_Ex 1_3 :
		// Add objects.
		//_addObject( new Plane( "Plan1", Vec3f( 0.f, -2.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );

		// Add materials.
		// TP4_Ex 1_2 :
		_addMaterial( new LambertMaterial( "LambertPlan1", RED ) );

		// Link objects and materials.
		//_attachMaterialToObject( "Red", "Plan1" );
		// TP4_Ex 1_2 :
		_attachMaterialToObject( "LambertPlan1", "Plan1" );

		////////////////////////////////////////////////
		// LIGHT

		// TP2_Ex 3_2 :
		// Add lights
		//_addLight( new PointLight( Vec3f( 1.f, 10.f, 1.f ), Vec3f( 1.f, 1.f, 1.f ), 100.f ) );
		// TP3_Ex 2_4 :
		//_addLight( new QuadLight(Vec3f( 1.f, 10.f, 2.f ), Vec3f( -2.f, 0.f, 0.f ), Vec3f( 0.f, 0.f, 2.f ), Vec3f( 1.f, 1.f, 1.f ), 20.f ) );
		// TP4 :
		//_addLight( new PointLight( Vec3f( 0.f, 0.f, -2.f ), Vec3f( 1.f, 1.f, 1.f ), 60.f ) );



		// TP5_Configuration de la scene
		// ================================================================
		// Add materials .
		// ================================================================
		_addMaterial( new LambertMaterial( " WhiteMatte ", WHITE ) );
		_addMaterial( new LambertMaterial( " RedMatte ", RED ) );
		_addMaterial( new LambertMaterial( " GreenMatte ", GREEN ) );
		_addMaterial( new LambertMaterial( " BlueMatte ", BLUE ) );
		_addMaterial( new LambertMaterial( " GreyMatte ", GREY ) );
		_addMaterial( new LambertMaterial( " MagentaMatte ", MAGENTA ) );

		// TP5_Ex 2 :
		_addMaterial( new MirrorMaterial( " Mirror ") );

		// TP5_Ex 3 :
		_addMaterial( new TransparentMaterial( " Transparent " ) );

		// ================================================================
		// Add objects .
		// ================================================================
		// Spheres .
		/* _addObject( new Sphere( " Sphere1 ", Vec3f( -2.f, 0.f, 3.f ), 1.5f ) );
		_attachMaterialToObject( " WhiteMatte ", " Sphere1 " );
		// TP5_Ex 2 :
		_attachMaterialToObject( " Mirror ", " Sphere1 " );

		_addObject( new Sphere( " Sphere2 ", Vec3f( 2.f, 0.f, 3.f ), 1.5f ) );
		_attachMaterialToObject( " WhiteMatte ", " Sphere2 " );
		// TP5_Ex 2 :
		//_attachMaterialToObject( " Mirror ", " Sphere2 " );
		// TP5_Ex 3 :
		_attachMaterialToObject( " Transparent ", " Sphere2 " );

		// Pseudo Cornell box made with infinite planes.
		_addObject( new Plane( " PlaneGround ", Vec3f( 0.f, -3.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
		_attachMaterialToObject( " GreyMatte ", " PlaneGround " );
		_addObject( new Plane( " PlaneLeft ", Vec3f( 5.f, 0.f, 0.f ), Vec3f( -1.f, 0.f, 0.f ) ) );
		_attachMaterialToObject( " RedMatte ", " PlaneLeft " );
		_addObject( new Plane( " PlaneCeiling ", Vec3f( 0.f, 7.f, 0.f ), Vec3f( 0.f, -1.f, 0.f ) ) );
		_attachMaterialToObject( " GreenMatte ", " PlaneCeiling " );
		_addObject( new Plane( " PlaneRight ", Vec3f( -5.f, 0.f, 0.f ), Vec3f( 1.f, 0.f, 0.f ) ) );
		_attachMaterialToObject( " BlueMatte ", " PlaneRight " );
		_addObject( new Plane( " PlaneFront ", Vec3f( 0.f, 0.f, 10.f ), Vec3f( 0.f, 0.f, -1.f ) ) );
		_attachMaterialToObject( " MagentaMatte ", " PlaneFront " );
		// TP5_Ex 2 :
		//_attachMaterialToObject( " Mirror ", " PlaneFront " );

		// ================================================================
		// Add lights .
		// ================================================================
		_addLight( new PointLight( Vec3f( 0.f, 5.f, 0.f ), WHITE, 100.f ) );
		//_addLight(new QuadLight( Vec3f( 1.f, 5.f, -2.f ), Vec3f( -2.f, 0.f, 0.f ), Vec3f( 0.f, 1.f, 2.f ), WHITE, 40.f ) );*/


		// TP5_Configuration de la scene
		// ================================================================
		// Add materials .
		// ================================================================
		/* _addMaterial( new LambertMaterial( " RedMatte ", RED ) );
		_addMaterial( new LambertMaterial( " GreenMatte ", GREEN) );
		_addMaterial( new LambertMaterial( " BlueMatte ", BLUE ) );
		_addMaterial( new LambertMaterial( " GreyMatte ", GREY ) );
		_addMaterial( new LambertMaterial( " MagentaMatte ", MAGENTA ) );
		_addMaterial( new LambertMaterial( " YellowMatte ", YELLOW ) );
		_addMaterial( new LambertMaterial( " CyanMatte ", CYAN ) );
		// ================================================================
		// Add objects .
		// ================================================================
		// OBJ.
		loadFileTriangleMesh( "UVsphere", DATA_PATH "uvsphere.obj" );
		_attachMaterialToObject( " CyanMatte ", "UVsphere_defaultobject" );
		// Pseudo Cornell box made with infinite planes .
		_addObject( new Plane( " PlaneGround ", Vec3f( 0.f, -3.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
		_attachMaterialToObject( " GreyMatte ", " PlaneGround " );
		_addObject( new Plane( " PlaneLeft ", Vec3f( 5.f, 0.f, 0.f ), Vec3f( -1.f, 0.f, 0.f ) ) );
		_attachMaterialToObject( " RedMatte ", " PlaneLeft " );
		_addObject( new Plane( " PlaneCeiling ", Vec3f( 0.f, 7.f, 0.f ), Vec3f( 0.f, -1.f, 0.f ) ) );
		_attachMaterialToObject( " GreenMatte ", " PlaneCeiling " );
		_addObject( new Plane( " PlaneRight ", Vec3f( -5.f, 0.f, 0.f ), Vec3f( 1.f, 0.f, 0.f ) ) );
		_attachMaterialToObject( " BlueMatte ", " PlaneRight " );
		_addObject( new Plane( " PlaneFront ", Vec3f( 0.f, 0.f, 10.f ), Vec3f( 0.f, 0.f, -1.f ) ) );
		_attachMaterialToObject( " MagentaMatte ", " PlaneFront " );
		_addObject( new Plane( " PlaneRear ", Vec3f( 0.f, 0.f, -10.f ), Vec3f( 0.f, 0.f, 1.f ) ) );
		_attachMaterialToObject( " YellowMatte ", " PlaneRear " );
		// ================================================================
		// Add lights .
		// ================================================================
		_addLight( new PointLight( Vec3f( 0.f, 3.f, -5.f ), WHITE, 100.f ) );*/




		// CONFIGURATION DE MA SCENE
		// ================================================================
		// Add materials.
		// ================================================================
		_addMaterial( new LambertMaterial( " Glace ", CYAN ) );
		_addMaterial( new LambertMaterial( " Nuit ", Vec3f(0.f, 0.f, 0.2f )) );

		_addMaterial( new ColorMaterial( " Corps ", Vec3f(0.2f, 0.2f, 0.2f ))  );
		_addMaterial( new ColorMaterial( " White ", WHITE) );
		_addMaterial( new ColorMaterial( " Yeux ", BLACK ) );
		_addMaterial( new ColorMaterial( " Orange ", Vec3f( 1.f, 0.5f, 0.f ) ) );

		_addMaterial( new PlasticMaterial( " PhongBonnet ", RED * 0.7f, RED * 0.3f, 8.f ) );
		_addMaterial(new CookTorranceMaterial( " Torrance1 ", YELLOW, GREEN, 0.6f, Vec3f( 1.f, 0.85f, 0.57f ), 0.3f ) );

		// ================================================================
		// Add objects.
		// ================================================================
		// Environnement :
		_addObject( new Plane( " PlaneGround ", Vec3f( 0.f, -3.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
		_attachMaterialToObject( " Glace ", " PlaneGround " );
		_addObject( new Plane( " PlaneLeft ", Vec3f( 10.f, 0.f, 0.f ), Vec3f( -1.f, 0.f, 0.f ) ) );
		_attachMaterialToObject( " RedMatte ", " PlaneLeft " );
		_addObject( new Plane( " PlaneCeiling ", Vec3f( 0.f, 7.f, 0.f ), Vec3f( 0.f, -1.f, 0.f ) ) );
		_attachMaterialToObject( " Nuit ", " PlaneCeiling " );
		_addObject( new Plane( " PlaneRight ", Vec3f( -10.f, 0.f, 0.f ), Vec3f( 1.f, 0.f, 0.f ) ) );
		_attachMaterialToObject( " BlueMatte ", " PlaneRight " );
		_addObject( new Plane( " PlaneFront ", Vec3f( 0.f, 0.f, 15.f ), Vec3f( 0.f, 0.f, -1.f ) ) );
		_attachMaterialToObject( " MagentaMatte ", " PlaneFront " );

		// Pingouin
		_addObject( new Sphere( " BasCorps ", Vec3f( -2.f, -2.f, 5.f ), 1.5f ) );
		_attachMaterialToObject( " Corps ", " BasCorps " );
		_addObject( new Sphere( " SphereVentre ", Vec3f( -2.f, -2.f, 4.8f ), 1.4f ) );
		_attachMaterialToObject( " White ", " SphereVentre " );
		_addObject( new Sphere( " HautCorps ", Vec3f( -2.f, 0.f, 5.f ), 1.f ) );
		_attachMaterialToObject( " Corps ", " HautCorps " );

		_addObject( new Sphere( " Oeil1 ", Vec3f( -2.2f, 0.5f, 4.3f ), 0.25f ) );
		_attachMaterialToObject( " Yeux ", " Oeil1 " );
		_addObject( new Sphere( " BlancOeil1 ", Vec3f( -2.15f, 0.6f, 4.f ), 0.05f ) );
		_attachMaterialToObject( " White ", " BlancOeil1 " );
		_addObject( new Sphere( " Oeil2 ", Vec3f( -1.6f, 0.5f, 4.3f ), 0.25f ) );
		_attachMaterialToObject( " Yeux ", " Oeil2 " );
		_addObject( new Sphere( " BlancOeil2 ", Vec3f( -1.6f, 0.6f, 4.f ), 0.05f ) );
		_attachMaterialToObject( " White ", " BlancOeil2 " );
		_addObject( new Sphere( " Bec ", Vec3f( -1.9f, 0.2f, 4.f ), 0.15f ) );
		_attachMaterialToObject( " Orange ", " Bec " );

		//Bonnet
		_addObject( new Sphere( " Bonnet1 ", Vec3f( -5.5f, -3.f, 4.5f ), 0.7f ) );
		_attachMaterialToObject( "Red", " Bonnet1 " );
		_addObject( new Sphere( " Bonnet2 ", Vec3f( -5.5f, -2.25f, 4.5f ), 0.15f ) );
		_attachMaterialToObject( " PhongBonnet ", " Bonnet2 " );

		//Sphere metalique
		_addObject( new Sphere( " SphereTorrance ", Vec3f( -6.5f, 3.f, 11.5f ), 1.5f ) );
		_attachMaterialToObject( " Torrance1 ", " SphereTorrance " );
		
		//Spheres miroir
		_addObject( new Sphere( " Spheremiroir1 ", Vec3f( 7.5f, -1.f, 12.5f ), 2.5f ) );
		_attachMaterialToObject( " Mirror ", " Spheremiroir1 " );
		_addObject( new Sphere( " Spheremiroir2 ", Vec3f( 3.5f, -1.7f, 8.5f ), 1.5f ) );
		_attachMaterialToObject( " Mirror ", " Spheremiroir2 " );
		_addObject( new Sphere( " Spheremiroir3 ", Vec3f( 1.4f, -2.5f, 7.f ), 0.7f ) );
		_attachMaterialToObject( " Mirror ", " Spheremiroir3 " );

		//Sphere transparente
		_addObject( new Sphere( " Spheretrans ", Vec3f( 6.f, -1.9f, 3.f ), 1.f ) );
		_attachMaterialToObject( " Transparent ", " Spheretrans " );

		// ================================================================
		// Add lights.
		// ================================================================
		//Etoiles
		_addLight( new PointLight( Vec3f( 1.f, 6.5f, 3.f ), WHITE, 40.f ) );
		_addLight(new QuadLight( Vec3f( -4.5f, 6.5f, 10.f ), Vec3f( -1.f, 0.f, 0.f ), Vec3f( 0.f, 1.f, 1.f ), WHITE, 70.f ) );
		_addLight(new QuadLight( Vec3f( 6.5f, 6.5f, 4.5f ), Vec3f( -1.f, 0.f, 0.f ), Vec3f( 0.f, 1.f, 1.f ), WHITE, 70.f ) );
		_addLight(new QuadLight( Vec3f( 4.f, 6.5f, 11.f ), Vec3f( -1.f, 0.f, 0.f ), Vec3f( 0.f, 1.f, 1.f ), WHITE, 70.f ) );
		_addLight( new QuadLight(Vec3f( -6.5f, 6.5f, 6.5f ), Vec3f( -1.f, 0.f, 0.f ), Vec3f( 0.f, 1.f, 1.f ), WHITE, 70.f ) );
	}

	void Scene::loadFileTriangleMesh( const std::string & p_name, const std::string & p_path )
	{
		std::cout << "Loading: " << p_path << std::endl;
		Assimp::Importer importer;

		// Read scene and triangulate meshes
		const aiScene * const scene
			= importer.ReadFile( p_path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_GenUVCoords );

		if ( scene == nullptr ) { throw std::runtime_error( "Fail to load file: " + p_path ); }

		unsigned int cptTriangles = 0;
		unsigned int cptVertices  = 0;

		for ( unsigned int m = 0; m < scene->mNumMeshes; ++m )
		{
			const aiMesh * const mesh = scene->mMeshes[ m ];
			if ( mesh == nullptr ) { throw std::runtime_error( "Fail to load file: " + p_path + ": mesh is null" ); }

			const std::string meshName = p_name + "_" + std::string( mesh->mName.C_Str() );
			std::cout << "-- Load mesh " << m + 1 << "/" << scene->mNumMeshes << ": " << meshName << std::endl;

			cptTriangles += mesh->mNumFaces;
			cptVertices += mesh->mNumVertices;

			const bool hasUV = mesh->HasTextureCoords( 0 );

			MeshTriangle * triMesh = new MeshTriangle( meshName );
			// Vertices before faces otherwise face normals cannot be computed.
			for ( unsigned int v = 0; v < mesh->mNumVertices; ++v )
			{
				triMesh->addVertex( mesh->mVertices[ v ].x, mesh->mVertices[ v ].y, mesh->mVertices[ v ].z );
				triMesh->addNormal( mesh->mNormals[ v ].x, mesh->mNormals[ v ].y, mesh->mNormals[ v ].z );
				if ( hasUV ) triMesh->addUV( mesh->mTextureCoords[ 0 ][ v ].x, mesh->mTextureCoords[ 0 ][ v ].y );
			}
			for ( unsigned int f = 0; f < mesh->mNumFaces; ++f )
			{
				const aiFace & face = mesh->mFaces[ f ];
				triMesh->addTriangle( face.mIndices[ 0 ], face.mIndices[ 1 ], face.mIndices[ 2 ] );
			}

			_addObject( triMesh );

			const aiMaterial * const mtl = scene->mMaterials[ mesh->mMaterialIndex ];
			if ( mtl == nullptr )
			{
				std::cerr << "Material undefined," << meshName << " assigned to default material" << std::endl;
			}
			else
			{
				Vec3f kd = WHITE;
				Vec3f ks = BLACK;
				float s	 = 0.f;

				aiColor3D aiKd;
				if ( mtl->Get( AI_MATKEY_COLOR_DIFFUSE, aiKd ) == AI_SUCCESS ) kd = Vec3f( aiKd.r, aiKd.g, aiKd.b );
				aiColor3D aiKs;
				if ( mtl->Get( AI_MATKEY_COLOR_SPECULAR, aiKs ) == AI_SUCCESS ) ks = Vec3f( aiKs.r, aiKs.g, aiKs.b );
				float aiS = 0.f;
				if ( mtl->Get( AI_MATKEY_SHININESS, aiS ) == AI_SUCCESS ) s = aiS;
				aiString mtlName;
				mtl->Get( AI_MATKEY_NAME, mtlName );

				//_addMaterial( new PlasticMaterial( std::string( mtlName.C_Str() ), kd, ks, s ) );
				//_attachMaterialToObject( mtlName.C_Str(), meshName );
			}

			std::cout << "-- [DONE] " << triMesh->getNbTriangles() << " triangles, " << triMesh->getNbVertices()
					  << " vertices." << std::endl;
		}
		std::cout << "[DONE] " << scene->mNumMeshes << " meshes, " << cptTriangles << " triangles, " << cptVertices
				  << " vertices." << std::endl;
	}



	bool Scene::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const
	{
		float tMax = p_tMax;
		bool  hit  = false;
		for ( const ObjectMapPair & object : _objectMap )
		{
			if ( object.second->intersect( p_ray, p_tMin, tMax, p_hitRecord ) )
			{
				tMax = p_hitRecord._distance; 
				hit	 = true;
			}
		}
		return hit;
	}

	// TP2_Exo 5_1 :
	bool Scene::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		bool  hit  = false;
		for ( const ObjectMapPair & object : _objectMap )
		{
			if ( object.second->intersectAny( p_ray, p_tMin, p_tMax ) )
			{
				hit = true;
			}
		}
		return hit;
	}

	void Scene::_addObject( BaseObject * p_object )
	{
		const std::string & name = p_object->getName();
		if ( _objectMap.find( name ) != _objectMap.end() )
		{
			std::cout << "[Scene::addObject] Object \'" << name << "\' already exists" << std::endl;
			delete p_object;
		}
		else
		{
			_objectMap[ name ] = p_object;
			_objectMap[ name ]->setMaterial( _materialMap[ "default" ] );
		}
	}

	void Scene::_addMaterial( BaseMaterial * p_material )
	{
		const std::string & name = p_material->getName();
		if ( _materialMap.find( name ) != _materialMap.end() )
		{
			std::cout << "[Scene::addMaterial] Material \'" << name << "\' already exists" << std::endl;
			delete p_material;
		}
		else
		{
			_materialMap[ name ] = p_material;
		}
	}

	void Scene::_addLight( BaseLight * p_light ) { _lightList.emplace_back( p_light ); }

	void Scene::_attachMaterialToObject( const std::string & p_materialName, const std::string & p_objectName )
	{
		if ( _objectMap.find( p_objectName ) == _objectMap.end() )
		{
			std::cout << "[Scene::attachMaterialToObject] Object \'" << p_objectName << "\' does not exist"
					  << std::endl;
		}
		else if ( _materialMap.find( p_materialName ) == _materialMap.end() )
		{
			std::cout << "[Scene::attachMaterialToObject] Material \'" << p_materialName << "\' does not exist, "
					  << "object \'" << p_objectName << "\' keeps its material \'"
					  << _objectMap[ p_objectName ]->getMaterial()->getName() << "\'" << std::endl;
		}
		else
		{
			_objectMap[ p_objectName ]->setMaterial( _materialMap[ p_materialName ] );
		}
	}

} // namespace RT_ISICG

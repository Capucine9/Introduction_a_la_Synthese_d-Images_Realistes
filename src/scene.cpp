#include "scene.hpp"
#include "materials/color_material.hpp"
#include "materials/lambert_material.hpp"
#include "materials/Plasticmaterial.hpp"
#include "materials/CookTorranceMaterial.hpp"
#include "objects/sphere.hpp"
#include "objects/Plane.hpp"
#include "lights/PointLight.hpp"
#include "lights/QuadLight.hpp"

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
		_addObject( new Sphere( "Sphere1", Vec3f( 0.f, 0.f, 3.f ), 1.f ) );

		// Add materials
		// TP4_Ex 1_2 :
		_addMaterial( new LambertMaterial( "LambertSphere", GREY ) );
		// TP4_Ex 3 :
		_addMaterial( new PlasticMaterial( "PhongSphere", GREY * 0.7f, GREY * 0.3f, 64.f) );
		// TP4_Ex 4 :
		_addMaterial( new CookTorranceMaterial( "TorranceSphere", YELLOW, YELLOW, 0.f, Vec3f( 1.f, 0.85f, 0.57f ), 0.3f ) );
		
		// Link objects and materials.
		//_attachMaterialToObject( "Blue", "Sphere1" );
		// TP4 :
		//_attachMaterialToObject( "Grey", "Sphere1" );
		// TP4_Ex 1_2 :
		//_attachMaterialToObject( "LambertSphere", "Sphere1" );
		// TP4_Ex 3 :
		//_attachMaterialToObject( "PhongSphere", "Sphere1" );
		// TP4_Ex 4 :
		_attachMaterialToObject( "TorranceSphere", "Sphere1" );

		////////////////////////////////////////////////
		// PLAN

		// TP2_Ex 1_3 :
		// Add objects.
		_addObject( new Plane( "Plan1", Vec3f( 0.f, -2.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );

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
		_addLight( new PointLight( Vec3f( 0.f, 0.f, -2.f ), Vec3f( 1.f, 1.f, 1.f ), 60.f ) );



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

		// ================================================================
		// Add objects .
		// ================================================================
		// Spheres .
		//_addObject( new Sphere( " Sphere1 ", Vec3f( -2.f, 0.f, 3.f ), 1.5f ) );
		//_attachMaterialToObject( " WhiteMatte ", " Sphere1 " );
		//_addObject( new Sphere( " Sphere2 ", Vec3f( 2.f, 0.f, 3.f ), 1.5f ) );
		//_attachMaterialToObject( " WhiteMatte ", " Sphere2 " );

		// Pseudo Cornell box made with infinite planes.
		//_addObject( new Plane( " PlaneGround ", Vec3f( 0.f, -3.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
		//_attachMaterialToObject( " GreyMatte ", " PlaneGround " );
		//_addObject( new Plane( " PlaneLeft ", Vec3f( 5.f, 0.f, 0.f ), Vec3f( -1.f, 0.f, 0.f ) ) );
		//_attachMaterialToObject( " RedMatte ", " PlaneLeft " );
		//_addObject( new Plane( " PlaneCeiling ", Vec3f( 0.f, 7.f, 0.f ), Vec3f( 0.f, -1.f, 0.f ) ) );
		//_attachMaterialToObject( " GreenMatte ", " PlaneCeiling " );
		//_addObject( new Plane( " PlaneRight ", Vec3f( -5.f, 0.f, 0.f ), Vec3f( 1.f, 0.f, 0.f ) ) );
		//_attachMaterialToObject( " BlueMatte ", " PlaneRight " );
		//_addObject( new Plane( " PlaneFront ", Vec3f( 0.f, 0.f, 10.f ), Vec3f( 0.f, 0.f, -1.f ) ) );
		//_attachMaterialToObject( " MagentaMatte ", " PlaneFront " );

		// ================================================================
		// Add lights .
		// ================================================================
		//_addLight( new PointLight( Vec3f( 0.f, 5.f, 0.f ), WHITE, 100.f ) );
		//_addLight(new QuadLight( Vec3f( 1.f, 5.f, -2.f ), Vec3f( -2.f, 0.f, 0.f ), Vec3f( 0.f, 1.f, 2.f ), WHITE, 40.f ) );
	}

	bool Scene::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const
	{
		float tMax = p_tMax;
		bool  hit  = false;
		for ( const ObjectMapPair & object : _objectMap )
		{
			if ( object.second->intersect( p_ray, p_tMin, p_tMax, p_hitRecord ) )
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
				hit	 = true;
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

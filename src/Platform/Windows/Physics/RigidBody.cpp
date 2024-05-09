#include "Andromeda/Physics/RigidBody.h"
#include "PxPhysicsAPI.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace And{


	struct PhysicsData {
		physx::PxPhysics* physics;
		physx::PxRigidDynamic* actor;
		physx::PxScene* scene;
	};

RigidBody::RigidBody() : m_data(){
}

RigidBody::~RigidBody() {

}

RigidBody::RigidBody(const RigidBody& other) {
	
	this->m_data = other.m_data;
	/*this->m_affects_gravity = other.m_affects_gravity;
	this->m_actor = other.m_actor;
	this->m_physics = other.m_physics;
	this->m_scene = other.m_scene;*/
}

RigidBody RigidBody::operator=(const RigidBody& other){
	this->m_data = other.m_data;
	/*this->m_actor = other.m_actor;
	this->m_physics = other.m_physics;
	this->m_scene = other.m_scene;*/
	return *this;
}


RigidBody::RigidBody(RigidBody&& other) {
	this->m_data = other.m_data;
	/*this->m_actor = other.m_actor;
	this->m_physics = other.m_physics;
	this->m_scene = other.m_scene;*/
}

void RigidBody::AffectsGravity(bool value)
{
}

void RigidBody::AddBoxCollider(const float* position, const float* scale){

	physx::PxTransform transform(physx::PxVec3(0.0f));
	transform.p = physx::PxVec3(position[0], position[1], position[2]);
	m_data->actor = m_data->physics->createRigidDynamic(transform);
	
	physx::PxBoxGeometry box(scale[0] * 0.5f, scale[1] * 0.5f, scale[2] * 0.5f);
	physx::PxMaterial* mat = m_data->physics->createMaterial(1.0f, 1.0f, 1.0f); // static friction, dynamic friction, restitution);
	physx::PxShape* shape = m_data->physics->createShape(box, *mat, false); // is exclusive = false
	//boxShape->setLocalPose(physx::PxTransform(0.0f, 0.0f, 0.0f));
	//boxShape->setLocalPose(transform);

	m_data->actor->attachShape(*shape);
	m_data->actor->setGlobalPose(transform);
	m_data->actor->getGlobalPose();
	m_data->actor->setMass(1.0f);
	m_data->scene->addActor(*(m_data->actor));
}

void RigidBody::AddSphereCollider(const float* position, const float* radius){

	physx::PxTransform transform(physx::PxVec3(0.0f));
	transform.p = physx::PxVec3(position[0], position[1], position[2]);
	m_data->actor = m_data->physics->createRigidDynamic(transform);

	float r = *radius;

	physx::PxSphereGeometry sphere(r);
	physx::PxMaterial* mat = m_data->physics->createMaterial(0.5f, 0.5f, 0.0f); // static friction, dynamic friction, restitution);
	physx::PxShape* shape = m_data->physics->createShape(sphere, *mat, true);

	m_data->actor->attachShape(*shape);
	m_data->actor->setGlobalPose(transform);
	m_data->actor->getGlobalPose();
	m_data->actor->setMass(1.0f);
	m_data->scene->addActor(*(m_data->actor));
}

void RigidBody::Release(){
	m_data->actor->release();
}

void RigidBody::SetMass(float mass) {
	m_data->actor->setMass(mass);
}

void RigidBody::AddForce(const float x, const float y, const float z, ForceMode fmod){

	physx::PxForceMode::Enum f;

	switch (fmod) {
		case ForceMode::ACCELERATION: f = physx::PxForceMode::eACCELERATION; break;
		case ForceMode::FORCE: f = physx::PxForceMode::eFORCE; break;
		case ForceMode::IMPULSE: f = physx::PxForceMode::eIMPULSE; break;
		case ForceMode::VELOCITY_CHANGE: f = physx::PxForceMode::eVELOCITY_CHANGE; break;
	}
	m_data->actor->addForce(physx::PxVec3(x,y,z), f);
}

void RigidBody::AddForce(const float* direction, ForceMode fmod){
	physx::PxForceMode::Enum f;

	switch (fmod) {
		case ForceMode::ACCELERATION: f = physx::PxForceMode::eACCELERATION; break;
		case ForceMode::FORCE: f = physx::PxForceMode::eFORCE; break;
		case ForceMode::IMPULSE: f = physx::PxForceMode::eIMPULSE; break;
		case ForceMode::VELOCITY_CHANGE: f = physx::PxForceMode::eVELOCITY_CHANGE; break;
	}

	m_data->actor->addForce(physx::PxVec3(direction[0], direction[1], direction[2]), f);
}

void RigidBody::SetPosition(float* pos){

	physx::PxTransform tr{ pos[0], pos[1], pos[2]};
	m_data->actor->setGlobalPose(tr);
}

void RigidBody::SetPosition(float x, float y, float z){

	physx::PxTransform tr{ x, y, z };
	m_data->actor->setGlobalPose(tr);
}


void RigidBody::GetPosition(float* position){

	physx::PxTransform transform = m_data->actor->getGlobalPose();
	position[0] = transform.p.x;
	position[1] = transform.p.y;
	position[2] = transform.p.z;
}

void RigidBody::GetRotation(float* rotation)
{
	
	physx::PxTransform transform = m_data->actor->getGlobalPose();
	rotation[0] = transform.q.x;
	rotation[1] = transform.q.y;
	rotation[2] = transform.q.z;
}

void RigidBody::GetPositionRotation(float* position, float* rotation){

	
	physx::PxTransform transform = m_data->actor->getGlobalPose();
	rotation[0] = transform.q.x;
	rotation[1] = transform.q.y;
	rotation[2] = transform.q.z;

	position[0] = transform.p.x;
	position[1] = transform.p.y;
	position[2] = transform.p.z;
}

}
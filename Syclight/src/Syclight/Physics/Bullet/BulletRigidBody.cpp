#include "BulletRigidBody.h"

namespace syc {

	BulletRigidBody::BulletRigidBody(Ref<btRigidBody> body) : m_body(body) {}

	BulletRigidBody::~BulletRigidBody()
	{
		delete m_body->getMotionState();
		delete m_body->getCollisionShape();
		delete m_body;
	}

	void BulletRigidBody::ApplyForce(const glm::vec3& force)
	{
		m_body->applyCentralForce(btVector3(force.x, force.y, force.z));
	}

	glm::vec3 BulletRigidBody::GetPosition() const
	{
		btTransform trans;
		m_body->getMotionState()->getWorldTransform(trans);
		btVector3 origin = trans.getOrigin();
		return glm::vec3(origin.x(), origin.y(), origin.z());
	}

	glm::quat BulletRigidBody::GetRotation() const
	{
		btTransform trans;
		m_body->getMotionState()->getWorldTransform(trans);
		btQuaternion q = trans.getRotation();
		return glm::quat(q.w(), q.x(), q.y(), q.z());
	}
}
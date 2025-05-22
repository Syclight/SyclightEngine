#include "sycpch.h"
#include "BulletPhysicsWorld.h"
#include "BulletRigidBody.h"

namespace syc {
    BulletPhysicsWorld::BulletPhysicsWorld()
    {
        m_config = new btDefaultCollisionConfiguration();
        m_dispatcher = new btCollisionDispatcher(m_config);
        m_broadphase = new btDbvtBroadphase();
        m_solver = new btSequentialImpulseConstraintSolver();
        m_world = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_config);
        m_world->setGravity(btVector3(0, -9.8f, 0));
    }

    BulletPhysicsWorld::~BulletPhysicsWorld()
    {
        delete m_world;
        delete m_solver;
        delete m_broadphase;
        delete m_dispatcher;
        delete m_config;
    }

    void_ BulletPhysicsWorld::StepSimulation(float deltaTime)
    {
        m_world->stepSimulation(deltaTime);
    }

    void_ BulletPhysicsWorld::SetGravity(const glm::vec3& gravity)
    {
        m_world->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
    }

    Ref<IRigidBody> BulletPhysicsWorld::CreateRigidBody(float mass, const glm::vec3& pos)
    {
        btCollisionShape* shape = new btBoxShape(btVector3(1, 1, 1)); // 固定大小
        btTransform transform;
        transform.setIdentity();
        transform.setOrigin(btVector3(pos.x, pos.y, pos.z));

        btVector3 inertia(0, 0, 0);
        if (mass > 0.0f)
            shape->calculateLocalInertia(mass, inertia);

        btDefaultMotionState* motionState = new btDefaultMotionState(transform);
        btRigidBody::btRigidBodyConstructionInfo info(mass, motionState, shape, inertia);
        btRigidBody* body = new btRigidBody(info);

        m_world->addRigidBody(body);

        auto rigidBody = std::make_unique<BulletRigidBody>(body);
        IRigidBody* result = rigidBody.get();
        m_bodies.push_back(std::move(rigidBody));
        return result;
    }
}
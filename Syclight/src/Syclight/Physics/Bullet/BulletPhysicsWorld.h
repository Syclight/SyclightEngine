#pragma once

#include "../IPhysicsWorld.h"
#include <btBulletDynamicsCommon.h>
#include <vector>
#include <memory>

namespace syc {

    class BulletRigidBody;

    class SYC_API BulletPhysicsWorld : public IPhysicsWorld {
    public:
        BulletPhysicsWorld();
        ~BulletPhysicsWorld();

        void_ StepSimulation(float deltaTime) override;
        void_ SetGravity(const glm::vec3& gravity) override;
        Ref<IRigidBody> CreateRigidBody(float mass, const glm::vec3& position) override;

    private:
        btDefaultCollisionConfiguration* m_config;
        btCollisionDispatcher* m_dispatcher;
        btBroadphaseInterface* m_broadphase;
        btSequentialImpulseConstraintSolver* m_solver;
        btDiscreteDynamicsWorld* m_world;

        std::vector<std::unique_ptr<BulletRigidBody>> m_bodies;
    };
}
#pragma once
#include "../IRigidBody.h"
#include <btBulletDynamicsCommon.h>

namespace syc {

    class SYC_API BulletRigidBody : public IRigidBody {
    public:
        BulletRigidBody(Ref<btRigidBody> body);
        ~BulletRigidBody();

        void ApplyForce(const glm::vec3& force) override;
        glm::vec3 GetPosition() const override;
        glm::quat GetRotation() const override;

    private:
        Ref<btRigidBody> m_body;
    };
}
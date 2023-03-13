#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

namespace graphics{
    class Camera{
    private:
        glm::vec3 pos;
        float yaw, pitch, roll;
        glm::mat4 projection;
    public:
        Camera(glm::vec3 pos, float yaw, float pitch, float roll);
        ~Camera();
        void setPos(glm::vec3 newPos);
        void addPos(glm::vec3 dPos);
        void setYaw(float newYaw);
        void setPitch(float newPitch);
        void setRoll(float newRoll);
        void updateProjectionMatrix(float FOV, float aspectRatio, float near = 0.1f, float far = 1000.0f);
        const glm::vec3 *getPos();
        float getYaw();
        float getPitch();
        float getRoll();
        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix();
        glm::mat4 getViewProjMatrix();
        glm::vec3 getFacingVector();
    };
}
/**
 * Copyright 2012 Batis Degryll Ludo
 * @file builders.cpp
 * @since 2026-12-05
 * @date 2026-12-05
 * @author Degryll Batis Ludo
 * @brief Define the basic functionality of every entity.
 */

#include "ZBE/entities/builders/builders.h"

namespace zbe {

void calculateRotation(glm::vec3 originDirection, glm::vec3 originUp, glm::vec3 destinationDirection, glm::vec3 destinationUp, glm::vec3& rotationAxis, double& rotationAngle) {
    // Crear las matrices de orientación
    glm::mat4 originOrientation = glm::lookAt(glm::vec3(0.0f), originDirection, originUp);
    glm::mat4 destinationOrientation = glm::lookAt(glm::vec3(0.0f), destinationDirection, destinationUp);

    // Calcular la matriz de rotación
    glm::mat4 rotationMatrix = glm::inverse(originOrientation) * destinationOrientation;

    // Convertir la matriz de rotación a un cuaternión
    glm::quat quaternion = glm::quat_cast(rotationMatrix);

    // Obtener el ángulo y el vector de rotación del cuaternión
    rotationAngle = 2 * acos(quaternion.w);
    rotationAxis = glm::normalize(glm::vec3(quaternion.x, quaternion.y, quaternion.z));
}

}  // namespace zbe


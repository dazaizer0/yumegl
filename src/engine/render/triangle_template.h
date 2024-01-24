#pragma once

#include "../../config.h"
#include "triangle_modules.h"

trm::classic_triangle::classic_triangle() {
    data = {
            -0.5f/*x*/, -0.5f /*y*/, -0.0f/*z*/, 1.0f/*r*/, 1.0f/*g*/, 1.0f/*b*/,
            0.5f/*x*/, -0.5f/*y*/, 0.0f/*z*/, 1.0f/*r*/, 1.0f/*g*/, 1.0f/*b*/,
            -0.5f/*x*/,  0.5f/*y*/, 0.0f/*z*/, 1.0f/*r*/, 1.0f/*g*/, 1.0f/*b*/
    };

    vertex_count = 3;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*)0);
    glEnableVertexAttribArray(0);

    //color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*)12);
    glEnableVertexAttribArray(1);

}

void trm::classic_triangle::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}

void trm::classic_triangle::del() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

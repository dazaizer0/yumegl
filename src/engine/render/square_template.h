#pragma once

#include "../../config.h"
#include "square_module.h"

 sqm::classic_square::classic_square() {
    data = {
            -0.2f/*0-x*/, -0.2f /*1-y*/, 0.0f/*2-z*/,
            1.0f/*3-r*/, 0.0f/*4-g*/, 0.0f/*5-b*/,

            0.2f/*6-x*/, -0.2f/*7-y*/, 0.0f/*8-z*/, 0.0f/*9-r*/,
            1.0f/*10-g*/, 0.0f/*11-b*/,

            -0.2f/*12-x*/,  0.2f/*13-y*/, 0.0f/*14-z*/, 0.0f/*15-r*/,
            0.0f/*16-g*/, 1.0f/*17-b*/,

            0.2f/*18-x*/,  0.2f/*19-y*/, 0.0f/*20-z*/, 1.0f/*21-r*/,
            0.0f/*22-g*/, 0.0f/*23-b*/
    };

    vertex_count = 4;

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

void sqm::classic_square::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, vertex_count);
}

void sqm::classic_square::del() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

#include "skybox.h"
#include "tools.h"

#include <string>
#include <vector>

#include <iostream>
using namespace std;

Skybox::Skybox(std::string vert_path, std::string frag_path) :
    skyboxShader(vert_path.c_str(), frag_path.c_str()), textureSkybox(0)
{
    //��������
    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    //����
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //��
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

    //��������
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    return;
}

Skybox::~Skybox()
{

}

void Skybox::release()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Skybox::render(glm::mat4 projection, glm::mat4 view)
{
    glDepthFunc(GL_LEQUAL);		//��պ����Ϊ1.0��<=1.0ͨ����Ȳ���

    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);

    view = glm::mat4(glm::mat3(view));  //mat4-->mat3-->mat4������λ�ƣ�������ת
    skyboxShader.setMat4("view", view);
    skyboxShader.setMat4("projection", projection);

    //����
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureSkybox);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
    glDepthFunc(GL_LESS);		//������Ȳ��Ժ���Ϊ<

    return;
}

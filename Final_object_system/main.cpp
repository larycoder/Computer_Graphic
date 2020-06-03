// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include Glew. Always include it before gl.h and glfw3.h, since its a bit magic
#include <GL/glew.h>

// Include GLFW = handle the window and the keyboard 2 option: GLFW/freeglut
#include <GLFW/glfw3.h>

// Include glm for 3D mathematics
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>

#include "common/shader.h"

GLFWwindow* window; // window object

struct model_buffer{
  GLuint id;
  GLuint texture_id;
  int size;
  glm::mat4 MVP;
};

// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};

// One color for each vertex. They were generated randomly.
static const GLfloat g_color_buffer_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};

// Two UV coordinatesfor each vertex. They were created with Blender. You'll learn shortly how to do this yourself.
static const GLfloat g_uv_buffer_data[] = {
    0.000059f, 1.0f-0.000004f,
    0.000103f, 1.0f-0.336048f,
    0.335973f, 1.0f-0.335903f,
    1.000023f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.336024f, 1.0f-0.671877f,
    0.667969f, 1.0f-0.671889f,
    1.000023f, 1.0f-0.000013f,
    0.668104f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.000059f, 1.0f-0.000004f,
    0.335973f, 1.0f-0.335903f,
    0.336098f, 1.0f-0.000071f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.336024f, 1.0f-0.671877f,
    1.000004f, 1.0f-0.671847f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.668104f, 1.0f-0.000013f,
    0.335973f, 1.0f-0.335903f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.668104f, 1.0f-0.000013f,
    0.336098f, 1.0f-0.000071f,
    0.000103f, 1.0f-0.336048f,
    0.000004f, 1.0f-0.671870f,
    0.336024f, 1.0f-0.671877f,
    0.000103f, 1.0f-0.336048f,
    0.336024f, 1.0f-0.671877f,
    0.335973f, 1.0f-0.335903f,
    0.667969f, 1.0f-0.671889f,
    1.000004f, 1.0f-0.671847f,
    0.667979f, 1.0f-0.335851f
};

// ground model : vertex, normal, uv
static const GLfloat ground[] = {
  -50.0f, -5.0f, -50.0f,
  0.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  -50.0f, -5.0f, 50.0f,
  0.0f, 1.0f,
  0.0f, 1.0f, 0.0f,
  50.0f, -5.0f, -50.0f,
  1.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  -50.0f, -5.0f, 50.0f,
  0.0f, 1.0f,
  0.0f, 1.0f, 0.0f,
  50.0f, -5.0f, 50.0f,
  1.0f, 1.0f,
  0.0f, 1.0f, 0.0f,
  50.0f, -5.0f, -50.0f,
  1.0f, 0.0f,
  0.0f, 1.0f, 0.0f
};

model_buffer setGround(void){
  // load texture
  GLuint groundTexture = loadBMP_custom("image/usth.bmp");
  // This will identify our vertex buffer
  model_buffer ground_model;
  // Generate 1 buffer, put the resulting identifier in vertexbuffer
  glGenBuffers(1, &ground_model.id);
  // talk about our 'vertexbuffer' buffer
  glBindBuffer(GL_ARRAY_BUFFER, ground_model.id);
  // give our vertices to openGL
  glBufferData(GL_ARRAY_BUFFER, sizeof(ground), ground, GL_STATIC_DRAW);
  // model size
  ground_model.size = sizeof(ground);
  // Model transform
  ground_model.MVP = glm::mat4(1.0f);
  // texture id
  ground_model.texture_id = groundTexture;
  return ground_model;
}

void drawGround(GLuint programID, model_buffer ground_model){
  GLuint MatrixID = glGetUniformLocation(programID, "M");
  glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(ground_model.MVP));
  MatrixID = glGetUniformLocation(programID, "V");
  glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(getViewMatrix()));
  MatrixID = glGetUniformLocation(programID, "P");
  glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(getProjMatrix()));
  // load texture
  glBindTexture(GL_TEXTURE_2D, ground_model.texture_id);
  glActiveTexture(GL_TEXTURE + ground_model.texture_id);

  glBindBuffer(GL_ARRAY_BUFFER, ground_model.id);
  // 1st attribute buffer: vertices
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, (void *)0);
  // 2nd attr: uv coordinate
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (void *)12);
  // 3rd attr: normal coordinate
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (void *)20);
  // Accept fragment if it closer to the camera than the former one
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  // Cull triangles which normal is not towards the camera
  glEnable(GL_CULL_FACE);
  // Use our shader
  glUseProgram(programID);
  // Draw the triangle
  glDrawArrays(GL_TRIANGLES, 0, ground_model.size / 12); // Starting from vertex 0; 3 vertices total -> 1 triangle
  // disable stream
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}

// constant string of model file
const char *model_file[] = {
  "blender_model/cube.obj",
  "blender_model/cube2.obj",
  "blender_model/suzanna2.obj",
  "blender_model/suzanne.obj",
  "blender_model/tube.obj"
};

model_buffer *setModel(void){
  // load object model from blender obj file
  static model_buffer obj_model[5];

  for(int i = 0; i < 5; i++){
    // create vbo
    printf("load file %s\n", model_file[i]);
    obj_model[i].id = loadOBJ(model_file[i]);
    printf("obj model id: %d\n", obj_model[i].id);
    // get size of VBO
    glBindBuffer(GL_ARRAY_BUFFER, obj_model[i].id);
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &obj_model[i].size);
    // set MVP
    obj_model[i].MVP = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f * i * 4.0f));
    // obj_model[i].MVP = glm::mat4(1.0f);

    // load texture
    GLuint objTexture;
    if(i == 0){
      objTexture = loadBMP_custom("image/sun.bmp");
    }
    else if(i < 2){
      objTexture = loadBMP_custom("image/ground.bmp");
    }
    else{
      objTexture = loadBMP_custom("image/wood_MC.bmp");
    }
    // set texture
    obj_model[i].texture_id = objTexture;
    printf("obj model texture id: %d\n", obj_model[i].texture_id);
  }
  return obj_model;
}

void drawModel(GLuint programID, model_buffer *obj_model){
  for(int i = 0; i < 5; i++){
      // Send our transformation to the currently bound shader, in the "MVP" uniform
      // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
      GLuint MatrixID = glGetUniformLocation(programID, "M");
      glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(obj_model[i].MVP));
      MatrixID = glGetUniformLocation(programID, "V");
      glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(getViewMatrix()));
      MatrixID = glGetUniformLocation(programID, "P");
      glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(getProjMatrix()));
      // load texture
      glBindTexture(GL_TEXTURE_2D, obj_model[i].texture_id);
      glActiveTexture(GL_TEXTURE + obj_model[i].texture_id);

      glBindBuffer(GL_ARRAY_BUFFER, obj_model[i].id);
      // 1st attribute buffer: vertices
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, (void *)0);
      // 2nd attr: uv coordinate
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (void *)12);
      // 3rd attr: normal coordinate
      glEnableVertexAttribArray(2);
      glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (void *)20);
      // Accept fragment if it closer to the camera than the former one
      glEnable(GL_DEPTH_TEST);
      glDepthFunc(GL_LESS);
      // Cull triangles which normal is not towards the camera
      glEnable(GL_CULL_FACE);
      // Use our shader
      glUseProgram(programID);
      // Draw the triangle
      glDrawArrays(GL_TRIANGLES, 0, obj_model[i].size / 12); // Starting from vertex 0; 3 vertices total -> 1 triangle
      // disable stream
      glDisableVertexAttribArray(0);
      glDisableVertexAttribArray(1);
      glDisableVertexAttribArray(2);
    }
}

int main(){
  glewExperimental = true; // Needed for core profile

  // Initialize GLFW
  if(!glfwInit()){
    fprintf(stderr, "Failed to initialize GLFW\n");
    return -1;
  }

  // open openGL window
  glfwWindowHint(GLFW_SAMPLES, 4); //  4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // we want openGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // we dont want the old openGL

  // Open a window and create its OpenGL context
  window = glfwCreateWindow(500, 458, "openGL_Learn", NULL, NULL);
  if(window == NULL){
    fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version.\n" );
    glfwTerminate();
    return -1;
  }


  glfwMakeContextCurrent(window); // Initialize GLEW
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return -1;
  }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // VAO
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  // Color attribute
  // GLuint colorbuffer;
  // glGenBuffers(1, &colorbuffer);
  // glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

  // texture attribute
  // GLuint uv_buffer;
  // glGenBuffers(1, &uv_buffer);
  // glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

  // Create and compile our GLSL program from the shaders
  GLuint programID = loadShaders("simpleVrtShd.glsl", "simpleFrgShd.glsl");

  // register callback for mouse
  glfwSetCursorPosCallback(window, direction_update);

  // set screen to blue sky
  glClearColor(0.53, 0.8, 0.92, 1.0);

  // setup model
  model_buffer *obj_model = setModel();
  model_buffer ground_model = setGround();
  // loop
  do{
    // Clear the screen buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // compute new position
    computeMatricesFromInputs(window);

    // lighting setup
    GLuint ambientStrength = glGetUniformLocation(programID, "ambientStrength");
    glUniform1f(ambientStrength, 0.1f);
    GLuint specularStrength = glGetUniformLocation(programID, "specularStrength");
    glUniform1f(specularStrength, 0.9f);
    GLuint lightPos = glGetUniformLocation(programID, "lightPos");
    glUniform3f(lightPos, 0.0f, 50.0f, 10.0f);
    GLuint viewPos = glGetUniformLocation(programID, "viewPos");
    glUniform3f(viewPos, getCamPos().x, getCamPos().y, getCamPos().z);

    // draw object
    drawModel(programID, obj_model);
    drawGround(programID, ground_model);

    // swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

  // check if the ESC key was pressed or the window was closed
  } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

  return 0;
}

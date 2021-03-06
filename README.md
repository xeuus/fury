# FURY
I know it sound promising, but it's a big project of mine, feel free to collaborate, i keep pushing the updates.  

![box3d](https://github.com/xeuus/fury/raw/master/screen.png)


## Working Example
```cpp

#include <Fury/Core.h>
static f32 pitch = 0;
static f32 yaw = 0;
static f32 pitch2 = 1;
static f32 yaw2 = 0.6;
static f32 distance = 6;
static f32 distance2 = 10;

static Shader sh;
static GLuint vao, vbo, ebo;

Vec3 cam{0, 0, 0}, lightPos{0, 0, 0}, center{0, 0, 0};
Vec3 vel = 0;

f32 fps = 0;
f32 lt = 0;

class Win1 : public Window {

    void create() override {

        Input::Init(this->window);

        sh.create(Path::local("..", "src", "z04_ok", "shader"));


        GLfloat vertices[] = {
                // front
                -1.0f, -1.0f, 1.0f, 0, 0, 1,
                1.0f, -1.0f, 1.0f, 0, 0, 1,
                1.0f, 1.0f, 1.0f, 0, 0, 1,
                -1.0f, 1.0f, 1.0f, 0, 0, 1,

                //right
                1.0f, 1.0f, 1.0f, 1, 0, 0,
                1.0f, 1.0f, -1.0f, 1, 0, 0,
                1.0f, -1.0f, -1.0f, 1, 0, 0,
                1.0f, -1.0f, 1.0f, 1, 0, 0,

                //back
                -1.0f, -1.0f, -1.0f, 0, 0, -1,
                1.0f, -1.0f, -1.0f, 0, 0, -1,
                1.0f, 1.0f, -1.0f, 0, 0, -1,
                -1.0f, 1.0f, -1.0f, 0, 0, -1,

                //left
                -1.0f, -1.0f, -1.0f, -1, 0, 0,
                -1.0f, -1.0f, 1.0f, -1, 0, 0,
                -1.0f, 1.0f, 1.0f, -1, 0, 0,
                -1.0f, 1.0f, -1.0f, -1, 0, 0,

                //upper
                1.0f, 1.0f, 1.0f, 0, 1, 0,
                -1.0f, 1.0f, 1.0f, 0, 1, 0,
                -1.0f, 1.0f, -1.0f, 0, 1, 0,
                1.0f, 1.0f, -1.0f, 0, 1, 0,

                //bottom
                -1.0f, -1.0f, -1.0f, 0, -1, 0,
                1.0f, -1.0f, -1.0f, 0, -1, 0,
                1.0f, -1.0f, 1.0f, 0, -1, 0,
                -1.0f, -1.0f, 1.0f, 0, -1, 0,
        };
        GLuint indices[] = {
                0, 1, 2, 0, 2, 3, //front
                4, 5, 6, 4, 6, 7, //right
                8, 9, 10, 8, 10, 11, //back
                12, 13, 14, 12, 14, 15, //left
                16, 17, 18, 16, 18, 19, //upper
                20, 21, 22, 20, 22, 23, //bottom
        };


        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);


        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    }

    void fixedUpdate() override {


    }

    void update() override {

        Input::update();


        f32 deltaTime = Time::smoothDeltaTime;

        pitch -= Input::GetAxis(Axis::Horizontal) * deltaTime;
        yaw += Input::GetAxis(Axis::Vertical) * deltaTime;


        cam = Vec3::smoothDamp(cam, Quaternion::fromEulerAngles(pitch, 0, yaw) * Vec3{0, 0, -distance} + center, vel, 0.2f, 40, deltaTime);
        lightPos = Quaternion::fromEulerAngles(pitch2, 0, yaw2) * Vec3{0, 0, -distance2} + center;


    }

    void draw() override {


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        f32 width = Display::width;
        f32 height = Display::height;

        sh.begin();


        Mat4 model = Mat4::identify * Mat4::createScale({1, 1, 1});
        Mat4 proj = Mat4::perspective(50 * Math::DEG2RAD, width / height, 0.1, 100);
        Mat4 view = Mat4::lookAt(cam, center, {0, 1, 0});


        sh.setParam("world", model);
        sh.setParam("view", view);
        sh.setParam("projection", proj);
        sh.setParam("cameraPosition", cam);
        sh.setParam("lightPosition", lightPos);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        sh.end();


    }

    void dispose() override {
        sh.dispose();
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
    };

};


int main() {

    auto w = Win1();
    return w.run();
}


```

run the example:
```

git clone https://github.com/xeuus/fury
cd fury
mkdir build && cd build
cmake ..
make && ././bin_z04_ok

```
## Future of this project

well, there are couple of things i like to put on this project, 
1. Decent ECS(entity/component/system) manager.
2. Assent pipelining tools.
3. 2d Graphics helpers,
4. 2d Physics implementation. 
5. 2d Asset editor.
6. 2d Scene editor.
7. 2d Character rig, animator studio.
8. 


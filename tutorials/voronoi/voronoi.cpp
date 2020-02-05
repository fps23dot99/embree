// ======================================================================== //
// Copyright 2009-2020 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#include "../common/tutorial/tutorial.h"

namespace embree
{
  typedef void (*DrawGUI)(void);

  extern "C" {
    int g_num_points = 128;
    int g_num_knn = 4;
    bool g_show_voronoi = true;
    bool g_point_repulsion = false;
    float g_tmax = inf;
    DrawGUI g_drawGUI = nullptr;
    Vec3fa g_query_point(0.7f, 0.0f, 0.3f);
  }

  struct Tutorial : public TutorialApplication 
  {
    Tutorial()
      : TutorialApplication("voronoi", FEATURE_RTCORE | FEATURE_STREAM) 
    { }

    void drawGUI() override
    {
      ImGui::SliderInt ("Number of points", &g_num_points, 4, 4096);
      if (g_drawGUI)
        g_drawGUI();
    }

    void keypressed(int key) override
    {
      if (key == GLFW_KEY_RIGHT) g_query_point.x += 0.01f;
      if (key == GLFW_KEY_LEFT)  g_query_point.x -= 0.01f;
      if (key == GLFW_KEY_UP)    g_query_point.z += 0.01f;
      if (key == GLFW_KEY_DOWN)  g_query_point.z -= 0.01f;
      g_query_point = max(g_query_point, Vec3fa(0.f));
      g_query_point = min(g_query_point, Vec3fa(1.f));
      
      TutorialApplication::keypressed(key);
    }

  };

}

int main(int argc, char** argv) {
  return embree::Tutorial().main(argc,argv);
}

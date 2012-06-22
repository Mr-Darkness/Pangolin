#include <iostream>
#include <boost/thread.hpp>
#include <pangolin/pangolin.h>

using namespace pangolin;
using namespace std;

#include <pangolin/display_internal.h>

int main( int /*argc*/, char* argv[] )
{
  // Create OpenGL window in single line thanks to GLUT
  pangolin::CreateGlutWindowAndBind("Main",640,480);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Issue specific OpenGl we might need
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  DataLog log;

  const int UI_WIDTH = 180;

  View& d_graph = pangolin::CreatePlotter("x",&log)
      .SetBounds(0.0, 1.0, Attach::Pix(UI_WIDTH), 1.0);

  View& d_panel = pangolin::CreatePanel("ui")
      .SetBounds(0.0, 1.0, 0.0, Attach::Pix(UI_WIDTH) );

  double t = 0;

  vector<std::string> labels;

  labels.push_back(std::string("sin(t)"));
  labels.push_back(std::string("cos(t)"));
  labels.push_back(std::string("tan(t)"));
  labels.push_back(std::string("sin(t)+cos(t)"));

  log.SetLabels(labels);

  // Default hooks for exiting (Esc) and fullscreen (tab).
  while( !pangolin::ShouldQuit() )
  {
    if(HasResized())
      DisplayBase().ActivateScissorAndClear();

    static Var<double> tinc("ui.t inc",0.01,0,0.1);

    log.Log(sin(t),cos(t),tan(t),sin(t)+cos(t));
    t += tinc;

    // Render special panals
    d_panel.Render();
    d_graph.Render();

    // Swap frames and Process Events
    SwapBuffersProcessEvents();
    boost::this_thread::sleep(boost::posix_time::milliseconds(10));
  }

  return 0;
}

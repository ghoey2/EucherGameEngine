#include <visualizer/euchre_app.h>

using euchre::EuchreApp;


void prepareSettings(EuchreApp::Settings *settings) {
    settings->setResizable(false);
    settings->setFrameRate( 1.0f );

}

CINDER_APP(EuchreApp, cinder::app::RendererGl, prepareSettings);
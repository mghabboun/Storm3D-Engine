#ifndef APP_WORLD_WINDOW
#define APP_WORLD_WINDOW

namespace AppWorld 
{


class Window
{

    Window();
   void Initialize(int argc, char**argv);

    void Close();
    void MainLoop();
    void Render();
    void Update();
    void LateUpdate();

    void SetWindowDimensions(int width, int height);
    void SetFullScreen (bool fullscreen);

private: 

    int m_width; 
    int m_height; 
    bool m_done; 
    bool m_fullScreen; 



};

}
#endif 
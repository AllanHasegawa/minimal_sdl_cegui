
#include <iostream>

#include <string>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <CEGUI/CEGUI.h>

using namespace std;

int main(void)
{
	cout << "Hello world" << endl;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cout << SDL_GetError() << endl;
	}

	SDL_Window* win = SDL_CreateWindow("msc", 0, 0, 1280, 720,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	SDL_GLContext gl_context = SDL_GL_CreateContext(win);
	SDL_GL_MakeCurrent(win, gl_context);

	CEGUI::OpenGL3Renderer& myRenderer =
		    CEGUI::OpenGL3Renderer::bootstrapSystem();

	//CEGUI::System::create( myRenderer );
	CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>
		    (CEGUI::System::getSingleton().getResourceProvider());
	rp->setResourceGroupDirectory("schemes", "./datafiles/schemes/");
	rp->setResourceGroupDirectory("imagesets", "./datafiles/imagesets/");
	rp->setResourceGroupDirectory("fonts", "./datafiles/fonts/");
	rp->setResourceGroupDirectory("layouts", "./datafiles/layouts/");
	rp->setResourceGroupDirectory("looknfeels", "./datafiles/looknfeel/");
	rp->setResourceGroupDirectory("lua_scripts", "./datafiles/lua_scripts/");

	CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

	CEGUI::SchemeManager::getSingleton().createFromFile( "OgreTray.scheme" );

	CEGUI::WindowManager& winMgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window* root;
	root = winMgr.loadLayoutFromFile("gui.layout");
	CEGUI::GUIContext& gt = CEGUI::System::getSingleton().getDefaultGUIContext();
	gt.setRootWindow( root );

	CEGUI::Window* st = root->getChild("testWindow/text");
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	int i{0};
	while (true) {
		++i;
		st->setText("Hi " + std::to_string(i) + "\n" + "Hello World!");
		glClear(GL_COLOR_BUFFER_BIT);
		CEGUI::System::getSingleton().renderAllGUIContexts();
		SDL_GL_SwapWindow(win);
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return 0;
			} else if (event.type == SDL_MOUSEMOTION) {
				gt.injectMousePosition(event.motion.x, event.motion.y);
			} else if (event.type == SDL_MOUSEBUTTONDOWN) {
				gt.injectMouseButtonDown(CEGUI::LeftButton);
			} else if (event.type == SDL_MOUSEBUTTONUP) {
				gt.injectMouseButtonUp(CEGUI::LeftButton);
			}
		}
	}

	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}

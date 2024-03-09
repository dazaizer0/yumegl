#ifndef YUMEGL_RENDERER_HPP
#define YUMEGL_RENDERER_HPP

#include "../../config.h"
#include "render.hpp"

namespace rd::mng {
	class Renderer {
	public:
		Renderer ();
		~Renderer ();

	private:
		// example 
		std::vector<rd2::ExtendedObject> rendererData;
	};

	Renderer::Renderer () {
	}

	Renderer::~Renderer () {
	}
}

#endif
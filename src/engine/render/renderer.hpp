#include <vector>
#include "../../config.h"
#include "render.hpp"

namespace rd::mng {
	class Renderer {
	public:
		Renderer();
		~Renderer();

		void append(rd2::ExtendedObject obj);
		void render();

	private:
		std::vector<rd2::ExtendedObject> rendererData;
	};

	Renderer::Renderer() {
		rendererData = std::vector<rd2::ExtendedObject>();
	}

	void Renderer::append(rd2::ExtendedObject obj) {
		rendererData.push_back(obj);
	}

	void Renderer::render() {
		for (rd2::ExtendedObject& obj : rendererData) {
			obj.render();
		}
	}

	Renderer::~Renderer() {
	}
}

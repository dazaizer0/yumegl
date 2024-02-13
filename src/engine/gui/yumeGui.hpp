#ifndef YUMEGL_YUMEGUI_HPP
#define YUMEGL_YUMEGUI_HPP

#include "../../config.h"
#include "../../yume.h"

namespace gui {
#pragma region PANEL
	class Panel {
	public:
		// PROPERTIES
		glm::vec3 position{ 0.0f };
        bool enable{};

		explicit Panel(glm::vec3 positionV, bool enableV);

		void render_ownShader() const;

		~Panel();

	private:

	};

	Panel::Panel(glm::vec3 positionV, bool enableV) {
		position = positionV;
        enable = enableV;
	}

    void Panel::render_ownShader() const {

    }

	Panel::~Panel() {
	}

#pragma endregion

#pragma region IMAGE
	class Image {
	public:
		glm::vec3 position{ 0.0f };
		glm::vec3 center{ 0.0f };

		explicit Image(const Panel &parent_panel);
		~Image();

	private:

	};

	Image ::Image(const Panel &parent_panel) {
		center = parent_panel.position;
		position = position + center;
	}

	Image ::~Image() {
	}
#pragma endregion
};
#endif
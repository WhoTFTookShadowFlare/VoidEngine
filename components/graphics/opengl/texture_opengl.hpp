#include "ve/event/event_listener.hpp"
#include "ve/io/gfx/texture.hpp"
#include "ve/io/res_providers/texture/a_provider.hpp"
#include "ve/object.hpp"
#include <cstdint>
#include <memory>

namespace VoidEngine::IO::GFX::OpenGL {
	class GLTexture : public Texture,
		public std::enable_shared_from_this<GLTexture>
	{
	private:
		uint32_t texture = 0;
		bool filtered = false;

		void uploadTexture();

	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }

		GLTexture(uint8_t slot);
		~GLTexture();

		void bindTexture();
		void setTextureProvider(std::shared_ptr<ResourceProviders::ATextureProvider>);

		void setFiltered(bool);
		bool isFiltered();

		void onTextureChangeEvent(std::shared_ptr<Object>);
	};
}


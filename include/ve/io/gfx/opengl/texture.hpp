#include "ve/event/event_listener.hpp"
#include "ve/io/gfx/texture.hpp"
#include "ve/io/res_providers/texture/a_provider.hpp"
#include <cstdint>
#include <memory>

namespace VoidEngine::IO::GFX::OpenGL {
	class GLTexture : public Texture,
		public Event::IEventListener<ResourceProviders::ETextureChanged>,
		public std::enable_shared_from_this<GLTexture>
	{
	private:
		uint32_t texture = 0;
		bool filtered = false;

		void uploadTexture();

	public:
		GLTexture(uint8_t slot);
		~GLTexture();

		void bindTexture();
		void setTextureProvider(std::shared_ptr<ResourceProviders::ATextureProvider>);

		void setFiltered(bool);
		bool isFiltered();

		void onEvent(ResourceProviders::ETextureChanged&);
	};
}


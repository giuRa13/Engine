#pragma once
#include "../Core.hpp"
#include <vector>

namespace ENGINE 
{

	enum class FramebufferTextureFormat
	{
		None = 0,
		RGBA8, // Color
		RED_INTEGER,// Color
		DEPTH24STENCIL8,// Depth/stencil
		Depth = DEPTH24STENCIL8 // Defaults
	};

	struct FramebufferTextureSpecification
	{
		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat format)
			: TextureFormat(format) {}

		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
		// TODO: filtering/wrap
	};

	struct FramebufferAttachmentSpecification
	{
		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
			: Attachments(attachments) {}

		std::vector<FramebufferTextureSpecification> Attachments;
	};


	//////////////////////////////////////////////////////////
	struct FramebufferSpecification
	{
		uint32_t Width, Height;
		FramebufferAttachmentSpecification Attachments;
		uint32_t Samples = 1;
		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		Framebuffer(const FramebufferSpecification& spec);
		virtual ~Framebuffer();

		void Invalidate();
		void Bind();
		void Unbind();
		void Resize(uint32_t width, uint32_t height);
		int ReadPixel(uint32_t attachmentIndex, int x, int y);
		void ClearAttachment(uint32_t attachmentIndex, int value);

		//uint32_t GetColorAttachmentRendererID() const { return m_ColorAttachment; }
		uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const { return m_ColorAttachments[index]; }
		const FramebufferSpecification& GetSpecification() const { return m_Specification; }

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec); 

	private:
		uint32_t m_RendererID = 0;
		FramebufferSpecification m_Specification;

		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
		FramebufferTextureSpecification m_DepthAttachmentSpecification = FramebufferTextureFormat::None;

		std::vector<uint32_t> m_ColorAttachments; //(Render ID)
		uint32_t m_DepthAttachment = 0;
	};

}
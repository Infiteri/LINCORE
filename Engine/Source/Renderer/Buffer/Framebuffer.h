#pragma once

#include "Base.h"
#include <vector>

namespace Core
{

    /// @brief Render pass texture type
    enum class RPTextureType
    {
        Depth,
        Rgb,
        Rgba8
    };

    struct FBRenderPass
    {
        RPTextureType Type;
        u32 Index, Id;
    };

    struct FramebufferConfiguration
    {
        float Width, Height;

        std::vector<FBRenderPass> Passes;
    };

    class CE_API Framebuffer
    {
    public:
        Framebuffer(const FramebufferConfiguration &cfg);
        ~Framebuffer();

        void Bind();
        void Unbind();
        void Create();

        FBRenderPass *GetRenderPass(int index);

        inline u32 GetID() const { return id; };

    private:
        u32 id;
        FramebufferConfiguration state;
    };
} // namespace Core

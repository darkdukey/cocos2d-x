//
// Created by NiTe Luo on 11/6/13.
//


#include "QuadCommand.h"
#include "ccGLStateCache.h"

NS_CC_BEGIN

QuadCommand::QuadCommand()
:RenderCommand()
,_viewport(0)
,_depth(0)
,_textureID(0)
,_blendType(BlendFunc::DISABLE)
,_quadCount(0)
{
    _type = QUAD_COMMAND;
    _shader = nullptr;
    _quad = nullptr;
}

//QuadCommand::QuadCommand(int viewport, int32_t depth, GLuint textureID, GLProgram* shader, BlendFunc blendType, V3F_C4B_T2F_Quad* quad, int quadCount)
//:RenderCommand()
//,_viewport(viewport)
//,_depth(depth)
//,_textureID(textureID)
//,_blendType(blendType)
//,_quadCount(quadCount)
//{
//    _type = QUAD_COMMAND;
//    _shader = shader;
//    _quad = (V3F_C4B_T2F_Quad*)malloc(sizeof(V3F_C4B_T2F_Quad) * quadCount);
//    memcpy(_quad, quad, sizeof(V3F_C4B_T2F_Quad) * quadCount);
//}

QuadCommand::~QuadCommand()
{
    free(_quad);
}

void QuadCommand::init(int viewport, int32_t depth, GLuint texutreID, GLProgram *shader, BlendFunc blendType, V3F_C4B_T2F_Quad *quad, int quadCount)
{
    _viewport = viewport;
    _depth = depth;
    _textureID = texutreID;
    _shader = shader;
    _blendType = blendType;
    _quadCount = quadCount;
    free(_quad);
    _quad = (V3F_C4B_T2F_Quad*)malloc(sizeof(V3F_C4B_T2F_Quad) * quadCount);
    memcpy(_quad, quad, sizeof(V3F_C4B_T2F_Quad) * quadCount);
}

int64_t QuadCommand::generateID()
{
    _id = 0;

    //Generate Material ID
    //TODO fix shader ID generation
    CCASSERT(_shader->getProgram() < 64, "ShaderID is greater than 64");
    //TODO fix texture ID generation
    CCASSERT(_textureID < 1024, "TextureID is greater than 1024");

    //TODO fix blend id generation
    int blendID = 0;
    if(_blendType == BlendFunc::DISABLE)
    {
        blendID = 0;
    }
    else if(_blendType == BlendFunc::ALPHA_PREMULTIPLIED)
    {
        blendID = 1;
    }
    else if(_blendType == BlendFunc::ALPHA_NON_PREMULTIPLIED)
    {
        blendID = 2;
    }
    else if(_blendType == BlendFunc::ADDITIVE)
    {
        blendID = 3;
    }
    else
    {
        blendID = 4;
    }

    _materialID = (int32_t)_shader->getProgram() << 28
            | (int32_t)blendID << 24
            | (int32_t)_textureID << 14;

    //Generate RenderCommandID
    _id = (int64_t)_viewport << 61
            | (int64_t)1 << 60 //translucent
            | (int64_t)_depth << 36;

    return _id;
}

void QuadCommand::useMaterial()
{
    _shader->use();

    _shader->setUniformsForBuiltins();

    //set blend mode
    GL::blendFunc(_blendType.src, _blendType.dst);

    //Set texture
    GL::bindTexture2D(_textureID);
}

NS_CC_END
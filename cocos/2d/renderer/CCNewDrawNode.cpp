//
// Created by NiTe Luo on 11/14/13.
//


#include "CCNewDrawNode.h"
#include "QuadCommand.h"
#include "Renderer.h"
#include "CustomCommand.h"

NS_CC_BEGIN

NewDrawNode *NewDrawNode::create()
{
    NewDrawNode* pRet = new NewDrawNode();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

NewDrawNode::NewDrawNode()
{

}

NewDrawNode::~NewDrawNode()
{

}

bool NewDrawNode::init()
{
    return DrawNode::init();
}

void NewDrawNode::draw()
{
    kmGLGetMatrix(KM_GL_MODELVIEW, &_transformMatrix);

    CustomCommand* cmd = CustomCommand::getCommandPool().generateCommand();
    cmd->init(0, _vertexZ);
    cmd->func = CC_CALLBACK_0(NewDrawNode::onDraw, this);
    Renderer::getInstance()->addCommand(cmd);
}

void NewDrawNode::onDraw()
{
    kmMat4 prevMatrix;
    kmGLGetMatrix(KM_GL_MODELVIEW, &prevMatrix);
    
    kmGLLoadMatrix(&_transformMatrix);

    CC_NODE_DRAW_SETUP();
    GL::blendFunc(_blendFunc.src, _blendFunc.dst);

    render();

    kmGLLoadMatrix(&prevMatrix);
}

NS_CC_END
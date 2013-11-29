//
// Created by NiTe Luo on 11/13/13.
//



#ifndef _CC_GROUPCOMMAND_H_
#define _CC_GROUPCOMMAND_H_

#include "CCPlatformMacros.h"
#include "RenderCommand.h"
#include <map>

NS_CC_BEGIN
using namespace std;

class GroupCommandManager : public Object
{
public:
    static GroupCommandManager* getInstance();

    ~GroupCommandManager();

    bool init();

    int getGroupID();
    void releaseGroupID(int groupID);

protected:
    GroupCommandManager();
    map<int, bool> _groupMapping;
};

class GroupCommand : public RenderCommand
{

public:
    GroupCommand();
    void init(int viewport, int32_t depth);
    //GroupCommand(int viewport, int32_t depth);
    ~GroupCommand();

    // +----------+----------+-----+-----------------------------------+
    // |          |          |     |                |                  |
    // | ViewPort | Transluc |     |      Depth     |                  |
    // |   3 bits |    1 bit |     |    24 bits     |                  |
    // +----------+----------+-----+----------------+------------------+
    virtual int64_t generateID() override;

    inline bool isTranslucent() {return true;}
    inline int getRenderQueueID() {return _renderQueueID;}

protected:
    int _viewport;
    int32_t _depth;
    int _renderQueueID;
};

NS_CC_END

#endif //_CC_GROUPCOMMAND_H_

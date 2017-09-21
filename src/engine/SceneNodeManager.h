#pragma once

#include <stack>

#include "Pool.h"
#include "Tree.h"
#include "SceneNode.h"

#define MAX_NODES 64

namespace engine
{
    typedef unsigned int uint;
    
    typedef Pool<SceneNode, MAX_NODES> SceneNodePool;

    /*
        For data coherence, updating each node by iterating through the array
        is desirable. If a node has a set of children, we want to update these children by updating the parent first,
        and maybe ignore the children until the parent is found.
    */

    class SceneNodeManager
    {
    public:
        uint activateSceneNode();
        uint activateSceneNodeAfter(uint min_id);

        void assignChild(uint parent, uint child) = 0;
        
        uint getParent(uint child) = 0;
        std::vector<uint> getChildren(uint parent) = 0;

        void updateAllNodes();
        void updateNode(uint id)
    private:
        utils::Tree<uint> sceneNodeTree_;
        SceneNodePool sceneNodePool_;
    };
}
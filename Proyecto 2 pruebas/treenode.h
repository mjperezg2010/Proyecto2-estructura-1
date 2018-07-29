#include <vector>
#include "treeelement.h"

using namespace std;

class TreeNode
{ //Clase principal
  private:
    vector<TreeNode *> _children;
    TreeNode *_parent;
    TreeElement *_data;

  public:
    TreeNode (const TreeElement&);
    TreeNode (const TreeElement&,TreeNode*);
    ~TreeNode();
    vector<TreeNode*>& GetChildren();
    void SetParent(TreeNode*);
    void AddChild(const TreeElement&); 
    void AddChild(TreeNode*);
    TreeElement* GetData();
    void SetData(const TreeElement&);
    bool IsRoot();
    bool IsLeaf();
};

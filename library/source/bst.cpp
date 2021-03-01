#include <iostream>
#include <memory>
#include <stack>
#include <vector>
#include <queue>
using namespace std;

template <typename t> class BST {
public:
  using datatype = t;
  using ref = t &;
  using const_ref = const t &;

  class Node {
  private:
    datatype data = 0;
    shared_ptr<Node> right, left;

  public:
    Node(datatype d) : data{d} {}

    Node(Node &lhs){
        data = lhs.data;
        right = lhs.right;
        left = lhs.left;
    }

    Node(const Node &&lhs){
        data = move(lhs.data);
        right = move(lhs.right);
        left = move(lhs.left);
    }

    Node& operator=(Node &lhs){
        data = lhs.data;
        right = lhs.right;
        left = lhs.left;
        return *this;
    }

    Node& operator=(Node &&lhs){
        data = move(lhs.data);
        right = move(lhs.right);
        left = move(lhs.left);
        return *this;
    }

    void setData(datatype d) { data = d; }

    void setRight(shared_ptr<Node> r) { right = r; }

    void setLeft(shared_ptr<Node> l) { left = l; }

    const_ref getData() const { return data; }

    const shared_ptr<Node>& getLeft() const { return left; }

    const shared_ptr<Node>& getRight() const { return right; }
  };

private:
  shared_ptr<Node> root = nullptr;

  BST(shared_ptr<Node> r) : root{r} {}

public:
  BST() = default;

  BST(BST &lhs){
      root = lhs.root;
  }

  BST(const BST &&lhs){
      root = move(lhs.root);
  }

  BST& operator=(BST &lhs){
      root= lhs.root;
      return *this;
  }

  BST& operator=(BST &&lhs){
      root = move(lhs.root);
      return *this;
  }

  void insert(datatype val) {
    auto new_node = make_shared<Node>(val);
    if (root == nullptr) {
      root = new_node;
    }

    else {
      shared_ptr<Node> temp = root;
      while (1) {
        if (temp->getData() > val) {
          if (temp->getLeft() == nullptr)
            break;
          else
            temp = temp->getLeft();
        } else {
          if (temp->getRight() == nullptr)
            break;
          else
            temp = temp->getRight();
        }
      }
      if (temp->getData() < val)
        temp->setRight(new_node);
      else
        temp->setLeft(new_node);
    }
  }

  BST getLeft() const {
    if (root != nullptr)
      return BST{root->getLeft()};
    else
      return BST{};
  }

  BST getRight() const {
    if (root != nullptr)
      return BST{root->getRight()};
    else
      return BST{};
  }

  template <typename Fun> 
  void inorder(Fun fun) const {
    if(root==nullptr){
        return;
    }
    stack<shared_ptr<Node>> nodeStack;
    shared_ptr<Node> curr = root;
 
    while (curr != nullptr || nodeStack.empty() == false)
    {
        while (curr !=  nullptr)
        {
            nodeStack.push(curr);
            curr = curr->getLeft();
        }
 
        curr = nodeStack.top();
        nodeStack.pop();
        fun(curr->getData());

        curr = curr->getRight(); 
    } 
}

  template <typename Fun> 
  void preorder(Fun fun) const {

    if (root == nullptr)
      return;

    stack<shared_ptr<Node>> nodeStack;
    nodeStack.push(root);
    while (nodeStack.empty() == false) {
      // cout<<"ok"<<endl;
      shared_ptr<Node> temp = nodeStack.top();
      nodeStack.pop();

      fun(temp->getData());

      if (temp->getRight() != nullptr)
        nodeStack.push(temp->getRight());
      if (temp->getLeft() != nullptr)
        nodeStack.push(temp->getLeft());
    }
  }


    template <typename Fun> 
    void postorder(Fun fun) const {
    
    if (root == NULL) 
        return; 
  
    stack<shared_ptr<Node >> s1, s2; 
  
    s1.push(root); 
    shared_ptr<Node> temp; 
  
    while (!s1.empty()) { 
        temp = s1.top(); 
        s1.pop(); 
        s2.push(temp); 
  
        if (temp->getLeft()) 
            s1.push(temp->getLeft()); 
        if (temp->getRight()) 
            s1.push(temp->getRight()); 
    } 
  
    while (!s2.empty()) { 
        temp = s2.top(); 
        s2.pop(); 
        fun(temp->getData());
    } 
    }
      uint32_t numberOfLeafNodes()const{
      if (root== nullptr)
        return 0;
 
    queue<shared_ptr<Node>> q;
 
    uint32_t count = 0; 
    q.push(root);
    while (!q.empty())
    {
        shared_ptr< Node> temp = q.front();
        q.pop();
 
        if (temp->getLeft() != nullptr)
            q.push(temp->getLeft());
        if (temp->getRight() != nullptr)
            q.push(temp->getRight());
        if (temp->getLeft() == nullptr && temp->getRight() == nullptr)
            count++;
    }
    return count;
  }

    uint32_t numberOfNodes()const{
        if (root== nullptr) 
            return 0; 
        queue<shared_ptr<Node>> q; 
      
    int count = 0;
    q.push(root); 
    while (!q.empty()) 
    { 
        shared_ptr <Node> temp = q.front(); 
        q.pop(); 
        count++;               
        if (temp->getLeft() != nullptr) 
            q.push(temp->getLeft()); 
        if (temp->getRight() != nullptr) 
            q.push(temp->getRight()); 
    } 
    return count; 
    }

  
  std::optional<BST> search(datatype val)
  {
    shared_ptr<Node> temp= root;
      while (temp != nullptr) { 
        if (val > temp->getData()) 
            temp = temp->getRight(); 
  
        // pass left subtree as new tree 
        else if (val < temp->getData()) 
            temp = temp->getLeft(); 
        else
            return BST{temp};
    } 
    return BST{temp}; 
  }

  void deleteNode(datatype val)
  {
        shared_ptr<Node> curr = root;
        shared_ptr<Node> prev = nullptr;
 
    while (curr != nullptr && curr->getData() != val) {
        prev = curr;
        if (val < curr->getData())
            curr = curr->getLeft();
        else
            curr = curr->getRight();
    }
 
    if (curr == nullptr) {
        cout << "val " << val << " not found in the"
             << " provided BST.\n";
       // return root;
    }
 
    if (curr->getLeft() == nullptr || curr->getRight() == nullptr) {
 
        shared_ptr<Node> newCurr;
 
        if (curr->getLeft() == nullptr)
            newCurr = curr->getRight();
        else
            newCurr = curr->getLeft();
 
        //if (prev == nullptr)
           // return newCurr;
 
        if (curr == prev->getLeft())
            prev->setLeft( newCurr);
        else
            prev->setRight(newCurr);
 
        curr.reset();
    }
 
    else {
        shared_ptr<Node> p = nullptr;
        shared_ptr<Node> temp;
 
        temp = curr->getRight();
        while (temp->getLeft() != nullptr) {
            p = temp;
            temp = temp->getLeft();
        }
 
        if (p != nullptr)
            p->setLeft(temp->getRight());
 
        else
            curr->setRight(temp->getRight());
 
        curr->setData(temp->getData());
        temp.reset();
    }
    //return root;
    }

  bool isBinaryComplete()const{
      if (root == nullptr) 
        return true; 
  
    queue<shared_ptr<Node>> q; 
    q.push(root); 
    bool flag = false; 
  
    while(!q.empty()) 
    { 
        shared_ptr<Node> temp =q.front(); 
        q.pop(); 
  
        if(temp->getLeft()!=nullptr) 
        { 
        if (flag == true) 
            return false; 
  
        q.push(temp->getLeft());
        } 
        else
            flag = true; 
  
        if(temp->getRight()!=nullptr) 
        { 
        if(flag == true) 
            return false; 
  
        q.push(temp->getRight());
        } 
        else 
        flag = true; 
    } 
      return true; 
  }

  bool isFullBinary()const{
      if (root == nullptr) 
        return true; 
     
    queue<shared_ptr<Node>> q; 
    q.push(root); 
  
    while (!q.empty()) { 
        shared_ptr<Node> temp = q.front(); 
        q.pop(); 
  
        if (temp->getLeft() == nullptr && temp->getRight() == nullptr) 
            continue; 
  
        if (temp->getLeft() == nullptr || temp->getRight() == nullptr) 
            return false; 
  
        q.push(temp->getLeft()); 
        q.push(temp->getRight()); 
    } 
      return true;  
  }
  
};

int main() {

  BST<uint32_t> tree;
  tree.insert(4);
  tree.insert(3);
  tree.insert(1);
  tree.insert(2);
  tree.insert(5);

  cout << "Preorder : ";
  tree.preorder([](auto v) { cout << v << " "; });

  cout << endl;
  cout << "Inorder : ";
  tree.inorder([](auto v) { cout << v << " "; });

  cout << endl;
  cout << "Postorder : ";
  tree.postorder([](auto v) { cout << v << " "; });

  cout << endl;
  cout << "Number of leaf nodes : ";
  cout<<tree.numberOfLeafNodes();

  cout << endl;
  cout << "Number of nodes : ";
  cout<<tree.numberOfNodes();

  cout << endl;
  cout << "Is Complete Binary Tree : ";
  cout<<tree.isBinaryComplete();

  cout << endl;
  cout << "Is Full Binary : ";
  cout<<tree.isFullBinary();

  cout << endl;
  cout << "Find 2 : ";
  tree.search(2);

  cout << endl;
  cout << "Delete 2 : ";
  tree.deleteNode(2);

  cout << endl;
/*
  //tree << 5 ; 
  

  auto nodes = tree.getAllNodes();

  vector<BST<int>> mynodes;
  tree.inorder([&](auto v){
      BST<int> t;
      t.insert(v);
      mynodes.push_back(t);
  })
*/

  return 0;
}
#include <iostream>
#include <memory>
#include <optional>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

template <typename t> class BST {
public:
  using datatype = t;
  using ref = t &;
  using const_ref = const t &;

  class Node {
  private:
    datatype data = 0;
    shared_ptr<Node> right, left, parent;

  public:
    Node(datatype d) : data{d} {}

    Node(Node &lhs) {
      data = lhs.data;
      right = lhs.right;
      left = lhs.left;
      parent = lhs.parent;
    }

    Node(const Node &&lhs) {
      data = move(lhs.data);
      right = move(lhs.right);
      left = move(lhs.left);
      parent = move(lhs.parent);
    }

    Node &operator=(Node &lhs) {
      data = lhs.data;
      right = lhs.right;
      left = lhs.left;
      parent = lhs.parent;
      return *this;
    }

    Node &operator=(Node &&lhs) {
      data = move(lhs.data);
      right = move(lhs.right);
      left = move(lhs.left);
      parent = move(lhs.parent);
      return *this;
    }

    void setData(datatype d) { data = d; }

    void setRight(shared_ptr<Node> r) { right = r; }

    void setLeft(shared_ptr<Node> l) { left = l; }

    void setParent(shared_ptr<Node> p) { parent = p; }

    const_ref getData() const { return data; }

    const shared_ptr<Node> &getLeft() const { return left; }

    const shared_ptr<Node> &getRight() const { return right; }

    const shared_ptr<Node> &getParent() const { return parent; }
  };

private:
  shared_ptr<Node> root = nullptr;

  BST(shared_ptr<Node> r) : root{r} {}

  shared_ptr<Node> getPreorderPredecessor(datatype n) {
    vector<datatype> mynodes;
    inorder([&](auto v) { mynodes.push_back(v); });

    auto it = find(mynodes.begin(), mynodes.end(), n);
    size_t index = distance(mynodes.begin(), it);

    if (index != 0) {
      index--;
    } else if (index == mynodes.size())
      throw string{"This is a empty tree"};
    else
      index++;
    auto result = search(mynodes[index]);
    return result->root;
  }

public:
  BST() = default;

  BST(BST &lhs) { root = lhs.root; }

  BST(const BST &&lhs) { root = move(lhs.root); }

  BST &operator=(BST &lhs) {
    root = lhs.root;
    return *this;
  }

  BST &operator=(BST &&lhs) {
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
      new_node->setParent(temp);
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
    if (root == nullptr) {
      return;
    }
    stack<shared_ptr<Node>> nodeStack;
    shared_ptr<Node> curr = root;

    while (curr != nullptr || nodeStack.empty() == false) {
      while (curr != nullptr) {
        nodeStack.push(curr);
        curr = curr->getLeft();
      }

      curr = nodeStack.top();
      nodeStack.pop();
      fun(curr->getData());

      curr = curr->getRight();
    }
  }

  template <typename Fun> void preorder(Fun fun) const {

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

  template <typename Fun> void postorder(Fun fun) const {

    if (root == NULL)
      return;

    stack<shared_ptr<Node>> s1, s2;

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
  uint32_t numberOfLeafNodes() const {
    if (root == nullptr)
      return 0;

    queue<shared_ptr<Node>> q;

    uint32_t count = 0;
    q.push(root);
    while (!q.empty()) {
      shared_ptr<Node> temp = q.front();
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

  uint32_t numberOfNodes() const {
    if (root == nullptr)
      return 0;
    queue<shared_ptr<Node>> q;

    int count = 0;
    q.push(root);
    while (!q.empty()) {
      shared_ptr<Node> temp = q.front();
      q.pop();
      count++;
      if (temp->getLeft() != nullptr)
        q.push(temp->getLeft());
      if (temp->getRight() != nullptr)
        q.push(temp->getRight());
    }
    return count;
  }

  std::optional<BST> search(datatype val) {
    shared_ptr<Node> temp = root;
    while (temp != nullptr) {
      // cout<<"ok";
      if (val > temp->getData())
        temp = temp->getRight();
      // pass left subtree as new tree
      else if (val < temp->getData())
        temp = temp->getLeft();
      else
        return BST{temp};
    }
    return nullopt;
  }

  void deleteNode(datatype key) {
    /*

                            a
                        /      \
                       b         c
                     /   \     /   \
                    d     e   f     g
                             / \
                            h   I

                toDel = c;
                pNode = a;   // c-> getParent()
                preNode = I;  // predecessor(c)
                ppNode = f;  // I->getParent()

                a->right = I;
                I->parent = a;
                f->right = nullptr;

                I->left=f;
                I->right=g;

                f->parent =I;
                g->parent =I;

                c->parent = a;
                c->left = f;
                c->right = g;

                preNode->setLeft(toDel->getLeft());
                preNode->setRight(toDel->getRight());
                preNode->setParent(toDel->getParent());

                if(ppNode->getData() < preNode->getData())
                  ppNode->setRight(nullptr);
                else
                  ppNode->setLeft(nullptr);

                if(pNode->getData() < toDel->getData())
                  pNode->setRight(preNode);
                else
                  pNode->setLeft(preNode);


                toDel->getLeft()->setParent(preNode);
                toDel->getRight()->setParent(preNode);
    */

    try {
      auto toDel = search(key)->root;
      cout<<toDel->getData();
      if (toDel) {
        shared_ptr pNode = toDel->getParent();
        shared_ptr preNode = getPreorderPredecessor(toDel->getData());
        shared_ptr ppNode = preNode->getParent();
        // 0 child
        if (toDel->getLeft() == nullptr && toDel->getRight() == nullptr) {
          if (pNode != nullptr) {
            pNode->setLeft(nullptr);
            pNode->setRight(nullptr);
            toDel->setParent(nullptr);
          } else {
            root = nullptr;
            toDel = nullptr;
          }
        }

        // 1 child
        if (pNode != nullptr) {
          if (toDel->getLeft() == nullptr && toDel->getRight() != nullptr) {
            toDel->getRight()->setParent(pNode);
            if (toDel->getData() < pNode->getData()) {
              pNode->setLeft(toDel->getRight());
            }
            if (toDel->getData() > pNode->getData()) {
              pNode->setRight(toDel->getRight());
            }
            toDel->setRight(nullptr);
          }

          if (toDel->getRight() == nullptr && toDel->getLeft() != nullptr) {
            preNode->setParent(toDel->getParent());
            if (toDel->getData() < pNode->getData()) {
              pNode->setLeft(toDel->getLeft());
              toDel->setLeft(nullptr);
            }

            if (toDel->getData() > pNode->getData()) {
              pNode->setRight(preNode);
            }
          }
          toDel->setRight(nullptr);
          toDel->setLeft(nullptr);
          toDel->setParent(nullptr);
        } else {
          root = preNode;
          preNode->setParent(nullptr);
          toDel->getLeft()->setParent(nullptr);
        }

        // 2 child
        if (toDel->getLeft() != nullptr && toDel->getRight() != nullptr) {

          if (preNode->getLeft() != nullptr) {
            preNode->setParent(toDel->getParent());

            if (pNode != nullptr) {
              if (toDel->getData() < pNode->getData()) {
                pNode->setLeft(toDel->getLeft());
              }
              if (toDel->getData() > pNode->getData()) {
                pNode->setRight(toDel->getLeft());
              }
            } else
              root = preNode;

            preNode->setRight(toDel->getRight());
            toDel->getRight()->setParent(preNode);
            toDel->setLeft(nullptr);
            toDel->setRight(nullptr);

          } else {
            preNode->setLeft(toDel->getLeft());
            preNode->setRight(toDel->getRight());
            preNode->setParent(toDel->getParent());

            if (ppNode->getData() < preNode->getData())
              ppNode->setRight(nullptr);
            else
              ppNode->setLeft(nullptr);

            if (pNode->getData() < toDel->getData())
              pNode->setRight(preNode);
            else
              pNode->setLeft(preNode);

            if (toDel->getLeft() != nullptr)
              toDel->getLeft()->setParent(preNode);
            if (toDel->getRight() != nullptr)
              toDel->getRight()->setParent(preNode);
          }
        }
      } else
        throw("value not present in the tree");
    } catch (string) {
      root = nullptr;
    }
  }

  bool isBinaryComplete() const {
    if (root == nullptr)
      return true;

    queue<shared_ptr<Node>> q;
    q.push(root);
    bool flag = false;

    while (!q.empty()) {
      shared_ptr<Node> temp = q.front();
      q.pop();

      if (temp->getLeft() != nullptr) {
        if (flag == true)
          return false;

        q.push(temp->getLeft());
      } else
        flag = true;

      if (temp->getRight() != nullptr) {
        if (flag == true)
          return false;

        q.push(temp->getRight());
      } else
        flag = true;
    }
    return true;
  }

  bool isFullBinary() const {
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
  tree.insert(20);
  tree.insert(10);
  tree.insert(5);
  tree.insert(7);
  tree.insert(30);
  tree.insert(25);
  tree.insert(22);
  tree.insert(21);
  tree.insert(40);

  cout << "Preorder : ";
  tree.preorder([](auto v) { cout << v << " "; });

  cout << endl;
  cout << "Inorder : ";
  tree.inorder([](auto v) { cout << v << " "; });

  cout << endl;
  /*cout << "Postorder : ";
  tree.postorder([](auto v) { cout << v << " "; });

  cout << endl;
  cout << "Number of leaf nodes : ";
  cout << tree.numberOfLeafNodes();

  cout << endl;
  cout << "Number of nodes : ";
  cout << tree.numberOfNodes();

  cout << endl;
  cout << "Is Complete Binary Tree : ";
  cout << tree.isBinaryComplete();

  cout << endl;
  cout << "Is Full Binary : ";
  cout << tree.isFullBinary();

  cout << endl;
  cout << "Find 2 : ";
  tree.search(2);
*/
  cout << endl;
  cout << "Delete 25 : ";
  tree.deleteNode(2);
  cout << endl;
  cout << "Inorder : ";
  tree.inorder([](auto v) { cout << v << " "; });

  cout << endl;
  cout << "Delete 20 : ";
  // cout <<
  tree.deleteNode(20);

  cout << endl;
  cout << "Inorder : ";
  tree.inorder([](auto v) { cout << v << " "; });

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
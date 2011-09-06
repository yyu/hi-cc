#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <iterator>
#include <cassert>

#include <cstdio>
#include <cstdlib>
#include <cstring>

template <typename T>
class TreeNode
{
public:
    TreeNode() : L(NULL), R(NULL) {}
    TreeNode(T v) : val(v), L(NULL), R(NULL) {}
    ~TreeNode() {}

    void setLR(TreeNode* l, TreeNode* r) {L = l; R = r;}

    // It's OK to visit the members directly, so:
    //   - val, L and R are public
    //   - they are not val_, L_ and R_
    T val;
    TreeNode* L;
    TreeNode* R;
private:
    // disallow copy constructor and assignment operator
    TreeNode(const TreeNode&);
    TreeNode& operator=(const TreeNode&);
};

template <typename T>
class SimplePrint
{
public:
    SimplePrint(std::ostream& out, const std::string& sep) : out_(out), separator_(sep) {}
    void operator()(const TreeNode<T>* p) const
    {
        if (p)
            out_ << p->val << separator_;
        else
            out_ << "\n";
    }
private:
    std::ostream& out_;
    std::string separator_;
};

template <typename T>
class NicePrint
{
public:
    NicePrint(std::string& s) : s_(s) {}
    void operator()(const TreeNode<T>* p, int depth, int dir) const {
        std::stringstream ss;
        int i;

        for (i = depth - 1; i >= 1; i--)
            if ((dir >> i & 1) ^ (dir >> (i-1) & 1))
                ss << "| ";
            else
                ss << "  ";
        //ss << ((dir >> i & 1) ^ (dir >> (i-1) & 1)) ? "|" : " " << " ";

        if (depth)
            ss << ((dir & 1) ? "`-" : ".-");

        ss << p->val << "\n";

        s_ += ss.str();
    }
private:
    std::string& s_;
};

template <typename T>
class BST
{
public:
    BST() : root_(NULL) {}
    template <typename IN_ITER> BST(IN_ITER b, IN_ITER e);
    ~BST() {}

    bool empty() const;
    void insert(TreeNode<T>* node);
    void preorder(const SimplePrint<T>& visit) const;
    void inorder(const SimplePrint<T>& visit) const;
    void postorder(const SimplePrint<T>& visit) const;
    void levelorder(const SimplePrint<T>& visit) const;

    friend std::ostream& operator<< (std::ostream& out, const BST& t) {return out << t.toString();}
private:
    std::string toString() const;

    void traverse(TreeNode<T>* node, const NicePrint<T>& visit, int depth, int dir) const;

    TreeNode<T>* root_;

    // copy constructor
    BST(const BST &);
};

template <typename T>
template <typename IN_ITER>
BST<T>::BST(IN_ITER b, IN_ITER e)
    : root_(NULL)
{
    for (IN_ITER it = b; it != e; ++it)
        insert(new TreeNode<T>(*it));
}

template <typename T>
bool BST<T>::empty() const
{
    return root_ == NULL;
}

template <typename T>
void BST<T>::insert(TreeNode<T>* node)
{
    if (!node)
        return;

    assert(node->L == NULL && node->R == NULL);

    if (!root_) {
        root_ = node;
        return;
    }

    TreeNode<T>* p;
    TreeNode<T>* q = root_;

    while (q) {
        p = q;
        if (node->val < q->val)
            q = q->L;
        else
            q = q->R;
    }
    if (node->val < p->val) {
        assert(p->L == NULL);
        p->L = node;
    } else {
        assert(p->R == NULL);
        p->R = node;
    }
}

template <typename T>
void BST<T>::traverse(TreeNode<T>* node, const NicePrint<T>& visit, int depth, int dir) const {
    if (!node)
        return;
    traverse(node->L, visit, depth + 1, dir << 1);
    visit(node, depth, dir);
    traverse(node->R, visit, depth + 1, (dir << 1) | 1);
}

template <typename T>
std::string BST<T>::toString() const
{
    std::string str;
    traverse(root_, NicePrint<T>(str), 0, 0);

    std::string nice_str;
    std::vector<std::string> lines;

    std::stringstream ss(str);
    std::string line;
    while (std::getline(ss, line)) {
        lines.push_back(line);
        std::cout << line << "\n";
    }

    bool the_end = false;
    size_t column_nr = 0;
    while (!the_end) {
        the_end = true;
        for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it) {
            if (column_nr >= it->size()) {
                nice_str += " ";
                continue;
            }

            char c = (*it)[column_nr];
            if (c == '\n') {
                nice_str += " ";
            } else {
                switch (c) {
                case '|':
                    nice_str += "_"; break;
                case '-':
                    nice_str += "|"; break;
                case '`':
                case '.':
                    nice_str += " "; break;
                case ' ':
                    nice_str += " "; break;
                case '#':
                    nice_str += "^"; break;
                default:
                    nice_str += c; break;
                }
                the_end = false;
            }
        }
        nice_str += "\n";
        column_nr++;
    }
    return nice_str;
}

template <typename T>
void BST<T>::preorder(const SimplePrint<T>& visit) const
{
    std::stack<const TreeNode<T>*> stk;
    const TreeNode<T>* p = root_;
    while (1) {
        while (p) {
            visit(p);
            stk.push(p);
            p = p->L;
        }
        if (stk.empty())
            break;
        p = stk.top(); stk.pop();
        p = p->R;
    }
    visit(NULL);               // output an ending char
}

template <typename T>
void BST<T>::inorder(const SimplePrint<T>& visit) const
{
    std::stack<TreeNode<T>*> stk;
    TreeNode<T>* p = root_;
    while (1) {
        while (p) {
            stk.push(p);
            p = p->L;
        }
        if (stk.empty())
            break;
        p = stk.top(); stk.pop();
        visit(p);
        p = p->R;
    }
    visit(NULL);               // output an ending char
}

template <typename T>
void BST<T>::postorder(const SimplePrint<T>& visit) const
{
    TreeNode<T>* p = root_;
    TreeNode<T>* recent = NULL;
    std::stack<TreeNode<T>*> stk;
    while (1) {
        while (p) {
            stk.push(p);
            p = p->L;
        }
        if (stk.empty())
            break;
        p = stk.top();
        if (p->R == recent || p->R == NULL) {
            stk.pop();
            visit(p);
            recent = p;
            p = NULL;  // so that we'll go on to pop in the coming loop
        } else {
            p = p->R;
        }
    }
    visit(NULL);
}

template <typename T>
void BST<T>::levelorder(const SimplePrint<T>& visit) const
{
    if (!root_)
        return;

    TreeNode<T>* p = root_;
    TreeNode<T>* sentinel = NULL;

    std::queue<TreeNode<T>*> q;

    q.push(sentinel);
    q.push(p);
    while (1) {
        p = q.front(); q.pop();
        if (p == sentinel) {
            visit(NULL);        // print a newline
            if (q.empty())
                break;
            q.push(sentinel);
        } else {
            visit(p);
            if (p->L)
                q.push(p->L);
            if (p->R)
                q.push(p->R);
        }
    }
}

int main(int argc, char* argv[])
{
    // typedef int NodeValType;
    // NodeValType A[] = {3, 2, 6, 1, 4, 8, 5, 7, 9};
    // size_t N = sizeof(A) / sizeof(A[0]);
    // BST<NodeValType> bst(A, A + N);

    typedef char NodeValType;
    NodeValType A[] = "THEBROWNQUICKFOXJUMPSOVERALAZYDOG";
    size_t N = sizeof(A) / sizeof(A[0]);
    BST<NodeValType> bst(A, A + N - 1); // -1 because of the trailing '\n'

    assert(!bst.empty());

    std::cout << bst;

    bst.preorder(SimplePrint<NodeValType>(std::cout, "."));

    std::stringstream ss;
    bst.inorder(SimplePrint<NodeValType>(ss, " "));
    std::cout << ss.str();

    bst.postorder(SimplePrint<NodeValType>(std::cout, "."));

    bst.levelorder(SimplePrint<NodeValType>(std::cout, "."));

    return 0;
}

/* DISCLAIMER - Instead of making repeated comments about one topic again
and again, I just wanted to make a general comment at the top. I used the powerpoints
as references for several of my functions. I tried to implement some my way but
most of the ones that I found on the powerpoint, I used them. Thats all! */

#include <stack>

using namespace std;

// Constructors

BET::BET() : current{nullptr} { }

BET::BET(const string & postfix)
{
  buildFromPostfix(postfix);
}

BET::BET(const BET & temp)
{
  current = clone(temp.current);
}

// Destructor

BET::~BET()
{
  makeEmpty(current);
}

// Assignment operator

const BET & BET::operator= (const BET & temp)
{
  makeEmpty(current);
  current = clone(temp.current);
  return *this;
}

// Building from Postfix expression

bool BET::buildFromPostfix(const string & postfix)
{
  makeEmpty(current);

  stack<BinaryNode*> answer;
  string temp;
  int counter = 0;

  for (int i = 0; i < postfix.length(); i++)
  {
    if (Operators(postfix[i]))
    {
      if (answer.size() >= 2)
      {
        temp.clear();

        temp += postfix[i];

        BinaryNode * right = answer.top();
        answer.pop();
        BinaryNode * left = answer.top();
        answer.pop();

        BinaryNode * tempnode = new BinaryNode(temp, left, right);
        answer.push(tempnode);

        counter--;
      }
      else if (answer.size() < 2)
      {
        counter--;
        break;
      }
    }

    else if (!Operators(postfix[i]) && !isspace(postfix[i]))
    {
      temp.clear();

      while (!Operators(postfix[i]) && !isspace(postfix[i]) && (i < postfix.length()))
      {
        temp += postfix[i];
        i++;
      }

      i--;
      BinaryNode * tempnode = new BinaryNode(temp, nullptr, nullptr);
      answer.push(tempnode);

      counter++;
    }

    else continue;
  }

  if (counter != 1)
  {
    cout << "Invalid Postfix Expression!" << endl;
    return false;
  }

  swap(current, answer.top());

  return counter == 1;
}

// Print functions (public)

void BET::printInfixExpression() const
{
  printInfixExpression(current);
  cout << endl;
}

void BET::printPostfixExpression() const
{
  printPostfixExpression(current);
  cout << endl;
}

// Return nodes/leaf_nodes functions (public)

size_t BET::size() const
{
  return size(current);
}

size_t BET::leaf_nodes() const
{
  return leaf_nodes(current);
}

// Empty function

bool BET::empty() const
{
  if (size() == 0)
    return true;
  else
    return false;
}

// Print functions (private)

void BET::printInfixExpression(BinaryNode * n) const
{
  if (n->left == nullptr)
    cout << n->element;

  else
  {
    if (n != current)
      cout << "(";

    printInfixExpression(n->left);
    cout << ' ' << n->element << ' ';
    printInfixExpression(n->right);

    if (n != current)
      cout << ")";
  }
}

void BET::printPostfixExpression(BinaryNode * n) const
{
  if (n != nullptr)
  {
    printPostfixExpression(n->left);
    printPostfixExpression(n->right);

    cout << n->element << ' ';
  }
}

// Delete function

void BET::makeEmpty(BinaryNode *& t)
{
  if (t != nullptr)
  {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
  }

  t = nullptr;
}

// Return nodes/leaf_nodes functions (private)

size_t BET::size(BinaryNode * t) const
{
  if (t == nullptr)
    return 0;
  else
  {
    size_t temp = 1 + size(t->left) + size(t->right);
    return temp;
  }
}

size_t BET::leaf_nodes(BinaryNode * t) const
{
  if (t == nullptr)
    return 0;
  else if (t->left == nullptr || t->right == nullptr)
    return 1;
  else
  {
    size_t temp = leaf_nodes(t->left) + leaf_nodes(t->right);
    return temp;
  }
}

// Clone function

BET::BinaryNode * BET::clone(BinaryNode * t)
{
  if (t == nullptr)
    return nullptr;
  else
    return new BinaryNode{t->element, clone(t->left), clone(t->right)};
}

// Stand-alone function

bool Operators(char sign)
{
  if (sign == '+' || sign == '-' || sign == '*' || sign == '/')
    return true;
  else
    return false;
}

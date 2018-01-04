#include <iostream>
#include <string>
#include <stack>
#include <sstream>

using namespace std;

// 基于Stack构建计算器（带括号等等）
// ① Item类 存储数据和操作符
// ② 出入Push和Pop函数
// ③ Calculate函数——里面有一个Stack<Item>的堆和 stringstream，用于分析每个字符形式
// ④ Run函数——实现具体计算

struct Item {
    int number = 0;
    char op = '\0';

    // 默认的构造函数
    Item() {}
    Item(char operators): op{operators} {}
};


// Run返回的栈顶的最上面两个元素的和，保存在第二高的栈顶元素上。并把最高的栈顶元素出栈。
void Run(stack<Item>& items)
{
    auto second = items.top();
    items.pop();
    auto& first = items.top().number;
    switch (second.op)
    {
    case '+':
        first += second.number;
        break;
    case '-':
        first -= second.number;
        break;
    case '*':
        first *= second.number;
        break;
    case '/':
        first /= second.number;
        break;
    }
}

void Push(stack<Item>& items, int number) {

    items.top().number = number;
    switch (items.top().op)
    {
    // 只要运算符为*或者/，都执行Run(items)
    case '*':case '/':
        Run(items);
    }

}

int Pop(stack<Item>& items)
{
    while (items.top().op != '\0')
    {
    // 根据Run可以看出，真正实现出栈操作的stack.pop()是在
    // Run函数里面完成的。
        Run(items);
    }
    /*4*/
    // pop()没有返回值
    auto number = items.top().number;
    items.pop();
    return number;
}

int Calculate(string text)
{
    stringstream ss(text);
    stack<Item> items;
    // 栈初始化的时候，就往里面添加一个item
    items.push({});

    while (true)
    {
        // ss.peek 查看下一字符，但不提取
        char op = ss.peek();
        switch (op)
        {
        case '(':
            // 相当于items.push(Item {});
            items.push({});
            break;
        case ')':
            Push(items, Pop(items));
            break;
        case '+':case '-':case '*':case '/':
            items.push({op});
            break;
        }

        if (isdigit(op))
        {
            int number;
            ss >> number;
            Push(items, number);
        }
        else if (ss.eof())
        // 到头了——>string stream到达末尾
        {
            return Pop(items);
        }
        else
        {
            ss.ignore();
        }
    }
}


#include <stack>

namespace ilrd
{
    using namespace std;

    template <class T>
    class Generic_stack
    {
    public:
        void Push(T data);
        T Pop();
        T Peek();
        size_t Size();
        bool Empty();

    private:
        stack<T> generic_stack;
    };

    template <class T>
    void Generic_stack<T>::Push(T data)
    {
        generic_stack.push(data);
    }

    template <class T>
    T Generic_stack<T>::Pop()
    {
        T ret_val = generic_stack.top();
        generic_stack.pop();
        return ret_val;
    }

    template <class T>
    T Generic_stack<T>::Peek()
    {
        return generic_stack.top();
    }

    template <class T>
    size_t Generic_stack<T>::Size()
    {
        return generic_stack.size();
    }

    template <class T>
    bool Generic_stack<T>::Empty()
    {
        return generic_stack.empty();
    }

} // namespace ilrd

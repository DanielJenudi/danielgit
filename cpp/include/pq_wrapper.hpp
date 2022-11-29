/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Author: Daniel Jenudi
- Date: 13/09/22
- Reviwer: Hagar Gur-Arie
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <queue> // queue

template <
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>>

class PQ_Wrapper
{
public:
    void push(const T &data);
    const T &front() const;
    void pop();

private:
    std::priority_queue<T, Container, Compare> m_pq;
};

template <class T, class Container, class Compare>
void PQ_Wrapper<T, Container, Compare>::push(const T &data)
{
    m_pq.push(data);
}

template <class T, class Container, class Compare>
const T &PQ_Wrapper<T, Container, Compare>::front() const
{
    return m_pq.top();
}

template <class T, class Container, class Compare>
void PQ_Wrapper<T, Container, Compare>::pop()
{
    m_pq.pop();
}

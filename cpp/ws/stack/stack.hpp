// RD66 - C++ - stack on singly linked list
// Version 1
// Dekel Sror
// Review: Shon Weinberg
#ifndef _ILRD_RD66_HPP
#define _ILRD_RD66_HPP

#include <cstddef> // size_t

#if __cplusplus < 201103L
	#define nullptr (0)
#endif

template <typename DataType>
struct Stack
{
public:
	explicit Stack();
	explicit Stack(const Stack &other);
	~Stack();

	Stack &operator=(const Stack &other);

	void Push(DataType data);
	void Pop();
	DataType Top();
	std::size_t Count() const;
	bool IsEmpty() const;

	struct Node
	{
		explicit Node();
		explicit Node(DataType data, Node* next);

		Node& operator=(const Node& other);

		DataType GetData() const;
		bool HasNext() const;
		const Node &GetNext() const;
		DataType m_data;
		Node* m_next;
	};

	Node m_dummmy;

private: // utility for CCtor and copy assignment
	void ListCopy(const Node *other);
};

// Stack API
// Ctors, Dtors, CCtors, operators
template <typename DataType>
Stack<DataType>::Stack()
{}

template <typename DataType>
Stack<DataType>::~Stack()
{
	while(!IsEmpty())
	{
		Pop();
	}
}

template <typename DataType>
Stack<DataType>::Stack(const Stack &other)
{
	ListCopy(other.m_dummmy.m_next);
}

template <typename DataType>
Stack<DataType>& Stack<DataType>::operator=(const Stack &other)
{
	while(!IsEmpty())
	{
		Pop();
	}

	ListCopy(other.m_dummmy.m_next);

	return *this;
}

template <typename DataType>
void Stack<DataType>::Push(DataType data)
{
	Node* newNode = new Node(data, m_dummmy.m_next);

	m_dummmy.m_next = newNode;
}

template <typename DataType>
DataType Stack<DataType>::Top()
{
	return m_dummmy.m_next->GetData();
}

template <typename DataType>
void Stack<DataType>::Pop()
{
	Node *restOfList = m_dummmy.m_next->m_next; // can be nullptr too

	delete (m_dummmy.m_next);

	m_dummmy.m_next = restOfList;
}

template <typename DataType>
std::size_t Stack<DataType>::Count() const
{
	Node *nodeRunner = m_dummmy.m_next;
	std::size_t count(0);

	while (nullptr != nodeRunner)
	{
		nodeRunner = nodeRunner->m_next;

		++count;
	}

	return count;
}

template <typename DataType>
bool Stack<DataType>::IsEmpty() const
{
	return (nullptr == m_dummmy.m_next);
}

// Node API
template <typename DataType>
Stack<DataType>::Node::Node(DataType data, Node *next)
	: m_data(data), m_next(next)
{}

template <typename DataType>
Stack<DataType>::Node::Node()
	: m_next(nullptr)
{}

template <typename DataType>
typename Stack<DataType>::Node&
Stack<DataType>::Node::operator=(const Stack<DataType>::Node& other)
{
	m_data = other.GetData();

	return *this;
}

template <typename DataType>
const typename Stack<DataType>::Node& Stack<DataType>::Node::GetNext() const
{
	return *m_next;
}

template <typename DataType>
DataType Stack<DataType>::Node::GetData() const
{
	return m_data;
}

template <typename DataType>
bool Stack<DataType>::Node::HasNext() const
{
	return (nullptr != m_next);
}

template <typename DataType>
void Stack<DataType>::ListCopy(const Node *list)
{
	if (nullptr == list)
	{
		return;
	}

	ListCopy(list->m_next);

	Push(list->m_data);
}

#endif /* _ILRD_RD66_HPP */

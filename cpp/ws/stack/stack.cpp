// // RD66 - C++ - stack on singly linked list
// // Version 1
// // Dekel Sror
// // Review: Shon Weinberg
// #include "stack.hpp"
//
// // recursively copy list last to first to maintain stack order
// #ifndef nullptr // for older standards (pre C++11)
// #define nullptr (0)
// #endif
//
// // Stack API
// // Ctors, Dtors, CCtors, operators
// Stack<class DataType>::Stack()
// {}
//
// Stack::~Stack()
// {
// 	while(!IsEmpty())
// 	{
// 		Pop();
// 	}
// }
//
// Stack::Stack(const Stack &other)
// {
// 	ListCopy(other.m_dummmy.m_next);
// }
//
// Stack &Stack::operator=(const Stack &other)
// {
// 	while(!IsEmpty())
// 	{
// 		Pop();
// 	}
//
// 	ListCopy(other.m_dummmy.m_next);
//
// 	return *this;
// }
//
// void Stack::Push(DataType data)
// {
// 	Stack::Node *newNode = new Stack::Node(data, m_dummmy.m_next);
//
// 	m_dummmy.m_next = newNode;
// }
//
// DataType Stack::Top()
// {
// 	return m_dummmy.m_next->GetData();
// }
//
// void Stack::Pop()
// {
// 	Stack::Node *restOfList = m_dummmy.m_next->m_next; // can be nullptr too
//
// 	delete (m_dummmy.m_next);
//
// 	m_dummmy.m_next = restOfList;
// }
//
// std::size_t Stack::Count() const
// {
// 	Stack::Node *nodeRunner = m_dummmy.m_next;
// 	std::size_t count(0);
//
// 	while (nullptr != nodeRunner)
// 	{
// 		nodeRunner = nodeRunner->m_next;
//
// 		++count;
// 	}
//
// 	return count;
// }
//
// bool Stack::IsEmpty() const
// {
// 	return (nullptr == m_dummmy.m_next);
// }
//
// // Node API
//
// Stack::Node::Node(DataType data, Stack::Node *next)
// : m_data(data), m_next(next)
// {}
//
// Stack::Node::Node()
// : m_data(0), m_next(nullptr)
// {}
//
// Stack::Node& Stack::Node::operator=(const Stack::Node& other)
// {
// 	m_data = other.GetData();
//
// 	return *this;
// }
//
// const Stack::Node& Stack::Node::GetNext() const
// {
// 	return *m_next;
// }
//
// DataType Stack::Node::GetData() const
// {
// 	return m_data;
// }
//
// bool Stack::Node::HasNext() const
// {
// 	return (nullptr != m_next);
// }
//
//
// void Stack::ListCopy(const Stack::Node *list)
// {
// 	if (nullptr == list)
// 	{
// 		return;
// 	}
//
// 	ListCopy(list->m_next);
//
// 	Push(list->m_data);
// }

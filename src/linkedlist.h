#ifndef __LINKED_LIST_H_
#define __LINKED_LIST_H_

class Node
{
	public:
		Node();
		~Node();

		inline int value() const { return _value; };
		inline void value(int v) { _value = v; };

	private:

		int _value;
};

class LinkedList
{
	public:

		LinkedList();
		~LinkedList();

		bool init();

	private:

		Node* _head;
		Node* _tail;

};

#endif // __LINKED_LIST_H_

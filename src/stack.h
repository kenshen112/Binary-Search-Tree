/***********************************************************************
* Header:
*    STACK
* Summary:
*    A custom Stack class
* Author
*    Kenyon Bunker and Tim O'Barr
************************************************************************/
#ifndef STACK_H
#define STACK_H

namespace custom {

	template <class T> class stack {

	private:
		T *data;
		int numElements;
		int numCapacity;
		bool isEmpty;

	public:

		//Constructors
		//Default Cosntructor
		stack()
		{
			numElements = 0;
			numCapacity = 0;
			data = new T[numCapacity];
		}

		//Non-default cosntructor
		stack(int c)
		{
			numElements = 0;
			numCapacity = c;
			data = new T[numCapacity];
		}

		//Copy Constructor
		stack(const stack<T> &rhs)
		{
			try
			{
				if (numElements != rhs.numElements) {
					data = new T[rhs.numElements];
				}

				for (int i = 0; i < rhs.size(); i++) {
					data[i] = rhs.data[i];
				}

				numCapacity = rhs.numCapacity;
				numElements = rhs.numElements;
			}
			catch (std::bad_alloc &er) {
				throw(" ERROR: Unable to allocate a new buffer for vector");
				exit(1);
			}
		}

		//Function Prototypes
		int size() const { return numElements; }
		int capacity() const { return numCapacity; }
		bool empty();
		void clear();
		void push(const T &element);
		void pop();
		int resize(int capacityNew);
		// Top Getter
		T top() const;
		// Top Setter
		T top();

		//assignment operator
		stack <T> & operator = (const stack <T> & rhs)
		{
			numElements = 0;
			if (numElements != rhs.numElements) {
				resize(rhs.size());
			}

			numElements = rhs.size();

			for (int i = 0; i < numElements - 1; i++) {
				data[i] = rhs.data[i];
			}

			return *this;
		}

		//Destructor
		~stack()
		{
			clear();
		}
	};

	/********************************************
	 * Stack : EMPTY
	 * checks if the vector is empty
	 *******************************************/
	template <class T>
	bool stack<T>::empty() {
		if (size() == 0) {
			isEmpty = true;
		}
		else {
			isEmpty = false;
		}
		return isEmpty;
	}

	/********************************************
	 * Stack : PUSH
	 * Adds an element to the top of the stack,
	 * thereby increasing size by one
	 *******************************************/
	template <class T>
	void stack<T>::push(const T &element) {

		if (numCapacity == 0)
		{
			numCapacity = 1;
			//data = new T[numElements];
		}
		if (size() <= capacity()) {
			resize(numCapacity *= 2);
		}
		data[numElements++] = element;
	}

	/********************************************
	 * Stack : POP
	 * Remove the top-most element in the stack,
	 * thereby reducing the size by one.
	 *******************************************/
	template <class T>
	void stack<T>::pop() {
		if (!empty()) {
			--numElements;
		}
		else {
			return;
		}
	}

	/********************************************
	 * Stack : TOP : getter
	 * Returns the top-most element in the stack.
	 *******************************************/
	template <class T>
	T stack<T>::top() const {
		if (!empty()) {
			return data[numElements - 1];
		}
		else {
			throw "ERROR: Unable to reference the element from an empty Stack";
		}
	}

	/********************************************
	 * Stack : TOP : setter
	 * Returns the top-most element in the stack.
	 *******************************************/
	template <class T>
	T stack<T>::top() {
		if (!empty()) {
			return data[numElements - 1];
		}
		else {
			throw "ERROR: Unable to reference the element from an empty Stack";
		}
	}

	/********************************************
	 * Stack : RESIZE
	 * resizes the stack buffer
	 *******************************************/
	template <class T>
	int stack<T>::resize(int capacityNew) {
		try {
			T *dataNew = new T[capacityNew];

			for (int i = 0; i < numElements; i++) {
				dataNew[i] = data[i];
			}

			data = dataNew;
			numCapacity = capacityNew;
		}
		catch (std::bad_alloc) {
			throw "ERROR: Unable to allocate new buffer for Stack";
		}
	};

	/********************************************
	 * Stack : CLEAR
	 * frees stack memory
	 *******************************************/
	template <class T>
	void stack <T> ::clear()
	{
		data = nullptr;
		delete[] data;
		numElements = 0;
		numCapacity = 0;
	}

} // namespace custom

#endif /* STACK_H */
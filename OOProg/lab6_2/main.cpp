#include <iostream>
#include <string>
#include <stdexcept>
#include <queue>
using namespace::std;


class EmptyStack : public runtime_error
{
public:
	EmptyStack(const string & message = "") :runtime_error(message) {}
};


class PriorityQueue2Min
{
	priority_queue <long long, vector<long long>,greater <long long> > data;

public:
	PriorityQueue2Min() :data{}
	{}


	void insert(long long a)
	{
		data.push(a);
	}

	long long firstMin()
	{
		if (data.size())
			return data.top();
		else
			throw EmptyStack("Empty on firstMin()");
	}

	long long secondMin()
	{
		if (data.size() > 1)
		{
			long long  a = data.top();
			data.pop();
			long long  b = data.top();
			data.push(a);
			return b;
		}
			
		else
			throw EmptyStack("Empty on secondMin()");
	}


	long long extractMin()
	{
		if (data.size())
		{
			long long a = data.top();
			data.pop();
			return a;
		}
		else
			throw EmptyStack("Empty on extractMin()");
		
	}

};





int main()
{
	char c;
	int_least64_t v;
	PriorityQueue2Min mpq;
	while (cin >> c)
	{
		try
		{
			switch (c)
			{
			case 'f':
				cout << mpq.firstMin() << "\n";
				break;
			case 's':
				cout << mpq.secondMin() << "\n";
				break;
			case 'a':
				cin >> v;
				mpq.insert(v);
				break;
			case 'p':
				cout << mpq.extractMin() << "\n";
				break;
			}
		}
		catch (const std::exception & e)
		{
			cout << e.what() << "\n";
		}
		catch (...)
		{
			cout << "Dead case\n";
		}
	}
	return 0;
}
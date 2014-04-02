#include <string>
using namespace std;

class IPerson
{
public:
	string FirstName;
	string LastName;

	IPerson(string _firstName, string _lastName)
		: FirstName(_firstName), LastName(_lastName) { }

	virtual ~IPerson() = 0;
};

IPerson::~IPerson() { }
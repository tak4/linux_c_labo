class Super
{
public:
	virtual ~Super(){}
	virtual void func(){}
};

class Sub1 : public Super
{
};

class Sub2 : public Super
{
};

class SubA : public Sub1
{
};


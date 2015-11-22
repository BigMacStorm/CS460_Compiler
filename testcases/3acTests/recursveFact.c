int factorial(int);

//input a number and print resulting factorial
int main()
{
	int fact = 5;
	int total = 1;

	total = factorial(fact);
	return 0;
}

int factorial(int num)
{
	if(num <= 1)
	{
		return 1;
	}	
	return factorial(num-1) * num;
}

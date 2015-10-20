class Constant: public ASTNode{
public:

private:

};

class IntConstant: public Constant{
public:
  IntConstant(std::string id, int integer);
  std::string toString();
  void setID(std::string newid);
  void setInteger(int newInteger);
  int getInteger();
  std::string getID();
private:
  std::string id;
  int integer;
};
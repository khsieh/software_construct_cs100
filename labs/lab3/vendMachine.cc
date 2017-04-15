//Kevin Hsieh, 861054367
//Brittany Seto, 861058099

#include <iostream>
#include <vector>

using namespace std;

class VendMachine
{
  private:
    vector < vector<char> > items;
    vector < vector<bool> > stock;
  public:
    VendMachine();
   // ~VendMachine();
    void buyItem(char c);
    bool outOfStock(char check);
    void print();
    void restock();
    void makeVendMachine();
};

VendMachine::VendMachine()
{
    vector<char> temp(5,' ');
    for(unsigned x = 0; x < 5; x++)
	 items.push_back(temp);
    vector<bool> temp2(5, false);
   for(unsigned y = 0; y < 5; y++)
	 stock.push_back(temp2);

}

void VendMachine::makeVendMachine()
{
   //error1: no initialization
   char itemChar = 'a';
   for(unsigned x = 0; x < 5; x++)
   {
    for(unsigned y = 0; y < 5; y++)
    {
        items.at(x).at(y) = itemChar;
        itemChar++;
    }
   }

  for(unsigned x = 0; x < 5; ++x)
  {
    for(unsigned y = 0; y < 5; ++y)
    {
        stock.at(x).at(y) = true;
    }
  }
}

void VendMachine::buyItem(char c)
{
  char toBuy = c;
  for(unsigned x = 0; x < 5; ++x)
  {
    //error3: infinity loop
    for(unsigned y = 0; y < 5; y = y)
    {
        if(toBuy = items.at(x).at(y) && stock.at(x).at(y))
	{
          cout << "Enjoy your candybar! C:" << endl;
          stock.at(x).at(y) = false;
          return;
        }
    }
  }
}

bool VendMachine::outOfStock(char check)
{
  for(unsigned x = 0; x < 5; ++x)
  {
    //infinite loop
    for(unsigned y = 0; y < 5; ++y)
    {
        if(check == items.at(x).at(y) && stock.at(x).at(y))
        {
          return false;
        }
    }
  }
  //error4: missing return true;
  return true;
}


void VendMachine::print()
{
  cout << "============================" << endl;
  for(unsigned x = 0; x < 5; ++x)
  {
    for(unsigned y = 0; y < 5; ++y)
    {
        cout << items.at(x).at(y) << " ";
    }
    cout << endl;
  }
  cout << "============================" << endl;
}

void VendMachine::restock()
{
  for(unsigned x = 0; x < 5; ++x)
  {
    for(unsigned y = 0; y < 5; ++y)
    {
        stock.at(x).at(y) = true;
    }
  }
}

int main()
{
  VendMachine v;
  v.makeVendMachine();
  char toBuy;
  v.print();
  cout << "Enter the item char of the item you want to buy: ";
  while(cin >> toBuy)
  {
    if(v.outOfStock(toBuy))
    {
      cout << "Item its out of stock! :c"
           << "please come back later."
           << endl;
    }
    else
    {
       v.buyItem(toBuy);
    }
    char restock;
    cout << "restock items now?(y/n)";
    cin >> restock;
    if(restock == 'y')
       v.restock();
    cout << "Enter the item char of the item you want to buy: ";
  }
  return 0;
}

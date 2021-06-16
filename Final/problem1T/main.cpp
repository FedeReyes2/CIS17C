#include <iostream>
#include <array> 
#include <random>
#include <list>
#include <string>
#include <map>
#include <algorithm>

char nth_letter(const int& n)
{
    return "abcdefghijklmnopqrstuvwxyz"[n-1];
}

int appendDigit(int i1, int i2) {
  int i2_copy = i2;
    while (i2_copy) {
        i1 *= 10;
        i2_copy /= 10;
    }
    return i1 + i2;

}
int returnNumber(const int& n)
{
  char temp = std::toupper(nth_letter(n));
  int value;
  if(temp == 'A' || temp == 'B' || temp == 'C')
    value=2;
  else if(temp == 'D' || temp == 'E' || temp == 'F')
    value=3;
  else if(temp == 'G' || temp == 'H' || temp == 'I')
    value=4;
  else if(temp == 'J' || temp == 'K' || temp == 'L')
    value=5;
  else if(temp == 'M' || temp == 'N' || temp == 'O')
    value=6;
  else if(temp == 'P' || temp == 'Q' || temp == 'R'|| temp == 'S')
    value=7;
  else if(temp == 'T' || temp == 'U' || temp == 'V')
    value=8;
  else if(temp == 'W' || temp == 'X' || temp == 'Y' || temp == 'Z' )
    value=9;

  
  return value;
}

int main() {
  std::array<std::list<std::string>,999> hash;
  int length{200}; 
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> dist(1,26);
  std::vector<int> ocurrences;
  
  for(size_t i{}; i < length; i++)
  {
    std::string temp;
    int index{};
    for(size_t j{}; j < 3; j++)
    {
      int random = dist(mt);
      temp += nth_letter(random);
      std::transform(temp.begin(), temp.end(),temp.begin(), ::toupper);
      int val = returnNumber(random);
      index = appendDigit(index, val);
    }
    hash[index].push_back(temp);

    std::cout << i << " " <<  hash[index].front() << index << " ";
  }
  std::cout << hash.size();
  for(size_t i; i < length; i++)
  {
    ocurrences[hash[i].size()] = ocurrences[hash[i].size()]++;
  }
   
  std::cout << "Collision vector length " << length << '\n';
  std::cout << "For 1 occurences: " << ocurrences[1];

  return 0;
}
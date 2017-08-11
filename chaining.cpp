#include <iostream>
#include <map>
#include <utility>
#include <tuple>
#include <vector>
#include <algorithm>


typedef std::tuple<int, int, int, int, int> alignment;

int main() {
  typedef std::multimap<char, int> MCI;
  MCI m;

  m.insert(MCI::value_type('c', 30));
  m.insert(MCI::value_type('a', 10));
  m.insert(MCI::value_type('a', 40));

  MCI::size_type count = m.count('a');
  std::cout << "count = " << count << std::endl;

  std::pair<MCI::iterator, MCI::iterator> p = m.equal_range('a');
  for (MCI::iterator it = p.first; it != p.second; ++it) {
    std::cout << it->second << std::endl;
  }


  std::vector<alignment> As {
    std::make_tuple(1, 7, 1, 10, 10),
    std::make_tuple(3,9,23,32,11)
  };

  std::cout << std::get<0>(As[0]) << std::endl;
  

}

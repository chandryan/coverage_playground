#include "boost/signals2.hpp"
#include <iostream>
#include <vector>

static int some_function(bool in, bool in2) {
  if (in && in2) {
    return 0;
  } else {
    throw 1;
  }
}

int main() {
  std::cout << "Hello, World!" << std::endl;

  boost::signals2::signal<void(int)> sig;
  sig.connect([](int i) {
    if (i) {
      std::cout << "Hello, World!" << std::endl;
    }
  });
  sig(42);

  try {
    some_function(true, true);
    some_function(true, false);
  } catch (int e) {
    std::cout << "Caught exception: " << e;
  }

  std::string one_string{"abc"};
  std::vector<std::string> string_vector{"a", "b", "c"};
  string_vector.push_back("d");
  string_vector.emplace_back("e");
  std::vector<int> v = {1, 2, 3, 4, 5};
  v.emplace_back(6);

  return 0;
}
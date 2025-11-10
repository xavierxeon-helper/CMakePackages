#ifndef PoolH
#define PoolH

#include <cstddef>  // For std::ptrdiff_t
#include <iterator> // For std::forward_iterator_tag

class Pool
{
public:
   Pool(int max);
   Pool(int min, int max, int step = 1);

public:
   class Iterator
   {
   public: // for std:algorithm
      using iterator_category = std::forward_iterator_tag;
      using difference_type = std::ptrdiff_t;
      using value_type = int;
      using pointer = void;
      using reference = void;

   public:
      Iterator(int number, int step, bool isEnd);

   public:
      int operator*() const;
      Iterator& operator++();

      bool operator==(const Iterator& other) const;
      bool operator!=(const Iterator& other) const;

   private:
      int number;
      const int step;
      const bool isEnd;
   };

public:
   Iterator begin();
   Iterator end();

private:
   const int min;
   const int max;
   const int step;
};

#endif // NOT PoolH

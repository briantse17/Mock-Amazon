#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>


#include <iostream>
template <
         typename T,
         typename TComparator = std::equal_to<T>,
         typename PComparator = std::less<double>,
         typename Hasher = std::hash<T> >
class Heap
{
public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const TComparator& tcomp = TComparator()  );

    /// Destructor as needed
    ~Heap();

    /// Adds an item with the provided priority
    void push(double pri, const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

    /// decreaseKey reduces the current priority of
    /// item to newpri, moving it up in the heap
    /// as appropriate.
    void decreaseKey(double newpri, const T& item);

private:
    /// Add whatever helper functions you need below
    void trickleDown(int idx);
    void trickleUp(int size);



    // These should be all the data members you need.
    std::vector< std::pair<double, T> > store_;
    int m_;
    PComparator c_;
    std::unordered_map<T, size_t, Hasher, TComparator> keyToLocation_;

};

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::Heap(
    int m,
    const PComparator& c,
    const Hasher& hash,
    const TComparator& tcomp ) :

    store_(),
    m_(m),
    c_(c),
    keyToLocation_(100, hash, tcomp)

{

}

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::~Heap()
{

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::push(double priority, const T& item)
{
    store_.push_back(make_pair(priority,item));
    keyToLocation_.insert(make_pair(item, store_.size()-1));
    trickleUp(int(store_.size())-1);
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::decreaseKey(double priority, const T& item)
{
    int index = keyToLocation_[item];
    store_[index].first = priority;
    trickleUp(index);
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
T const & Heap<T,TComparator,PComparator,Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }
    return store_[0].second;
    // You complete
}

/// Removes the top element
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::pop()
{
    if(empty()) {
        throw std::logic_error("can't pop an empty heap");
    }
    keyToLocation_.erase(store_[0].second);
    store_[0] = store_.back();
    store_.pop_back();
    trickleDown(0);
}

/// returns true if the heap is empty
template <typename T, typename TComparator, typename PComparator, typename Hasher >
bool Heap<T,TComparator,PComparator,Hasher>::empty() const
{
    return store_.empty();
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::trickleUp(int size)
{
  //parent for 0-based indexing
  int parent = (size-1)/m_;
  //if parent is root node or the current node is preffered to parent
  if(parent < 0 || !(c_(store_[size].first, store_[parent].first)))
  {
    return;
  }
  keyToLocation_[store_[size].second] = parent;
  keyToLocation_[store_[parent].second] = size;
  std::swap(store_[size], store_[parent]);
  trickleUp(parent);
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::trickleDown(int idx)
{
  //if child node not within the tree's boundariesu
  if(idx*m_+1 > int(store_.size()-1))
  {
      return;
  }
  int bestChild = m_*idx+1;
  int rChild = bestChild;
  for(int i = 1; i < m_; i++)
  {
    if(rChild+1 <= int(store_.size()-1))
    {
      rChild += 1;
      //if rChild is preferred to the current bestChild
      if(c_(store_[rChild].first, store_[bestChild].first))
      {
        bestChild = rChild;
      }
    }
  }
  //if bestChild is preferred to current node 
  if(c_(store_[bestChild].first, store_[idx].first))
  {
    keyToLocation_[store_[idx].second] = bestChild;
    keyToLocation_[store_[bestChild].second] = idx;
    std::swap(store_[idx], store_[bestChild]);
    trickleDown(bestChild);
  }
}
#endif


#pragma once

#include <utility>
#include <cstddef>

#define OFFSET_OF(m, n) reinterpret_cast<size_t>(&(((m*)0)->*(&m::n)))

struct impl_t {
  template <class T> T* get_struct() const;
};

template <class T>
struct struct_base_t {
  impl_t __impl__[0];

  template <class... Args>
  static T* create(Args&&... args) {
    return new T(std::forward<Args>(args)...);
  }
};

template <class T>
T* impl_t::get_struct() const {
  return static_cast<T*>(
    static_cast<void*>(
      reinterpret_cast<char*>(
        const_cast<impl_t*>(this)) - OFFSET_OF(T, __impl__)));
}

template <class T>
struct impl : impl_t {
  T* self() {
    return get_struct<T>();
  }
};

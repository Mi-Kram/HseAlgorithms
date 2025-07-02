#ifndef TERNARY_STRING_QUICKSORT_H
#define TERNARY_STRING_QUICKSORT_H

template <typename T>
void ternary_string_quicksort(T* begin, T* end) {
  ternary_string_quicksort(begin, end, 0);
}

template <typename T>
void ternary_string_quicksort(T* begin, T* end, int d) {
  if (end - begin <= 1) return;

  T* mid = begin + (end - begin) / 2;
  int pivot = mid->char_at(d), t;

  T* lt = begin;
  T* gt = end;
  T* i = begin;

  while (i < gt) {
    t = i->char_at(d);
    if (t < pivot) std::swap(*lt++, *i++);
    else if (t > pivot) std::swap(*--gt, *i);
    else ++i;
  }

  ternary_string_quicksort(begin, lt, d);
  if (pivot >= 0) ternary_string_quicksort(lt, gt, d + 1);
  ternary_string_quicksort(gt, end, d);
}

#endif

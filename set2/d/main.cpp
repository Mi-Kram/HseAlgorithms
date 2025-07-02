#include <iomanip>
#include <iostream>
#include <vector>

struct WayInfo {
  int time;
  int speed;
};

class Train {
 public:
  Train(std::vector<WayInfo>* ways)
    : time_(0)
    , total_time_(0)
    , distance_(0)
    , way_idx(0)
    , ways(ways) {
  }

  double distance() const {
    return distance_;
  }

  double totalTime() const {
    return total_time_;
  }

  WayInfo* way() {
    return way_idx == ways->size() ? nullptr : &(*ways)[way_idx];
  }

  double distanceToNextStation() const {
    if (way_idx == ways->size())
      return 0;

    return (*ways)[way_idx].speed * ((*ways)[way_idx].time - time_);
  }

  void nextStation() {
    if (way_idx == ways->size())
      return;

    total_time_ += (*ways)[way_idx].time - time_;
    distance_ += (*ways)[way_idx].speed * ((*ways)[way_idx].time - time_);
    time_ = 0;
    ++way_idx;
  }

  void nextDistance(double d) {
    while (d && way_idx < ways->size()) {
      if (d < distanceToNextStation()) {
        double tmp = d / (*ways)[way_idx].speed;
        time_ += tmp;
        total_time_ += tmp;
        distance_ += d;
        break;
      }

      d -= distanceToNextStation();
      nextStation();
    }
  }

  bool HasStations() {
    return way_idx != ways->size();
  }

 private:
  double time_;
  double total_time_;
  double distance_;
  size_t way_idx;
  std::vector<WayInfo>* ways;
};

int main() {
  int l;
  size_t n;
  std::cin >> l >> n;

  std::vector<WayInfo> ways(n);
  for (size_t i = 0; i < n; i++)
    std::cin >> ways[i].time >> ways[i].speed;

  Train first{&ways}, second{&ways};
  first.nextDistance(l);

  double delay = first.totalTime() - second.totalTime();
  double a, b;

  while (first.HasStations()) {
    a = first.distanceToNextStation(), b = second.distanceToNextStation();
    if (a == b) {
      first.nextStation();
      second.nextStation();
    } else if (a < b) {
      first.nextStation();
      second.nextDistance(a);
    } else {
      first.nextDistance(b);
      second.nextStation();
    }

    delay = std::max(delay, first.totalTime() - second.totalTime());
  }
  delay = std::max(delay, first.totalTime() - second.totalTime());

  std::cout << std::fixed << std::setprecision(3) << delay << std::endl;

  return 0;
}

#include <vector>

class SumTree {
  public:
    SumTree() : v(0), p(0) {}

    void add(int pos, int val) {
        const auto last = v.size() > 0 ? v.back() : 0;
        p.push_back(pos);
        v.push_back(val + last);
    }
    bool is_empty() const { return p.size() == 0; }

    int sample() const { return p[0]; }

    int sum(const int to) const {
        int left = 0; 
        int right = p.size();
        while (right > left + 1) {
            int piv = (left + right) / 2;
            (p[piv] <= to ? left : right) = piv;
        }
        return (left < right && p[left] <= to) ? v[left] : 0;
    }

    int sum_range(const int from, const int to) const {
        return sum(to) - sum(from - 1);
    }

  private:
    std::vector<int> p, v;
};

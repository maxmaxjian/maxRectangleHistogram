// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <iterator>
//
// solution 1
// class solution {
//   public:
//     int largestRectangleArea(const std::vector<int> & heights) {
//         int maxArea = 0;
//         if (heights.size() == 1)
//             return heights[0];
//         else if (heights.size() > 1) {
//             for (auto it = heights.begin()+1; it != heights.end(); ++it) {
//                 // std::copy(heights.begin(), it, std::ostream_iterator<int>(std::cout, " "));
//                 // std::cout << std::endl;
//                 // std::cout << "w = " << std::distance(heights.begin(),it) << ", h = " << *std::min_element(heights.begin(), it) << std::endl;
//                 if (std::distance(heights.begin(),it)**std::min_element(heights.begin(), it) > maxArea) {
//                     maxArea = std::distance(heights.begin(),it)**std::min_element(heights.begin(), it);
//                 }
//             }
//             return std::max(maxArea, largestRectangleArea(std::vector<int>(heights.begin()+1, heights.end())));
//         }
//     }
// };


#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>

// solution 2
class solution {
  public:
    int largestRectangleArea(const std::vector<int> & heights) {
        if (heights.size() == 1)
            return heights[0];
        else if (heights.size() > 1) {
            std::vector<int> minH;
            std::partial_sum(heights.begin(), heights.end(), std::inserter(minH, minH.begin()),
                             [](int prev, int curr){
                                 return prev < curr ? prev : curr;
                             });
            // std::copy(minH.begin(), minH.end(), std::ostream_iterator<int>(std::cout, " "));
            // std::cout << std::endl;
            
            int idx = 1;
            std::transform(minH.begin(), minH.end(), minH.begin(),
                           [&](int i){
                               return i*(idx++);
                           });
            // std::copy(minH.begin(), minH.end(), std::ostream_iterator<int>(std::cout, " "));
            // std::cout << std::endl;
            return std::max(*std::max_element(minH.begin(), minH.end()), largestRectangleArea(std::vector<int>(heights.begin()+1, heights.end())));
        }
    }
};

int main() {
    std::vector<int> hgts{2,1,5,6,2,3};

    solution soln;
    int mA = soln.largestRectangleArea(hgts);
    std::cout << "The largest rectangle area is:\n"
              << mA << std::endl;
}

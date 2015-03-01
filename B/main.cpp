#include <iostream>
#include <algorithm>
#include <vector>
#include <cstddef>

struct InspectionWindow {
    std::intmax_t start;
    std::intmax_t end;

    bool operator<(const InspectionWindow& rhs) const {
        if (end != rhs.end) {
            return end < rhs.end;
        }
        return start < rhs.start;
    }
};

std::ostream& operator<<(std::ostream& os, const InspectionWindow& iw) {
    return os << iw.start << " " << iw.end;
}

std::istream& operator>>(std::istream& is, InspectionWindow& iw) {
    return is >> iw.start >> iw.end;
}

int main() {
    const std::size_t numberOfTestCases = []() {
        std::size_t tmp;
        std::cin >> tmp;
        return tmp;
    }();

    for (std::size_t testCaseId = 0; testCaseId < numberOfTestCases;
         ++testCaseId) {
        const std::size_t numberOfPatrolsToInspect = []() {
            std::size_t tmp;
            std::cin >> tmp;
            return tmp;
        }();
        std::vector<InspectionWindow> patrols(numberOfPatrolsToInspect);

        for (std::size_t patrol = 0; patrol < numberOfPatrolsToInspect;
             ++patrol) {
            std::cin >> patrols[patrol];
        } // for patrol

        // impl begin
        std::sort(patrols.begin(), patrols.end());

        std::vector<InspectionWindow> firstInspection;
        std::vector<InspectionWindow> secondInspection;
        std::intmax_t largeValue = std::numeric_limits<std::intmax_t>::max();
        for (auto it = patrols.begin(); it != patrols.end(); ++it) {
            std::intmax_t deltaTo1 = [&]() {
                if (firstInspection.empty())
                    return largeValue;
                return it->start - firstInspection.back().end;
            }();

            std::intmax_t deltaTo2 = [&]() {
                if (secondInspection.empty()) {
                    return largeValue;
                }
                return it->start - secondInspection.back().end;
            }();

            if (deltaTo1 >= 0 && deltaTo2 >= 0) {
                if (deltaTo1 < deltaTo2) {
                    firstInspection.push_back(*it);
                    continue;
                } else {
                    secondInspection.push_back(*it);
                    continue;
                }
            }
            if (deltaTo1 >= 0) {
                firstInspection.push_back(*it);
                continue;
            }
            if (deltaTo2 >= 0) {
                secondInspection.push_back(*it);
                continue;
            }
        }

        // impl end

        std::cout << firstInspection.size() + secondInspection.size()
                  << std::endl;

        std::cerr << "decisions: " << std::endl;

        for (auto& inspection : firstInspection) {
            std::cerr << inspection << std::endl;
        }
        std::cerr << "-----------" << std::endl;
        for (auto& inspection : secondInspection) {
            std::cerr << inspection << std::endl;
        }
        std::cerr << "===========" << std::endl;

    } // for testcase
} // main

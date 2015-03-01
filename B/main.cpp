#include <iostream>
#include <algorithm>
#include <vector>
#include <cstddef>

struct InspectionWindow {
    std::size_t start;
    std::size_t end;

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

        // first inspection
        std::vector<InspectionWindow> firstInspection;
        std::vector<InspectionWindow> secondInspection;
        InspectionWindow dummy{0, 0};
        firstInspection.push_back(dummy);
        secondInspection.push_back(dummy);
        for (auto it = patrols.begin(); it != patrols.end(); ++it) {
            auto end1 = firstInspection.back().end;
            auto end2 = secondInspection.back().end;
            if (it->start < std::min(end1, end2)) {
                continue;
            }

            int deltaTo1 = it->start - end1;
            int deltaTo2 = it->start - end2;

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

        firstInspection.erase(firstInspection.begin());
        secondInspection.erase(secondInspection.begin());

        // impl end

        std::cout << firstInspection.size() + secondInspection.size()
                  << std::endl;

        std::cerr << "decisions: " << std::endl;

        for (auto& ins : firstInspection) {
            std::cerr << ins << std::endl;
        }
        std::cerr << "-----------" << std::endl;
        for (auto& ins : secondInspection) {
            std::cerr << ins << std::endl;
        }
        std::cerr << "===========" << std::endl;

    } // for testcase
} // main

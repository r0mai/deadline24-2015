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
        firstInspection.push_back(patrols.front());
        for (auto it = patrols.begin() + 1; it != patrols.end(); ++it) {
            if (firstInspection.back().end <= it->start) {
                firstInspection.push_back(*it);
            }
        }

        std::vector<InspectionWindow> remaining;
        std::set_difference(patrols.begin(),
                            patrols.end(),
                            firstInspection.begin(),
                            firstInspection.end(),
                            std::back_inserter(remaining));

        std::vector<InspectionWindow> secondInspection;
        if (!remaining.empty()) {
            secondInspection.push_back(remaining.front());
            for (auto it = remaining.begin() + 1; it != remaining.end(); ++it) {
                if (secondInspection.back().end <= it->start) {
                    secondInspection.push_back(*it);
                }
            }
        }

        // impl end

        std::cout << firstInspection.size() + secondInspection.size()
                  << std::endl;

        std::cout << "decisions: " << std::endl;

        for (auto& ins : firstInspection) {
            std::cout << ins << std::endl;
        }
        std::cout << "-----------" << std::endl;
        for (auto& ins : secondInspection) {
            std::cout << ins << std::endl;
        }
        std::cout << "===========" << std::endl;

    } // for testcase
} // main

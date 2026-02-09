#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        for (auto &ch : line) {
            if (std::isalpha(ch)) ch = ch ^ 32;
        }

        std::reverse(line.begin(), line.end());
        std::cout << line << '\n';
    }

    return 0;
}
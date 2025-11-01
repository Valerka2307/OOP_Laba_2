#include <../include/seven.hpp>

int main() {
    try {
        Seven six("666666");
        Seven one("1");
        Seven num_1("1234");
        Seven num_2("234");
        Seven num_3("1000");
        Seven num_4 = {'1', '2', '3', '4'};
        Seven num_copy = num_1;
        Seven num_move = std::move(num_2);

        std::cout << "666666 + 1 = " << six + one << '\n';
        std::cout << "num_1 = " << num_1 << "\n";
        std::cout << "num_copy = " << num_copy << "\n";
        std::cout << "num_move = " << num_move << "\n";
        std::cout << "num_3 = " << num_3 << "\n";
        std::cout << "num_4 = " << num_4 << "\n\n";

        std::cout << num_1 << " + " << num_move << " = " << (num_1 + num_move) << "\n";
        std::cout << num_1 << " - " << num_move << " = " << (num_1 - num_move) << "\n";

        Seven sum = num_1;
        sum += num_move;
        std::cout << "sum += num_move → sum = " << sum << "\n";

        Seven diff = num_1;
        diff -= num_move;
        std::cout << "diff -= num_move → diff = " << diff << "\n\n";

        std::cout << "++num_1 = " << ++num_1 << "\n";
        std::cout << "num_3-- = " << num_3-- << ", num_3 = " << num_3 << "\n\n";

        std::cout << "num_1 == num_copy : " << (num_1 == num_copy ? "true" : "false") << "\n";
        std::cout << "num_1 > num_move  : " << (num_1 > num_move ? "true" : "false") << "\n";
        std::cout << "num_4 < num_3     : " << (num_4 < num_3 ? "true" : "false") << "\n\n";

        Seven small("56");
        Seven big("654");
        std::cout << small << " - " << big << std::endl;
        Seven bad = small - big;

    } catch (const std::underflow_error& e) {
        std::cerr << e.what() << "\n";

    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << "\n";

    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    }

    try {
        Seven wrong("1784");
        std::cout << wrong << "\n";

    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << "\n";
    }
}

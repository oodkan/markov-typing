#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <random>
#include <algorithm>
#include <stdexcept>
#include <curses.h>

bool is_backspace(const int ch){
    return  ch == KEY_BACKSPACE || ch == '\b' || ch == 127;
}

bool is_enter(const int ch){
    return ch == KEY_ENTER || ch == '\n' || ch == 10;
}

// print somewhere in the screen and return the cursor to original position
// print_no_move
void printnm(const int y, const int x, const std::string& str){
    int old_y, old_x;
    getyx(stdscr, old_y, old_x);
    move(y, x);
    clrtoeol();
    printw(str.c_str());
    move(old_y, old_x);
}

template <typename Seq>
char choice(const Seq& sequence){
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(0, std::size(sequence) - 1);
    return sequence[dis(gen)];
}

template <typename Seq, typename W>
auto weighted_choice(const Seq& sequence, const W& weights){
    auto sum = std::accumulate(std::begin(weights), std::end(weights), 0.0);
    std::mt19937 gen(std::random_device{}());
    auto rnd = std::uniform_real_distribution<>{0, sum}(gen);

    auto it_w = std::begin(weights);
    double rolling_sum = 0;
    while (rolling_sum < rnd)
        rolling_sum += *it_w++;

    auto it = std::begin(sequence);
    std::advance(it, std::distance(std::begin(weights), it_w));
    return *it;
}

template <typename F, typename S>
auto zip(const F& lhs, const S& rhs){
    std::vector<std::pair<typename F::value_type, typename S::value_type>> zipped;
    zipped.reserve(std::size(lhs));

    auto lhs_iter = std::begin(lhs);
    auto rhs_iter = std::begin(rhs);
    while(lhs_iter != std::end(lhs) || rhs_iter != std::end(rhs))
        zipped.emplace_back(*lhs_iter++, *rhs_iter++);

    return zipped;
}

template <typename T, typename E>
bool is_in(const T& container, const E& el){
    auto result = std::find(std::begin(container), std::end(container), el);
    if (result == std::end(container))
        return false;
    return true;
}

#endif /* UTILS_H */

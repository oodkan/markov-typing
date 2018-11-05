#ifndef IO_HH
#define IO_HH

#include "probability_matrix.hh"
#include <string_view>

void write_json(std::string_view, ProbabilityMatrix &);
std::optional<ProbabilityMatrix> read_json(std::string_view, std::string);

void write_frequencies(std::string_view, ProbabilityMatrix &);
std::optional<ProbabilityMatrix> read_frequencies(std::string_view);

void ls_frequencies();

#endif /* ifndef IO_HH */

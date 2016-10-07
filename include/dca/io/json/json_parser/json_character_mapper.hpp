// Copyright (C) 2009-2016 ETH Zurich
// Copyright (C) 2007?-2016 Center for Nanophase Materials Sciences, ORNL
// All rights reserved.
//
// See LICENSE.txt for terms of usage.
// See CITATION.txt for citation guidelines if you use this code for scientific publications.
//
// Author: Peter Staar (taa@zurich.ibm.com)
//
// Description

#ifndef DCA_IO_JSON_JSON_PARSER_JSON_CHARACTER_MAPPER_HPP
#define DCA_IO_JSON_JSON_PARSER_JSON_CHARACTER_MAPPER_HPP

#include <iostream>
#include "dca/io/json/json_parser/json_enumerations.hpp"

namespace dca {
namespace io {
// dca::io::

class JSON_character_mapper {
public:
  static JSON_character_class_type map_char_to_class(wchar_t widec);

  static bool is_white_space(JSON_character_class_type& nextClass);

  static wchar_t get_escaped_character(std::wistream& inputStream);

private:
  static JSON_character_class_type ascii_class[128];
};

}  // io
}  // dca

#endif  // DCA_IO_JSON_JSON_PARSER_JSON_CHARACTER_MAPPER_HPP

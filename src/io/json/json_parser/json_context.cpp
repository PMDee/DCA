// Copyright (C) 2009-2016 ETH Zurich
// Copyright (C) 2007?-2016 Center for Nanophase Materials Sciences, ORNL
// All rights reserved.
//
// See LICENSE.txt for terms of usage.
// See CITATION.txt for citation guidelines if you use this code for scientific publications.
//
// Author: Peter Staar (taa@zurich.ibm.com)
//
// This file implements json_context.hpp.

#include "dca/io/json/json_parser/json_context.hpp"

namespace dca {
namespace io {
// dca::io::

// Object and Array Referenced objects are created when needed on LHS of assignment!
Whatever& JSON_context::referencedObject() {
  Whatever& current(currentObject());

  switch (current.type) {
    case WHATEVER_MAP: {
      Whatever& result(current.whateverMap[key]);
      result.myKey = key;
      result.parent = &current;

      if (trace)
        std::cout << "   referencedMap => '" << result.name() << "' !\n";

      return result;
    }

    case WHATEVER_VECTOR: {
      size_t idx = current.size();
      current.push_back();
      Whatever& result(current.back());
      result.myIndex = idx;
      result.parent = &current;

      if (trace)
        std::cout << "   referencedVector => '" << result.name() << "' !\n";

      return result;
    }

    default:
      if (trace)
        std::cout << "   referencedObject => '" << current.name() << "' !\n";

      return current;
  }
}

}  // io
}  // dca

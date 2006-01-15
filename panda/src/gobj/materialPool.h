// Filename: materialPool.h
// Created by:  drose (30Apr01)
//
////////////////////////////////////////////////////////////////////
//
// PANDA 3D SOFTWARE
// Copyright (c) 2001 - 2004, Disney Enterprises, Inc.  All rights reserved
//
// All use of this software is subject to the terms of the Panda 3d
// Software license.  You should have received a copy of this license
// along with this source code; you will also find a current copy of
// the license at http://etc.cmu.edu/panda3d/docs/license/ .
//
// To contact the maintainers of this program write to
// panda3d-general@lists.sourceforge.net .
//
////////////////////////////////////////////////////////////////////

#ifndef MATERIALPOOL_H
#define MATERIALPOOL_H

#include "pandabase.h"

#include "material.h"

#include "pointerTo.h"

#include "pset.h"

////////////////////////////////////////////////////////////////////
//       Class : MaterialPool
// Description : The MaterialPool (there is only one in the universe)
//               serves to unify different pointers to the same
//               Material, so we do not (a) waste memory with many
//               different Material objects that are all equivalent,
//               and (b) waste time switching the graphics engine
//               between different Material states that are really the
//               same thing.
//
//               The idea is to create a temporary Material
//               representing the lighting state you want to apply,
//               then call get_material(), passing in your temporary
//               Material.  The return value will either be a new
//               Material object, or it may be the the same object you
//               supplied; in either case, it will have the same
//               value.
////////////////////////////////////////////////////////////////////
class EXPCL_PANDA MaterialPool {
PUBLISHED:
  INLINE static Material *get_material(Material *temp);
  INLINE static int garbage_collect();
  INLINE static void list_contents(ostream &out);
  static void write(ostream &out);

private:
  INLINE MaterialPool();

  Material *ns_get_material(Material *temp);
  int ns_garbage_collect();
  void ns_list_contents(ostream &out) const;

  static MaterialPool *get_ptr();

  static MaterialPool *_global_ptr;

  // We store a map of CPT(Material) to PT(Material).  These are two
  // equivalent structures, but different pointers.  The first pointer
  // never leaves this class.  If the second pointer changes value,
  // we'll notice it and return a new one.
  typedef pmap< CPT(Material), PT(Material), indirect_compare_to<const Material *> > Materials;
  Materials _materials;
};

#include "materialPool.I"

#endif



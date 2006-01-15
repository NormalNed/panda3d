// Filename: geomTransformer.h
// Created by:  drose (14Mar02)
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

#ifndef GEOMTRANSFORMER_H
#define GEOMTRANSFORMER_H

#include "pandabase.h"

#include "luse.h"
#include "geom.h"
#include "geomVertexData.h"

class GeomNode;
class RenderState;
class InternalName;

////////////////////////////////////////////////////////////////////
//       Class : GeomTransformer
// Description : An object specifically designed to transform the
//               vertices of a Geom without disturbing indexing or
//               affecting any other Geoms that may share the same
//               vertex arrays, and without needlessly wasting memory
//               when different Geoms sharing the same vertex arrays
//               are transformed by the same amount.
//
//               If you create a single GeomTransformer and use it to
//               transform a number of different Geoms by various
//               transformations, then those Geoms which happen to
//               share the same arrays and are transformed by the same
//               amounts will still share the same arrays as each
//               other (but different from the original arrays).
////////////////////////////////////////////////////////////////////
class EXPCL_PANDA GeomTransformer {
public:
  GeomTransformer();
  GeomTransformer(const GeomTransformer &copy);
  ~GeomTransformer();

  INLINE int get_max_collect_vertices() const;
  INLINE void set_max_collect_vertices(int max_collect_vertices);

  bool transform_vertices(Geom *geom, const LMatrix4f &mat);
  bool transform_vertices(GeomNode *node, const LMatrix4f &mat);

  bool transform_texcoords(Geom *geom, const InternalName *from_name,
                           InternalName *to_name, const LMatrix4f &mat);
  bool transform_texcoords(GeomNode *node, const InternalName *from_name,
                           InternalName *to_name, const LMatrix4f &mat);

  bool set_color(Geom *geom, const Colorf &color);
  bool set_color(GeomNode *node, const Colorf &color);

  bool transform_colors(Geom *geom, const LVecBase4f &scale);
  bool transform_colors(GeomNode *node, const LVecBase4f &scale);

  bool apply_state(GeomNode *node, const RenderState *state);

  int collect_vertex_data(Geom *geom, int collect_bits);
  int collect_vertex_data(GeomNode *node, int collect_bits);

private:
  int _max_collect_vertices;

  class SourceVertices {
  public:
    INLINE bool operator < (const SourceVertices &other) const;

    LMatrix4f _mat;
    CPT(GeomVertexData) _vertex_data;
  };
  typedef pmap<SourceVertices, PT(GeomVertexData) > NewVertices;
  NewVertices _vertices;

  class SourceTexCoords {
  public:
    INLINE bool operator < (const SourceTexCoords &other) const;

    LMatrix4f _mat;
    CPT(InternalName) _from;
    CPT(InternalName) _to;
    CPT(GeomVertexData) _vertex_data;
  };
  typedef pmap<SourceTexCoords, PT(GeomVertexData) > NewTexCoords;
  NewTexCoords _texcoords;

  class SourceColors {
  public:
    INLINE bool operator < (const SourceColors &other) const;

    LVecBase4f _color;
    CPT(GeomVertexData) _vertex_data;
  };
  typedef pmap<SourceColors, CPT(GeomVertexData) > NewColors;

  // We have two concepts of colors: the "fixed" colors, which are
  // slapped in as a complete replacement of the original colors
  // (e.g. via a ColorAttrib), and the "transformed" colors, which are
  // modified from the original colors (e.g. via a ColorScaleAttrib).
  NewColors _fcolors, _tcolors;

  class AlreadyCollectedData {
  public:
    CPT(GeomVertexData) _data;
    int _offset;
  };
  typedef pmap< CPT(GeomVertexData), AlreadyCollectedData> AlreadyCollected;
  AlreadyCollected _already_collected;

  class NewCollectedKey {
  public:
    INLINE bool operator < (const NewCollectedKey &other) const;

    string _name;
    CPT(GeomVertexFormat) _format;
    Geom::UsageHint _usage_hint;
  };
  typedef pmap< NewCollectedKey, PT(GeomVertexData) > NewCollectedData;
  NewCollectedData _new_collected_data;
};

#include "geomTransformer.I"

#endif


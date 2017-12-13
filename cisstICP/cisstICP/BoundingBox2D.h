// ****************************************************************************
//
//    Copyright (c) 2014, Seth Billings, Russell Taylor, Johns Hopkins University
//    All rights reserved.
//
//    Redistribution and use in source and binary forms, with or without
//    modification, are permitted provided that the following conditions are
//    met:
//
//    1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
//    3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
//    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//    A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//    HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  
// ****************************************************************************
#ifndef H_BoundingBox2D
#define H_BoundingBox2D

#include <cisstVector.h>
#include <cisstCommon.h>

class BoundingBox2D
{
 public: 
  vct2 MinCorner;
  vct2 MaxCorner;
  //vct2 HalfExtents;  // SDB
 public:

  //void ComputeHalfExtents();

  vct2 Diagonal() const {return MaxCorner-MinCorner;};
  double DiagonalLength() const {return Diagonal().Norm();};

  vct2 MidPoint() const { return (MinCorner+MaxCorner)*0.5;};

  BoundingBox2D(const vct2& MinC, const vct2& MaxC )
    : MinCorner(MinC), MaxCorner(MaxC)
    {}; //{ ComputeHalfExtents(); };

  BoundingBox2D()
    : MinCorner(HUGE_VAL,HUGE_VAL), MaxCorner(-HUGE_VAL,-HUGE_VAL)
    {}; //{ ComputeHalfExtents(); };
  
  BoundingBox2D(const BoundingBox2D& S)
    : MinCorner(S.MinCorner), MaxCorner(S.MaxCorner)
    {}; //{ ComputeHalfExtents(); };
  
  BoundingBox2D& operator=(const BoundingBox2D& S)
    { MinCorner=S.MinCorner; MaxCorner=S.MaxCorner; 
      //HalfExtents=S.HalfExtents; 
      return *this; };

  BoundingBox2D& operator=(const vct2& V)
	{ MinCorner=MaxCorner=V;
    //HalfExtents.Assign(0.0,0.0,0.0);
    return *this;};

  BoundingBox2D& Include(const BoundingBox2D& him);
  BoundingBox2D& Include(const vct2& V);
 
  BoundingBox2D& EnlargeBy(double dist)
  { MinCorner -= dist; MaxCorner+= dist; };
    //ComputeHalfExtents(); };

  int Includes(const vct2& p,double dist=0.0) const
  { if (p[0] +dist < MinCorner[0]) return 0;
    if (p[1] +dist < MinCorner[1]) return 0;
    //if (p[2] +dist < MinCorner[2]) return 0;
    if (p[0] -dist > MaxCorner[0]) return 0;
    if (p[1] -dist > MaxCorner[1]) return 0;
    //if (p[2] -dist > MaxCorner[2]) return 0;
	  return 1; // point is within distance "dist" of this bounding box
  };
  
  int Includes(const BoundingBox2D& B,double dist=0.0) const
  { return Includes(B.MinCorner,dist)&&Includes(B.MaxCorner,dist);
  };
};

#endif
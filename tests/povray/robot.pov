#version 3.7;

global_settings {
  assumed_gamma 1.0
}

#include "colors.inc"
#include "metals.inc"
#include "finish.inc"

camera {
  right x
  angle 20
  location < 10 * sin(clock * 2 * pi), 5, 10 * cos(clock * 2 * pi)>
  look_at  <0, 0, 0>
}

#declare Arm = merge {
  sphere {
    <0, 0, 0>, 0.5
    pigment {
      color Red
    }
  }

  cylinder {
    <0, 0, -(0.5 - 0.15)>,
    <-1, 0, -(0.5 - 0.15)>,
    0.15
  }

}

merge {
  box {
    <1, 1, 1>, <-1, -1, -1>
  }

  sphere {
    <0, 1, 0>, 0.65
    pigment {
      color Red
    }
  }

  object {
    Arm
    rotate <0, 0, 30>
    translate <0, 0, -1>
  }

  object {
    Arm
    rotate <180, 0, 0>
    rotate <0, 0, 30>
    translate <0, 0, 1>
  }

  cylinder {
    <-1, -1, -0.9>,
    <-1, -1, 0.9>,
    0.5
    pigment {
      color Black
    }
  }

  cylinder {
    <1, -1, -0.9>,
    <1, -1, 0.9>,
    0.5
    pigment {
      color Black
    }
  }

  texture { pigment { P_Chrome5 } finish { F_MetalB  } }

  finish {
    Shiny
  }
}

light_source {
  <0, 50, 0>
  color White
  area_light <5, 0, 0>, <0, 0, 5>, 5, 5
  adaptive 1
  jitter
}

// light_source {
//   <-10, -10, 0>
//   color White
// }

// light_source {
//   <0, 10, 0>
//   color White
// }

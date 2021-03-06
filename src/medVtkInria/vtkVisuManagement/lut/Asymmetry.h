/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#pragma once


static const float AsymmetryLUT[256][3] =
{

  { 0.0      ,  0.0      ,  1.0      }, // 0.0
  { 0.0      ,  0.019608 ,  1.0      },
  { 0.0      ,  0.039216 ,  1.0      },
  { 0.0      ,  0.058824 ,  1.0      },
  { 0.0      ,  0.078431 ,  1.0      },
  { 0.0      ,  0.098039 ,  1.0      },
  { 0.0      ,  0.117647 ,  1.0      },
  { 0.0      ,  0.137255 ,  1.0      },
  { 0.0      ,  0.156863 ,  1.0      },
  { 0.0      ,  0.176471 ,  1.0      },
  { 0.0      ,  0.196078 ,  1.0      },
  { 0.0      ,  0.215686 ,  1.0      },
  { 0.0      ,  0.235294 ,  1.0      },
  { 0.0      ,  0.254902 ,  1.0      },
  { 0.0      ,  0.274510 ,  1.0      },
  { 0.0      ,  0.294118 ,  1.0      },
  { 0.0      ,  0.313725 ,  1.0      },
  { 0.0      ,  0.333333 ,  1.0      },
  { 0.0      ,  0.352941 ,  1.0      },
  { 0.0      ,  0.372549 ,  1.0      },
  { 0.0      ,  0.392157 ,  1.0      },
  { 0.0      ,  0.411765 ,  1.0      },
  { 0.0      ,  0.431373 ,  1.0      },
  { 0.0      ,  0.450980 ,  1.0      },
  { 0.0      ,  0.470588 ,  1.0      },
  { 0.0      ,  0.490196 ,  1.0      },
  { 0.0      ,  0.509804 ,  1.0      },
  { 0.0      ,  0.529412 ,  1.0      },
  { 0.0      ,  0.549020 ,  1.0      },
  { 0.0      ,  0.568627 ,  1.0      },
  { 0.0      ,  0.588235 ,  1.0      },
  { 0.0      ,  0.607843 ,  1.0      },
  { 0.0      ,  0.627451 ,  1.0      },
  { 0.0      ,  0.647059 ,  1.0      },
  { 0.0      ,  0.666667 ,  1.0      },
  { 0.0      ,  0.686275 ,  1.0      },
  { 0.0      ,  0.705882 ,  1.0      },
  { 0.0      ,  0.725490 ,  1.0      },
  { 0.0      ,  0.745098 ,  1.0      },
  { 0.0      ,  0.764706 ,  1.0      },
  { 0.0      ,  0.784314 ,  1.0      },
  { 0.0      ,  0.803922 ,  1.0      },
  { 0.0      ,  0.823529 ,  1.0      },
  { 0.0      ,  0.843137 ,  1.0      },
  { 0.0      ,  0.862745 ,  1.0      },
  { 0.0      ,  0.882353 ,  1.0      },
  { 0.0      ,  0.901961 ,  1.0      },
  { 0.0      ,  0.921569 ,  1.0      },
  { 0.0      ,  0.941176 ,  1.0      },
  { 0.0      ,  0.960784 ,  1.0      },
  { 0.0      ,  0.980392 ,  1.0      },

  { 0.0      ,  1.0      ,  1.0      }, // 0.2
  { 0.0      ,  1.0      ,  0.980392 },
  { 0.0      ,  1.0      ,  0.960784 },
  { 0.0      ,  1.0      ,  0.941176 },
  { 0.0      ,  1.0      ,  0.921569 },
  { 0.0      ,  1.0      ,  0.901961 },
  { 0.0      ,  1.0      ,  0.882353 },
  { 0.0      ,  1.0      ,  0.862745 },
  { 0.0      ,  1.0      ,  0.843137 },
  { 0.0      ,  1.0      ,  0.823529 },
  { 0.0      ,  1.0      ,  0.803922 },
  { 0.0      ,  1.0      ,  0.784314 },
  { 0.0      ,  1.0      ,  0.764706 },
  { 0.0      ,  1.0      ,  0.745098 },
  { 0.0      ,  1.0      ,  0.725490 },
  { 0.0      ,  1.0      ,  0.705882 },
  { 0.0      ,  1.0      ,  0.686275 },
  { 0.0      ,  1.0      ,  0.666667 },
  { 0.0      ,  1.0      ,  0.647059 },
  { 0.0      ,  1.0      ,  0.627451 },
  { 0.0      ,  1.0      ,  0.607843 },
  { 0.0      ,  1.0      ,  0.588235 },
  { 0.0      ,  1.0      ,  0.568627 },
  { 0.0      ,  1.0      ,  0.549020 },
  { 0.0      ,  1.0      ,  0.529412 },
  { 0.0      ,  1.0      ,  0.509804 },
  { 0.0      ,  1.0      ,  0.490196 },
  { 0.0      ,  1.0      ,  0.470588 },
  { 0.0      ,  1.0      ,  0.450980 },
  { 0.0      ,  1.0      ,  0.431373 },
  { 0.0      ,  1.0      ,  0.411765 },
  { 0.0      ,  1.0      ,  0.392157 },
  { 0.0      ,  1.0      ,  0.372549 },
  { 0.0      ,  1.0      ,  0.352941 },
  { 0.0      ,  1.0      ,  0.333333 },
  { 0.0      ,  1.0      ,  0.313725 },
  { 0.0      ,  1.0      ,  0.294118 },
  { 0.0      ,  1.0      ,  0.274510 },
  { 0.0      ,  1.0      ,  0.254902 },
  { 0.0      ,  1.0      ,  0.235294 },
  { 0.0      ,  1.0      ,  0.215686 },
  { 0.0      ,  1.0      ,  0.196078 },
  { 0.0      ,  1.0      ,  0.176471 },
  { 0.0      ,  1.0      ,  0.156863 },
  { 0.0      ,  1.0      ,  0.137255 },
  { 0.0      ,  1.0      ,  0.117647 },
  { 0.0      ,  1.0      ,  0.098039 },
  { 0.0      ,  1.0      ,  0.078431 },
  { 0.0      ,  1.0      ,  0.058824 },
  { 0.0      ,  1.0      ,  0.039216 },
  { 0.0      ,  1.0      ,  0.019608 },

  { 0.0      ,  1.0      ,  0.0      }, // 0.4
  { 0.019608 ,  1.0      ,  0.0      },
  { 0.039216 ,  1.0      ,  0.0      },
  { 0.058824 ,  1.0      ,  0.0      },
  { 0.078431 ,  1.0      ,  0.0      },
  { 0.098039 ,  1.0      ,  0.0      },
  { 0.117647 ,  1.0      ,  0.0      },
  { 0.137255 ,  1.0      ,  0.0      },
  { 0.156863 ,  1.0      ,  0.0      },
  { 0.176471 ,  1.0      ,  0.0      },
  { 0.196078 ,  1.0      ,  0.0      },
  { 0.215686 ,  1.0      ,  0.0      },
  { 0.235294 ,  1.0      ,  0.0      },
  { 0.254902 ,  1.0      ,  0.0      },
  { 0.274510 ,  1.0      ,  0.0      },
  { 0.294118 ,  1.0      ,  0.0      },
  { 0.313725 ,  1.0      ,  0.0      },
  { 0.333333 ,  1.0      ,  0.0      },
  { 0.352941 ,  1.0      ,  0.0      },
  { 0.372549 ,  1.0      ,  0.0      },
  { 0.392157 ,  1.0      ,  0.0      },
  { 0.411765 ,  1.0      ,  0.0      },
  { 0.431373 ,  1.0      ,  0.0      },
  { 0.450980 ,  1.0      ,  0.0      },
  { 0.470588 ,  1.0      ,  0.0      },
  { 0.490196 ,  1.0      ,  0.0      },
  { 0.509804 ,  1.0      ,  0.0      },
  { 0.529412 ,  1.0      ,  0.0      },
  { 0.549020 ,  1.0      ,  0.0      },
  { 0.568627 ,  1.0      ,  0.0      },
  { 0.588235 ,  1.0      ,  0.0      },
  { 0.607843 ,  1.0      ,  0.0      },
  { 0.627451 ,  1.0      ,  0.0      },
  { 0.647059 ,  1.0      ,  0.0      },
  { 0.666667 ,  1.0      ,  0.0      },
  { 0.686275 ,  1.0      ,  0.0      },
  { 0.705882 ,  1.0      ,  0.0      },
  { 0.725490 ,  1.0      ,  0.0      },
  { 0.745098 ,  1.0      ,  0.0      },
  { 0.764706 ,  1.0      ,  0.0      },
  { 0.784314 ,  1.0      ,  0.0      },
  { 0.803922 ,  1.0      ,  0.0      },
  { 0.823529 ,  1.0      ,  0.0      },
  { 0.843137 ,  1.0      ,  0.0      },
  { 0.862745 ,  1.0      ,  0.0      },
  { 0.882353 ,  1.0      ,  0.0      },
  { 0.901961 ,  1.0      ,  0.0      },
  { 0.921569 ,  1.0      ,  0.0      },
  { 0.941176 ,  1.0      ,  0.0      },
  { 0.960784 ,  1.0      ,  0.0      },
  { 0.980392 ,  1.0      ,  0.0      },

  { 1.0      ,  1.0      ,  0.0      }, // 0.6
  { 1.0      ,  0.980392 ,  0.0      },
  { 1.0      ,  0.960784 ,  0.0      },
  { 1.0      ,  0.941176 ,  0.0      },
  { 1.0      ,  0.921569 ,  0.0      },
  { 1.0      ,  0.901961 ,  0.0      },
  { 1.0      ,  0.882353 ,  0.0      },
  { 1.0      ,  0.862745 ,  0.0      },
  { 1.0      ,  0.843137 ,  0.0      },
  { 1.0      ,  0.823529 ,  0.0      },
  { 1.0      ,  0.803922 ,  0.0      },
  { 1.0      ,  0.784314 ,  0.0      },
  { 1.0      ,  0.764706 ,  0.0      },
  { 1.0      ,  0.745098 ,  0.0      },
  { 1.0      ,  0.725490 ,  0.0      },
  { 1.0      ,  0.705882 ,  0.0      },
  { 1.0      ,  0.686275 ,  0.0      },
  { 1.0      ,  0.666667 ,  0.0      },
  { 1.0      ,  0.647059 ,  0.0      },
  { 1.0      ,  0.627451 ,  0.0      },
  { 1.0      ,  0.607843 ,  0.0      },
  { 1.0      ,  0.588235 ,  0.0      },
  { 1.0      ,  0.568627 ,  0.0      },
  { 1.0      ,  0.549020 ,  0.0      },
  { 1.0      ,  0.529412 ,  0.0      },
  { 1.0      ,  0.509804 ,  0.0      },
  { 1.0      ,  0.490196 ,  0.0      },
  { 1.0      ,  0.470588 ,  0.0      },
  { 1.0      ,  0.450980 ,  0.0      },
  { 1.0      ,  0.431373 ,  0.0      },
  { 1.0      ,  0.411765 ,  0.0      },
  { 1.0      ,  0.392157 ,  0.0      },
  { 1.0      ,  0.372549 ,  0.0      },
  { 1.0      ,  0.352941 ,  0.0      },
  { 1.0      ,  0.333333 ,  0.0      },
  { 1.0      ,  0.313725 ,  0.0      },
  { 1.0      ,  0.294118 ,  0.0      },
  { 1.0      ,  0.274510 ,  0.0      },
  { 1.0      ,  0.254902 ,  0.0      },
  { 1.0      ,  0.235294 ,  0.0      },
  { 1.0      ,  0.215686 ,  0.0      },
  { 1.0      ,  0.196078 ,  0.0      },
  { 1.0      ,  0.176471 ,  0.0      },
  { 1.0      ,  0.156863 ,  0.0      },
  { 1.0      ,  0.137255 ,  0.0      },
  { 1.0      ,  0.117647 ,  0.0      },
  { 1.0      ,  0.098039 ,  0.0      },
  { 1.0      ,  0.078431 ,  0.0      },
  { 1.0      ,  0.058824 ,  0.0      },
  { 1.0      ,  0.039216 ,  0.0      },
  { 1.0      ,  0.019608 ,  0.0      },

  { 1.0      ,  0.0      ,  0.0      }, // 0.8
  { 1.0      ,  0.0      ,  0.019608 },
  { 1.0      ,  0.0      ,  0.039216 },
  { 1.0      ,  0.0      ,  0.058824 },
  { 1.0      ,  0.0      ,  0.078431 },
  { 1.0      ,  0.0      ,  0.098039 },
  { 1.0      ,  0.0      ,  0.117647 },
  { 1.0      ,  0.0      ,  0.137255 },
  { 1.0      ,  0.0      ,  0.156863 },
  { 1.0      ,  0.0      ,  0.176471 },
  { 1.0      ,  0.0      ,  0.196078 },
  { 1.0      ,  0.0      ,  0.215686 },
  { 1.0      ,  0.0      ,  0.235294 },
  { 1.0      ,  0.0      ,  0.254902 },
  { 1.0      ,  0.0      ,  0.274510 },
  { 1.0      ,  0.0      ,  0.294118 },
  { 1.0      ,  0.0      ,  0.313725 },
  { 1.0      ,  0.0      ,  0.333333 },
  { 1.0      ,  0.0      ,  0.352941 },
  { 1.0      ,  0.0      ,  0.372549 },
  { 1.0      ,  0.0      ,  0.392157 },
  { 1.0      ,  0.0      ,  0.411765 },
  { 1.0      ,  0.0      ,  0.431373 },
  { 1.0      ,  0.0      ,  0.450980 },
  { 1.0      ,  0.0      ,  0.470588 },
  { 1.0      ,  0.0      ,  0.490196 },
  { 1.0      ,  0.0      ,  0.509804 },
  { 1.0      ,  0.0      ,  0.529412 },
  { 1.0      ,  0.0      ,  0.549020 },
  { 1.0      ,  0.0      ,  0.568627 },
  { 1.0      ,  0.0      ,  0.588235 },
  { 1.0      ,  0.0      ,  0.607843 },
  { 1.0      ,  0.0      ,  0.627451 },
  { 1.0      ,  0.0      ,  0.647059 },
  { 1.0      ,  0.0      ,  0.666667 },
  { 1.0      ,  0.0      ,  0.686275 },
  { 1.0      ,  0.0      ,  0.705882 },
  { 1.0      ,  0.0      ,  0.725490 },
  { 1.0      ,  0.0      ,  0.745098 },
  { 1.0      ,  0.0      ,  0.764706 },
  { 1.0      ,  0.0      ,  0.784314 },
  { 1.0      ,  0.0      ,  0.803922 },
  { 1.0      ,  0.0      ,  0.823529 },
  { 1.0      ,  0.0      ,  0.843137 },
  { 1.0      ,  0.0      ,  0.862745 },
  { 1.0      ,  0.0      ,  0.882353 },
  { 1.0      ,  0.0      ,  0.901961 },
  { 1.0      ,  0.0      ,  0.921569 },
  { 1.0      ,  0.0      ,  0.941176 },
  { 1.0      ,  0.0      ,  0.960784 },
  { 1.0      ,  0.0      ,  0.980392 },
  { 1.0      ,  0.0      ,  1.0      }  // 1.0
};




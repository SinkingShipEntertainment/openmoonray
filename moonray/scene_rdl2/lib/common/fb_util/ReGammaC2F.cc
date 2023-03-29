// Copyright 2023 DreamWorks Animation LLC
// SPDX-License-Identifier: Apache-2.0

//
//
#include "ReGammaC2F.h"

#include <math.h>

namespace scene_rdl2 {
namespace fb_util {

//
// Precomputed lookup table for conversion of gamma 2.2 corrected 8bit value to linear float.
// This table is generated by ReGammaC2FLUT::tblGen().
// Toshi (Apr/12/2018)
//
static const float gamma22c2f[256] = {
  /* tblid:  0 */ 0,
  /* tblid:  1 */ 5.07705e-06,
  /* tblid:  2 */ 2.3328e-05,
  /* tblid:  3 */ 5.69218e-05,
  /* tblid:  4 */ 0.000107187,
  /* tblid:  5 */ 0.000175124,
  /* tblid:  6 */ 0.000261544,
  /* tblid:  7 */ 0.000367136,
  /* tblid:  8 */ 0.000492504,
  /* tblid:  9 */ 0.000638183,
  /* tblid: 10 */ 0.000804658,
  /* tblid: 11 */ 0.000992374,
  /* tblid: 12 */ 0.00120174,
  /* tblid: 13 */ 0.00143313,
  /* tblid: 14 */ 0.00168692,
  /* tblid: 15 */ 0.00196342,
  /* tblid: 16 */ 0.00226295,
  /* tblid: 17 */ 0.00258583,
  /* tblid: 18 */ 0.00293232,
  /* tblid: 19 */ 0.0033027,
  /* tblid: 20 */ 0.00369724,
  /* tblid: 21 */ 0.00411618,
  /* tblid: 22 */ 0.00455975,
  /* tblid: 23 */ 0.0050282,
  /* tblid: 24 */ 0.00552174,
  /* tblid: 25 */ 0.00604059,
  /* tblid: 26 */ 0.00658496,
  /* tblid: 27 */ 0.00715504,
  /* tblid: 28 */ 0.00775103,
  /* tblid: 29 */ 0.00837312,
  /* tblid: 30 */ 0.00902149,
  /* tblid: 31 */ 0.00969633,
  /* tblid: 32 */ 0.0103978,
  /* tblid: 33 */ 0.0111261,
  /* tblid: 34 */ 0.0118813,
  /* tblid: 35 */ 0.0126637,
  /* tblid: 36 */ 0.0134734,
  /* tblid: 37 */ 0.0143105,
  /* tblid: 38 */ 0.0151752,
  /* tblid: 39 */ 0.0160677,
  /* tblid: 40 */ 0.0169881,
  /* tblid: 41 */ 0.0179364,
  /* tblid: 42 */ 0.018913,
  /* tblid: 43 */ 0.0199178,
  /* tblid: 44 */ 0.0209511,
  /* tblid: 45 */ 0.022013,
  /* tblid: 46 */ 0.0231036,
  /* tblid: 47 */ 0.0242229,
  /* tblid: 48 */ 0.0253713,
  /* tblid: 49 */ 0.0265487,
  /* tblid: 50 */ 0.0277553,
  /* tblid: 51 */ 0.0289912,
  /* tblid: 52 */ 0.0302565,
  /* tblid: 53 */ 0.0315514,
  /* tblid: 54 */ 0.0328759,
  /* tblid: 55 */ 0.0342302,
  /* tblid: 56 */ 0.0356144,
  /* tblid: 57 */ 0.0370285,
  /* tblid: 58 */ 0.0384727,
  /* tblid: 59 */ 0.0399472,
  /* tblid: 60 */ 0.0414519,
  /* tblid: 61 */ 0.042987,
  /* tblid: 62 */ 0.0445526,
  /* tblid: 63 */ 0.0461488,
  /* tblid: 64 */ 0.0477758,
  /* tblid: 65 */ 0.0494335,
  /* tblid: 66 */ 0.0511221,
  /* tblid: 67 */ 0.0528416,
  /* tblid: 68 */ 0.0545923,
  /* tblid: 69 */ 0.0563741,
  /* tblid: 70 */ 0.0581872,
  /* tblid: 71 */ 0.0600316,
  /* tblid: 72 */ 0.0619075,
  /* tblid: 73 */ 0.0638149,
  /* tblid: 74 */ 0.0657539,
  /* tblid: 75 */ 0.0677246,
  /* tblid: 76 */ 0.0697271,
  /* tblid: 77 */ 0.0717615,
  /* tblid: 78 */ 0.0738278,
  /* tblid: 79 */ 0.0759261,
  /* tblid: 80 */ 0.0780566,
  /* tblid: 81 */ 0.0802193,
  /* tblid: 82 */ 0.0824142,
  /* tblid: 83 */ 0.0846415,
  /* tblid: 84 */ 0.0869013,
  /* tblid: 85 */ 0.0891935,
  /* tblid: 86 */ 0.0915184,
  /* tblid: 87 */ 0.0938759,
  /* tblid: 88 */ 0.0962661,
  /* tblid: 89 */ 0.0986892,
  /* tblid: 90 */ 0.101145,
  /* tblid: 91 */ 0.103634,
  /* tblid: 92 */ 0.106156,
  /* tblid: 93 */ 0.108711,
  /* tblid: 94 */ 0.111299,
  /* tblid: 95 */ 0.113921,
  /* tblid: 96 */ 0.116576,
  /* tblid: 97 */ 0.119264,
  /* tblid: 98 */ 0.121986,
  /* tblid: 99 */ 0.124741,
  /* tblid:100 */ 0.12753,
  /* tblid:101 */ 0.130352,
  /* tblid:102 */ 0.133209,
  /* tblid:103 */ 0.136099,
  /* tblid:104 */ 0.139022,
  /* tblid:105 */ 0.14198,
  /* tblid:106 */ 0.144972,
  /* tblid:107 */ 0.147998,
  /* tblid:108 */ 0.151058,
  /* tblid:109 */ 0.154152,
  /* tblid:110 */ 0.157281,
  /* tblid:111 */ 0.160444,
  /* tblid:112 */ 0.163641,
  /* tblid:113 */ 0.166872,
  /* tblid:114 */ 0.170138,
  /* tblid:115 */ 0.173439,
  /* tblid:116 */ 0.176774,
  /* tblid:117 */ 0.180144,
  /* tblid:118 */ 0.183549,
  /* tblid:119 */ 0.186989,
  /* tblid:120 */ 0.190463,
  /* tblid:121 */ 0.193972,
  /* tblid:122 */ 0.197516,
  /* tblid:123 */ 0.201096,
  /* tblid:124 */ 0.20471,
  /* tblid:125 */ 0.20836,
  /* tblid:126 */ 0.212044,
  /* tblid:127 */ 0.215764,
  /* tblid:128 */ 0.21952,
  /* tblid:129 */ 0.22331,
  /* tblid:130 */ 0.227137,
  /* tblid:131 */ 0.230998,
  /* tblid:132 */ 0.234895,
  /* tblid:133 */ 0.238828,
  /* tblid:134 */ 0.242796,
  /* tblid:135 */ 0.2468,
  /* tblid:136 */ 0.25084,
  /* tblid:137 */ 0.254916,
  /* tblid:138 */ 0.259027,
  /* tblid:139 */ 0.263175,
  /* tblid:140 */ 0.267358,
  /* tblid:141 */ 0.271577,
  /* tblid:142 */ 0.275833,
  /* tblid:143 */ 0.280124,
  /* tblid:144 */ 0.284452,
  /* tblid:145 */ 0.288816,
  /* tblid:146 */ 0.293216,
  /* tblid:147 */ 0.297653,
  /* tblid:148 */ 0.302126,
  /* tblid:149 */ 0.306635,
  /* tblid:150 */ 0.311181,
  /* tblid:151 */ 0.315763,
  /* tblid:152 */ 0.320382,
  /* tblid:153 */ 0.325037,
  /* tblid:154 */ 0.329729,
  /* tblid:155 */ 0.334458,
  /* tblid:156 */ 0.339223,
  /* tblid:157 */ 0.344026,
  /* tblid:158 */ 0.348865,
  /* tblid:159 */ 0.353741,
  /* tblid:160 */ 0.358654,
  /* tblid:161 */ 0.363604,
  /* tblid:162 */ 0.368591,
  /* tblid:163 */ 0.373615,
  /* tblid:164 */ 0.378676,
  /* tblid:165 */ 0.383775,
  /* tblid:166 */ 0.38891,
  /* tblid:167 */ 0.394083,
  /* tblid:168 */ 0.399293,
  /* tblid:169 */ 0.404541,
  /* tblid:170 */ 0.409826,
  /* tblid:171 */ 0.415148,
  /* tblid:172 */ 0.420508,
  /* tblid:173 */ 0.425905,
  /* tblid:174 */ 0.43134,
  /* tblid:175 */ 0.436813,
  /* tblid:176 */ 0.442323,
  /* tblid:177 */ 0.447871,
  /* tblid:178 */ 0.453456,
  /* tblid:179 */ 0.45908,
  /* tblid:180 */ 0.464741,
  /* tblid:181 */ 0.47044,
  /* tblid:182 */ 0.476177,
  /* tblid:183 */ 0.481952,
  /* tblid:184 */ 0.487765,
  /* tblid:185 */ 0.493616,
  /* tblid:186 */ 0.499505,
  /* tblid:187 */ 0.505432,
  /* tblid:188 */ 0.511398,
  /* tblid:189 */ 0.517401,
  /* tblid:190 */ 0.523443,
  /* tblid:191 */ 0.529523,
  /* tblid:192 */ 0.535642,
  /* tblid:193 */ 0.541798,
  /* tblid:194 */ 0.547994,
  /* tblid:195 */ 0.554227,
  /* tblid:196 */ 0.560499,
  /* tblid:197 */ 0.56681,
  /* tblid:198 */ 0.573159,
  /* tblid:199 */ 0.579547,
  /* tblid:200 */ 0.585973,
  /* tblid:201 */ 0.592438,
  /* tblid:202 */ 0.598942,
  /* tblid:203 */ 0.605484,
  /* tblid:204 */ 0.612066,
  /* tblid:205 */ 0.618686,
  /* tblid:206 */ 0.625345,
  /* tblid:207 */ 0.632043,
  /* tblid:208 */ 0.638779,
  /* tblid:209 */ 0.645555,
  /* tblid:210 */ 0.65237,
  /* tblid:211 */ 0.659224,
  /* tblid:212 */ 0.666117,
  /* tblid:213 */ 0.673049,
  /* tblid:214 */ 0.68002,
  /* tblid:215 */ 0.687031,
  /* tblid:216 */ 0.694081,
  /* tblid:217 */ 0.701169,
  /* tblid:218 */ 0.708298,
  /* tblid:219 */ 0.715465,
  /* tblid:220 */ 0.722672,
  /* tblid:221 */ 0.729919,
  /* tblid:222 */ 0.737205,
  /* tblid:223 */ 0.74453,
  /* tblid:224 */ 0.751895,
  /* tblid:225 */ 0.7593,
  /* tblid:226 */ 0.766744,
  /* tblid:227 */ 0.774227,
  /* tblid:228 */ 0.781751,
  /* tblid:229 */ 0.789314,
  /* tblid:230 */ 0.796917,
  /* tblid:231 */ 0.804559,
  /* tblid:232 */ 0.812241,
  /* tblid:233 */ 0.819964,
  /* tblid:234 */ 0.827726,
  /* tblid:235 */ 0.835528,
  /* tblid:236 */ 0.84337,
  /* tblid:237 */ 0.851252,
  /* tblid:238 */ 0.859174,
  /* tblid:239 */ 0.867136,
  /* tblid:240 */ 0.875138,
  /* tblid:241 */ 0.88318,
  /* tblid:242 */ 0.891262,
  /* tblid:243 */ 0.899384,
  /* tblid:244 */ 0.907547,
  /* tblid:245 */ 0.91575,
  /* tblid:246 */ 0.923993,
  /* tblid:247 */ 0.932277,
  /* tblid:248 */ 0.940601,
  /* tblid:249 */ 0.948965,
  /* tblid:250 */ 0.95737,
  /* tblid:251 */ 0.965815,
  /* tblid:252 */ 0.9743,
  /* tblid:253 */ 0.982826,
  /* tblid:254 */ 0.991393,
  /* tblid:255 */ 1
};

// static function
float
ReGammaC2F::rg22(const uint8_t uc)
//
// This is equivalent to powf((float)uc / 255.0f, 2.2f)
//
{
    return gamma22c2f[uc];
}

} // namespace fb_util
} // namespace scene_rdl2


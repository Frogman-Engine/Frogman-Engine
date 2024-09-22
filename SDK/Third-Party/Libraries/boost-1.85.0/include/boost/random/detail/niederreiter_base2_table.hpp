/* boost random/detail/nierderreiter_base2_table.hpp header file
 *
 * Copyright Justinas Vygintas Daugmaudis 2010-2018
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_RANDOM_DETAIL_NIEDERREITER_BASE2_TABLE_HPP
#define BOOST_RANDOM_DETAIL_NIEDERREITER_BASE2_TABLE_HPP

#include <boost/config.hpp>
#include <cstddef>

namespace boost {
namespace random {

namespace detail {
namespace qrng_tables {

// Maximum allowed space dimension. This number of dimensions has been
// chosen because up to 4720th GF(2) prime the values fit to unsigned short,
// which produces a (still) reasonably small table.
#define BOOST_RANDOM_NIEDERREITER_BASE2_MAX_DIMENSION 4720

struct niederreiter_base2
{
  BOOST_STATIC_CONSTANT(unsigned, max_dimension = BOOST_RANDOM_NIEDERREITER_BASE2_MAX_DIMENSION);

  typedef unsigned short value_type;

  // Binary irreducible polynomials (primes in the ring GF(2)[X]), evaluated at X=2.
  // Mathematica code:
  // Reap[
  //   Do[If[IrreduciblePolynomialQ[
  //       IntegerDigits[n, 2].x^Reverse[Range[0, Floor[Log[2, n]]]],
  //       Modulus -> 2], Sow[n]], {n, 2, 65535}]][[2, 1]]
  static value_type polynomial(std::size_t n)
  {
    static const value_type nb2_a[max_dimension] = {
      2, 3, 7, 11, 13, 19, 25, 31, 37, 41, 47, 55, 59, 61, 67, 73, 87, 91,
      97, 103, 109, 115, 117, 131, 137, 143, 145, 157, 167, 171, 185, 191,
      193, 203, 211, 213, 229, 239, 241, 247, 253, 283, 285, 299, 301, 313,
      319, 333, 351, 355, 357, 361, 369, 375, 379, 391, 395, 397, 415, 419,
      425, 433, 445, 451, 463, 471, 477, 487, 499, 501, 505, 515, 529, 535,
      539, 545, 557, 563, 587, 601, 607, 613, 617, 623, 631, 637, 647, 661,
      665, 675, 677, 687, 695, 701, 719, 721, 731, 757, 761, 769, 787, 789,
      799, 803, 817, 827, 841, 847, 859, 865, 875, 877, 883, 895, 901, 911,
      929, 949, 953, 967, 971, 973, 981, 985, 995, 1001, 1019, 1033, 1039,
      1051, 1053, 1063, 1069, 1077, 1095, 1107, 1123, 1125, 1135, 1153,
      1163, 1177, 1193, 1199, 1221, 1225, 1239, 1255, 1261, 1267, 1279,
      1291, 1293, 1305, 1311, 1315, 1329, 1341, 1347, 1367, 1377, 1383,
      1387, 1413, 1423, 1431, 1435, 1441, 1451, 1465, 1473, 1479, 1509,
      1527, 1531, 1555, 1557, 1571, 1573, 1585, 1591, 1603, 1615, 1617,
      1627, 1657, 1663, 1669, 1673, 1703, 1709, 1717, 1727, 1729, 1741,
      1747, 1759, 1783, 1789, 1807, 1809, 1815, 1821, 1825, 1835, 1845,
      1849, 1863, 1869, 1877, 1881, 1891, 1915, 1917, 1921, 1927, 1933,
      1939, 1961, 1969, 1989, 2011, 2027, 2035, 2041, 2047, 2053, 2071,
      2091, 2093, 2119, 2147, 2149, 2161, 2171, 2189, 2197, 2207, 2217,
      2225, 2243, 2255, 2257, 2273, 2279, 2283, 2293, 2317, 2323, 2341,
      2345, 2359, 2363, 2365, 2373, 2377, 2385, 2395, 2419, 2421, 2431,
      2435, 2447, 2475, 2477, 2489, 2503, 2521, 2533, 2543, 2551, 2561,
      2567, 2579, 2581, 2601, 2633, 2657, 2669, 2681, 2687, 2693, 2705,
      2717, 2727, 2731, 2739, 2741, 2773, 2783, 2787, 2793, 2799, 2801,
      2811, 2819, 2825, 2833, 2867, 2879, 2881, 2891, 2905, 2911, 2917,
      2927, 2941, 2951, 2955, 2963, 2965, 2991, 2999, 3005, 3017, 3035,
      3037, 3047, 3053, 3083, 3085, 3097, 3103, 3121, 3159, 3169, 3179,
      3187, 3189, 3205, 3209, 3223, 3227, 3229, 3251, 3263, 3271, 3277,
      3283, 3285, 3299, 3305, 3319, 3331, 3343, 3357, 3367, 3373, 3393,
      3399, 3413, 3417, 3427, 3439, 3441, 3475, 3487, 3497, 3515, 3517,
      3529, 3543, 3547, 3553, 3559, 3573, 3583, 3589, 3613, 3617, 3623,
      3627, 3635, 3641, 3655, 3659, 3669, 3679, 3697, 3707, 3709, 3713,
      3731, 3743, 3747, 3771, 3785, 3791, 3805, 3827, 3833, 3851, 3865,
      3889, 3895, 3933, 3947, 3949, 3957, 3961, 3971, 3985, 3991, 3995,
      4007, 4013, 4021, 4045, 4051, 4069, 4073, 4091, 4105, 4119, 4129,
      4147, 4149, 4159, 4173, 4179, 4201, 4215, 4219, 4221, 4225, 4235,
      4249, 4259, 4261, 4303, 4305, 4331, 4333, 4351, 4359, 4383, 4387,
      4401, 4407, 4411, 4431, 4439, 4449, 4459, 4461, 4473, 4483, 4485,
      4497, 4523, 4531, 4569, 4575, 4579, 4591, 4593, 4609, 4621, 4627,
      4633, 4645, 4663, 4667, 4669, 4675, 4677, 4711, 4717, 4723, 4735,
      4789, 4793, 4801, 4811, 4873, 4879, 4891, 4893, 4897, 4915, 4921,
      4927, 4941, 4965, 4977, 5017, 5023, 5027, 5033, 5039, 5051, 5059,
      5073, 5079, 5085, 5107, 5109, 5127, 5139, 5169, 5175, 5193, 5199,
      5211, 5213, 5223, 5227, 5237, 5247, 5257, 5281, 5287, 5293, 5301,
      5325, 5331, 5337, 5343, 5349, 5391, 5405, 5451, 5453, 5505, 5523,
      5541, 5545, 5563, 5573, 5591, 5597, 5611, 5625, 5635, 5641, 5659,
      5695, 5697, 5703, 5707, 5717, 5721, 5731, 5733, 5743, 5779, 5797,
      5821, 5827, 5833, 5841, 5857, 5863, 5875, 5887, 5899, 5909, 5913,
      5949, 5955, 5957, 5967, 5975, 5981, 6003, 6005, 6009, 6025, 6031,
      6039, 6045, 6061, 6067, 6079, 6081, 6111, 6139, 6151, 6157, 6175,
      6179, 6193, 6199, 6217, 6231, 6237, 6253, 6265, 6271, 6275, 6289,
      6295, 6305, 6329, 6347, 6349, 6383, 6385, 6395, 6405, 6409, 6427,
      6445, 6453, 6465, 6475, 6495, 6501, 6511, 6523, 6529, 6539, 6553,
      6577, 6583, 6589, 6601, 6607, 6621, 6631, 6637, 6649, 6683, 6685,
      6689, 6699, 6707, 6733, 6739, 6741, 6751, 6755, 6761, 6779, 6795,
      6833, 6853, 6865, 6881, 6887, 6891, 6901, 6923, 6925, 6931, 6937,
      6943, 6959, 6981, 6999, 7049, 7055, 7057, 7079, 7093, 7097, 7103,
      7105, 7115, 7123, 7139, 7165, 7171, 7173, 7183, 7185, 7191, 7207,
      7245, 7263, 7303, 7327, 7333, 7351, 7355, 7365, 7369, 7375, 7383,
      7403, 7405, 7411, 7425, 7431, 7459, 7471, 7485, 7491, 7505, 7515,
      7517, 7527, 7541, 7545, 7555, 7557, 7561, 7569, 7591, 7603, 7617,
      7663, 7687, 7701, 7705, 7727, 7739, 7741, 7749, 7761, 7773, 7777,
      7783, 7795, 7823, 7831, 7835, 7865, 7871, 7885, 7891, 7907, 7921,
      7927, 7939, 7953, 7963, 7975, 7993, 8007, 8011, 8019, 8037, 8049,
      8061, 8065, 8077, 8089, 8111, 8123, 8125, 8131, 8133, 8137, 8161,
      8173, 8191, 8219, 8231, 8245, 8275, 8293, 8303, 8331, 8333, 8351,
      8357, 8367, 8379, 8381, 8387, 8393, 8417, 8435, 8461, 8469, 8489,
      8495, 8507, 8515, 8551, 8555, 8569, 8585, 8599, 8605, 8639, 8641,
      8647, 8653, 8671, 8675, 8689, 8699, 8729, 8741, 8759, 8765, 8771,
      8795, 8797, 8825, 8831, 8841, 8855, 8859, 8883, 8895, 8909, 8943,
      8951, 8955, 8965, 8999, 9003, 9031, 9045, 9049, 9071, 9073, 9085,
      9095, 9101, 9109, 9123, 9129, 9137, 9143, 9147, 9185, 9197, 9209,
      9227, 9235, 9247, 9253, 9257, 9277, 9297, 9303, 9313, 9325, 9343,
      9347, 9371, 9373, 9397, 9407, 9409, 9415, 9419, 9443, 9481, 9495,
      9501, 9505, 9517, 9529, 9555, 9557, 9571, 9585, 9591, 9607, 9611,
      9621, 9625, 9631, 9647, 9661, 9669, 9679, 9687, 9707, 9731, 9733,
      9745, 9773, 9791, 9803, 9811, 9817, 9833, 9847, 9851, 9863, 9875,
      9881, 9905, 9911, 9917, 9923, 9963, 9973, 10003, 10025, 10043, 10063,
      10071, 10077, 10091, 10099, 10105, 10115, 10129, 10145, 10169, 10183,
      10187, 10207, 10223, 10225, 10247, 10265, 10271, 10275, 10289, 10299,
      10301, 10309, 10343, 10357, 10373, 10411, 10413, 10431, 10445, 10453,
      10463, 10467, 10473, 10491, 10505, 10511, 10513, 10523, 10539, 10549,
      10559, 10561, 10571, 10581, 10615, 10621, 10625, 10643, 10655, 10671,
      10679, 10685, 10691, 10711, 10739, 10741, 10755, 10767, 10781, 10785,
      10803, 10805, 10829, 10857, 10863, 10865, 10875, 10877, 10917, 10921,
      10929, 10949, 10967, 10971, 10987, 10995, 11009, 11029, 11043, 11045,
      11055, 11063, 11075, 11081, 11117, 11135, 11141, 11159, 11163, 11181,
      11187, 11225, 11237, 11261, 11279, 11297, 11307, 11309, 11327, 11329,
      11341, 11377, 11403, 11405, 11413, 11427, 11439, 11453, 11461, 11473,
      11479, 11489, 11495, 11499, 11533, 11545, 11561, 11567, 11575, 11579,
      11589, 11611, 11623, 11637, 11657, 11663, 11687, 11691, 11701, 11747,
      11761, 11773, 11783, 11795, 11797, 11817, 11849, 11855, 11867, 11869,
      11873, 11883, 11919, 11921, 11927, 11933, 11947, 11955, 11961, 11999,
      12027, 12029, 12037, 12041, 12049, 12055, 12095, 12097, 12107, 12109,
      12121, 12127, 12133, 12137, 12181, 12197, 12207, 12209, 12239, 12253,
      12263, 12269, 12277, 12287, 12295, 12309, 12313, 12335, 12361, 12367,
      12391, 12409, 12415, 12433, 12449, 12469, 12479, 12481, 12499, 12505,
      12517, 12527, 12549, 12559, 12597, 12615, 12621, 12639, 12643, 12657,
      12667, 12707, 12713, 12727, 12741, 12745, 12763, 12769, 12779, 12781,
      12787, 12799, 12809, 12815, 12829, 12839, 12857, 12875, 12883, 12889,
      12901, 12929, 12947, 12953, 12959, 12969, 12983, 12987, 12995, 13015,
      13019, 13031, 13063, 13077, 13103, 13137, 13149, 13173, 13207, 13211,
      13227, 13241, 13249, 13255, 13269, 13283, 13285, 13303, 13307, 13321,
      13339, 13351, 13377, 13389, 13407, 13417, 13431, 13435, 13447, 13459,
      13465, 13477, 13501, 13513, 13531, 13543, 13561, 13581, 13599, 13605,
      13617, 13623, 13637, 13647, 13661, 13677, 13683, 13695, 13725, 13729,
      13753, 13773, 13781, 13785, 13795, 13801, 13807, 13825, 13835, 13855,
      13861, 13871, 13883, 13897, 13905, 13915, 13939, 13941, 13969, 13979,
      13981, 13997, 14027, 14035, 14037, 14051, 14063, 14085, 14095, 14107,
      14113, 14125, 14137, 14145, 14151, 14163, 14193, 14199, 14219, 14229,
      14233, 14243, 14277, 14287, 14289, 14295, 14301, 14305, 14323, 14339,
      14341, 14359, 14365, 14375, 14387, 14411, 14425, 14441, 14449, 14499,
      14513, 14523, 14537, 14543, 14561, 14579, 14585, 14593, 14599, 14603,
      14611, 14641, 14671, 14695, 14701, 14723, 14725, 14743, 14753, 14759,
      14765, 14795, 14797, 14803, 14831, 14839, 14845, 14855, 14889, 14895,
      14909, 14929, 14941, 14945, 14951, 14963, 14965, 14985, 15033, 15039,
      15053, 15059, 15061, 15071, 15077, 15081, 15099, 15121, 15147, 15149,
      15157, 15167, 15187, 15193, 15203, 15205, 15215, 15217, 15223, 15243,
      15257, 15269, 15273, 15287, 15291, 15313, 15335, 15347, 15359, 15373,
      15379, 15381, 15391, 15395, 15397, 15419, 15439, 15453, 15469, 15491,
      15503, 15517, 15527, 15531, 15545, 15559, 15593, 15611, 15613, 15619,
      15639, 15643, 15649, 15661, 15667, 15669, 15681, 15693, 15717, 15721,
      15741, 15745, 15765, 15793, 15799, 15811, 15825, 15835, 15847, 15851,
      15865, 15877, 15881, 15887, 15899, 15915, 15935, 15937, 15955, 15973,
      15977, 16011, 16035, 16061, 16069, 16087, 16093, 16097, 16121, 16141,
      16153, 16159, 16165, 16183, 16189, 16195, 16197, 16201, 16209, 16215,
      16225, 16259, 16265, 16273, 16299, 16309, 16355, 16375, 16381, 16417,
      16427, 16435, 16441, 16447, 16467, 16479, 16485, 16507, 16519, 16553,
      16559, 16571, 16573, 16591, 16599, 16619, 16627, 16633, 16651, 16653,
      16659, 16699, 16707, 16713, 16727, 16743, 16749, 16785, 16795, 16797,
      16807, 16811, 16813, 16821, 16853, 16857, 16881, 16897, 16909, 16965,
      16969, 16983, 16993, 17011, 17017, 17023, 17027, 17029, 17053, 17057,
      17095, 17099, 17101, 17123, 17129, 17135, 17155, 17161, 17179, 17185,
      17191, 17215, 17257, 17275, 17277, 17287, 17301, 17327, 17353, 17373,
      17387, 17389, 17407, 17419, 17421, 17475, 17501, 17523, 17545, 17601,
      17619, 17621, 17631, 17635, 17649, 17659, 17667, 17673, 17679, 17707,
      17721, 17753, 17775, 17783, 17789, 17805, 17817, 17823, 17829, 17847,
      17861, 17865, 17873, 17879, 17895, 17907, 17919, 17935, 17949, 17959,
      17973, 17991, 18009, 18019, 18033, 18043, 18061, 18067, 18069, 18083,
      18085, 18117, 18127, 18139, 18155, 18175, 18213, 18225, 18243, 18255,
      18303, 18313, 18321, 18331, 18343, 18357, 18369, 18387, 18393, 18405,
      18409, 18415, 18429, 18451, 18457, 18463, 18491, 18499, 18513, 18523,
      18529, 18535, 18559, 18563, 18577, 18623, 18631, 18659, 18673, 18679,
      18685, 18717, 18721, 18733, 18745, 18753, 18771, 18783, 18789, 18793,
      18807, 18823, 18827, 18857, 18895, 18897, 18909, 18913, 18919, 18967,
      18997, 19033, 19045, 19067, 19073, 19079, 19083, 19091, 19107, 19119,
      19133, 19145, 19165, 19181, 19193, 19231, 19255, 19273, 19291, 19297,
      19307, 19309, 19315, 19321, 19333, 19343, 19351, 19361, 19371, 19379,
      19385, 19403, 19405, 19413, 19423, 19441, 19451, 19465, 19483, 19485,
      19495, 19499, 19519, 19527, 19531, 19539, 19541, 19557, 19581, 19597,
      19621, 19645, 19653, 19665, 19671, 19693, 19711, 19733, 19743, 19753,
      19761, 19781, 19791, 19793, 19829, 19845, 19855, 19885, 19891, 19905,
      19923, 19953, 19963, 19969, 19989, 20003, 20023, 20035, 20041, 20049,
      20075, 20077, 20099, 20123, 20147, 20179, 20197, 20201, 20207, 20253,
      20257, 20299, 20309, 20319, 20329, 20335, 20353, 20365, 20383, 20389,
      20393, 20407, 20411, 20439, 20459, 20461, 20473, 20487, 20511, 20517,
      20571, 20573, 20641, 20683, 20693, 20697, 20707, 20713, 20719, 20731,
      20763, 20769, 20781, 20799, 20819, 20825, 20831, 20847, 20861, 20875,
      20889, 20901, 20913, 20919, 20943, 20945, 20955, 20971, 20973, 20981,
      20991, 20997, 21007, 21037, 21093, 21105, 21131, 21145, 21155, 21169,
      21181, 21187, 21189, 21199, 21201, 21223, 21227, 21241, 21249, 21273,
      21285, 21289, 21303, 21321, 21339, 21351, 21365, 21403, 21405, 21415,
      21433, 21439, 21447, 21459, 21477, 21489, 21501, 21507, 21519, 21527,
      21557, 21561, 21575, 21593, 21599, 21627, 21645, 21651, 21653, 21663,
      21681, 21687, 21691, 21725, 21729, 21739, 21779, 21785, 21807, 21815,
      21863, 21867, 21877, 21881, 21887, 21891, 21893, 21905, 21911, 21933,
      21953, 21971, 21983, 21993, 22007, 22023, 22029, 22037, 22051, 22057,
      22063, 22065, 22103, 22109, 22171, 22187, 22189, 22195, 22209, 22215,
      22221, 22257, 22263, 22267, 22315, 22317, 22335, 22347, 22357, 22361,
      22371, 22373, 22397, 22419, 22447, 22461, 22467, 22469, 22487, 22503,
      22515, 22531, 22545, 22561, 22573, 22579, 22581, 22591, 22593, 22653,
      22663, 22667, 22677, 22681, 22691, 22703, 22705, 22737, 22749, 22759,
      22763, 22777, 22783, 22803, 22819, 22843, 22863, 22911, 22927, 22935,
      22941, 22945, 22951, 22955, 22965, 22987, 23007, 23017, 23037, 23053,
      23059, 23071, 23077, 23099, 23101, 23107, 23109, 23113, 23157, 23183,
      23207, 23221, 23233, 23251, 23253, 23257, 23287, 23311, 23319, 23325,
      23339, 23347, 23353, 23361, 23395, 23401, 23415, 23449, 23459, 23465,
      23491, 23493, 23521, 23531, 23545, 23559, 23563, 23577, 23601, 23607,
      23625, 23645, 23661, 23673, 23683, 23713, 23743, 23745, 23755, 23757,
      23781, 23813, 23825, 23837, 23859, 23861, 23879, 23919, 23943, 23949,
      23957, 23967, 23971, 23977, 23995, 24009, 24015, 24027, 24033, 24067,
      24079, 24091, 24109, 24135, 24139, 24163, 24189, 24193, 24217, 24229,
      24233, 24279, 24283, 24295, 24309, 24327, 24333, 24345, 24351, 24355,
      24381, 24387, 24389, 24401, 24417, 24427, 24437, 24457, 24471, 24491,
      24525, 24543, 24547, 24549, 24561, 24587, 24589, 24597, 24623, 24637,
      24655, 24657, 24673, 24679, 24683, 24713, 24727, 24733, 24737, 24747,
      24755, 24761, 24787, 24789, 24823, 24841, 24849, 24877, 24889, 24897,
      24915, 24945, 24957, 24991, 24997, 25007, 25019, 25051, 25069, 25077,
      25087, 25131, 25139, 25141, 25145, 25159, 25165, 25187, 25199, 25213,
      25229, 25247, 25253, 25257, 25265, 25271, 25303, 25307, 25309, 25323,
      25325, 25331, 25343, 25379, 25393, 25399, 25405, 25435, 25453, 25461,
      25477, 25481, 25489, 25505, 25535, 25583, 25597, 25609, 25623, 25645,
      25665, 25671, 25677, 25685, 25739, 25749, 25759, 25769, 25777, 25831,
      25845, 25857, 25867, 25881, 25911, 25915, 25923, 25925, 25929, 25947,
      25987, 26001, 26023, 26029, 26041, 26047, 26067, 26069, 26073, 26085,
      26095, 26097, 26103, 26113, 26119, 26125, 26147, 26171, 26191, 26205,
      26219, 26221, 26227, 26243, 26255, 26263, 26279, 26283, 26293, 26297,
      26329, 26335, 26345, 26385, 26395, 26401, 26419, 26443, 26463, 26473,
      26487, 26497, 26531, 26543, 26551, 26577, 26599, 26603, 26613, 26627,
      26641, 26651, 26653, 26667, 26689, 26707, 26735, 26743, 26763, 26765,
      26771, 26783, 26789, 26793, 26821, 26825, 26879, 26887, 26905, 26927,
      26941, 26967, 26987, 26995, 26997, 27001, 27013, 27023, 27035, 27037,
      27041, 27051, 27079, 27085, 27113, 27137, 27143, 27147, 27161, 27171,
      27183, 27217, 27227, 27239, 27243, 27245, 27253, 27267, 27287, 27315,
      27317, 27327, 27329, 27339, 27341, 27369, 27375, 27387, 27389, 27395,
      27415, 27435, 27443, 27449, 27463, 27467, 27477, 27497, 27517, 27521,
      27533, 27541, 27551, 27555, 27557, 27569, 27575, 27589, 27607, 27617,
      27629, 27635, 27641, 27659, 27673, 27695, 27709, 27717, 27735, 27745,
      27763, 27829, 27833, 27839, 27841, 27847, 27851, 27877, 27889, 27909,
      27913, 27919, 27927, 27947, 27987, 28003, 28005, 28009, 28027, 28067,
      28081, 28091, 28093, 28099, 28101, 28125, 28169, 28199, 28205, 28211,
      28225, 28237, 28243, 28271, 28283, 28289, 28295, 28309, 28335, 28343,
      28355, 28379, 28381, 28409, 28417, 28437, 28457, 28465, 28475, 28495,
      28503, 28507, 28513, 28549, 28561, 28567, 28587, 28597, 28615, 28633,
      28639, 28649, 28677, 28701, 28715, 28723, 28725, 28747, 28797, 28801,
      28813, 28841, 28855, 28859, 28873, 28879, 28893, 28897, 28947, 28949,
      28953, 28963, 28977, 28983, 28989, 29021, 29035, 29065, 29079, 29083,
      29089, 29109, 29119, 29131, 29151, 29157, 29175, 29179, 29209, 29215,
      29231, 29233, 29243, 29263, 29281, 29287, 29327, 29357, 29363, 29377,
      29389, 29395, 29407, 29413, 29425, 29431, 29443, 29449, 29479, 29483,
      29505, 29525, 29541, 29551, 29581, 29587, 29605, 29629, 29641, 29649,
      29671, 29683, 29685, 29695, 29715, 29717, 29737, 29775, 29783, 29787,
      29803, 29805, 29827, 29867, 29875, 29895, 29901, 29909, 29919, 29929,
      29947, 29949, 29975, 29979, 29985, 30005, 30017, 30027, 30071, 30075,
      30081, 30105, 30115, 30141, 30159, 30161, 30187, 30197, 30201, 30207,
      30237, 30265, 30279, 30291, 30293, 30303, 30307, 30309, 30313, 30343,
      30357, 30367, 30371, 30383, 30395, 30405, 30417, 30443, 30451, 30457,
      30475, 30511, 30537, 30545, 30551, 30573, 30579, 30595, 30601, 30631,
      30637, 30645, 30663, 30675, 30677, 30703, 30741, 30757, 30769, 30781,
      30799, 30801, 30811, 30829, 30887, 30893, 30899, 30911, 30923, 30925,
      30937, 30943, 30953, 30959, 30979, 30991, 30999, 31015, 31027, 31053,
      31065, 31087, 31089, 31099, 31105, 31111, 31141, 31153, 31173, 31177,
      31191, 31197, 31235, 31259, 31271, 31275, 31285, 31295, 31307, 31317,
      31351, 31361, 31373, 31401, 31415, 31419, 31427, 31457, 31475, 31477,
      31499, 31523, 31547, 31557, 31567, 31569, 31581, 31591, 31609, 31621,
      31631, 31649, 31659, 31673, 31699, 31715, 31729, 31735, 31749, 31753,
      31783, 31789, 31833, 31849, 31869, 31883, 31891, 31893, 31907, 31927,
      31939, 31953, 31965, 31979, 31993, 31999, 32001, 32021, 32055, 32069,
      32073, 32115, 32121, 32143, 32145, 32151, 32167, 32179, 32199, 32205,
      32213, 32233, 32251, 32253, 32257, 32269, 32281, 32303, 32325, 32353,
      32373, 32383, 32393, 32399, 32411, 32413, 32427, 32447, 32455, 32467,
      32483, 32485, 32521, 32545, 32575, 32589, 32597, 32625, 32651, 32653,
      32665, 32671, 32675, 32689, 32707, 32709, 32721, 32727, 32737, 32743,
      32771, 32785, 32791, 32813, 32821, 32863, 32879, 32887, 32897, 32903,
      32915, 32933, 32945, 32957, 32963, 32975, 32989, 32999, 33013, 33023,
      33025, 33045, 33061, 33111, 33117, 33121, 33133, 33145, 33157, 33185,
      33191, 33209, 33227, 33229, 33237, 33247, 33277, 33299, 33339, 33349,
      33407, 33417, 33423, 33435, 33483, 33497, 33507, 33521, 33559, 33563,
      33579, 33587, 33607, 33613, 33631, 33635, 33641, 33649, 33675, 33685,
      33689, 33711, 33723, 33725, 33733, 33745, 33781, 33817, 33827, 33839,
      33841, 33847, 33865, 33895, 33901, 33913, 33923, 33925, 33943, 33953,
      33973, 34015, 34031, 34039, 34043, 34045, 34077, 34081, 34087, 34099,
      34119, 34123, 34143, 34161, 34171, 34177, 34189, 34211, 34225, 34231,
      34245, 34249, 34267, 34285, 34291, 34313, 34321, 34333, 34347, 34389,
      34393, 34405, 34429, 34433, 34451, 34473, 34479, 34487, 34499, 34523,
      34547, 34559, 34571, 34573, 34581, 34591, 34601, 34609, 34667, 34693,
      34697, 34703, 34717, 34731, 34733, 34739, 34751, 34783, 34793, 34801,
      34807, 34817, 34823, 34853, 34871, 34875, 34889, 34909, 34913, 34931,
      34937, 34947, 34959, 34961, 34995, 34997, 35015, 35033, 35075, 35077,
      35081, 35089, 35095, 35111, 35173, 35197, 35221, 35225, 35247, 35279,
      35281, 35291, 35293, 35309, 35327, 35351, 35385, 35413, 35427, 35429,
      35441, 35451, 35463, 35467, 35487, 35503, 35505, 35549, 35595, 35597,
      35643, 35645, 35651, 35693, 35699, 35729, 35741, 35777, 35787, 35797,
      35801, 35813, 35825, 35873, 35879, 35911, 35925, 35929, 35939, 35945,
      35975, 35987, 36003, 36009, 36027, 36041, 36065, 36075, 36097, 36103,
      36107, 36133, 36143, 36163, 36177, 36187, 36205, 36223, 36229, 36233,
      36251, 36257, 36287, 36299, 36301, 36325, 36329, 36335, 36343, 36363,
      36383, 36411, 36433, 36439, 36467, 36469, 36495, 36503, 36507, 36513,
      36543, 36545, 36563, 36575, 36581, 36603, 36623, 36647, 36651, 36665,
      36673, 36691, 36693, 36709, 36727, 36733, 36773, 36791, 36797, 36809,
      36817, 36833, 36839, 36875, 36889, 36895, 36901, 36919, 36925, 36931,
      36951, 36961, 36973, 36981, 37001, 37009, 37019, 37021, 37037, 37091,
      37125, 37129, 37135, 37143, 37147, 37149, 37185, 37197, 37239, 37243,
      37273, 37283, 37289, 37297, 37309, 37327, 37345, 37379, 37393, 37403,
      37409, 37415, 37427, 37439, 37453, 37459, 37471, 37499, 37511, 37525,
      37539, 37559, 37577, 37597, 37621, 37625, 37651, 37681, 37687, 37701,
      37705, 37719, 37747, 37759, 37763, 37789, 37793, 37813, 37835, 37855,
      37871, 37873, 37883, 37903, 37931, 37933, 37941, 37963, 37971, 38007,
      38013, 38027, 38035, 38041, 38053, 38057, 38075, 38085, 38103, 38107,
      38113, 38119, 38133, 38143, 38151, 38165, 38185, 38193, 38205, 38213,
      38241, 38251, 38281, 38299, 38317, 38349, 38367, 38371, 38377, 38419,
      38421, 38447, 38449, 38455, 38461, 38467, 38493, 38503, 38521, 38551,
      38573, 38593, 38603, 38611, 38623, 38639, 38651, 38661, 38699, 38709,
      38713, 38733, 38755, 38805, 38815, 38819, 38821, 38825, 38833, 38875,
      38877, 38881, 38899, 38911, 38921, 38945, 38957, 38983, 39061, 39065,
      39087, 39099, 39107, 39109, 39127, 39133, 39143, 39155, 39161, 39179,
      39193, 39205, 39209, 39215, 39223, 39235, 39237, 39259, 39277, 39295,
      39305, 39313, 39323, 39353, 39359, 39361, 39371, 39381, 39395, 39397,
      39461, 39473, 39503, 39511, 39515, 39517, 39521, 39533, 39545, 39551,
      39557, 39575, 39581, 39595, 39609, 39623, 39627, 39651, 39675, 39697,
      39707, 39725, 39731, 39745, 39763, 39775, 39791, 39799, 39805, 39815,
      39819, 39827, 39863, 39869, 39889, 39915, 39929, 39935, 39957, 39967,
      39983, 39995, 39997, 40017, 40029, 40039, 40051, 40053, 40057, 40069,
      40127, 40135, 40149, 40165, 40169, 40177, 40183, 40195, 40277, 40281,
      40291, 40311, 40321, 40331, 40345, 40351, 40357, 40381, 40451, 40465,
      40471, 40481, 40487, 40505, 40519, 40533, 40537, 40543, 40547, 40553,
      40577, 40607, 40611, 40685, 40691, 40715, 40723, 40729, 40739, 40751,
      40777, 40783, 40807, 40859, 40877, 40883, 40885, 40909, 40921, 40951,
      40971, 40981, 40995, 40997, 41007, 41027, 41051, 41053, 41063, 41067,
      41069, 41087, 41097, 41105, 41127, 41141, 41165, 41183, 41193, 41211,
      41219, 41231, 41245, 41249, 41255, 41267, 41269, 41273, 41287, 41305,
      41327, 41339, 41345, 41375, 41393, 41413, 41423, 41441, 41487, 41501,
      41517, 41525, 41537, 41543, 41557, 41571, 41583, 41625, 41641, 41659,
      41661, 41669, 41673, 41687, 41691, 41709, 41735, 41739, 41741, 41753,
      41759, 41763, 41769, 41797, 41835, 41843, 41861, 41871, 41879, 41889,
      41907, 41921, 41933, 41941, 41987, 41989, 41993, 42001, 42067, 42073,
      42085, 42113, 42119, 42123, 42133, 42137, 42149, 42159, 42161, 42173,
      42179, 42203, 42219, 42221, 42241, 42275, 42277, 42281, 42319, 42355,
      42371, 42407, 42425, 42439, 42445, 42473, 42481, 42491, 42515, 42533,
      42543, 42551, 42557, 42577, 42593, 42611, 42641, 42651, 42653, 42695,
      42737, 42749, 42779, 42795, 42809, 42847, 42865, 42893, 42905, 42929,
      42939, 42941, 42959, 42961, 42973, 42983, 43013, 43051, 43059, 43065,
      43083, 43085, 43093, 43113, 43119, 43133, 43137, 43155, 43167, 43171,
      43177, 43191, 43215, 43229, 43233, 43243, 43275, 43283, 43289, 43301,
      43337, 43381, 43409, 43431, 43437, 43455, 43457, 43497, 43503, 43511,
      43533, 43541, 43567, 43569, 43587, 43589, 43599, 43601, 43617, 43641,
      43677, 43691, 43693, 43699, 43705, 43731, 43743, 43761, 43779, 43791,
      43805, 43829, 43833, 43847, 43875, 43901, 43905, 43915, 43929, 43963,
      43973, 43985, 43991, 43995, 44007, 44019, 44033, 44039, 44045, 44051,
      44073, 44087, 44091, 44101, 44123, 44141, 44147, 44159, 44165, 44175,
      44183, 44231, 44245, 44255, 44265, 44285, 44293, 44305, 44315, 44321,
      44363, 44365, 44399, 44451, 44463, 44489, 44509, 44519, 44523, 44537,
      44553, 44573, 44589, 44601, 44607, 44621, 44639, 44643, 44657, 44663,
      44667, 44685, 44693, 44707, 44731, 44759, 44765, 44775, 44789, 44801,
      44819, 44831, 44841, 44847, 44859, 44867, 44873, 44903, 44917, 44943,
      44957, 44971, 44993, 45011, 45027, 45047, 45053, 45071, 45083, 45101,
      45109, 45119, 45141, 45175, 45197, 45203, 45231, 45251, 45253, 45265,
      45281, 45299, 45319, 45323, 45325, 45373, 45399, 45405, 45429, 45455,
      45463, 45469, 45473, 45511, 45535, 45541, 45579, 45587, 45589, 45635,
      45641, 45647, 45685, 45695, 45705, 45723, 45749, 45761, 45791, 45801,
      45807, 45815, 45829, 45847, 45863, 45923, 45947, 45953, 45971, 45989,
      45993, 46001, 46007, 46021, 46039, 46043, 46045, 46073, 46081, 46093,
      46105, 46111, 46121, 46147, 46149, 46167, 46189, 46197, 46207, 46247,
      46271, 46297, 46319, 46327, 46345, 46365, 46387, 46399, 46407, 46419,
      46421, 46441, 46455, 46459, 46485, 46505, 46523, 46531, 46551, 46561,
      46567, 46571, 46585, 46597, 46601, 46615, 46619, 46625, 46631, 46637,
      46643, 46645, 46667, 46681, 46715, 46721, 46731, 46745, 46767, 46769,
      46801, 46823, 46827, 46855, 46879, 46885, 46917, 46935, 46939, 46955,
      46969, 46979, 46993, 46999, 47005, 47009, 47027, 47051, 47101, 47135,
      47173, 47183, 47201, 47221, 47237, 47241, 47261, 47265, 47277, 47295,
      47315, 47317, 47355, 47363, 47369, 47389, 47399, 47403, 47431, 47445,
      47449, 47461, 47479, 47501, 47535, 47547, 47555, 47561, 47569, 47585,
      47597, 47603, 47605, 47621, 47631, 47633, 47659, 47673, 47705, 47721,
      47727, 47745, 47751, 47757, 47763, 47799, 47831, 47859, 47871, 47873,
      47879, 47893, 47897, 47907, 47933, 47939, 47945, 47951, 47953, 47963,
      47975, 47989, 48017, 48053, 48063, 48075, 48077, 48101, 48105, 48137,
      48179, 48185, 48227, 48229, 48233, 48251, 48267, 48269, 48287, 48297,
      48323, 48337, 48349, 48385, 48403, 48421, 48431, 48439, 48453, 48487,
      48511, 48515, 48521, 48569, 48577, 48595, 48601, 48613, 48625, 48647,
      48661, 48675, 48681, 48695, 48727, 48731, 48737, 48747, 48767, 48771,
      48785, 48811, 48853, 48857, 48881, 48919, 48929, 48935, 48947, 48949,
      48979, 48997, 49025, 49035, 49059, 49079, 49091, 49115, 49133, 49141,
      49151, 49153, 49159, 49171, 49183, 49189, 49225, 49267, 49273, 49285,
      49297, 49303, 49309, 49319, 49337, 49355, 49365, 49379, 49403, 49425,
      49441, 49459, 49471, 49483, 49503, 49519, 49527, 49531, 49533, 49555,
      49573, 49597, 49603, 49609, 49627, 49639, 49645, 49669, 49673, 49687,
      49709, 49741, 49747, 49749, 49769, 49817, 49841, 49871, 49873, 49885,
      49909, 49921, 49933, 49945, 49957, 49967, 49981, 50007, 50011, 50017,
      50035, 50051, 50075, 50077, 50091, 50093, 50111, 50119, 50147, 50159,
      50173, 50181, 50209, 50227, 50247, 50251, 50271, 50287, 50301, 50323,
      50335, 50341, 50359, 50373, 50391, 50397, 50411, 50425, 50431, 50443,
      50453, 50479, 50481, 50505, 50523, 50549, 50553, 50569, 50587, 50593,
      50611, 50613, 50623, 50635, 50655, 50665, 50671, 50685, 50735, 50737,
      50749, 50757, 50769, 50795, 50805, 50809, 50831, 50839, 50859, 50867,
      50873, 50881, 50887, 50893, 50901, 50915, 50921, 50939, 50947, 50953,
      51009, 51027, 51033, 51043, 51063, 51097, 51103, 51113, 51139, 51159,
      51163, 51189, 51203, 51227, 51253, 51265, 51277, 51295, 51301, 51305,
      51349, 51389, 51401, 51445, 51449, 51455, 51457, 51469, 51477, 51487,
      51491, 51497, 51505, 51511, 51515, 51547, 51549, 51553, 51583, 51587,
      51599, 51627, 51655, 51659, 51661, 51673, 51749, 51753, 51759, 51779,
      51785, 51815, 51855, 51885, 51903, 51929, 51939, 51951, 51953, 51965,
      51991, 51995, 51997, 52011, 52031, 52053, 52073, 52081, 52091, 52103,
      52157, 52183, 52199, 52213, 52231, 52245, 52259, 52285, 52297, 52315,
      52333, 52351, 52355, 52357, 52379, 52385, 52391, 52397, 52403, 52417,
      52441, 52471, 52475, 52477, 52497, 52523, 52531, 52565, 52579, 52591,
      52615, 52639, 52643, 52663, 52677, 52687, 52695, 52705, 52715, 52717,
      52729, 52735, 52739, 52753, 52775, 52789, 52793, 52837, 52847, 52849,
      52895, 52901, 52923, 52931, 52933, 52937, 52945, 52951, 52979, 52991,
      53005, 53017, 53023, 53039, 53085, 53089, 53099, 53107, 53113, 53135,
      53147, 53149, 53153, 53163, 53191, 53205, 53225, 53239, 53253, 53257,
      53311, 53319, 53325, 53361, 53367, 53383, 53387, 53389, 53397, 53401,
      53411, 53425, 53445, 53455, 53457, 53463, 53473, 53497, 53515, 53541,
      53545, 53551, 53565, 53585, 53595, 53613, 53659, 53689, 53695, 53697,
      53717, 53721, 53743, 53757, 53767, 53781, 53791, 53795, 53801, 53815,
      53847, 53867, 53869, 53891, 53903, 53921, 53941, 53963, 54019, 54039,
      54055, 54081, 54091, 54105, 54111, 54121, 54135, 54139, 54145, 54163,
      54169, 54179, 54193, 54217, 54225, 54237, 54247, 54253, 54293, 54313,
      54331, 54365, 54369, 54379, 54423, 54429, 54443, 54451, 54463, 54465,
      54483, 54501, 54505, 54513, 54543, 54555, 54567, 54571, 54599, 54613,
      54617, 54627, 54653, 54675, 54711, 54723, 54753, 54759, 54771, 54773,
      54789, 54823, 54827, 54859, 54879, 54883, 54895, 54909, 54919, 54953,
      54967, 54981, 54999, 55009, 55021, 55027, 55061, 55075, 55077, 55089,
      55143, 55149, 55167, 55213, 55219, 55221, 55231, 55257, 55287, 55291,
      55309, 55315, 55369, 55383, 55405, 55433, 55439, 55451, 55463, 55467,
      55477, 55489, 55495, 55507, 55513, 55525, 55561, 55579, 55603, 55617,
      55623, 55629, 55647, 55653, 55665, 55691, 55705, 55711, 55715, 55721,
      55729, 55747, 55767, 55795, 55801, 55813, 55831, 55847, 55859, 55861,
      55871, 55897, 55933, 55947, 55955, 55961, 55971, 55985, 56003, 56029,
      56045, 56071, 56095, 56101, 56105, 56123, 56133, 56143, 56161, 56195,
      56209, 56225, 56263, 56269, 56277, 56287, 56291, 56297, 56303, 56315,
      56317, 56337, 56363, 56373, 56377, 56385, 56431, 56433, 56467, 56479,
      56495, 56529, 56535, 56539, 56565, 56601, 56617, 56625, 56645, 56663,
      56679, 56691, 56693, 56733, 56749, 56769, 56789, 56805, 56823, 56827,
      56839, 56879, 56893, 56905, 56911, 56913, 56941, 56949, 56963, 56965,
      56969, 56993, 57005, 57035, 57037, 57043, 57091, 57093, 57111, 57117,
      57121, 57139, 57177, 57187, 57193, 57199, 57201, 57253, 57275, 57289,
      57307, 57323, 57347, 57359, 57361, 57395, 57397, 57415, 57419, 57439,
      57467, 57469, 57485, 57503, 57513, 57521, 57527, 57541, 57559, 57563,
      57565, 57581, 57599, 57601, 57611, 57637, 57649, 57673, 57679, 57681,
      57693, 57703, 57707, 57727, 57779, 57811, 57817, 57839, 57863, 57867,
      57881, 57891, 57905, 57925, 57935, 57959, 57977, 57989, 57999, 58011,
      58013, 58017, 58027, 58029, 58047, 58049, 58069, 58127, 58129, 58139,
      58165, 58169, 58201, 58211, 58213, 58231, 58253, 58259, 58271, 58277,
      58287, 58295, 58307, 58331, 58355, 58367, 58399, 58417, 58441, 58459,
      58475, 58477, 58483, 58489, 58501, 58513, 58519, 58525, 58529, 58539,
      58571, 58573, 58591, 58609, 58621, 58627, 58629, 58647, 58651, 58669,
      58675, 58753, 58773, 58789, 58799, 58855, 58885, 58913, 58937, 58943,
      58951, 58963, 58985, 59015, 59067, 59069, 59095, 59101, 59115, 59125,
      59129, 59137, 59161, 59177, 59245, 59253, 59267, 59279, 59303, 59307,
      59309, 59317, 59339, 59347, 59349, 59365, 59377, 59383, 59393, 59439,
      59459, 59471, 59473, 59483, 59501, 59513, 59529, 59537, 59559, 59583,
      59585, 59595, 59597, 59603, 59643, 59645, 59651, 59663, 59681, 59687,
      59691, 59701, 59737, 59743, 59747, 59753, 59761, 59789, 59831, 59845,
      59855, 59863, 59885, 59913, 59931, 59949, 59979, 59993, 60017, 60029,
      60033, 60045, 60091, 60099, 60105, 60119, 60141, 60159, 60167, 60171,
      60185, 60195, 60201, 60219, 60229, 60247, 60253, 60263, 60267, 60275,
      60277, 60311, 60315, 60333, 60339, 60365, 60371, 60373, 60387, 60425,
      60433, 60449, 60469, 60491, 60511, 60517, 60521, 60541, 60563, 60569,
      60591, 60599, 60605, 60617, 60623, 60671, 60679, 60693, 60707, 60727,
      60745, 60765, 60769, 60779, 60823, 60833, 60843, 60851, 60871, 60877,
      60889, 60895, 60911, 60913, 60925, 60929, 60939, 60941, 60959, 60969,
      61045, 61059, 61065, 61085, 61101, 61113, 61127, 61131, 61145, 61155,
      61169, 61175, 61199, 61217, 61229, 61235, 61241, 61261, 61303, 61333,
      61343, 61361, 61371, 61409, 61415, 61419, 61427, 61429, 61433, 61447,
      61453, 61471, 61481, 61487, 61509, 61533, 61573, 61577, 61591, 61611,
      61631, 61639, 61653, 61663, 61681, 61687, 61713, 61723, 61749, 61761,
      61767, 61771, 61779, 61795, 61809, 61837, 61843, 61893, 61921, 61927,
      61939, 61941, 61951, 61975, 61981, 62023, 62029, 62037, 62041, 62063,
      62075, 62087, 62111, 62117, 62171, 62173, 62201, 62207, 62209, 62219,
      62229, 62255, 62263, 62275, 62341, 62345, 62353, 62359, 62387, 62431,
      62437, 62469, 62479, 62487, 62497, 62521, 62547, 62549, 62563, 62565,
      62569, 62587, 62603, 62617, 62627, 62641, 62653, 62659, 62671, 62707,
      62709, 62713, 62733, 62745, 62757, 62775, 62779, 62801, 62817, 62829,
      62865, 62877, 62887, 62901, 62911, 62913, 62919, 62977, 62997, 63007,
      63011, 63035, 63045, 63055, 63069, 63083, 63091, 63107, 63109, 63155,
      63157, 63193, 63215, 63227, 63265, 63277, 63295, 63309, 63315, 63337,
      63343, 63367, 63371, 63381, 63395, 63409, 63415, 63427, 63433, 63451,
      63487, 63491, 63497, 63503, 63517, 63527, 63533, 63545, 63551, 63563,
      63599, 63601, 63607, 63635, 63685, 63707, 63713, 63725, 63731, 63733,
      63751, 63765, 63779, 63803, 63805, 63823, 63825, 63859, 63865, 63877,
      63899, 63923, 63929, 63943, 63971, 63977, 63991, 64001, 64007, 64019,
      64035, 64055, 64073, 64107, 64117, 64121, 64127, 64131, 64151, 64155,
      64161, 64193, 64203, 64217, 64223, 64229, 64261, 64271, 64289, 64295,
      64309, 64333, 64341, 64351, 64361, 64369, 64385, 64397, 64419, 64425,
      64439, 64457, 64463, 64475, 64481, 64523, 64525, 64543, 64585, 64603,
      64615, 64629, 64643, 64685, 64723, 64751, 64783, 64791, 64797, 64811,
      64813, 64825, 64839, 64851, 64881, 64907, 64917, 64921, 64931, 64943,
      64945, 64963, 64989, 64993, 65003, 65029, 65069, 65075, 65077, 65089,
      65101, 65113, 65119, 65149, 65159, 65171, 65177, 65201, 65213, 65225,
      65259, 65279, 65281, 65287, 65299, 65315, 65321, 65335, 65359, 65367,
      65373, 65377, 65395, 65407, 65423, 65425, 65459, 65479, 65497, 65513,
      65519, 65533};
    return nb2_a[n];
  }
};

} // namespace qrng_tables
} // namespace detail

} // namespace random

} // namespace boost

#endif // BOOST_RANDOM_DETAIL_NIEDERREITER_BASE2_TABLE_HPP

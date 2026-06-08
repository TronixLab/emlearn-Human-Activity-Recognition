#pragma once
#include <cstring>

namespace math {
    /**
     * absoluteolute value
     */
    float absolute(float x) {
        return x >= 0 ? x : -x;
    }

    /**
     * Alias of max
     */
    float largest(float x, float y) {
        return x > y ? x : y;
    }

    /**
     * Alias of min
     */
    float least(float x, float y) {
        return x < y ? x : y;
    }

    /**
     * Square root (absoluteolute value)
     */
    float sqrt(float x) {
        return std::sqrt(math::absolute(x));
    }

    /**
     * Division (0 safe)
     */
    float divide(float n, float d) {
        return math::absolute(d) > 0.000001 ? n / d : n;
    }

    /**
     * Log(1 + absolute(x))
     */
    float log(float x) {
        return std::log(1 + math::absolute(x));
    }

    /**
     * Exp(absolute(x)) with x <= 30
     */
    float exp(float x) {
        return math::absolute(x) <= 30 ? std::exp(math::absolute(x)) : 0;
    }
}

/**
 * A regression chain for tabular data
 */
namespace tinyml4all {
    /**
 * Handle all inputs of the chain
 * (from outside and internal)
 */
class Input {
    public:
        
            float _T8dZDj__sqrtb;
        
            float _g57w6Y__sqrtg;
        
            float _wJVRtn__squarer;
        
            float _s9Bc6m__sqrtr;
        
            float _z0gS8O__expr;
        
            float _svXR0N__g;
        
            float _Y58r2K__logr;
        
            float _teBbCj__inverseg;
        
            float _brHEVt__squareb;
        
            float _ZeQyVt__cuber;
        
            float _LoyWtD__cubeb;
        
            float _Ym5Dnr__inverser;
        
            float _1tDhv9__expg;
        
            float _DDgEB8__logb;
        
            float _S0Owru__r;
        
            float _sbotll__squareg;
        
            float _ckyYBj__logg;
        
            float _0tfHFt__expb;
        
            float _38pQTL__cubeg;
        
            float _kutfua__b;
        
            float _MowXHt__inverseb;
        

        /**
         * Copy from other input
         */
        void copyFrom(Input& other) {
            
                _T8dZDj__sqrtb = other._T8dZDj__sqrtb;
            
                _g57w6Y__sqrtg = other._g57w6Y__sqrtg;
            
                _wJVRtn__squarer = other._wJVRtn__squarer;
            
                _s9Bc6m__sqrtr = other._s9Bc6m__sqrtr;
            
                _z0gS8O__expr = other._z0gS8O__expr;
            
                _svXR0N__g = other._svXR0N__g;
            
                _Y58r2K__logr = other._Y58r2K__logr;
            
                _teBbCj__inverseg = other._teBbCj__inverseg;
            
                _brHEVt__squareb = other._brHEVt__squareb;
            
                _ZeQyVt__cuber = other._ZeQyVt__cuber;
            
                _LoyWtD__cubeb = other._LoyWtD__cubeb;
            
                _Ym5Dnr__inverser = other._Ym5Dnr__inverser;
            
                _1tDhv9__expg = other._1tDhv9__expg;
            
                _DDgEB8__logb = other._DDgEB8__logb;
            
                _S0Owru__r = other._S0Owru__r;
            
                _sbotll__squareg = other._sbotll__squareg;
            
                _ckyYBj__logg = other._ckyYBj__logg;
            
                _0tfHFt__expb = other._0tfHFt__expb;
            
                _38pQTL__cubeg = other._38pQTL__cubeg;
            
                _kutfua__b = other._kutfua__b;
            
                _MowXHt__inverseb = other._MowXHt__inverseb;
            
        }
};
    /**
 * Handle all outputs
 * TODO
 */
 class Output {
    public:
        struct {
            uint8_t idx;
            uint8_t prevIdx;
            float score;
            float prevScore;
            char label[32];
            char prevLabel[32];
        } classification;
        struct {
          float value;
        } regression;

        Output() {
            classification.idx = 0;
            classification.score = 0;
        }
 };

    // processing blocks
    
    /**
 * Scale(method=minmax, offsets=[3. 2. 2.], scales=[42. 45. 47.])
 */
class _3dU7EM__scale_7926188646107 {
    public:

        void operator()(Input& input, Output& output) {
            

            
                
                    input._S0Owru__r = (input._S0Owru__r - 3.0f) * 0.023809523809523808f;
                
                    input._svXR0N__g = (input._svXR0N__g - 2.0f) * 0.022222222222222223f;
                
                    input._kutfua__b = (input._kutfua__b - 2.0f) * 0.02127659574468085f;
                
            

            
        }

        /**
         * Always ready
         */
        bool isReady() {
            return true;
        }
};
    
    class _mHYBlH__monotonic_7926188645465 {
    public:

        /**
         * Perform monotonic transformations
         */
        void operator()(Input& input, Output& output) {
            
                {
                    const float x = input._S0Owru__r;

                    
                        
                        
                            input._wJVRtn__squarer = std::pow(x, 2);
                        
                    
                        
                        
                            input._ZeQyVt__cuber = std::pow(x, 3);
                        
                    
                        
                        
                            input._s9Bc6m__sqrtr = math::sqrt(x);
                        
                    
                        
                        
                            input._Ym5Dnr__inverser = math::divide(1, x);
                        
                    
                        
                        
                            input._Y58r2K__logr = math::log(x);
                        
                    
                        
                        
                            input._z0gS8O__expr = math::exp(x);
                        
                    
                }
            
                {
                    const float x = input._svXR0N__g;

                    
                        
                        
                            input._sbotll__squareg = std::pow(x, 2);
                        
                    
                        
                        
                            input._38pQTL__cubeg = std::pow(x, 3);
                        
                    
                        
                        
                            input._g57w6Y__sqrtg = math::sqrt(x);
                        
                    
                        
                        
                            input._teBbCj__inverseg = math::divide(1, x);
                        
                    
                        
                        
                            input._ckyYBj__logg = math::log(x);
                        
                    
                        
                        
                            input._1tDhv9__expg = math::exp(x);
                        
                    
                }
            
                {
                    const float x = input._kutfua__b;

                    
                        
                        
                            input._brHEVt__squareb = std::pow(x, 2);
                        
                    
                        
                        
                            input._LoyWtD__cubeb = std::pow(x, 3);
                        
                    
                        
                        
                            input._T8dZDj__sqrtb = math::sqrt(x);
                        
                    
                        
                        
                            input._MowXHt__inverseb = math::divide(1, x);
                        
                    
                        
                        
                            input._DDgEB8__logb = math::log(x);
                        
                    
                        
                        
                            input._0tfHFt__expb = math::exp(x);
                        
                    
                }
            
        }

        /**
         * Always ready
         */
        bool isReady() {
            return true;
        }
};
    
    class _Ewv9Jb__select_7926188609865 {
    public:

        /**
         * Perform feature selection
         */
        void operator()(Input& input, Output& output) {
            // nothing to do, feature selection is only needed in Python
        }

        /**
         * Always ready
         */
        bool isReady() {
            return true;
        }
};
    
    /**
 * DecisionTreeRegressor(max_depth=10, max_features=1.0, min_samples_leaf=5,
                      random_state=638275085)
 */
class _oCxhDv__decisiontree_7926188633483 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._0tfHFt__expb < 1.1858254075050354f) {
        
    if (input._sbotll__squareg < 0.0032098765950649977f) {
        
    if (input._sbotll__squareg < 0.0012345678987912834f) {
        
    output.regression.value = 27.71875f;
    return;

    }
    else {
        
    output.regression.value = 50.5f;
    return;

    }

    }
    else {
        
    if (input._g57w6Y__sqrtg < 0.278170645236969f) {
        
    output.regression.value = 69.875f;
    return;

    }
    else {
        
    output.regression.value = 104.33333333333333f;
    return;

    }

    }

    }
    else {
        
    if (input._g57w6Y__sqrtg < 0.6054605543613434f) {
        
    if (input._kutfua__b < 0.24468085169792175f) {
        
    output.regression.value = 136.625f;
    return;

    }
    else {
        
    output.regression.value = 164.27272727272728f;
    return;

    }

    }
    else {
        
    if (input._0tfHFt__expb < 1.9136123657226562f) {
        
    if (input._g57w6Y__sqrtg < 0.7226085364818573f) {
        
    output.regression.value = 214.71428571428572f;
    return;

    }
    else {
        
    output.regression.value = 260.6f;
    return;

    }

    }
    else {
        
    if (input._kutfua__b < 0.7978723645210266f) {
        
    output.regression.value = 195.0f;
    return;

    }
    else {
        
    output.regression.value = 226.07142857142858f;
    return;

    }

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeRegressor(max_depth=10, max_features=1.0, min_samples_leaf=5,
                      random_state=2117668905)
 */
class _uhsXyT__decisiontree_7926188633897 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._s9Bc6m__sqrtr < 0.37664054334163666f) {
        
    if (input._kutfua__b < 0.09574468061327934f) {
        
    if (input._g57w6Y__sqrtg < 0.17994485795497894f) {
        
    output.regression.value = 26.875f;
    return;

    }
    else {
        
    output.regression.value = 42.75f;
    return;

    }

    }
    else {
        
    if (input._kutfua__b < 0.11702127754688263f) {
        
    output.regression.value = 69.4f;
    return;

    }
    else {
        
    output.regression.value = 99.5f;
    return;

    }

    }

    }
    else {
        
    if (input._sbotll__squareg < 0.11876543238759041f) {
        
    if (input._kutfua__b < 0.24468085169792175f) {
        
    output.regression.value = 142.5f;
    return;

    }
    else {
        
    output.regression.value = 174.6153846153846f;
    return;

    }

    }
    else {
        
    if (input._sbotll__squareg < 0.3212345689535141f) {
        
    if (input._kutfua__b < 0.478723406791687f) {
        
    output.regression.value = 219.3f;
    return;

    }
    else {
        
    output.regression.value = 181.1f;
    return;

    }

    }
    else {
        
    if (input._0tfHFt__expb < 1.9136123657226562f) {
        
    output.regression.value = 277.42857142857144f;
    return;

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.8521394729614258f) {
        
    output.regression.value = 194.75f;
    return;

    }
    else {
        
    if (input._kutfua__b < 0.8510638475418091f) {
        
    output.regression.value = 229.88888888888889f;
    return;

    }
    else {
        
    output.regression.value = 225.77777777777777f;
    return;

    }

    }

    }

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeRegressor(max_depth=10, max_features=1.0, min_samples_leaf=5,
                      random_state=2080959841)
 */
class _jqSzfI__decisiontree_7926188525275 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._s9Bc6m__sqrtr < 0.3931063860654831f) {
        
    if (input._g57w6Y__sqrtg < 0.2345087006688118f) {
        
    if (input._s9Bc6m__sqrtr < 0.07715167850255966f) {
        
    output.regression.value = 25.681818181818183f;
    return;

    }
    else {
        
    output.regression.value = 46.875f;
    return;

    }

    }
    else {
        
    if (input._g57w6Y__sqrtg < 0.278170645236969f) {
        
    output.regression.value = 70.0f;
    return;

    }
    else {
        
    output.regression.value = 77.57142857142857f;
    return;

    }

    }

    }
    else {
        
    if (input._g57w6Y__sqrtg < 0.5476286113262177f) {
        
    if (input._0tfHFt__expb < 1.3047533631324768f) {
        
    output.regression.value = 144.8f;
    return;

    }
    else {
        
    output.regression.value = 170.88888888888889f;
    return;

    }

    }
    else {
        
    if (input._sbotll__squareg < 0.3212345689535141f) {
        
    if (input._0tfHFt__expb < 1.6141040325164795f) {
        
    output.regression.value = 209.53846153846155f;
    return;

    }
    else {
        
    output.regression.value = 189.25f;
    return;

    }

    }
    else {
        
    if (input._kutfua__b < 0.6702127456665039f) {
        
    output.regression.value = 266.22222222222223f;
    return;

    }
    else {
        
    if (input._g57w6Y__sqrtg < 0.9128506481647491f) {
        
    output.regression.value = 205.58823529411765f;
    return;

    }
    else {
        
    output.regression.value = 251.57142857142858f;
    return;

    }

    }

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeRegressor(max_depth=10, max_features=1.0, min_samples_leaf=5,
                      random_state=663529231)
 */
class _7O8xWI__decisiontree_7926188524645 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._0tfHFt__expb < 1.2240735292434692f) {
        
    if (input._s9Bc6m__sqrtr < 0.24273956567049026f) {
        
    if (input._g57w6Y__sqrtg < 0.07453560084104538f) {
        
    output.regression.value = 25.714285714285715f;
    return;

    }
    else {
        
    output.regression.value = 44.93333333333333f;
    return;

    }

    }
    else {
        
    if (input._sbotll__squareg < 0.010123456828296185f) {
        
    output.regression.value = 83.27272727272727f;
    return;

    }
    else {
        
    output.regression.value = 106.33333333333333f;
    return;

    }

    }

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.6267112195491791f) {
        
    if (input._sbotll__squareg < 0.07728395238518715f) {
        
    output.regression.value = 148.8f;
    return;

    }
    else {
        
    output.regression.value = 155.0f;
    return;

    }

    }
    else {
        
    if (input._sbotll__squareg < 0.3212345689535141f) {
        
    if (input._kutfua__b < 0.5f) {
        
    output.regression.value = 219.75f;
    return;

    }
    else {
        
    output.regression.value = 184.0f;
    return;

    }

    }
    else {
        
    if (input._g57w6Y__sqrtg < 0.8232449591159821f) {
        
    output.regression.value = 264.22222222222223f;
    return;

    }
    else {
        
    output.regression.value = 223.06666666666666f;
    return;

    }

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeRegressor(max_depth=10, max_features=1.0, min_samples_leaf=5,
                      random_state=349735759)
 */
class _MTmgyK__decisiontree_7926188524567 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._0tfHFt__expb < 1.277864158153534f) {
        
    if (input._0tfHFt__expb < 1.100540280342102f) {
        
    if (input._sbotll__squareg < 0.0002469135797582567f) {
        
    output.regression.value = 25.958333333333332f;
    return;

    }
    else {
        
    output.regression.value = 40.92857142857143f;
    return;

    }

    }
    else {
        
    if (input._kutfua__b < 0.11702127754688263f) {
        
    output.regression.value = 73.7f;
    return;

    }
    else {
        
    if (input._g57w6Y__sqrtg < 0.37977683544158936f) {
        
    output.regression.value = 101.07692307692308f;
    return;

    }
    else {
        
    output.regression.value = 116.0f;
    return;

    }

    }

    }

    }
    else {
        
    if (input._g57w6Y__sqrtg < 0.7740644812583923f) {
        
    if (input._sbotll__squareg < 0.11876543238759041f) {
        
    output.regression.value = 159.33333333333334f;
    return;

    }
    else {
        
    output.regression.value = 192.72727272727272f;
    return;

    }

    }
    else {
        
    if (input._0tfHFt__expb < 2.083604097366333f) {
        
    output.regression.value = 242.36363636363637f;
    return;

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.9063031673431396f) {
        
    output.regression.value = 208.14285714285714f;
    return;

    }
    else {
        
    output.regression.value = 224.11111111111111f;
    return;

    }

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeRegressor(max_depth=10, max_features=1.0, min_samples_leaf=5,
                      random_state=1067537386)
 */
class _JC2VBK__decisiontree_7926188525173 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._kutfua__b < 0.1702127680182457f) {
        
    if (input._kutfua__b < 0.09574468061327934f) {
        
    if (input._sbotll__squareg < 0.0002469135797582567f) {
        
    output.regression.value = 26.4f;
    return;

    }
    else {
        
    if (input._kutfua__b < 0.07446808367967606f) {
        
    output.regression.value = 42.0f;
    return;

    }
    else {
        
    output.regression.value = 48.2f;
    return;

    }

    }

    }
    else {
        
    if (input._kutfua__b < 0.11702127754688263f) {
        
    output.regression.value = 71.3f;
    return;

    }
    else {
        
    output.regression.value = 94.66666666666667f;
    return;

    }

    }

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.6267112195491791f) {
        
    if (input._sbotll__squareg < 0.044691357761621475f) {
        
    output.regression.value = 141.57142857142858f;
    return;

    }
    else {
        
    output.regression.value = 160.31578947368422f;
    return;

    }

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.9193455278873444f) {
        
    if (input._kutfua__b < 0.521276593208313f) {
        
    output.regression.value = 231.44444444444446f;
    return;

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.8521394729614258f) {
        
    output.regression.value = 190.5f;
    return;

    }
    else {
        
    output.regression.value = 222.33333333333334f;
    return;

    }

    }

    }
    else {
        
    output.regression.value = 240.6f;
    return;

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeRegressor(max_depth=10, max_features=1.0, min_samples_leaf=5,
                      random_state=677464280)
 */
class _5Npl4G__decisiontree_7926188525419 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._kutfua__b < 0.22340425848960876f) {
        
    if (input._g57w6Y__sqrtg < 0.2345087006688118f) {
        
    if (input._s9Bc6m__sqrtr < 0.07715167850255966f) {
        
    output.regression.value = 25.653846153846153f;
    return;

    }
    else {
        
    output.regression.value = 42.92857142857143f;
    return;

    }

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.3931063860654831f) {
        
    if (input._kutfua__b < 0.11702127754688263f) {
        
    output.regression.value = 72.45454545454545f;
    return;

    }
    else {
        
    output.regression.value = 96.71428571428571f;
    return;

    }

    }
    else {
        
    output.regression.value = 124.9f;
    return;

    }

    }

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.6267112195491791f) {
        
    if (input._s9Bc6m__sqrtr < 0.5454355478286743f) {
        
    output.regression.value = 158.42857142857142f;
    return;

    }
    else {
        
    output.regression.value = 188.22222222222223f;
    return;

    }

    }
    else {
        
    if (input._sbotll__squareg < 0.334320992231369f) {
        
    output.regression.value = 211.6153846153846f;
    return;

    }
    else {
        
    if (input._kutfua__b < 0.6914893388748169f) {
        
    output.regression.value = 265.85714285714283f;
    return;

    }
    else {
        
    if (input._g57w6Y__sqrtg < 0.8943409025669098f) {
        
    output.regression.value = 215.88888888888889f;
    return;

    }
    else {
        
    output.regression.value = 223.0f;
    return;

    }

    }

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeRegressor(max_depth=10, max_features=1.0, min_samples_leaf=5,
                      random_state=1221547712)
 */
class _lWwV8s__decisiontree_7926188525203 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._0tfHFt__expb < 1.2639843225479126f) {
        
    if (input._kutfua__b < 0.11702127754688263f) {
        
    if (input._s9Bc6m__sqrtr < 0.07715167850255966f) {
        
    output.regression.value = 25.84f;
    return;

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.24273956567049026f) {
        
    output.regression.value = 47.666666666666664f;
    return;

    }
    else {
        
    output.regression.value = 69.72727272727273f;
    return;

    }

    }

    }
    else {
        
    output.regression.value = 113.15384615384616f;
    return;

    }

    }
    else {
        
    if (input._g57w6Y__sqrtg < 0.7527364492416382f) {
        
    if (input._kutfua__b < 0.3297872245311737f) {
        
    output.regression.value = 181.54545454545453f;
    return;

    }
    else {
        
    if (input._kutfua__b < 0.478723406791687f) {
        
    output.regression.value = 206.8181818181818f;
    return;

    }
    else {
        
    output.regression.value = 187.44444444444446f;
    return;

    }

    }

    }
    else {
        
    if (input._kutfua__b < 0.6489361524581909f) {
        
    output.regression.value = 280.6666666666667f;
    return;

    }
    else {
        
    if (input._sbotll__squareg < 0.5217283964157104f) {
        
    output.regression.value = 188.6f;
    return;

    }
    else {
        
    if (input._0tfHFt__expb < 2.3174840211868286f) {
        
    output.regression.value = 240.22222222222223f;
    return;

    }
    else {
        
    output.regression.value = 222.22222222222223f;
    return;

    }

    }

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeRegressor(max_depth=10, max_features=1.0, min_samples_leaf=5,
                      random_state=705874705)
 */
class _i22b48__decisiontree_7926188525206 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._0tfHFt__expb < 1.2503966689109802f) {
        
    if (input._s9Bc6m__sqrtr < 0.24273956567049026f) {
        
    if (input._s9Bc6m__sqrtr < 0.07715167850255966f) {
        
    output.regression.value = 25.956521739130434f;
    return;

    }
    else {
        
    if (input._0tfHFt__expb < 1.077371895313263f) {
        
    output.regression.value = 39.0f;
    return;

    }
    else {
        
    output.regression.value = 52.4f;
    return;

    }

    }

    }
    else {
        
    if (input._0tfHFt__expb < 1.148382544517517f) {
        
    output.regression.value = 82.14285714285714f;
    return;

    }
    else {
        
    output.regression.value = 115.25f;
    return;

    }

    }

    }
    else {
        
    if (input._sbotll__squareg < 0.1523456797003746f) {
        
    output.regression.value = 169.0f;
    return;

    }
    else {
        
    if (input._kutfua__b < 0.6489361524581909f) {
        
    if (input._s9Bc6m__sqrtr < 0.7398378849029541f) {
        
    output.regression.value = 213.88235294117646f;
    return;

    }
    else {
        
    output.regression.value = 277.0f;
    return;

    }

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.9193455278873444f) {
        
    output.regression.value = 200.94444444444446f;
    return;

    }
    else {
        
    output.regression.value = 248.14285714285714f;
    return;

    }

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeRegressor(max_depth=10, max_features=1.0, min_samples_leaf=5,
                      random_state=1777778571)
 */
class _ei7Wsu__decisiontree_7926188525191 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._s9Bc6m__sqrtr < 0.46219290792942047f) {
        
    if (input._s9Bc6m__sqrtr < 0.24273956567049026f) {
        
    if (input._0tfHFt__expb < 1.0324880480766296f) {
        
    output.regression.value = 25.625f;
    return;

    }
    else {
        
    output.regression.value = 44.166666666666664f;
    return;

    }

    }
    else {
        
    if (input._0tfHFt__expb < 1.1242069602012634f) {
        
    output.regression.value = 69.9f;
    return;

    }
    else {
        
    output.regression.value = 99.0f;
    return;

    }

    }

    }
    else {
        
    if (input._g57w6Y__sqrtg < 0.6054605543613434f) {
        
    if (input._s9Bc6m__sqrtr < 0.5454355478286743f) {
        
    output.regression.value = 171.42857142857142f;
    return;

    }
    else {
        
    output.regression.value = 152.42857142857142f;
    return;

    }

    }
    else {
        
    if (input._sbotll__squareg < 0.3212345689535141f) {
        
    if (input._0tfHFt__expb < 1.6842716336250305f) {
        
    output.regression.value = 224.58333333333334f;
    return;

    }
    else {
        
    output.regression.value = 184.22222222222223f;
    return;

    }

    }
    else {
        
    if (input._kutfua__b < 0.6489361524581909f) {
        
    output.regression.value = 281.77777777777777f;
    return;

    }
    else {
        
    if (input._g57w6Y__sqrtg < 0.9603066146373749f) {
        
    output.regression.value = 216.9f;
    return;

    }
    else {
        
    output.regression.value = 235.9f;
    return;

    }

    }

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeRegressor(max_depth=10, max_features=1.0, min_samples_leaf=5,
                      random_state=131500071)
 */
class _zgZojE__decisiontree_7926188525029 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._kutfua__b < 0.22340425848960876f) {
        
    if (input._s9Bc6m__sqrtr < 0.24273956567049026f) {
        
    if (input._sbotll__squareg < 0.0002469135797582567f) {
        
    output.regression.value = 26.541666666666668f;
    return;

    }
    else {
        
    output.regression.value = 46.642857142857146f;
    return;

    }

    }
    else {
        
    if (input._sbotll__squareg < 0.010123456828296185f) {
        
    output.regression.value = 73.75f;
    return;

    }
    else {
        
    output.regression.value = 114.76923076923077f;
    return;

    }

    }

    }
    else {
        
    if (input._g57w6Y__sqrtg < 0.658226490020752f) {
        
    if (input._sbotll__squareg < 0.09111111238598824f) {
        
    output.regression.value = 160.7f;
    return;

    }
    else {
        
    output.regression.value = 183.22222222222223f;
    return;

    }

    }
    else {
        
    if (input._sbotll__squareg < 0.3212345689535141f) {
        
    output.regression.value = 225.13333333333333f;
    return;

    }
    else {
        
    if (input._0tfHFt__expb < 1.9547637701034546f) {
        
    output.regression.value = 260.77777777777777f;
    return;

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.9193455278873444f) {
        
    output.regression.value = 215.28571428571428f;
    return;

    }
    else {
        
    output.regression.value = 243.9090909090909f;
    return;

    }

    }

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeRegressor(max_depth=10, max_features=1.0, min_samples_leaf=5,
                      random_state=1712999742)
 */
class _1N1fl5__decisiontree_7926188525323 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._g57w6Y__sqrtg < 0.37977683544158936f) {
        
    if (input._s9Bc6m__sqrtr < 0.24273956567049026f) {
        
    if (input._0tfHFt__expb < 1.0324880480766296f) {
        
    output.regression.value = 25.346153846153847f;
    return;

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.1862606257200241f) {
        
    output.regression.value = 46.8f;
    return;

    }
    else {
        
    output.regression.value = 45.4f;
    return;

    }

    }

    }
    else {
        
    if (input._0tfHFt__expb < 1.1242069602012634f) {
        
    output.regression.value = 71.3f;
    return;

    }
    else {
        
    output.regression.value = 103.0f;
    return;

    }

    }

    }
    else {
        
    if (input._kutfua__b < 0.3510638177394867f) {
        
    if (input._0tfHFt__expb < 1.3328115344047546f) {
        
    output.regression.value = 139.36363636363637f;
    return;

    }
    else {
        
    output.regression.value = 152.5f;
    return;

    }

    }
    else {
        
    if (input._sbotll__squareg < 0.3212345689535141f) {
        
    if (input._s9Bc6m__sqrtr < 0.663623183965683f) {
        
    output.regression.value = 221.66666666666666f;
    return;

    }
    else {
        
    output.regression.value = 204.42857142857142f;
    return;

    }

    }
    else {
        
    if (input._0tfHFt__expb < 1.9556487202644348f) {
        
    output.regression.value = 283.8888888888889f;
    return;

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.9193455278873444f) {
        
    output.regression.value = 207.57142857142858f;
    return;

    }
    else {
        
    output.regression.value = 243.54545454545453f;
    return;

    }

    }

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeRegressor(max_depth=10, max_features=1.0, min_samples_leaf=5,
                      random_state=423073033)
 */
class _QV7wzi__decisiontree_7926188525137 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._kutfua__b < 0.22340425848960876f) {
        
    if (input._0tfHFt__expb < 1.100540280342102f) {
        
    if (input._s9Bc6m__sqrtr < 0.07715167850255966f) {
        
    output.regression.value = 26.28f;
    return;

    }
    else {
        
    if (input._kutfua__b < 0.07446808367967606f) {
        
    output.regression.value = 43.888888888888886f;
    return;

    }
    else {
        
    output.regression.value = 54.142857142857146f;
    return;

    }

    }

    }
    else {
        
    if (input._sbotll__squareg < 0.010123456828296185f) {
        
    output.regression.value = 85.15384615384616f;
    return;

    }
    else {
        
    output.regression.value = 110.27272727272727f;
    return;

    }

    }

    }
    else {
        
    if (input._sbotll__squareg < 0.2501234635710716f) {
        
    if (input._g57w6Y__sqrtg < 0.5770290791988373f) {
        
    output.regression.value = 172.0f;
    return;

    }
    else {
        
    if (input._kutfua__b < 0.42553192377090454f) {
        
    output.regression.value = 210.66666666666666f;
    return;

    }
    else {
        
    output.regression.value = 179.85714285714286f;
    return;

    }

    }

    }
    else {
        
    if (input._g57w6Y__sqrtg < 0.7527364492416382f) {
        
    output.regression.value = 208.6f;
    return;

    }
    else {
        
    if (input._kutfua__b < 0.6489361524581909f) {
        
    output.regression.value = 274.8f;
    return;

    }
    else {
        
    if (input._0tfHFt__expb < 2.2686967849731445f) {
        
    output.regression.value = 190.25f;
    return;

    }
    else {
        
    output.regression.value = 230.3125f;
    return;

    }

    }

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeRegressor(max_depth=10, max_features=1.0, min_samples_leaf=5,
                      random_state=1332112200)
 */
class _46flJN__decisiontree_7926188524663 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._0tfHFt__expb < 1.2503966689109802f) {
        
    if (input._s9Bc6m__sqrtr < 0.24273956567049026f) {
        
    if (input._0tfHFt__expb < 1.0324880480766296f) {
        
    output.regression.value = 25.5f;
    return;

    }
    else {
        
    if (input._kutfua__b < 0.07446808367967606f) {
        
    output.regression.value = 40.0f;
    return;

    }
    else {
        
    output.regression.value = 54.375f;
    return;

    }

    }

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.36149862408638f) {
        
    output.regression.value = 89.8f;
    return;

    }
    else {
        
    output.regression.value = 113.9f;
    return;

    }

    }

    }
    else {
        
    if (input._sbotll__squareg < 0.2728395164012909f) {
        
    if (input._sbotll__squareg < 0.11876543238759041f) {
        
    output.regression.value = 153.33333333333334f;
    return;

    }
    else {
        
    if (input._0tfHFt__expb < 1.5307506918907166f) {
        
    output.regression.value = 215.88888888888889f;
    return;

    }
    else {
        
    output.regression.value = 186.77777777777777f;
    return;

    }

    }

    }
    else {
        
    if (input._kutfua__b < 0.6595744490623474f) {
        
    output.regression.value = 262.2f;
    return;

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.9193455278873444f) {
        
    output.regression.value = 204.0f;
    return;

    }
    else {
        
    output.regression.value = 239.22222222222223f;
    return;

    }

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeRegressor(max_depth=10, max_features=1.0, min_samples_leaf=5,
                      random_state=1186061505)
 */
class _hPztGt__decisiontree_7926188525455 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._sbotll__squareg < 0.044691357761621475f) {
        
    if (input._kutfua__b < 0.11702127754688263f) {
        
    if (input._0tfHFt__expb < 1.077371895313263f) {
        
    if (input._g57w6Y__sqrtg < 0.07453560084104538f) {
        
    output.regression.value = 25.470588235294116f;
    return;

    }
    else {
        
    output.regression.value = 41.666666666666664f;
    return;

    }

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.24273956567049026f) {
        
    output.regression.value = 51.75f;
    return;

    }
    else {
        
    output.regression.value = 67.5f;
    return;

    }

    }

    }
    else {
        
    if (input._kutfua__b < 0.1702127680182457f) {
        
    output.regression.value = 96.44444444444444f;
    return;

    }
    else {
        
    output.regression.value = 115.0f;
    return;

    }

    }

    }
    else {
        
    if (input._g57w6Y__sqrtg < 0.6230355501174927f) {
        
    if (input._0tfHFt__expb < 1.3907509446144104f) {
        
    output.regression.value = 173.71428571428572f;
    return;

    }
    else {
        
    output.regression.value = 158.625f;
    return;

    }

    }
    else {
        
    if (input._0tfHFt__expb < 1.8936840891838074f) {
        
    if (input._s9Bc6m__sqrtr < 0.7398378849029541f) {
        
    output.regression.value = 217.63636363636363f;
    return;

    }
    else {
        
    output.regression.value = 251.1f;
    return;

    }

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.9193455278873444f) {
        
    output.regression.value = 206.3846153846154f;
    return;

    }
    else {
        
    output.regression.value = 234.0909090909091f;
    return;

    }

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeRegressor(max_depth=10, max_features=1.0, min_samples_leaf=5,
                      random_state=1155691840)
 */
class _d8yqI1__decisiontree_7926188525407 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._s9Bc6m__sqrtr < 0.37664054334163666f) {
        
    if (input._g57w6Y__sqrtg < 0.2345087006688118f) {
        
    if (input._g57w6Y__sqrtg < 0.07453560084104538f) {
        
    output.regression.value = 25.458333333333332f;
    return;

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.1862606257200241f) {
        
    output.regression.value = 40.90909090909091f;
    return;

    }
    else {
        
    output.regression.value = 49.4f;
    return;

    }

    }

    }
    else {
        
    if (input._sbotll__squareg < 0.006172839552164078f) {
        
    output.regression.value = 76.66666666666667f;
    return;

    }
    else {
        
    output.regression.value = 88.14285714285714f;
    return;

    }

    }

    }
    else {
        
    if (input._g57w6Y__sqrtg < 0.5868175327777863f) {
        
    if (input._0tfHFt__expb < 1.3328115344047546f) {
        
    output.regression.value = 144.11111111111111f;
    return;

    }
    else {
        
    output.regression.value = 168.0909090909091f;
    return;

    }

    }
    else {
        
    if (input._0tfHFt__expb < 1.9136123657226562f) {
        
    if (input._0tfHFt__expb < 1.7582851648330688f) {
        
    if (input._kutfua__b < 0.457446813583374f) {
        
    output.regression.value = 227.6f;
    return;

    }
    else {
        
    output.regression.value = 202.375f;
    return;

    }

    }
    else {
        
    output.regression.value = 259.1111111111111f;
    return;

    }

    }
    else {
        
    if (input._sbotll__squareg < 0.6404938399791718f) {
        
    output.regression.value = 193.0f;
    return;

    }
    else {
        
    output.regression.value = 222.0909090909091f;
    return;

    }

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeRegressor(max_depth=10, max_features=1.0, min_samples_leaf=5,
                      random_state=1358238036)
 */
class _vLAoiP__decisiontree_7926188525284 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._kutfua__b < 0.22340425848960876f) {
        
    if (input._s9Bc6m__sqrtr < 0.24273956567049026f) {
        
    if (input._kutfua__b < 0.031914892606437206f) {
        
    output.regression.value = 25.56f;
    return;

    }
    else {
        
    output.regression.value = 50.375f;
    return;

    }

    }
    else {
        
    if (input._sbotll__squareg < 0.010123456828296185f) {
        
    output.regression.value = 85.45454545454545f;
    return;

    }
    else {
        
    output.regression.value = 116.25f;
    return;

    }

    }

    }
    else {
        
    if (input._sbotll__squareg < 0.20765431970357895f) {
        
    if (input._s9Bc6m__sqrtr < 0.5454355478286743f) {
        
    output.regression.value = 154.0f;
    return;

    }
    else {
        
    output.regression.value = 183.6f;
    return;

    }

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.9193455278873444f) {
        
    if (input._0tfHFt__expb < 1.9136123657226562f) {
        
    if (input._0tfHFt__expb < 1.7582851648330688f) {
        
    output.regression.value = 243.875f;
    return;

    }
    else {
        
    output.regression.value = 230.875f;
    return;

    }

    }
    else {
        
    output.regression.value = 200.15384615384616f;
    return;

    }

    }
    else {
        
    output.regression.value = 241.25f;
    return;

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeRegressor(max_depth=10, max_features=1.0, min_samples_leaf=5,
                      random_state=534581027)
 */
class _PB27mT__decisiontree_7926188525509 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._kutfua__b < 0.23404255509376526f) {
        
    if (input._s9Bc6m__sqrtr < 0.24273956567049026f) {
        
    if (input._s9Bc6m__sqrtr < 0.07715167850255966f) {
        
    output.regression.value = 25.91304347826087f;
    return;

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.1862606257200241f) {
        
    output.regression.value = 38.285714285714285f;
    return;

    }
    else {
        
    output.regression.value = 48.142857142857146f;
    return;

    }

    }

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.28793397545814514f) {
        
    output.regression.value = 77.0f;
    return;

    }
    else {
        
    if (input._kutfua__b < 0.1702127680182457f) {
        
    output.regression.value = 99.64285714285714f;
    return;

    }
    else {
        
    output.regression.value = 108.25f;
    return;

    }

    }

    }

    }
    else {
        
    if (input._g57w6Y__sqrtg < 0.7527364492416382f) {
        
    if (input._0tfHFt__expb < 1.6141040325164795f) {
        
    output.regression.value = 197.93333333333334f;
    return;

    }
    else {
        
    output.regression.value = 181.1f;
    return;

    }

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.8521394729614258f) {
        
    output.regression.value = 218.0f;
    return;

    }
    else {
        
    if (input._g57w6Y__sqrtg < 0.971808522939682f) {
        
    output.regression.value = 237.73333333333332f;
    return;

    }
    else {
        
    output.regression.value = 230.66666666666666f;
    return;

    }

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeRegressor(max_depth=10, max_features=1.0, min_samples_leaf=5,
                      random_state=113755485)
 */
class _r7UKg1__decisiontree_7926188525536 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._0tfHFt__expb < 1.2503966689109802f) {
        
    if (input._s9Bc6m__sqrtr < 0.24273956567049026f) {
        
    if (input._s9Bc6m__sqrtr < 0.1862606257200241f) {
        
    if (input._g57w6Y__sqrtg < 0.07453560084104538f) {
        
    output.regression.value = 25.51851851851852f;
    return;

    }
    else {
        
    output.regression.value = 38.0f;
    return;

    }

    }
    else {
        
    output.regression.value = 54.142857142857146f;
    return;

    }

    }
    else {
        
    if (input._0tfHFt__expb < 1.1242069602012634f) {
        
    output.regression.value = 73.57142857142857f;
    return;

    }
    else {
        
    output.regression.value = 102.13333333333334f;
    return;

    }

    }

    }
    else {
        
    if (input._g57w6Y__sqrtg < 0.6054605543613434f) {
        
    if (input._s9Bc6m__sqrtr < 0.5454355478286743f) {
        
    output.regression.value = 155.0f;
    return;

    }
    else {
        
    output.regression.value = 164.25f;
    return;

    }

    }
    else {
        
    if (input._0tfHFt__expb < 1.9344069957733154f) {
        
    if (input._g57w6Y__sqrtg < 0.767356812953949f) {
        
    output.regression.value = 233.7058823529412f;
    return;

    }
    else {
        
    output.regression.value = 286.14285714285717f;
    return;

    }

    }
    else {
        
    if (input._sbotll__squareg < 0.8506172895431519f) {
        
    output.regression.value = 202.1f;
    return;

    }
    else {
        
    output.regression.value = 233.27272727272728f;
    return;

    }

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeRegressor(max_depth=10, max_features=1.0, min_samples_leaf=5,
                      random_state=1607060666)
 */
class _jHwYBv__decisiontree_7926188525242 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._kutfua__b < 0.20212766528129578f) {
        
    if (input._sbotll__squareg < 0.0032098765950649977f) {
        
    if (input._s9Bc6m__sqrtr < 0.07715167850255966f) {
        
    output.regression.value = 26.666666666666668f;
    return;

    }
    else {
        
    if (input._kutfua__b < 0.07446808367967606f) {
        
    output.regression.value = 44.333333333333336f;
    return;

    }
    else {
        
    output.regression.value = 52.8f;
    return;

    }

    }

    }
    else {
        
    if (input._0tfHFt__expb < 1.1242069602012634f) {
        
    output.regression.value = 77.66666666666667f;
    return;

    }
    else {
        
    output.regression.value = 96.45454545454545f;
    return;

    }

    }

    }
    else {
        
    if (input._sbotll__squareg < 0.2501234635710716f) {
        
    if (input._g57w6Y__sqrtg < 0.5269408226013184f) {
        
    output.regression.value = 154.25f;
    return;

    }
    else {
        
    if (input._kutfua__b < 0.42553192377090454f) {
        
    output.regression.value = 199.0f;
    return;

    }
    else {
        
    output.regression.value = 192.5f;
    return;

    }

    }

    }
    else {
        
    if (input._0tfHFt__expb < 1.9344069957733154f) {
        
    output.regression.value = 257.1818181818182f;
    return;

    }
    else {
        
    if (input._s9Bc6m__sqrtr < 0.8930703401565552f) {
        
    output.regression.value = 206.8f;
    return;

    }
    else {
        
    output.regression.value = 236.66666666666666f;
    return;

    }

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};

class _cCRnmp__randomforest_7926188609979 {
    public:
        void operator()(Input& input, Output& output) {
            Output treeOutput;

            output.regression.value = 0;

            // iterate over trees
            
                tree1(input, treeOutput);
                output.regression.value += treeOutput.regression.value;
            
                tree2(input, treeOutput);
                output.regression.value += treeOutput.regression.value;
            
                tree3(input, treeOutput);
                output.regression.value += treeOutput.regression.value;
            
                tree4(input, treeOutput);
                output.regression.value += treeOutput.regression.value;
            
                tree5(input, treeOutput);
                output.regression.value += treeOutput.regression.value;
            
                tree6(input, treeOutput);
                output.regression.value += treeOutput.regression.value;
            
                tree7(input, treeOutput);
                output.regression.value += treeOutput.regression.value;
            
                tree8(input, treeOutput);
                output.regression.value += treeOutput.regression.value;
            
                tree9(input, treeOutput);
                output.regression.value += treeOutput.regression.value;
            
                tree10(input, treeOutput);
                output.regression.value += treeOutput.regression.value;
            
                tree11(input, treeOutput);
                output.regression.value += treeOutput.regression.value;
            
                tree12(input, treeOutput);
                output.regression.value += treeOutput.regression.value;
            
                tree13(input, treeOutput);
                output.regression.value += treeOutput.regression.value;
            
                tree14(input, treeOutput);
                output.regression.value += treeOutput.regression.value;
            
                tree15(input, treeOutput);
                output.regression.value += treeOutput.regression.value;
            
                tree16(input, treeOutput);
                output.regression.value += treeOutput.regression.value;
            
                tree17(input, treeOutput);
                output.regression.value += treeOutput.regression.value;
            
                tree18(input, treeOutput);
                output.regression.value += treeOutput.regression.value;
            
                tree19(input, treeOutput);
                output.regression.value += treeOutput.regression.value;
            
                tree20(input, treeOutput);
                output.regression.value += treeOutput.regression.value;
            

            output.regression.value /= 20;
        }

        /**
         * Always ready
         */
        bool isReady() {
            return true;
        }

    protected:
        
            _oCxhDv__decisiontree_7926188633483 tree1;
        
            _uhsXyT__decisiontree_7926188633897 tree2;
        
            _jqSzfI__decisiontree_7926188525275 tree3;
        
            _7O8xWI__decisiontree_7926188524645 tree4;
        
            _MTmgyK__decisiontree_7926188524567 tree5;
        
            _JC2VBK__decisiontree_7926188525173 tree6;
        
            _5Npl4G__decisiontree_7926188525419 tree7;
        
            _lWwV8s__decisiontree_7926188525203 tree8;
        
            _i22b48__decisiontree_7926188525206 tree9;
        
            _ei7Wsu__decisiontree_7926188525191 tree10;
        
            _zgZojE__decisiontree_7926188525029 tree11;
        
            _1N1fl5__decisiontree_7926188525323 tree12;
        
            _QV7wzi__decisiontree_7926188525137 tree13;
        
            _46flJN__decisiontree_7926188524663 tree14;
        
            _hPztGt__decisiontree_7926188525455 tree15;
        
            _d8yqI1__decisiontree_7926188525407 tree16;
        
            _vLAoiP__decisiontree_7926188525284 tree17;
        
            _PB27mT__decisiontree_7926188525509 tree18;
        
            _r7UKg1__decisiontree_7926188525536 tree19;
        
            _jHwYBv__decisiontree_7926188525242 tree20;
        
};
    

    /**
     * Chain class
     * Chain(blocks=[Scale(method=minmax, offsets=[3. 2. 2.], scales=[42. 45. 47.]), Monotonic(columns=['r', 'g', 'b'] functions=['square', 'cube', 'sqrt', 'inverse', 'log', 'exp']), Select(columns=['b', 'sqrt(r)', 'square(g)', 'sqrt(g)', 'exp(b)']), RandomForestRegressor(max_depth=10, min_samples_leaf=5, n_estimators=20)])
     */
     class DistanceChain {
        public:
            Input input;
            Output output;

            /**
             * Transform array input
             */
            bool operator()(float *inputs) {
                return operator()(inputs[0], inputs[1], inputs[2]);
            }

            /**
             * Transform const array input
             */
            bool operator()(const float *inputs) {
                return operator()(inputs[0], inputs[1], inputs[2]);
            }

            /**
             * Transform variadic input
             */
            bool operator()(const float _S0Owru__r, const float _svXR0N__g, const float _kutfua__b) {
                // assign variables to input
                
                    input._S0Owru__r = _S0Owru__r;
                
                    input._svXR0N__g = _svXR0N__g;
                
                    input._kutfua__b = _kutfua__b;
                

                // run blocks
                
                    // Scale(method=minmax, offsets=[3. 2. 2.], scales=[42. 45. 47.])
                    block1(input, output);

                    if (!block1.isReady())
                        return false;
                
                    // Monotonic(columns=['r', 'g', 'b'] functions=['square', 'cube', 'sqrt', 'inverse', 'log', 'exp'])
                    block2(input, output);

                    if (!block2.isReady())
                        return false;
                
                    // Select(columns=['b', 'sqrt(r)', 'square(g)', 'sqrt(g)', 'exp(b)'])
                    block3(input, output);

                    if (!block3.isReady())
                        return false;
                
                    // RandomForestRegressor(max_depth=10, min_samples_leaf=5, n_estimators=20)
                    block4(input, output);

                    if (!block4.isReady())
                        return false;
                

                

                return true;
            }

        protected:
            
                // Scale(method=minmax, offsets=[3. 2. 2.], scales=[42. 45. 47.])
                _3dU7EM__scale_7926188646107 block1;
            
                // Monotonic(columns=['r', 'g', 'b'] functions=['square', 'cube', 'sqrt', 'inverse', 'log', 'exp'])
                _mHYBlH__monotonic_7926188645465 block2;
            
                // Select(columns=['b', 'sqrt(r)', 'square(g)', 'sqrt(g)', 'exp(b)'])
                _Ewv9Jb__select_7926188609865 block3;
            
                // RandomForestRegressor(max_depth=10, min_samples_leaf=5, n_estimators=20)
                _cCRnmp__randomforest_7926188609979 block4;
            
    };
}